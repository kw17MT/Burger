#include "stdafx.h"
#include "effect/Effect.h"
#include "Guzai.h"
#include "math.h"
#include "Kitchen.h"
#include "GuzaiOkiba.h"
#include "SkinModelRender.h"
#include "Player.h"
#include "PlayerGene.h"
#include "SoundSource.h"
#include "TrashCan.h"
#include "Meter.h"
#include "GameDirector.h"
#include "GuzaiManager.h"
#include <random>
#include <ctime>
#include <cstdlib>

#include "GuzaiScale.h"

namespace
{
	const Vector3 EGG_SCALE = { 0.7f,1.0f,0.7f };
	const Vector3 CUT_EFFECT_SCALE = { 100.0f,100.0f,100.0f };
	const int PLAYER_NONE = -1;
	const int PLAYER_ONE = 0;
	const int PLAYER_TWO = 1;
	const int PLAYER_ONE_CONTROLLER = 0;
	const int PLAYER_TWO_CONTROLLER = 1;
	const int NONE = 9;
	const int GUZAI_TYPE_MIN_NUM = 0;
	const int GUZAI_TYPE_MAX_NUM = 6;
	const int GUZAIOKIBA_MIN_NUM = 0;
	const int GUZAIOKIBA_MIDDLE_NUM = 4;
	const int GUZAIOKIBA_MAX_NUM = 8;
	const float MOVESPEED = 130.0f;
	const float ADJUST_SPEED_TO_FOLLOW_PLAYER = 90.0f;
	const float ADJUST_GRAB_HEIGHT = 80.0f;
	const float ADJUST_HEIGHT = 40.0f;
	const float ADJUST_HEIGHT_ON_KITCHEN = 100.0f;
	const float DISTANCE_BETWEEN_PLAYER_TO_GUZAI = 100.0f;
	const float SE_GRAB_VOLUME = 0.9f;
	const float SE_PUT_VOLUME = 1.0f;
	const float SE_VOLUME = 3.0f;
	const float SE_CUTTING_VOLUME = 0.8f;
	const float SE_TARGET_VOLUME = 0.2f;
	const float ANGLE_ADD_AMOUNT = 2.0f;
	const float ADJUST_METER_X_POS0 = 350.0f;
	const float ADJUST_METER_X_POS1 = 250.0f;
	const float ADJUST_METER_Y_POS = 300.0f;
	const float ADJUST_METER_Z_POS = 20.0f;
	const float METER_SHRINK_SPEED = 1.4f / 60.0f;
}

Guzai::~Guzai()
{
	DeleteGO(m_skinModelRender);

	if (m_soundFlag01 || m_soundFlag02) {
		DeleteGO(m_cookingSe);
		DeleteGO(m_meter);
	}
}

//キッチン上で別のモデルに差し替える用
void Guzai::ChangeModel(const int guzaiType)
{
	//ヘッダに定義してあるファイルパス集を使用して具材のモデルを変更
	m_skinModelRender->ChangeModel(m_changedFilePaths[guzaiType]);
	//モデルに新しいファイルパスを適用する。
	m_skinModelRender->SetNewModel();
}

bool Guzai::Start()
{
	//両プレイヤーの情報取得
	m_player00 = FindGO<Player>("player00");
	m_player01 = FindGO<Player>("player01");
	//両キッチンの情報取得
	m_kitchen00 = FindGO<Kitchen>("kitchen00");
	m_kitchen01 = FindGO<Kitchen>("kitchen01");
	//プレイヤー生成器の情報取得
	m_playerGene = FindGO<PlayerGene>("playerGene");
	//全具材置き場の情報取得
	m_guzaiOkiba = FindGO<GuzaiOkiba>("GuzaiOkiba");
	//両ゴミ箱の情報取得
	m_trashCan[0] = FindGO<TrashCan>("trashcan00");
	m_trashCan[1] = FindGO<TrashCan>("trashcan01");

	//具材のモデルを初期化
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//通常描画用モデルの初期化
	m_skinModelRender->InitForRecieveShadow("Assets/modelData/gu/cheese.tkm", nullptr, enModelUpAxisZ, m_position);
	//m_skinModelRender->Init("Assets/modelData/gu/cheese.tkm",nullptr, enModelUpAxisZ, m_position);
	//影生成用の初期化
	m_skinModelRender->InitForCastShadow("Assets/modelData/gu/cheese.tkm", nullptr, enModelUpAxisZ, m_position);
	//乱数を用いて出現させるモデルの決定
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<int> rand(GUZAI_TYPE_MIN_NUM, GUZAI_TYPE_MAX_NUM);

	m_typeNo = rand(mt);
	m_isTargeted = false;
	m_scale = Vector3::One;

	//ヘッダに定義してあるファイルパス集を使用して具材のモデルを変更
	m_skinModelRender->ChangeModel(m_normalFilePaths[m_typeNo]);
	//モデルに新しいファイルパスを適用する。
	m_skinModelRender->SetNewModel();

	//自身がトマトとオニオン以外の時、調理される必要はないため
	if (m_typeNo != enTomato && m_typeNo != enOnion) {
		//調理されたフラグをすでに立てておく。
		m_isCooked = true;
	}

	return true;
}

void Guzai::Grab()
{
	//どちらに持たれるか分からないため、両方のポジションが毎フレーム必要。
	Vector3 plPos00 = m_player00->GetPosition();
	Vector3 plPos01 = m_player01->GetPosition();
	
	//キッチンから具材を取るときの処理はキッチンにあり！

	//プレイヤー1の持つ処理
	//Aボタンを押したとき
	if (g_pad[PLAYER_ONE_CONTROLLER]->IsTrigger(enButtonA)) {
		//私（この具材）はプレイヤー１にロックオンされている。
		if (m_whichPlayerTargetMe == PLAYER_ONE) {
			//プレイヤー1は何も持っていない。私はターゲットされている（距離測定済）。自身はキッチン上にない。プレイヤー1はバーガー作成中ではない。
			//最後の引数は、キッチン上でハンバーガーを作るために一か所に集まっている最中に取れないようにするため。
			if (m_player00->GetPlayerState() == enNothing && m_isTargeted == true && m_isPutOnKitchen == false && m_kitchen00->GetIsPlayerCookingOnKitchen() == false) {
				//もたれた！
				m_isHad = true;
				//Player0は具材をもっている！
				m_player00->SetPlayerState(enHaveGuzai);
				//自分はどっちのプレイヤーに持たれたか
				m_whichPlayerGet = PLAYER_ONE;
				//音を鳴らす
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/poka01.wav", false);
				se->SetVolume(SE_GRAB_VOLUME);
				se->Play(false);
				//普通に流れている具材をとった時
				if (m_guzaiOkibaSet == false) {
					//素直に空の皿の数を1増やす
					GuzaiManager::GetInstance().AddEmptyDishNum();
				}
				//補充を開始するかどうか判断する。
				GuzaiManager::GetInstance().JudgeToOrderRefill();
				//それが具材置き場にあった時の処理
				AwayFromGuzaiOkiba();
			}
		}
	}
	//プレイヤー2の持つ処理
	if (g_pad[PLAYER_TWO_CONTROLLER]->IsTrigger(enButtonA)) {
		if (m_whichPlayerTargetMe == PLAYER_TWO) {
			if (m_player01->GetPlayerState() == enNothing && m_isTargeted == true && m_isPutOnKitchen == false && m_kitchen01->GetIsPlayerCookingOnKitchen() == false) {
				m_isHad = true;
				m_player01->SetPlayerState(enHaveGuzai);
				m_whichPlayerGet = PLAYER_TWO;
				//音を鳴らす
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/poka01.wav", false);
				se->SetVolume(SE_GRAB_VOLUME);
				se->Play(false);
				if (m_guzaiOkibaSet == false) {
					//空の皿の数を1増やす
					GuzaiManager::GetInstance().AddEmptyDishNum();
				}
				//補充を開始するかどうか判断する。
				GuzaiManager::GetInstance().JudgeToOrderRefill();
				AwayFromGuzaiOkiba();
			}
		}
	}

	//持たれていたら具材の位置をプレイヤーの前にする。
	if (m_isHad == true) {
		if (m_whichPlayerGet == PLAYER_ONE) {
			//具材の位置をプレイヤーの少し前にする。
			Vector3 pl00MSpeed = m_player00->GetNormalMoveSpeed();
			pl00MSpeed *= ADJUST_SPEED_TO_FOLLOW_PLAYER;
			plPos00 += pl00MSpeed;
			plPos00.y += ADJUST_GRAB_HEIGHT;
			SetPosition(plPos00);
			//持っている最中、その具材を拡大表示したくないため。
			m_isTargeted = false;
		}
		if (m_whichPlayerGet == PLAYER_TWO) {
			Vector3 pl01MSpeed = m_player01->GetNormalMoveSpeed();
			pl01MSpeed *= ADJUST_SPEED_TO_FOLLOW_PLAYER;
			plPos01 += pl01MSpeed;
			plPos01.y += ADJUST_GRAB_HEIGHT;
			SetPosition(plPos01);
			m_isTargeted = false;
		}
	}
}

void Guzai::Put()
{
	//ここはキッチンに置く処理
	//Aボタンを押してその具材が調理されているとき（する必要がない時）
	if (g_pad[PLAYER_ONE_CONTROLLER]->IsTrigger(enButtonA) && m_isCooked == true && m_whichPlayerGet == PLAYER_ONE) {
		//自分は持たれている。距離は一定以内。一度キッチンに置かれていないか。←pl01->have = enNothingを回避するため必要
		if (m_isHad == true && m_kit2Pl00 < DISTANCE_BETWEEN_PLAYER_TO_GUZAI && m_returnedFromKitchen == false) {
			//具材の種類に応じて、キッチン上専用のモデルに切り替える。
			ChangeModel(m_typeNo);
			//卵だった時少し小さく
			if (m_typeNo == enEgg) {
				m_scale = { EGG_SCALE };
			}
			//キッチンに置いた具材の種類をプレイヤー側に保存
			m_player00->SetPlayerStackedGuzais(m_kitchen00->GetStackNum(), m_typeNo);
			//プレイヤーは何も持っていない
			m_player00->SetPlayerState(enNothing);
			//積んだ層数を1足す
			m_kitchen00->PlusStack();
			//この具材はキッチンに置かれている
			m_isPutOnKitchen = true;
			//自分は持たれていない
			m_isHad = false;
			//ターゲティングしていた具材を運んでいる最中は別の具材をターゲティングしたくないため、ここで初期化。
			m_isTargeted = false;
			//プレイヤーはターゲットしていないにする。
			m_player00->SetTarget(m_isTargeted);
			//キッチンのY座標を 積んだ具材数 分上げる。
			m_position = m_kitchen00->GetKitchenPos();
			if (m_kitchen00->GetStackNum() >= 1)
			{
				m_position.y += (m_kitchen00->GetStackNum()+1) * ADJUST_HEIGHT;
			}
			else
			{
				m_position.y += (m_kitchen00->GetStackNum()+1) * ADJUST_HEIGHT_ON_KITCHEN;
			}

			m_skinModelRender->SetPosition(m_position);

			//音を鳴らす
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/poka02.wav", false);
			se->SetVolume(SE_PUT_VOLUME);
			se->Play(false);

			//キッチンにあるスタックした具材の一覧にこの具材を追加。
			m_kitchen00->RegistStackedGuzai(this);

			//同じフレームで取れないようにする。
			m_kitchen00->ChangeGrabState(false);
		}
	}
	if (g_pad[PLAYER_TWO_CONTROLLER]->IsTrigger(enButtonA) && m_isCooked == true && m_whichPlayerGet == PLAYER_TWO) {
		if (m_isHad == true && m_kit2Pl01 < DISTANCE_BETWEEN_PLAYER_TO_GUZAI && m_returnedFromKitchen == false) {
			ChangeModel(m_typeNo);
			if (m_typeNo == enEgg) {
				m_scale = { EGG_SCALE };
			}
			m_player01->SetPlayerStackedGuzais(m_kitchen01->GetStackNum(), m_typeNo);
			m_player01->SetPlayerState(enNothing);
			m_kitchen01->PlusStack();
			m_isPutOnKitchen = true;
			m_isHad = false;
			m_isTargeted = false;
			m_player01->SetTarget(m_isTargeted);
			m_position = m_kitchen01->GetKitchenPos();
			if (m_kitchen01->GetStackNum() >= 1)
			{
				m_position.y += (m_kitchen01->GetStackNum()+1) * ADJUST_HEIGHT;
			}
			else
			{
				m_position.y += (m_kitchen01->GetStackNum()+1) * ADJUST_HEIGHT_ON_KITCHEN;
			}
			m_skinModelRender->SetPosition(m_position);

			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/poka02.wav", false);
			se->SetVolume(SE_PUT_VOLUME);
			se->Play(false);

			m_kitchen01->RegistStackedGuzai(this);
			m_kitchen01->ChangeGrabState(false);
		}
	}
}

void Guzai::Targeting()
{
		//具材との距離が一定以下。プレイヤーは何もターゲットしていない。私は誰にもターゲットされていない。キッチンに置かれていない。
		if (m_guzai2Pl00 < m_targetRangeNear && m_player00->GetTargetState() == false && !m_isTargeted && m_isPutOnKitchen == false) {
			//私をターゲットしているのはプレイヤー１だ。
			m_whichPlayerTargetMe = PLAYER_ONE;
			//私はターゲットされた。
			m_isTargeted = true;
			//プレイヤー１が具材はターゲットしている。
			m_player00->SetTarget(m_isTargeted);

			//音を鳴らす
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/select07.wav", false);
			se->SetVolume(SE_TARGET_VOLUME);
			se->Play(false);
		}
		if (m_guzai2Pl01 < m_targetRangeNear && m_player01->GetTargetState() == false && !m_isTargeted && m_isPutOnKitchen == false) {
			m_whichPlayerTargetMe = PLAYER_TWO;
			m_isTargeted = true;
			m_player01->SetTarget(m_isTargeted);

			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/select07.wav", false);
			se->SetVolume(SE_TARGET_VOLUME);
			se->Play(false);
		}

		//プレイヤー１が離れた。プレイヤー１は何かをターゲットしている。私はターゲットされている。
		if (m_guzai2Pl00 >= m_targetRangeFar && m_player00->GetTargetState() == true && m_isTargeted == true) {
			//プレイヤー１にターゲットされているとき
			if (m_whichPlayerTargetMe == PLAYER_ONE) {
				//ある程度ターゲットの切り替えに遅延を起こしたいため、それ用の変数
				m_decrementTime--;
				if (m_decrementTime <= 0) {
					//私はターゲットから逃れた
					m_isTargeted = false;
					//プレイヤー１は何もターゲットしていない
					m_player00->SetTarget(m_isTargeted);
					//次の遅延用に遅延時間を元に戻す
					m_decrementTime = m_holdTime;
					//私は誰にもターゲットされていない。
					m_whichPlayerTargetMe = PLAYER_NONE;
				}
			}
		}
		if (m_guzai2Pl01 >= m_targetRangeFar && m_player01->GetTargetState() == true && m_isTargeted == true) {
			if (m_whichPlayerTargetMe == PLAYER_TWO) {
				m_decrementTime--;
				if (m_decrementTime <= 0) {
					m_isTargeted = false;
					m_player01->SetTarget(m_isTargeted);
					m_decrementTime = m_holdTime;
					m_whichPlayerTargetMe = PLAYER_NONE;
				}
			}
		}
}
void Guzai::SetGuzaiOkiba()
{
	//プレイヤー１はAボタンを押した。私は持たれている。プレイヤー１に持たれている。
	if (g_pad[PLAYER_ONE_CONTROLLER]->IsTrigger(enButtonA) && m_isHad == true && m_whichPlayerGet == PLAYER_ONE) {
		//1P側の具材置き場の番号は4〜7なので、その範囲で調べる。
		for (int i = GUZAIOKIBA_MIDDLE_NUM; i < GUZAIOKIBA_MAX_NUM; i++) {
			//具材置き場にセット可能かどうか確認する。
			if (m_guzaiOkiba->FindKitchenSet(i) == true && m_guzaiOkiba->FindGuzaiSet(i) == false && m_guzaiOkibaSet == false) {
				//セット可能ならば具材置き場にセットされたことを伝え、自身の座標をセットされた具材置き場にする。
				m_guzaiOkiba->GuzaiSet(i, true);
				//座標を具材置き場の上にセットする。
				m_position = m_guzaiOkiba->GetKitchenPos(i);
				if (m_isCooked == true) {
					m_position.y += ADJUST_HEIGHT;
				}
				//具材置き場にセットされた。
				m_guzaiOkibaSet = true;
				//どこのキッチンにセットされたか。
				m_setKitchenNum = i;
				//音を鳴らす
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/poka02.wav", false);
				se->SetVolume(SE_PUT_VOLUME);
				se->Play(false);
				//プレイヤーが何も持っていない状態にする。
				m_player00->SetPlayerState(enNothing);
				//私はターゲットされていない。
				m_isTargeted = false;
				//プレイヤー１は何もターゲットしていない。
				m_player00->SetTarget(m_isTargeted);
				//遅延時間を元に戻す
				m_decrementTime = m_holdTime;
				//私は誰にも持たれていない。
				m_isHad = false;
			}
		}
	}
	//2P側の処理 1Pとほぼ同じ
	if (g_pad[PLAYER_TWO_CONTROLLER]->IsTrigger(enButtonA) && m_isHad == true && m_whichPlayerGet == PLAYER_TWO) {
		//2P側の具材置き場の番号は0〜4なので、その範囲で調べる。
		for (int i = GUZAIOKIBA_MIN_NUM; i < GUZAIOKIBA_MIDDLE_NUM; i++) {
			if (m_guzaiOkiba->FindKitchenSet(i) == true && m_guzaiOkiba->FindGuzaiSet(i) == false && m_guzaiOkibaSet == false) {
				m_guzaiOkiba->GuzaiSet(i, true);
				m_position = m_guzaiOkiba->GetKitchenPos(i);
				if (m_isCooked == true) {
					m_position.y += ADJUST_HEIGHT;
				}
				m_guzaiOkibaSet = true;
				m_setKitchenNum = i;
				//音を鳴らす
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/poka02.wav", false);
				se->SetVolume(SE_PUT_VOLUME);
				se->Play(false);
				m_player01->SetPlayerState(enNothing);
				m_isTargeted = false;
				m_player01->SetTarget(m_isTargeted);
				m_decrementTime = m_holdTime;
				m_isHad = false;
			}
		}
	}
}

void Guzai::AwayFromGuzaiOkiba()
{
	//具材置き場にセットされていたら…
	if (m_guzaiOkibaSet == true) {
		//セットされていた具材置き場に取り出されたことを伝える。
		m_guzaiOkiba->GuzaiSet(m_setKitchenNum, false);
		//そして自身が取り出されたことにする。
		m_guzaiOkibaSet = false;
		m_setKitchenNum = NONE;
		//取った瞬間に置くことを防ぐため。次のフレームからとれるような処理にしている。
		m_canPutOnGuzaiOkiba = false;
	}
}

void Guzai::Cooking()
{
	//自身が具材置き場にセットされていて、調理されておらず、ターゲットされているとき。
	if (m_guzaiOkibaSet == true && m_isCooked == false && m_isTargeted) {
		//1P側の処理
		//1P側のBボタンが押されていて自身のセット場所が1P側だった場合…
		if (g_pad[PLAYER_ONE_CONTROLLER]->IsPress(enButtonB) && m_setKitchenNum >= GUZAIOKIBA_MIDDLE_NUM && m_player00->GetPlayerState() <= enNothing) {
			//押している時間をインクリメント
			m_hold01++;
			m_player00->StopMove(true);
			m_player00->SetIsCooking(true);

			if (m_hold01 % 10 == 1 && m_hold01 < 59)
			{
				Effect cut;
				cut.Init(u"Assets/effect/cut2.efk");
				Vector3 pos = m_player00->GetPosition();
				pos.x -= 200.0f;
				pos.z += 70.0f;
				cut.SetPosition(pos);
				cut.SetScale({ 100.0f,100.0f,100.0f });
				cut.Play();
				cut.Update();
			}
			

			//音が出ていなかったら。
			if (m_soundFlag01 == false) {
				//調理の進み具合を示すメーター
				m_meter = NewGO<Meter>(0);
				Vector3 pos = m_position;
				pos.x -= ADJUST_METER_X_POS0;
				pos.y += ADJUST_METER_Y_POS;
				pos.z += ADJUST_METER_Z_POS;
				m_meter->SetPosition(pos);
				//音を鳴らす
				m_cookingSe = NewGO<CSoundSource>(0);
				m_cookingSe->Init(L"Assets/sound/cutting_a_onion_speedy.wav", false);
				m_cookingSe->SetVolume(SE_CUTTING_VOLUME);
				m_cookingSe->Play(true);
				m_soundFlag01 = true;
			}
			//メーターを少しずつへらす
			Vector3 Scale = m_meter->GetScale();
			Scale.x -= METER_SHRINK_SPEED;
			m_meter->SetScale(Scale);
			//調理完了時間まで押されたら…
			if (m_hold01 > m_cookingTime) {
				//調理後のモデルに変更。
				ChangeModel(m_typeNo);
				m_isCooked = true;
				m_position.y += ADJUST_HEIGHT;
				m_isTargeted = false;
				m_player00->SetTarget(m_isTargeted);
				m_whichPlayerTargetMe = PLAYER_NONE;
				//音が出ていたら。
				if (m_soundFlag01 == true) {
					DeleteGO(m_meter);
					//音を消す。
					DeleteGO(m_cookingSe);
					m_soundFlag01 = false;
				}
				//動けるようにする。
				m_player00->StopMove(false);
			}
		}
		else {
			//ボタンを離したらタイマーは0に戻る。
			m_hold01 = 0;
			//動けるようにする。
			m_player00->StopMove(false);
			m_player00->SetIsCooking(false);
			//音が出ていたら。
			if (m_soundFlag01 == true) {
				DeleteGO(m_meter);
				//音を消す。
				DeleteGO(m_cookingSe);
				m_soundFlag01 = false;
			}
		}

		//2P側の処理
		if (g_pad[PLAYER_TWO_CONTROLLER]->IsPress(enButtonB) && m_setKitchenNum < GUZAIOKIBA_MIDDLE_NUM && m_player01->GetPlayerState() <= enNothing) {
			m_hold02++;
			m_player01->StopMove(true);
			m_player01->SetIsCooking(true);

			if (m_hold02 % 10 == 1 && m_hold02 < 59)
			{
				//カットエフェクトの生成
				Effect cut;
				cut.Init(u"Assets/effect/cut2.efk");
				Vector3 pos = m_player01->GetPosition();
				Quaternion rot;
				rot.SetRotationDegY(180);
				pos.x += 200.0f;
				pos.z += 70.0f;
				cut.SetPosition(pos);
				cut.SetRotation(rot);
				cut.SetScale(CUT_EFFECT_SCALE);
				cut.Play();
				cut.Update();
			}

			////音が出ていなかったら。
			if (m_soundFlag02 == false) {
				m_meter = NewGO<Meter>(0);
				Vector3 pos = m_position;
				pos.x += ADJUST_METER_X_POS1;
				pos.y += ADJUST_METER_Y_POS;
				pos.z += ADJUST_METER_Z_POS;
				m_meter->SetPosition(pos);
				//音を鳴らす
				m_cookingSe = NewGO<CSoundSource>(0);
				m_cookingSe->Init(L"Assets/sound/cutting_a_onion_speedy.wav", false);
				m_cookingSe->SetVolume(SE_CUTTING_VOLUME);
				m_cookingSe->Play(true);
				m_soundFlag02 = true;
			}
			Vector3 Scale = m_meter->GetScale();
			Scale.x -= METER_SHRINK_SPEED;
			m_meter->SetScale(Scale);
			if (m_hold02 > m_cookingTime) {
				
				ChangeModel(m_typeNo);
				m_isCooked = true;
				m_position.y += ADJUST_HEIGHT;
				m_isTargeted = false;
				m_player01->SetTarget(m_isTargeted);
				m_whichPlayerTargetMe = PLAYER_NONE;
				//音が出ていたら。
				if (m_soundFlag02 == true) {
					//音を消す。
					DeleteGO(m_cookingSe);
					m_soundFlag02 = false;
					DeleteGO(m_meter);
				}
				m_player01->StopMove(false);
			}
		}
		else {
			m_player01->StopMove(false);
			m_player01->SetIsCooking(false);
			m_hold02 = 0;
			//音が出ていたら。
			if (m_soundFlag02 == true) {
				//音を消す。
				DeleteGO(m_meter);
				DeleteGO(m_cookingSe);
				m_soundFlag02 = false;
			}
		}
	}
}

void Guzai::SetOnTrashCan() {
	//プレイヤー１に持たれている
	if (m_whichPlayerGet == PLAYER_ONE) {
		//プレイヤー１がAボタンを押した
		if (g_pad[PLAYER_ONE_CONTROLLER]->IsTrigger(enButtonA)			//Aボタンを押して
			&& m_isHad == true											//この具材が持たれていて
			&& m_trashCan[0]->GetCanTrash()) {							//ゴミ箱は捨てる用意ができているか（距離的に）
			m_isSetOnTrashCan = true;									//ゴミ箱で捨てる準備
		}
		if (m_isSetOnTrashCan == true) {
			DeleteGO(this);
			//音を鳴らす
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/dumping.wav", false);
			se->SetVolume(SE_PUT_VOLUME);
			se->Play(false);
			m_player00->SetPlayerState(enNothing);
			m_isTargeted = false;
			m_player00->SetTarget(m_isTargeted);
			//ゴミ箱のリアクションをONにする
			m_trashCan[0]->ChangeMovingState(true);
		}
	}
	if (m_whichPlayerGet == PLAYER_TWO) {
		if (g_pad[PLAYER_TWO_CONTROLLER]->IsTrigger(enButtonA)
			&& m_isHad == true
			&& m_trashCan[1]->GetCanTrash()) {
			m_isSetOnTrashCan = true;
		}
		if (m_isSetOnTrashCan == true) {
			DeleteGO(this);
			//音を鳴らす
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/dumping.wav", false);
			se->SetVolume(SE_PUT_VOLUME);
			se->Play(false);
			m_player01->SetPlayerState(enNothing);
			m_isTargeted = false;
			m_player01->SetTarget(m_isTargeted);
			m_trashCan[PLAYER_TWO]->ChangeMovingState(true);
		}
	}
}

void Guzai::Rotation()
{
	//キッチンにセットされているとき。
	if (m_isPutOnKitchen == true) {
		//回転処理
		m_angle += ANGLE_ADD_AMOUNT;
		if (m_angle > 360.0f) {
			m_angle = 0.0f;
		}
		m_rotation.SetRotationDeg(Vector3::AxisY, m_angle);

	}
	//キッチンにセットされていないとき。
	else
	{
		//プレイヤーが具材を持ったときの具材の追従回転。
		if (m_isHad == true) {
			if (m_whichPlayerGet == PLAYER_ONE) {
				//プレイヤーが向いている方向に回転するので、プレイヤーの移動速度を参照する。
				Vector3 pl01MSpeed = m_player00->GetNormalMoveSpeed();
				m_angle = atan2(pl01MSpeed.x, pl01MSpeed.z);
				m_rotation.SetRotation(Vector3::AxisY, m_angle);
			}
			if (m_whichPlayerGet == PLAYER_TWO) {
				Vector3 pl02MSpeed = m_player01->GetNormalMoveSpeed();
				m_angle = atan2(pl02MSpeed.x, pl02MSpeed.z);
				m_rotation.SetRotation(Vector3::AxisY, m_angle);
			}
		}
		else {
			//プレイヤーが持っていないときは回転をリセット。
			m_rotation = Quaternion::Identity;
		}
	}
}

float Guzai::CalcDistance(Vector3 pos1, Vector3 pos2)
{
	//地点１と地点２の距離を測る。
	Vector3 distance = pos1 - pos2;
	return distance.Length();
}

void Guzai::IfReturnedFromKitchen()
{
	//キッチンに置かれて戻ってきたら具材の状態を更新。
	if (m_returnedFromKitchen) {
		//私は持たれている
		if (m_isHad == true) {
			//プレイヤー１にもたれている
			if (m_whichPlayerGet == PLAYER_ONE) {
				//具材の位置をプレイヤーの少し前にする。
				Vector3 pl00MSpeed = m_player00->GetNormalMoveSpeed();
				Vector3 plPos00 = m_player00->GetPosition();
				pl00MSpeed *= ADJUST_SPEED_TO_FOLLOW_PLAYER;
				plPos00 += pl00MSpeed;
				SetPosition(plPos00);
				//音を鳴らす
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/putting_a_book2.wav", false);
				se->SetVolume(SE_VOLUME);
				se->Play(false);
			}
			if (m_whichPlayerGet == PLAYER_TWO) {
				Vector3 pl01MSpeed = m_player01->GetNormalMoveSpeed();
				Vector3 plPos01 = m_player01->GetPosition();
				pl01MSpeed *= ADJUST_SPEED_TO_FOLLOW_PLAYER;
				plPos01 += pl01MSpeed;
				SetPosition(plPos01);
				//音を鳴らす
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/putting_a_book2.wav", false);
				se->SetVolume(SE_VOLUME);
				se->Play(false);
			}
		}
		m_returnedFromKitchen = false;
	}
	//モデルの回転状況を更新する。
}

void Guzai::Update()
{
	//１フレームにかかる時間（秒）を取得する。
	float gameTime = GameTime().GetFrameDeltaTime();

	//プレイヤー生成中はUpdate関数をスルー
	if (m_playerGene->GetPlayerGeneState() == true) {
		return;
	}
	//ゲームが終了したら、自身を消す。
	if (GameDirector::GetInstance().GetGameScene() == enGameEnd) {
		DeleteGO(this);
	}

	Vector3 plPos00 = m_player00->GetPosition();
	Vector3 plPos01 = m_player01->GetPosition();
	Vector3 kitchen00Pos = m_kitchen00->GetKitchenPos();
	Vector3 kitchen01Pos = m_kitchen01->GetKitchenPos();

	//具材からプレイヤーまでの距離
	m_guzai2Pl00 = CalcDistance(m_position, plPos00);
	//キッチンからプレイヤーの距離
	m_kit2Pl00 = CalcDistance(kitchen00Pos, plPos00);
	//具材からプレイヤーへの距離
	m_guzai2Pl01 = CalcDistance(m_position, plPos01);
	//キッチンからプレイヤーへの距離
	m_kit2Pl01 = CalcDistance(kitchen01Pos, plPos01);

	//プレイヤーにターゲットされる処理。
	Targeting();

	//置く処理より先にキッチンから取られる状態に設定しておく。
	//GrabAndPut関数で、具材をキッチンに置いたフレームはキッチンから具材をとれないようにしている。
	m_kitchen00->ChangeGrabState(true);
	m_kitchen01->ChangeGrabState(true);

	//具材が取られる処理。
	Grab();

	//置かれる処理
	Put();

	//具材置き場に具材を置く処理
	if (m_canPutOnGuzaiOkiba) {
		SetGuzaiOkiba();
	}
	//上の関数で個の変数をFALSEにしているが、次フレームからはとれるようにしたいためすぐにTRUEに。
	m_canPutOnGuzaiOkiba = true;

	//加工すべき具材を加工する。
	Cooking();

	//ゴミ箱にものを捨てる処理
	SetOnTrashCan();

	//具材の回転処理。キッチン上ではその場で回転、持たれていたらプレイヤーの正面に来るように
	Rotation();

	//キッチンからプレイヤーの手に来た時の処理
	IfReturnedFromKitchen();
	
	//モデルの回転を更新
	m_skinModelRender->SetRotation(m_rotation);

	//具材置き場に置かれているときの位置調整
	if (m_guzaiOkibaSet == true) {
		Vector3 SetPos = m_position;
		SetPos.y += ADJUST_HEIGHT;
		m_skinModelRender->SetPosition(SetPos);
	}
	//置かれていなければ
	else {
		m_skinModelRender->SetPosition(m_position);
	}
	
	//ターゲットされているかどうかの状況に応じた拡大率の更新
	m_scale = GuzaiScale::ChangeScaleDependOnTargetedState(m_isTargeted, m_typeNo, m_scale);
	m_skinModelRender->SetScale(m_scale);
}