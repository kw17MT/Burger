#include "stdafx.h"
#include "GuzaiGrab.h"
#include "Player.h"
#include "SoundSource.h"
#include "GuzaiManager.h"

//void GuzaiGrab::Grab(int playerNumber, Vector3 playerPos, int& playerState, bool& isTargeted, bool& isPutOnKitchen, bool& isPlayerCooking, int& whichPlayerGet, int& isHad)
//{
//	if (g_pad[playerNumber]->IsTrigger(enButtonA)) {
//		//���i���̋�ށj�̓v���C���[�P�Ƀ��b�N�I������Ă���B
//			//�v���C���[1�͉��������Ă��Ȃ��B���̓^�[�Q�b�g����Ă���i��������ρj�B���g�̓L�b�`����ɂȂ��B�v���C���[1�̓o�[�K�[�쐬���ł͂Ȃ��B
//			//�Ō�̈����́A�L�b�`����Ńn���o�[�K�[����邽�߂Ɉꂩ���ɏW�܂��Ă���Œ��Ɏ��Ȃ��悤�ɂ��邽�߁B
//			if (playerState == 0 && isTargeted == true && isPutOnKitchen == false && isPlayerCooking == false) {
//				//�����ꂽ�I
//				isHad = true;
//				//Player0�͋�ނ������Ă���I
//				//m_player00->SetPlayerState(enHaveGuzai);
//				playerState = 1;
//				//�����͂ǂ����̃v���C���[�Ɏ����ꂽ��
//				whichPlayerGet = playerNumber;
//				//����炷
//				CSoundSource* se = NewGO<CSoundSource>(0);
//				se->Init(L"Assets/sound/poka01.wav", false);
//				se->SetVolume(1.0f);
//				se->Play(false);
//				//���ʂɗ���Ă����ނ��Ƃ�����
//				if (m_guzaiOkibaSet == false) {
//					//�f���ɋ�̎M�̐���1���₷
//					GuzaiManager::GetInstance().AddEmptyDishNum();
//				}
//				//��[���J�n���邩�ǂ������f����B
//				GuzaiManager::GetInstance().JudgeToOrderRefill();
//				//���ꂪ��ޒu����ɂ��������̏���
//				//AwayFromGuzaiOkiba();
//			}
//	}
//}