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
//	//�ǂ���Ɏ�����邩������Ȃ����߁A�����̃|�W�V���������t���[���K�v�B
//	Vector3 plPos00 = playerPos[0];
//	Vector3 plPos01 = playerPos[1];
//	
//	//�L�b�`�������ނ����Ƃ��̏����̓L�b�`���ɂ���I
//
//	//�v���C���[1�̎�����
//	//A�{�^�����������Ƃ�
//	if (g_pad[playerNumber]->IsTrigger(enButtonA)) {
//		//���i���̋�ށj�̓v���C���[�P�Ƀ��b�N�I������Ă���B
//		if (whichPlayerGet == 0) {
//			//�v���C���[1�͉��������Ă��Ȃ��B���̓^�[�Q�b�g����Ă���i��������ρj�B���g�̓L�b�`����ɂȂ��B�v���C���[1�̓o�[�K�[�쐬���ł͂Ȃ��B
//			//�Ō�̈����́A�L�b�`����Ńn���o�[�K�[����邽�߂Ɉꂩ���ɏW�܂��Ă���Œ��Ɏ��Ȃ��悤�ɂ��邽�߁B
//			if (playerState == 0 && isTargeted == true && isPutOnKitchen == false && isPlayerCooking/*m_kitchen00->GetIsPlayerCookingOnKitchen()*/ == false) {
//				//�����ꂽ�I
//				isHad = true;
//				//Player0�͋�ނ������Ă���I
//				m_player00->SetPlayerState(enHaveGuzai);
//				//�����͂ǂ����̃v���C���[�Ɏ����ꂽ��
//				whichPlayerGet = 0;
//				//����炷
//				CSoundSource* se = NewGO<CSoundSource>(0);
//				se->Init(L"Assets/sound/poka01.wav", false);
//				se->SetVolume(0.8f);
//				se->Play(false);
//				//���ʂɗ���Ă����ނ��Ƃ�����
//				if (m_guzaiOkibaSet == false) {
//					//�f���ɋ�̎M�̐���1���₷
//					GuzaiManager::GetInstance().AddEmptyDishNum();
//				}
//				//��[���J�n���邩�ǂ������f����B
//				GuzaiManager::GetInstance().JudgeToOrderRefill();
//				//���ꂪ��ޒu����ɂ��������̏���
//				AwayFromGuzaiOkiba();
//			}
//		}
//	}
//	//�v���C���[2�̎�����
//	if (g_pad[PLAYER_TWO_CONTROLLER]->IsTrigger(enButtonA)) {
//		if (m_whichPlayerTargetMe == PLAYER_TWO) {
//			if (m_player01->GetPlayerState() == enNothing && m_isTargeted == true && m_isPutOnKitchen == false && m_kitchen01->GetIsPlayerCookingOnKitchen() == false) {
//				m_isHad = true;
//				m_player01->SetPlayerState(enHaveGuzai);
//				m_whichPlayerGet = PLAYER_TWO;
//				//����炷
//				CSoundSource* se = NewGO<CSoundSource>(0);
//				se->Init(L"Assets/sound/poka01.wav", false);
//				se->SetVolume(SE_GRAB_VOLUME);
//				se->Play(false);
//				if (m_guzaiOkibaSet == false) {
//					//��̎M�̐���1���₷
//					GuzaiManager::GetInstance().AddEmptyDishNum();
//				}
//				//��[���J�n���邩�ǂ������f����B
//				GuzaiManager::GetInstance().JudgeToOrderRefill();
//				AwayFromGuzaiOkiba();
//			}
//		}
//	}
//
//	//������Ă������ނ̈ʒu���v���C���[�̑O�ɂ���B
//	if (m_isHad == true) {
//		if (m_whichPlayerGet == PLAYER_ONE) {
//			//��ނ̈ʒu���v���C���[�̏����O�ɂ���B
//			Vector3 pl00MSpeed = m_player00->GetNormalMoveSpeed();
//			pl00MSpeed *= AJUST_SPEED_TO_FOLLOW_PLAYER;
//			plPos00 += pl00MSpeed;
//			plPos00.y += AJUST_HEIGHT;
//			SetPosition(plPos00);
//			//�����Ă���Œ��A���̋�ނ��g��\���������Ȃ����߁B
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