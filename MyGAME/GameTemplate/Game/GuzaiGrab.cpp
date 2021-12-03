#include "stdafx.h"
#include "GuzaiGrab.h"
#include "Player.h"
#include "SoundSource.h"
#include "GuzaiManager.h"



//void GuzaiGrab::Grab(
//	const int playerNumber, 
//	Vector3 playerPos[], 
//	int& playerState, 
//	bool& isTargeted, 
//	bool& isPutOnKitchen, 
//	bool& isPlayerCooking, 
//	int& whichPlayerGet, 
//	int& isHad)
//{
//	//どちらに持たれるか分からないため、両方のポジションが毎フレーム必要。
//	Vector3 plPos00 = playerPos[0];
//	Vector3 plPos01 = playerPos[1];
//	
//	//キッチンから具材を取るときの処理はキッチンにあり！
//
//	//プレイヤー1の持つ処理
//	//Aボタンを押したとき
//	if (g_pad[playerNumber]->IsTrigger(enButtonA)) {
//		//私（この具材）はプレイヤー１にロックオンされている。
//		if (whichPlayerGet == 0) {
//			//プレイヤー1は何も持っていない。私はターゲットされている（距離測定済）。自身はキッチン上にない。プレイヤー1はバーガー作成中ではない。
//			//最後の引数は、キッチン上でハンバーガーを作るために一か所に集まっている最中に取れないようにするため。
//			if (playerState == 0 && isTargeted == true && isPutOnKitchen == false && isPlayerCooking/*m_kitchen00->GetIsPlayerCookingOnKitchen()*/ == false) {
//				//もたれた！
//				isHad = true;
//				//Player0は具材をもっている！
//				m_player00->SetPlayerState(enHaveGuzai);
//				//自分はどっちのプレイヤーに持たれたか
//				whichPlayerGet = 0;
//				//音を鳴らす
//				CSoundSource* se = NewGO<CSoundSource>(0);
//				se->Init(L"Assets/sound/poka01.wav", false);
//				se->SetVolume(0.8f);
//				se->Play(false);
//				//普通に流れている具材をとった時
//				if (m_guzaiOkibaSet == false) {
//					//素直に空の皿の数を1増やす
//					GuzaiManager::GetInstance().AddEmptyDishNum();
//				}
//				//補充を開始するかどうか判断する。
//				GuzaiManager::GetInstance().JudgeToOrderRefill();
//				//それが具材置き場にあった時の処理
//				AwayFromGuzaiOkiba();
//			}
//		}
//	}
//	//プレイヤー2の持つ処理
//	if (g_pad[PLAYER_TWO_CONTROLLER]->IsTrigger(enButtonA)) {
//		if (m_whichPlayerTargetMe == PLAYER_TWO) {
//			if (m_player01->GetPlayerState() == enNothing && m_isTargeted == true && m_isPutOnKitchen == false && m_kitchen01->GetIsPlayerCookingOnKitchen() == false) {
//				m_isHad = true;
//				m_player01->SetPlayerState(enHaveGuzai);
//				m_whichPlayerGet = PLAYER_TWO;
//				//音を鳴らす
//				CSoundSource* se = NewGO<CSoundSource>(0);
//				se->Init(L"Assets/sound/poka01.wav", false);
//				se->SetVolume(SE_GRAB_VOLUME);
//				se->Play(false);
//				if (m_guzaiOkibaSet == false) {
//					//空の皿の数を1増やす
//					GuzaiManager::GetInstance().AddEmptyDishNum();
//				}
//				//補充を開始するかどうか判断する。
//				GuzaiManager::GetInstance().JudgeToOrderRefill();
//				AwayFromGuzaiOkiba();
//			}
//		}
//	}
//
//	//持たれていたら具材の位置をプレイヤーの前にする。
//	if (m_isHad == true) {
//		if (m_whichPlayerGet == PLAYER_ONE) {
//			//具材の位置をプレイヤーの少し前にする。
//			Vector3 pl00MSpeed = m_player00->GetNormalMoveSpeed();
//			pl00MSpeed *= AJUST_SPEED_TO_FOLLOW_PLAYER;
//			plPos00 += pl00MSpeed;
//			plPos00.y += AJUST_HEIGHT;
//			SetPosition(plPos00);
//			//持っている最中、その具材を拡大表示したくないため。
//			m_isTargeted = false;
//		}
//		if (m_whichPlayerGet == PLAYER_TWO) {
//			Vector3 pl01MSpeed = m_player01->GetNormalMoveSpeed();
//			pl01MSpeed *= AJUST_SPEED_TO_FOLLOW_PLAYER;
//			plPos01 += pl01MSpeed;
//			plPos01.y += AJUST_HEIGHT;
//			SetPosition(plPos01);
//			m_isTargeted = false;
//		}
//	}
//}