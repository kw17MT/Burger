#include "stdafx.h"
#include "Player.h"
#include "Guzai.h"
#include "FontRender.h"
#include "PathFactory.h"
#include "GameDirector.h"
#include "SkinModelRender.h"
#include "Kitchen.h"
#include "Emotion.h"
#include "EmotionSmile.h"
#include "EmotionCry.h"
#include "EmotionUm.h"

namespace
{
	const Vector3 EFFECT_SCALE = { 10.0f,10.0f,10.0f };
	const Vector3 FRONT_DIRECTION = { 0.0f,0.0f,1.0f };
	const Vector3 RIGHT_DIRECTION = { 1.0f,0.0f,0.0f };

	const int KITCHEN_NAME_SIZE = 10;
	const int PLAYER_NUMBER_ONE = 0;
	const int PLAYER_NUMBER_TWO = 1;
	const int MAX_NUM_TO_STACK_GUZAI = 10;
	const int STACK_EMPTY = 9;
	const int PLAYER_1_RESTRECTED_POS_X_MIN = 950;
	const int PLAYER_2_RESTRECTED_POS_X_MIN = -1250;
	const int PLAYER_1_RESTRECTED_POS_X_MAX = 1250;
	const int PLAYER_2_RESTRECTED_POS_X_MAX = -950;
	const int PLAYER_RESTRECTED_POS_Z_MIN = -530;
	const int PLAYER_RESTRECTED_POS_Z_MAX = 190;
	const int EFFECT_POP_RATE = 12;
	const int EFFECT_POP = 11;
	const int EFFECT_TIMER_MAX = 60;

	const float AJUST_PLAYER_SPEED = -10.0f;
	const Vector3 EMOTION_RIGHT = { -500.0f, 150.0f, 0.0f };		//右表示用の位置
	const Vector3 EMOTION_LEFT = { 500.0f, 150.0f, 0.0f };
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_effect);
	if (m_smile != nullptr)
	{
		DeleteGO(m_smile);
	}
	if (m_cry != nullptr)
	{
		DeleteGO(m_cry);
	}
	if (m_um != nullptr)
	{
		DeleteGO(m_um);
	}
	DeleteGO(m_emotion);
}

bool Player::Start()
{
	//モデルの描画
	m_skinModelRender = NewGO<SkinModelRender>(0);

	if (m_playerNo == PLAYER_NUMBER_ONE) {
		//通常描画用赤色シェフモデル
		m_skinModelRender->InitForRecieveShadow(
			"Assets/modelData/Chef/ChefRed/Chef01.tkm",
			"Assets/modelData/Chef/ChefRed/Chef_1.tks",
			enModelUpAxisZ,
			m_position
		);
		//影描画用
		m_skinModelRender->InitForCastShadow(
			"Assets/modelData/Chef/ChefRed/Chef01.tkm",
			"Assets/modelData/Chef/ChefRed/Chef_1.tks",
			enModelUpAxisZ,
			m_position
		);
	}
	else {
		//通常描画用青色シェフモデル
		m_skinModelRender->InitForRecieveShadow(
			"Assets/modelData/Chef/ChefBlue/chef.tkm",
			"Assets/modelData/Chef/ChefBlue/chef.tks",
			enModelUpAxisZ,
			m_position
		);
		//影描画用
		m_skinModelRender->InitForCastShadow(
			"Assets/modelData/Chef/ChefBlue/chef.tkm",
			"Assets/modelData/Chef/ChefBlue/chef.tks",
			enModelUpAxisZ,
			m_position
		);
	}

	//拡大率の調整
	m_skinModelRender->SetScale(m_scale);

	//念のため具材ナンバー配列のすべての要素を何もない状態に初期化
	SetGuzaiEmpty();

	//プレイヤー番号を用いて対応するオブジェクトを検索するための番号
	int endNo = m_playerNo;
	//string型に変えてcharに変換するための準備をする。
	std::string endNo_string = std::to_string(endNo);
	//不変箇所を定義
	char kitchenName[KITCHEN_NAME_SIZE] = "kitchen0";
	//末端番号だけを追加する
	strcat_s(kitchenName, endNo_string.c_str());
	//所定のキッチンを取得。
	Kitchen* kitchen = FindGO<Kitchen>(kitchenName);

	//エフェクトの初期化
	m_effect = NewGO<Effect>(0);
	m_effect->Init(u"Assets/effect/dust.efk");
	m_effect->SetScale(EFFECT_SCALE);

	return true;
}

void Player::SetGuzaiEmpty()
{
	for (int i = 0;i < MAX_NUM_TO_STACK_GUZAI;i++)
	{
		m_guzaiNo[i] = STACK_EMPTY;
	}
}

void Player::RestrictPos()
{
	//座標を用いてプレイヤーの移動範囲を管理する。
	if (m_playerNo == PLAYER_NUMBER_ONE) {
		if (m_position.x > PLAYER_1_RESTRECTED_POS_X_MAX) {
			m_position.x = PLAYER_1_RESTRECTED_POS_X_MAX;
		}
		if (m_position.x < PLAYER_1_RESTRECTED_POS_X_MIN) {
			m_position.x = PLAYER_1_RESTRECTED_POS_X_MIN;
		}
		if (m_position.z > PLAYER_RESTRECTED_POS_Z_MAX) {
			m_position.z = PLAYER_RESTRECTED_POS_Z_MAX;
		}
		if (m_position.z < PLAYER_RESTRECTED_POS_Z_MIN) {
			m_position.z = PLAYER_RESTRECTED_POS_Z_MIN;
		}
	}
	if (m_playerNo == PLAYER_NUMBER_TWO) {
		if (m_position.x > PLAYER_2_RESTRECTED_POS_X_MAX) {
			m_position.x = PLAYER_2_RESTRECTED_POS_X_MAX;
		}
		if (m_position.x < PLAYER_2_RESTRECTED_POS_X_MIN) {
			m_position.x = PLAYER_2_RESTRECTED_POS_X_MIN;
		}
		if (m_position.z > PLAYER_RESTRECTED_POS_Z_MAX) {
			m_position.z = PLAYER_RESTRECTED_POS_Z_MAX;
		}
		if (m_position.z < PLAYER_RESTRECTED_POS_Z_MIN) {
			m_position.z = PLAYER_RESTRECTED_POS_Z_MIN;
		}
	}
}

void Player::PlayerRotation()
{
	if (!m_moveStop)
	{
		//回転処理
		//自身の上と右を定義(見下ろしなので)
		Vector3 frontDirP1 = FRONT_DIRECTION;
		frontDirP1.Normalize();
		Vector3 rightDirP1 = RIGHT_DIRECTION;
		rightDirP1.Normalize();

		//回転軸の決定
		Vector3 AxisYP1;
		AxisYP1.Cross(frontDirP1, rightDirP1);

		//水平方向と奥行方向への入力を受け取り
		float LStickXP1 = g_pad[m_playerNo]->GetLStickXF();
		float LStickZP1 = g_pad[m_playerNo]->GetLStickYF() * -1.0f; //奥行方向の逆転を-1.0fを掛けて補正

		if (fabsf(LStickXP1) < 0.001f && fabsf(LStickZP1) < 0.001f) {
			//return; //returnすると以下の処理がすっ飛ばされてUpdateの最後にいってしまう。
		}
		else {
			//二つの入力値が成す角を求める(ラジアン角)
			m_angle = atan2(LStickXP1, LStickZP1);
			//縦軸まわりの回転を求める(ラジアン角を引数に渡すためSetRotation)
			m_rotation.SetRotation(AxisYP1, -m_angle);
		}
	}
}

void Player::RestrictMove()
{
	//プレイヤーを動かしたくないとき
	if (m_moveStop)
	{
		//移動速度をゼロに数する
		m_moveSpeed = Vector3::Zero;
	}
	//プレイヤーが動けるとき
	else
	{
		//コントローラの入力量によって移動速度を決定する。
		m_moveSpeed.x = g_pad[m_playerNo]->GetLStickXF() * AJUST_PLAYER_SPEED;
		m_moveSpeed.z = g_pad[m_playerNo]->GetLStickYF() * AJUST_PLAYER_SPEED;
	}

	m_position += m_moveSpeed;

	//プレイヤーが移動している限り移動速度を保存し続ける。
	if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f) {
		m_saveMoveSpeed = m_moveSpeed;
		m_saveMoveSpeed.Normalize();
	}
}

void Player::PopWalkingEffect()
{
	//エフェクト再生
	//移動中なら定期的に発生
	m_moveCounter++;
	if (m_moveSpeed.x != 0
		|| m_moveSpeed.z != 0 ) {
		if (m_moveCounter % EFFECT_POP_RATE == EFFECT_POP) {
			m_effect->SetPosition(m_position);
			m_effect->Play(0);
		}
	}

	if (m_moveCounter > EFFECT_TIMER_MAX) {
		m_moveCounter = 0;
	}
}

void Player::Update()
{
	//カウントダウン中でも、プレイヤーの初期位置は固定しておきたいため。
	m_skinModelRender->SetPosition(m_position);
	if (GetGameDirector().GetGameScene() == enResult
		&& m_emotion == nullptr)
	{
		m_emotion = NewGO<Emotion>(0);
		if (m_playerNo == 0)
		{
			m_emotion->SetPosition(EMOTION_LEFT);
			if (GetGameDirector().GetResult() == enPlayer1Win)
			{
				m_smile = NewGO<EmotionSmile>(0);
				m_smile->SetPosition(EMOTION_LEFT);
			}
			else if(GetGameDirector().GetResult() == enPlayer2Win)
			{
				m_cry = NewGO<EmotionCry>(0);
				m_cry->SetPosition(EMOTION_LEFT);
			}
			else
			{
				m_um = NewGO<EmotionUm>(0);
				m_um->SetPosition(EMOTION_LEFT);
			}
		}
		else
		{
			m_emotion->SetPosition(EMOTION_RIGHT);
			if (GetGameDirector().GetResult() == enPlayer2Win)
			{
				m_smile = NewGO<EmotionSmile>(0);
				m_smile->SetPosition(EMOTION_RIGHT);
			}
			else if(GetGameDirector().GetResult() == enPlayer1Win)
			{
				m_cry = NewGO<EmotionCry>(0);
				m_cry->SetPosition(EMOTION_RIGHT);
			}
			else
			{
				m_um = NewGO<EmotionUm>(0);
				m_um->SetPosition(EMOTION_RIGHT);
			}
		}
	}


	//ゲームプレイ中じゃなかったら。
	if (!GetGameDirector().GetIsGamePlay())
	{
		//処理しない。
		return;
	}

	//プレイヤーの回転処理
	PlayerRotation();

	//移動を制限
	RestrictMove();

	//移動範囲を制限
	RestrictPos();

	//歩いたときにエフェクトを出す
	PopWalkingEffect();

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);
	m_effect->Update();
}