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

namespace
{
	const Vector3 EGG_SCALE = { 0.7f,1.0f,0.7f };
	const Vector3 MOVE_SPEED_ZERO = Vector3::Zero;
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
	const float AJUST_SPEED_TO_FOLLOW_PLAYER = 90.0f;
	const float AJUST_HEIGHT = 50.0f;
	const float DISTANCE_BETWEEN_PLAYER_TO_GUZAI = 100.0f;
	const float SE_VOLUME = 3.0f;
	const float SE_VOLUME_SMALL = 0.2f;
	const float ANGLE_ADD_AMOUNT = 2.0f;
	const float AJUST_METER_X_POS0 = 350.0f;
	const float AJUST_METER_X_POS1 = 250.0f;
	const float AJUST_METER_Y_POS = 300.0f;
	const float AJUST_METER_Z_POS = 20.0f;
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

//�L�b�`����ŕʂ̃��f���ɍ����ւ���p
void Guzai::ChangeModel(int& guzaiType)
{
	switch (guzaiType) {
	case enCheese:
		m_skinModelRender->ChangeModel("Assets/modelData/food/cheese_kitchen.tkm");
		m_nowModelPath = "Assets/modelData/food/cheese_kitchen.tkm";
		break;
	case enEgg:
		m_skinModelRender->ChangeModel("Assets/modelData/food/egg_kitchen.tkm");
		m_nowModelPath = "Assets/modelData/food/egg_kitchen.tkm";
		break;
	case enLettuce:
		m_skinModelRender->ChangeModel("Assets/modelData/food/lettuce_kitchen.tkm");
		m_nowModelPath = "Assets/modelData/food/lettuce_kitchen.tkm";
		break;
	case enPatty:
		m_skinModelRender->ChangeModel("Assets/modelData/food/patty_kitchen.tkm");
		m_nowModelPath = "Assets/modelData/food/patty_kitchen.tkm";
		break;
	case enTomato:
		m_skinModelRender->ChangeModel("Assets/modelData/food/tomato_kitchen.tkm");
		m_nowModelPath = "Assets/modelData/food/tomato_kitchen.tkm";
		break;
	case enOnion:
		m_skinModelRender->ChangeModel("Assets/modelData/food/onion_kitchen.tkm");
		m_nowModelPath = "Assets/modelData/food/onion_kitchen.tkm";
		break;
	case enBacon:
		m_skinModelRender->ChangeModel("Assets/modelData/food/bacon_kitchen.tkm");
		m_nowModelPath = "Assets/modelData/food/bacon_kitchen.tkm";
		break;
	default:
		break;
	}
	
	m_skinModelRender->SetNewModel();
}

bool Guzai::Start()
{
	m_player00 = FindGO<Player>("player00");
	m_player01 = FindGO<Player>("player01");
	m_kitchen00 = FindGO<Kitchen>("kitchen00");
	m_kitchen01 = FindGO<Kitchen>("kitchen01");
	m_playerGene = FindGO<PlayerGene>("playerGene");
	m_guzaiOkiba = FindGO<GuzaiOkiba>("GuzaiOkiba");
	m_trashCan[0] = FindGO<TrashCan>("trashcan00");
	m_trashCan[1] = FindGO<TrashCan>("trashcan01");

	//��ނ̃��f����������
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//�ʏ�`��p���f���̏�����
	//m_skinModelRender->InitForRecieveShadow("Assets/modelData/gu/cheese.tkm", nullptr, enModelUpAxisZ, m_position);
	m_skinModelRender->Init("Assets/modelData/gu/cheese.tkm",nullptr, enModelUpAxisZ, m_position);
	//�e�����p�̏�����
	m_skinModelRender->InitForCastShadow("Assets/modelData/gu/cheese.tkm", nullptr, enModelUpAxisZ, m_position);
	//��ނ�ǉ������̂ŗ������o�͂���l��ύX
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<int> rand(GUZAI_TYPE_MIN_NUM, GUZAI_TYPE_MAX_NUM);

	m_typeNo = rand(mt);

	switch (m_typeNo) {
	case enCheese:
		m_skinModelRender->ChangeModel("Assets/modelData/food/cheese.tkm");
		m_nowModelPath = "Assets/modelData/food/cheese.tkm";
		break;
	case enEgg:
		m_skinModelRender->ChangeModel("Assets/modelData/food/egg.tkm");
		m_nowModelPath = "Assets/modelData/food/egg.tkm";
		break;
	case enLettuce:
		m_skinModelRender->ChangeModel("Assets/modelData/food/lettuce.tkm");
		m_nowModelPath = "Assets/modelData/food/lettuce.tkm";
		break;
	case enPatty:
		m_skinModelRender->ChangeModel("Assets/modelData/food/patty.tkm");
		m_nowModelPath = "Assets/modelData/food/patty.tkm";
		break;
	case enTomato:
		m_skinModelRender->ChangeModel("Assets/modelData/food/tomato.tkm");
		m_nowModelPath = "Assets/modelData/food/tomato.tkm";
		break;
	case enOnion:
		m_skinModelRender->ChangeModel("Assets/modelData/food/onion.tkm");
		m_nowModelPath = "Assets/modelData/food/onion.tkm";
		break;
	case enBacon:
		m_skinModelRender->ChangeModel("Assets/modelData/food/bacon.tkm");
		m_nowModelPath = "Assets/modelData/food/bacon.tkm";
		break;
	}

	m_skinModelRender->SetNewModel();
	return true;
}

void Guzai::GrabAndPut()
{
	//�ǂ���Ɏ�����邩������Ȃ����߁A�����̃|�W�V���������t���[���K�v�B
	Vector3 plPos00 = m_player00->GetPosition();
	Vector3 plPos01 = m_player01->GetPosition();
	
	//�L�b�`�������ނ����Ƃ��̏����̓L�b�`���ɂ���I

	//�v���C���[1�̎�����
	//A�{�^�����������Ƃ�
	if (g_pad[PLAYER_ONE_CONTROLLER]->IsTrigger(enButtonA)) {
		//���i���̋�ށj�̓v���C���[�P�Ƀ��b�N�I������Ă���B
		if (m_whichPlayerTargetMe == PLAYER_ONE) {
			//�v���C���[1�͉��������Ă��Ȃ��B���̓^�[�Q�b�g����Ă���i��������ρj�B���̓L�b�`����ɂȂ��B�v���C���[1�̓o�[�K�[�쐬���ł͂Ȃ��B
			//�Ō�̈����́A�L�b�`����Ńn���o�[�K�[����邽�߂Ɉꂩ���ɏW�܂��Ă���Œ��Ɏ��Ȃ��悤�ɂ��邽�߁B
			if (m_player00->GetPlayerState() == enNothing && m_isTargeted == true && m_isPutOnKitchen == false && m_kitchen00->GetIsPlayerCookingOnKitchen() == false) {
				//�����ꂽ�I
				m_isHad = true;
				//Player0�͋�ނ������Ă���I
				m_player00->SetPlayerState(enHaveGuzai);
				//�����͂ǂ����̃v���C���[�Ɏ����ꂽ��
				m_whichPlayerGet = PLAYER_ONE;
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/poka01.wav", false);
				se->SetVolume(SE_VOLUME);
				se->Play(false);
				//���ʂɗ���Ă����ނ��Ƃ�����
				if (m_guzaiOkibaSet == false) {
					//�f���ɋ�̎M�̐���1���₷
					GuzaiManager::GetInstance().AddEmptyDishNum();
				}
				//��[���J�n���邩�ǂ������f����B
				GuzaiManager::GetInstance().JudgeToOrderRefill();
				//���ꂪ��ޒu����ɂ��������̏���
				AwayFromGuzaiOkiba();
			}
		}
	}
	//�v���C���[2�̎�����
	if (g_pad[PLAYER_TWO_CONTROLLER]->IsTrigger(enButtonA)) {
		if (m_whichPlayerTargetMe == PLAYER_TWO) {
			if (m_player01->GetPlayerState() == enNothing && m_isTargeted == true && m_isPutOnKitchen == false && m_kitchen01->GetIsPlayerCookingOnKitchen() == false) {
				m_isHad = true;
				m_player01->SetPlayerState(enHaveGuzai);
				m_whichPlayerGet = PLAYER_TWO;
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/poka01.wav", false);
				se->SetVolume(SE_VOLUME);
				se->Play(false);
				if (m_guzaiOkibaSet == false) {
					//��̎M�̐���1���₷
					GuzaiManager::GetInstance().AddEmptyDishNum();
				}
				//��[���J�n���邩�ǂ������f����B
				GuzaiManager::GetInstance().JudgeToOrderRefill();
				AwayFromGuzaiOkiba();
			}
		}
	}

	//������Ă������ނ̈ʒu���v���C���[�̑O�ɂ���B
	if (m_isHad == true) {
		if (m_whichPlayerGet == PLAYER_ONE) {
			//��ނ̈ʒu���v���C���[�̏����O�ɂ���B
			Vector3 pl00MSpeed = m_player00->GetNormalMoveSpeed();
			pl00MSpeed *= AJUST_SPEED_TO_FOLLOW_PLAYER;
			plPos00 += pl00MSpeed;
			plPos00.y += AJUST_HEIGHT;
			SetPosition(plPos00);
			//�����Ă���Œ��A���̋�ނ��g��\���������Ȃ����߁B
			m_isTargeted = false;
		}
		if (m_whichPlayerGet == PLAYER_TWO) {
			Vector3 pl01MSpeed = m_player01->GetNormalMoveSpeed();
			pl01MSpeed *= AJUST_SPEED_TO_FOLLOW_PLAYER;
			plPos01 += pl01MSpeed;
			plPos01.y += AJUST_HEIGHT;
			SetPosition(plPos01);
			m_isTargeted = false;
		}
	}

	//�����̓L�b�`���ɒu������
	//A�{�^���������Ă��̋�ނ���������Ă���Ƃ��i����K�v���Ȃ����j
	if (g_pad[PLAYER_ONE_CONTROLLER]->IsTrigger(enButtonA) && m_isCooked == true && m_whichPlayerGet == PLAYER_ONE) {
		//�����͎�����Ă���B�����͈��ȓ��B��x�L�b�`���ɒu����Ă��Ȃ����B��pl01->have = enNothing��������邽�ߕK�v
		if (m_isHad == true && m_kit2Pl00 < DISTANCE_BETWEEN_PLAYER_TO_GUZAI && m_returnedFromKitchen == false) {
			//��ނ̎�ނɉ����āA�L�b�`�����p�̃��f���ɐ؂�ւ���B
			ChangeModel(m_typeNo);
			//��������������������
			if (m_typeNo == enEgg) {
				m_scale = {EGG_SCALE};
			}
			//�L�b�`���ɒu������ނ̎�ނ��v���C���[���ɕۑ�
			m_player00->SetPlayerStackedGuzais(m_kitchen00->GetStackNum(), m_typeNo);
			//�v���C���[�͉��������Ă��Ȃ�
			m_player00->SetPlayerState(enNothing);
			//�ς񂾑w����1����
			m_kitchen00->PlusStack();
			//���̋�ނ̓L�b�`���ɒu����Ă���
			m_isPutOnKitchen = true;
			//�����͎�����Ă��Ȃ�
			m_isHad = false;
			//�^�[�Q�e�B���O���Ă�����ނ��^��ł���Œ��͕ʂ̋�ނ��^�[�Q�e�B���O�������Ȃ����߁A�����ŏ������B
			m_isTargeted = false;
			//�v���C���[�̓^�[�Q�b�g���Ă��Ȃ��ɂ���B
			m_player00->SetTarget(m_isTargeted);
			//�L�b�`����Y���W�� �ς񂾋�ސ� ���グ��B
			m_position = m_kitchen00->GetKitchenPos();
			m_position.y += m_kitchen00->GetStackNum() * AJUST_HEIGHT;
			m_skinModelRender->SetPosition(m_position);

			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/poka02.wav", false);
			se->SetVolume(SE_VOLUME);
			se->Play(false);

			//�L�b�`���ɂ���X�^�b�N������ނ̈ꗗ�ɂ��̋�ނ�ǉ��B
			m_kitchen00->RegistStackedGuzai(this);

			//�����t���[���Ŏ��Ȃ��悤�ɂ���B
			m_kitchen00->ChangeGrabState(false);
		}
	}
	if (g_pad[PLAYER_TWO_CONTROLLER]->IsTrigger(enButtonA) && m_isCooked == true && m_whichPlayerGet == PLAYER_TWO) {
		if (m_isHad == true && m_kit2Pl01 < DISTANCE_BETWEEN_PLAYER_TO_GUZAI && m_returnedFromKitchen == false) {
			ChangeModel(m_typeNo);
			if (m_typeNo == enEgg) {
				m_scale = { EGG_SCALE };
			}
			m_player01->SetPlayerStackedGuzais(m_kitchen01->GetStackNum() ,m_typeNo);
			m_player01->SetPlayerState(enNothing);
			m_kitchen01->PlusStack();
			m_isPutOnKitchen = true;
			m_isHad = false;
			m_isTargeted = false;
			m_player01->SetTarget(m_isTargeted);
			m_position = m_kitchen01->GetKitchenPos();
			m_position.y += m_kitchen01->GetStackNum() * AJUST_HEIGHT;
			m_skinModelRender->SetPosition(m_position);

			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/poka02.wav", false);
			se->SetVolume(SE_VOLUME);
			se->Play(false);

			m_kitchen01->RegistStackedGuzai(this);
			m_kitchen01->ChangeGrabState(false);
		}
	}
}

void Guzai::Targeting()
{
		//��ނƂ̋��������ȉ��B�v���C���[�͉����^�[�Q�b�g���Ă��Ȃ��B���͒N�ɂ��^�[�Q�b�g����Ă��Ȃ��B�L�b�`���ɒu����Ă��Ȃ��B
		if (m_guzai2Pl00 < m_targetRangeNear && m_player00->GetTargetState() == false && !m_isTargeted && m_isPutOnKitchen == false) {
			//�����^�[�Q�b�g���Ă���̂̓v���C���[�P���B
			m_whichPlayerTargetMe = PLAYER_ONE;
			//���̓^�[�Q�b�g���ꂽ�B
			m_isTargeted = true;
			//�v���C���[�P����ނ̓^�[�Q�b�g���Ă���B
			m_player00->SetTarget(m_isTargeted);

			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/select07.wav", false);
			se->SetVolume(SE_VOLUME_SMALL);
			se->Play(false);
		}
		if (m_guzai2Pl01 < m_targetRangeNear && m_player01->GetTargetState() == false && !m_isTargeted && m_isPutOnKitchen == false) {
			m_whichPlayerTargetMe = PLAYER_TWO;
			m_isTargeted = true;
			m_player01->SetTarget(m_isTargeted);

			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/select07.wav", false);
			se->SetVolume(SE_VOLUME_SMALL);
			se->Play(false);
		}

		//�v���C���[�P�����ꂽ�B�v���C���[�P�͉������^�[�Q�b�g���Ă���B���̓^�[�Q�b�g����Ă���B
		if (m_guzai2Pl00 >= m_targetRangeFar && m_player00->GetTargetState() == true && m_isTargeted == true) {
			//�v���C���[�P�Ƀ^�[�Q�b�g����Ă���Ƃ�
			if (m_whichPlayerTargetMe == PLAYER_ONE) {
				//������x�^�[�Q�b�g�̐؂�ւ��ɒx�����N�����������߁A����p�̕ϐ�
				m_decrementTime--;
				if (m_decrementTime <= 0) {
					//���̓^�[�Q�b�g���瓦�ꂽ
					m_isTargeted = false;
					//�v���C���[�P�͉����^�[�Q�b�g���Ă��Ȃ�
					m_player00->SetTarget(m_isTargeted);
					//���̒x���p�ɒx�����Ԃ����ɖ߂�
					m_decrementTime = m_holdTime;
					//���͒N�ɂ��^�[�Q�b�g����Ă��Ȃ��B
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
	//�v���C���[�P��A�{�^�����������B���͎�����Ă���B�v���C���[�P�Ɏ�����Ă���B
	if (g_pad[PLAYER_ONE_CONTROLLER]->IsTrigger(enButtonA) && m_isHad == true && m_whichPlayerGet == PLAYER_ONE) {
		//1P���̋�ޒu����̔ԍ���4�`7�Ȃ̂ŁA���͈̔͂Œ��ׂ�B
		for (int i = GUZAIOKIBA_MIDDLE_NUM; i < GUZAIOKIBA_MAX_NUM; i++) {
			//��ޒu����ɃZ�b�g�\���ǂ����m�F����B
			if (m_guzaiOkiba->FindKitchenSet(i) == true && m_guzaiOkiba->FindGuzaiSet(i) == false && m_guzaiOkibaSet == false) {
				//�Z�b�g�\�Ȃ�΋�ޒu����ɃZ�b�g���ꂽ���Ƃ�`���A���g�̍��W���Z�b�g���ꂽ��ޒu����ɂ���B
				m_guzaiOkiba->GuzaiSet(i, true);
				//���W����ޒu����̏�ɃZ�b�g����B
				m_position = m_guzaiOkiba->GetKitchenPos(i);
				if (m_isCooked == true) {
					m_position.y += AJUST_HEIGHT;
				}
				//��ޒu����ɃZ�b�g���ꂽ�B
				m_guzaiOkibaSet = true;
				//�ǂ��̃L�b�`���ɃZ�b�g���ꂽ���B
				m_setKitchenNum = i;
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/poka02.wav", false);
				se->SetVolume(SE_VOLUME);
				se->Play(false);
				//�v���C���[�����������Ă��Ȃ���Ԃɂ���B
				m_player00->SetPlayerState(enNothing);
				//���̓^�[�Q�b�g����Ă��Ȃ��B
				m_isTargeted = false;
				//�v���C���[�P�͉����^�[�Q�b�g���Ă��Ȃ��B
				m_player00->SetTarget(m_isTargeted);
				//�x�����Ԃ����ɖ߂�
				m_decrementTime = m_holdTime;
				//���͒N�ɂ�������Ă��Ȃ��B
				m_isHad = false;
			}
		}
	}
	//2P���̏��� 1P�Ƃقړ���
	if (g_pad[PLAYER_TWO_CONTROLLER]->IsTrigger(enButtonA) && m_isHad == true && m_whichPlayerGet == PLAYER_TWO) {
		//2P���̋�ޒu����̔ԍ���0�`4�Ȃ̂ŁA���͈̔͂Œ��ׂ�B
		for (int i = GUZAIOKIBA_MIN_NUM; i < GUZAIOKIBA_MIDDLE_NUM; i++) {
			if (m_guzaiOkiba->FindKitchenSet(i) == true && m_guzaiOkiba->FindGuzaiSet(i) == false && m_guzaiOkibaSet == false) {
				m_guzaiOkiba->GuzaiSet(i, true);
				m_position = m_guzaiOkiba->GetKitchenPos(i);
				if (m_isCooked == true) {
					m_position.y += AJUST_HEIGHT;
				}
				m_guzaiOkibaSet = true;
				m_setKitchenNum = i;
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/poka02.wav", false);
				se->SetVolume(SE_VOLUME);
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
	//��ޒu����ɃZ�b�g����Ă�����c
	if (m_guzaiOkibaSet == true) {
		//�Z�b�g����Ă�����ޒu����Ɏ��o���ꂽ���Ƃ�`����B
		m_guzaiOkiba->GuzaiSet(m_setKitchenNum, false);
		//�����Ď��g�����o���ꂽ���Ƃɂ���B
		m_guzaiOkibaSet = false;
		m_setKitchenNum = NONE;
		//������u�Ԃɒu�����Ƃ�h�����߁B���̃t���[������Ƃ��悤�ȏ����ɂ��Ă���B
		m_canPutOnGuzaiOkiba = false;
	}
}

void Guzai::Cooking()
{
	//���g����ޒu����ɃZ�b�g����Ă��āA��������Ă��炸�A�_�~�[���o���Ă���Ƃ��B
	if (m_guzaiOkibaSet == true && m_isCooked == false && m_isTargeted) {
		//1P���̏���
		//1P����B�{�^����������Ă��Ď��g�̃Z�b�g�ꏊ��1P���������ꍇ�c
		if (g_pad[PLAYER_ONE_CONTROLLER]->IsPress(enButtonB) && m_setKitchenNum >= GUZAIOKIBA_MIDDLE_NUM && m_player00->GetPlayerState() <= enNothing) {
			//�����Ă��鎞�Ԃ��C���N�������g
			m_hold01++;
			m_player00->StopMove(true);
			m_player00->SetMoveSpeed(MOVE_SPEED_ZERO);
			//�����o�Ă��Ȃ�������B
			if (m_soundFlag01 == false) {
				//�����̐i�݋���������[�^�[
				m_meter = NewGO<Meter>(0);
				Vector3 pos = m_position;
				pos.x -= AJUST_METER_X_POS0;
				pos.y += AJUST_METER_Y_POS;
				pos.z += AJUST_METER_Z_POS;
				m_meter->SetPosition(pos);
				//����炷
				m_cookingSe = NewGO<CSoundSource>(0);
				m_cookingSe->Init(L"Assets/sound/cutting_a_onion_speedy.wav", false);
				m_cookingSe->Play(true);
				m_soundFlag01 = true;
			}
			//���[�^�[���������ւ炷
			Vector3 Scale = m_meter->GetScale();
			Scale.x -= METER_SHRINK_SPEED;
			m_meter->SetScale(Scale);
			//�����������Ԃ܂ŉ����ꂽ��c
			if (m_hold01 > m_cookingTime) {
				//������̃��f���ɕύX�B
				ChangeModel(m_typeNo);
				m_isCooked = true;
				m_position.y += AJUST_HEIGHT;
				m_isTargeted = false;
				m_player00->SetTarget(m_isTargeted);
				m_whichPlayerTargetMe = PLAYER_NONE;
				//�����o�Ă�����B
				if (m_soundFlag01 == true) {
					DeleteGO(m_meter);
					//���������B
					DeleteGO(m_cookingSe);
					m_soundFlag01 = false;
				}
				//������悤�ɂ���B
				m_player00->StopMove(false);
			}
		}
		else {
			//�{�^���𗣂�����^�C�}�[��0�ɖ߂�B
			m_hold01 = 0;
			//������悤�ɂ���B
			m_player00->StopMove(false);
			//�����o�Ă�����B
			if (m_soundFlag01 == true) {
				DeleteGO(m_meter);
				//���������B
				DeleteGO(m_cookingSe);
				m_soundFlag01 = false;
			}
		}

		//2P���̏���
		if (g_pad[PLAYER_TWO_CONTROLLER]->IsPress(enButtonB) && m_setKitchenNum < GUZAIOKIBA_MIDDLE_NUM && m_player01->GetPlayerState() <= enNothing) {
			m_hold02++;
			m_player01->StopMove(true);
			m_player01->SetMoveSpeed(MOVE_SPEED_ZERO);
			////�����o�Ă��Ȃ�������B
			if (m_soundFlag02 == false) {
				m_meter = NewGO<Meter>(0);
				Vector3 pos = m_position;
				pos.x += AJUST_METER_X_POS1;
				pos.y += AJUST_METER_Y_POS;
				pos.z += AJUST_METER_Z_POS;
				m_meter->SetPosition(pos);
				//����炷
				m_cookingSe = NewGO<CSoundSource>(0);
				m_cookingSe->Init(L"Assets/sound/cutting_a_onion_speedy.wav", false);
				m_cookingSe->Play(true);
				m_soundFlag02 = true;
			}
			Vector3 Scale = m_meter->GetScale();
			Scale.x -= METER_SHRINK_SPEED;
			m_meter->SetScale(Scale);
			if (m_hold02 > m_cookingTime) {
				
				ChangeModel(m_typeNo);
				m_isCooked = true;
				m_position.y += AJUST_HEIGHT;
				m_isTargeted = false;
				m_player01->SetTarget(m_isTargeted);
				m_whichPlayerTargetMe = PLAYER_NONE;
				//�����o�Ă�����B
				if (m_soundFlag02 == true) {
					//���������B
					DeleteGO(m_cookingSe);
					m_soundFlag02 = false;
					DeleteGO(m_meter);
				}
				m_player01->StopMove(false);
			}
		}
		else {
			m_player01->StopMove(false);
			m_hold02 = 0;
			//�����o�Ă�����B
			if (m_soundFlag02 == true) {
				//���������B
				DeleteGO(m_meter);
				DeleteGO(m_cookingSe);
				m_soundFlag02 = false;
			}
		}
	}
}

void Guzai::SetOnTrashCan() {
	//�v���C���[�P�Ɏ�����Ă���
	if (m_whichPlayerGet == PLAYER_ONE) {
		//�v���C���[�P��A�{�^����������
		if (g_pad[PLAYER_ONE_CONTROLLER]->IsTrigger(enButtonA)			//A�{�^����������
			&& m_isHad == true											//���̋�ނ�������Ă���
			&& m_trashCan[0]->GetCanTrash()) {							//�S�~���͎̂Ă�p�ӂ��ł��Ă��邩�i�����I�Ɂj
			m_isSetOnTrashCan = true;									//�S�~���Ŏ̂Ă鏀��
		}
		if (m_isSetOnTrashCan == true) {
			DeleteGO(this);
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/dumping.wav", false);
			se->SetVolume(SE_VOLUME);
			se->Play(false);
			m_player00->SetPlayerState(enNothing);
			m_isTargeted = false;
			m_player00->SetTarget(m_isTargeted);
			//�S�~���̃��A�N�V������ON�ɂ���
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
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/dumping.wav", false);
			se->SetVolume(SE_VOLUME);
			se->Play(false);
			m_player01->SetPlayerState(enNothing);
			m_isTargeted = false;
			m_player01->SetTarget(m_isTargeted);
			m_trashCan[1]->ChangeMovingState(true);
		}
	}
}

void Guzai::Rotation()
{
	//�L�b�`���ɃZ�b�g����Ă���Ƃ��B
	if (m_isPutOnKitchen == true) {
		//��]����
		m_angle += ANGLE_ADD_AMOUNT;
		if (m_angle > 360.0f) {
			m_angle = 0.0f;
		}
		m_rotation.SetRotationDeg(Vector3::AxisY, m_angle);

	}
	//�L�b�`���ɃZ�b�g����Ă��Ȃ��Ƃ��B
	else
	{
		//�v���C���[����ނ��������Ƃ��̋�ނ̒Ǐ]��]�B
		if (m_isHad == true) {
			if (m_whichPlayerGet == PLAYER_ONE) {
				//�v���C���[�������Ă�������ɉ�]����̂ŁA�v���C���[�̈ړ����x���Q�Ƃ���B
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
			//�v���C���[�������Ă��Ȃ��Ƃ��͉�]�����Z�b�g�B
			m_rotation = Quaternion::Identity;
		}
	}
}

float Guzai::CalcDistance(Vector3 pos1, Vector3 pos2)
{
	//�n�_�P�ƒn�_�Q�̋����𑪂�B
	Vector3 distance = pos1 - pos2;
	return distance.Length();
}

void Guzai::Update()
{
	//�P�t���[���ɂ����鎞�ԁi�b�j���擾����B
	float gameTime = GameTime().GetFrameDeltaTime();

	//�v���C���[��������Update�֐����X���[
	if (m_playerGene->GetPlayerGeneState() == true) {
		return;
	}
	//�Q�[�����I��������A���g�������B
	if (GameDirector::GetInstance().GetGameScene() == enGameEnd) {
		DeleteGO(this);
	}

	Vector3 plPos00 = m_player00->GetPosition();
	Vector3 plPos01 = m_player01->GetPosition();
	Vector3 kitchen00Pos = m_kitchen00->GetKitchenPos();
	Vector3 kitchen01Pos = m_kitchen01->GetKitchenPos();

	//��ނ���v���C���[�܂ł̋���
	m_guzai2Pl00 = CalcDistance(m_position, plPos00);
	//�L�b�`������v���C���[�̋���
	m_kit2Pl00 = CalcDistance(kitchen00Pos, plPos00);
	//��ނ���v���C���[�ւ̋���
	m_guzai2Pl01 = CalcDistance(m_position, plPos01);
	//�L�b�`������v���C���[�ւ̋���
	m_kit2Pl01 = CalcDistance(kitchen01Pos, plPos01);

	//�g�}�g�ƃI�j�I���ȊO�͒������Ȃ��ł悢�B
	if (m_typeNo != enTomato && m_typeNo != enOnion) {
		m_isCooked = true;
	}

	Targeting();

	m_kitchen00->ChangeGrabState(true);
	m_kitchen01->ChangeGrabState(true);

	GrabAndPut();

	if (m_canPutOnGuzaiOkiba) {
		SetGuzaiOkiba();
	}
	m_canPutOnGuzaiOkiba = true;

	Cooking();

	SetOnTrashCan();

	Rotation();

	//�L�b�`���ɒu����Ė߂��Ă������f���̂��̂�������B
	if (m_returnedFromKitchen){
		//���͎�����Ă���
		if (m_isHad == true) {
			//�v���C���[�P�ɂ�����Ă���
			if (m_whichPlayerGet == PLAYER_ONE) {
				//��ނ̈ʒu���v���C���[�̏����O�ɂ���B
				Vector3 pl00MSpeed = m_player00->GetNormalMoveSpeed();
				pl00MSpeed *= AJUST_SPEED_TO_FOLLOW_PLAYER;
				plPos00 += pl00MSpeed;
				SetPosition(plPos00);
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/putting_a_book2.wav", false);
				se->SetVolume(SE_VOLUME);
				se->Play(false);
			}
			if (m_whichPlayerGet == PLAYER_TWO) {
				Vector3 pl01MSpeed = m_player01->GetNormalMoveSpeed();
				pl01MSpeed *= AJUST_SPEED_TO_FOLLOW_PLAYER;
				plPos01 += pl01MSpeed;
				SetPosition(plPos01);
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/putting_a_book2.wav", false);
				se->SetVolume(SE_VOLUME);
				se->Play(false);
			}
		}
		m_returnedFromKitchen = false;
	}
	//���f���̉�]�󋵂��X�V����B
	m_skinModelRender->SetRotation(m_rotation);

	//��ޒu����ɒu����Ă���Ƃ��̈ʒu����
	if (m_guzaiOkibaSet == true) {
		Vector3 SetPos = m_position;
		SetPos.y += AJUST_HEIGHT;
		m_skinModelRender->SetPosition(SetPos);
	}
	//�u����Ă��Ȃ����
	else {
		m_skinModelRender->SetPosition(m_position);
	}
	//�v���C���[�Ƀ^�[�Q�b�g����Ă�����g��\��
	if (m_isTargeted == true) {
		m_skinModelRender->SetScale(m_TargetedScale);
	}
	//����Ă��Ȃ���Ε��ʂ̃T�C�Y��
	else {
		m_skinModelRender->SetScale(m_scale);
	}

	if (m_shouldDelete == true) {
		DeleteGO(this);
	}
}