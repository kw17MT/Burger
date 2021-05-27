#include "stdafx.h"
#include "Guzai.h"
#include "math.h"
#include "Kitchen.h"
#include "GuzaiGene.h"
#include "GuzaiOkiba.h"
#include "SkinModelRender.h"
#include "Player.h"
#include "PlayerGene.h"
#include "TrashCan.h"
#include "SoundSource.h"
#include "effect/Effect.h"
#include "Meter.h"
#include "GameDirector.h"
#include<random>
#include <ctime>
#include <cstdlib>

namespace
{
	const float MOVESPEED = 130.0f;
}

Guzai::Guzai()
{
}

Guzai::~Guzai()
{
	DeleteGO(m_skinModelRender);
	
	//�_�~�[������
	if (targetDummy01 != nullptr) {
		DeleteGO(targetDummy01);
	}
	if (targetDummy02 != nullptr) {
		DeleteGO(targetDummy02);
	}

	if (m_soundFlag01 == true || m_soundFlag02) {
		DeleteGO(m_cookingSe);
		DeleteGO(m_meter);
	}
}

void Guzai::ChangeGuzai(int num)
{
	TypeNo = num;

	switch (TypeNo) {
	case 0:
		m_skinModelRender->ChangeModel("Assets/modelData/food/cheese.tkm");
		NowModelPath = "Assets/modelData/food/cheese.tkm";
		break;
	case 1:
		m_skinModelRender->ChangeModel("Assets/modelData/food/egg.tkm");
		NowModelPath = "Assets/modelData/food/egg.tkm";
		break;
	case 2:
		m_skinModelRender->ChangeModel("Assets/modelData/food/lettuce.tkm");
		NowModelPath = "Assets/modelData/food/lettuce.tkm";
		break;
	case 3:
		m_skinModelRender->ChangeModel("Assets/modelData/food/patty.tkm");
		NowModelPath = "Assets/modelData/food/patty.tkm";
		break;
	case 4:
		m_skinModelRender->ChangeModel("Assets/modelData/food/tomato.tkm");
		NowModelPath = "Assets/modelData/food/tomato.tkm";
		break;
	case 5:
		m_skinModelRender->ChangeModel("Assets/modelData/food/onion.tkm");
		NowModelPath = "Assets/modelData/food/onion.tkm";
		break;
	case 6:
		m_skinModelRender->ChangeModel("Assets/modelData/food/bacon.tkm");
		NowModelPath = "Assets/modelData/food/bacon.tkm";
		break;
	}
	
	m_skinModelRender->SetNewModel();
}

//�L�b�`����ŕʂ̃��f���ɍ����ւ���p
void Guzai::ChangeModel(int& num)
{
	switch (num) {
	case 0:
		m_skinModelRender->ChangeModel("Assets/modelData/food/cheese_kitchen.tkm");
		NowModelPath = "Assets/modelData/food/cheese_kitchen.tkm";
		break;
	case 1:
		m_skinModelRender->ChangeModel("Assets/modelData/food/egg_kitchen.tkm");
		NowModelPath = "Assets/modelData/food/egg_kitchen.tkm";
		break;
	case 2:
		m_skinModelRender->ChangeModel("Assets/modelData/food/lettuce_kitchen.tkm");
		NowModelPath = "Assets/modelData/food/lettuce_kitchen.tkm";
		break;
	case 3:
		m_skinModelRender->ChangeModel("Assets/modelData/food/patty_kitchen.tkm");
		NowModelPath = "Assets/modelData/food/patty_kitchen.tkm";
		break;
	case 4:
		m_skinModelRender->ChangeModel("Assets/modelData/food/tomato_kitchen.tkm");
		NowModelPath = "Assets/modelData/food/tomato_kitchen.tkm";
		break;
	case 5:
		m_skinModelRender->ChangeModel("Assets/modelData/food/onion_kitchen.tkm");
		NowModelPath = "Assets/modelData/food/onion_kitchen.tkm";
		break;
	case 6:
		m_skinModelRender->ChangeModel("Assets/modelData/food/bacon_kitchen.tkm");
		NowModelPath = "Assets/modelData/food/bacon_kitchen.tkm";
		break;
	default:
		break;
	}
	
	m_skinModelRender->SetNewModel();
}

bool Guzai::Start()
{
	pl01 = FindGO<Player>("player01");
	pl02 = FindGO<Player>("player02");
	ki01 = FindGO<Kitchen>("kitchen01");
	ki02 = FindGO<Kitchen>("kitchen02");
	playerGene = FindGO<PlayerGene>("playerGene");
	m_guzaiGene = FindGO<GuzaiGene>("guzaiGene");
	m_guzaiOkiba = FindGO<GuzaiOkiba>("GuzaiOkiba");
	m_trashCan[0] = FindGO<TrashCan>("trashcan01");
	m_trashCan[1] = FindGO<TrashCan>("trashcan02");

	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/gu/cheese.tkm",nullptr, enModelUpAxisZ, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	
	std::random_device rnd;
	std::mt19937 mt(rnd());
	//��ނ�ǉ������̂ŗ������o�͂���l��ύX
	std::uniform_int_distribution<int> rand(0, 6);

	TypeNo = rand(mt);

	switch (TypeNo) {
	case 0:
		m_skinModelRender->ChangeModel("Assets/modelData/food/cheese.tkm");
		NowModelPath = "Assets/modelData/food/cheese.tkm";
		break;
	case 1:
		m_skinModelRender->ChangeModel("Assets/modelData/food/egg.tkm");
		NowModelPath = "Assets/modelData/food/egg.tkm";
		break;
	case 2:
		m_skinModelRender->ChangeModel("Assets/modelData/food/lettuce.tkm");
		NowModelPath = "Assets/modelData/food/lettuce.tkm";
		break;
	case 3:
		m_skinModelRender->ChangeModel("Assets/modelData/food/patty.tkm");
		NowModelPath = "Assets/modelData/food/patty.tkm";
		break;
	case 4:
		m_skinModelRender->ChangeModel("Assets/modelData/food/tomato.tkm");
		NowModelPath = "Assets/modelData/food/tomato.tkm";
		break;
	case 5:
		m_skinModelRender->ChangeModel("Assets/modelData/food/onion.tkm");
		NowModelPath = "Assets/modelData/food/onion.tkm";
		break;
	case 6:
		m_skinModelRender->ChangeModel("Assets/modelData/food/bacon.tkm");
		NowModelPath = "Assets/modelData/food/bacon.tkm";
		break;

	}

	m_skinModelRender->SetNewModel();
	return true;
}

void Guzai::GrabNPut()
{
	Vector3 plPos01 = pl01->GetPosition();
	Vector3 plPos02 = pl02->GetPosition();
	
	
	//���߂ăv���C���[�Ɏ�����鎞
	//A�{�^�����������Ƃ��A�v���C���[�͉��������Ă��Ȃ��A��苗�����߂��ʒu�ɂ���A�����̓^�[�Q�b�g����Ă��邩�A��x�ł��u����Ă��Ȃ����B
	if (g_pad[0]->IsTrigger(enButtonA)) {
		if (pl01->have == 0 && guzai2Pl01 < 150.0f && targeted == true && put == 0 && ki01->GetKitchenCooking() == false) {
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/poka01.wav", false);
			se->SetVolume(3.0f);
			se->Play(false);
			GetGuzaiOkiba();
			//�����ꂽ�I
			state = 1;
			//Player1�͋�ނ������Ă���I
			pl01->have = 1;
			//�����͂ǂ����̃v���C���[�Ɏ����ꂽ��
			whichPlayerGet = 1;
			//��̎M�̐���1���₷
			playerGene->AddNoHavingDishCounter();
		}
	}
	if (g_pad[1]->IsTrigger(enButtonA)) {
		if (pl02->have == 0 && guzai2Pl02 < 150.0f && targeted == true && put == 0) {
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/poka01.wav", false);
			se->SetVolume(3.0f);
			se->Play(false);
			GetGuzaiOkiba();
			state = 1;
			pl02->have = 1;
			
			whichPlayerGet = 2;

			playerGene->AddNoHavingDishCounter();
		}
	}

	//������Ă������ނ̈ʒu���v���C���[�̏�ɂ���B
	if (state == 1) {
		if (whichPlayerGet == 1) {
			//��ނ̈ʒu���v���C���[�̏����O�ɂ���B
			Vector3 pl01MSpeed = pl01->GetNormalMoveSpeed();
			pl01MSpeed *= 90.0f;
			plPos01 += pl01MSpeed;
			plPos01.y += 50.0f;
			SetPosition(plPos01);

			//��ޒu����ɒu������ł��܂��߂Â��ƃ_�~�[���o��悤�ɂ���B
			if (targetDummy01 != nullptr) {
				DeleteGO(targetDummy01);
				isSetTargetDummy = false;
				decrementTime = holdTime;
				whichPlayerTargetMe = 0;
			}
		}
		if (whichPlayerGet == 2) {
			//plPos02.y += 100.0f;
			//SetPosition(plPos02);
			Vector3 pl02MSpeed = pl02->GetNormalMoveSpeed();
			pl02MSpeed *= 90.0f;
			plPos02 += pl02MSpeed;
			plPos02.y += 50.0f;
			SetPosition(plPos02);

			if (targetDummy02 != nullptr) {

				DeleteGO(targetDummy02);
				isSetTargetDummy = false;
				decrementTime = holdTime;
				whichPlayerTargetMe = 0;
			}
		}
	}

	//�����̓L�b�`���ɒu������
	//A�{�^���������Ă��̋�ނ���������Ă���Ƃ��i����K�v���Ȃ����j
	if (g_pad[0]->IsTrigger(enButtonA) && m_isCooked == true && whichPlayerGet == 1) {
		//�����͎�����Ă��邩�A�����͈��ȓ����A��x�L�b�`���ɒu����Ă��Ȃ����B��pl01->have = 0��������邽�ߕK�v
		if (state == 1 && kit2Pl01 < 100.0f && returned == false) {
			ChangeModel(TypeNo);
			//�������������������
			if (TypeNo == 1) {
				m_scale = { 0.7f,1.0f,0.7f };
			}
			Kitchen* ki01 = FindGO<Kitchen>("kitchen01");
			//�L�b�`���ɒu������ނ̎�ނ��v���C���[���ɕۑ�
			pl01->GuzaiNo[ki01->GetStackNum()] = TypeNo;
			//�v���C���[�͉��������Ă��Ȃ�
			pl01->have = 0;
			//�ς񂾑w����1����
			ki01->PlusStack();
			//���̋�ނ̓L�b�`���ɒu����Ă���
			put = 1;
			//�����͎�����Ă��Ȃ�
			state = 0;
			//�^�[�Q�e�B���O���Ă�����ނ��^��ł���Œ��͕ʂ̋�ނ��^�[�Q�e�B���O�������Ȃ����߁A�����ŏ������B
			//�v���C���[�̓^�[�Q�b�g���Ă��Ȃ��ɂ���B
			targeted = false;
			pl01->SetTarget(targeted);
			//�_�~�[���o���Ă��邩���o���Ă��Ȃ��ɂ��Ď�����o��悤�ɂ���
			isSetTargetDummy = false;
			//�L�b�`����Y���W�{60 * �ς񂾋�ސ� ���グ��B
			m_position = ki01->GetKitchenPos();
			m_position.y += ki01->GetStackNum() * 60;
			m_skinModelRender->SetPosition(m_position);

			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/poka02.wav", false);
			se->SetVolume(3.0f);
			se->Play(false);

			//�L�b�`���ɂ���X�^�b�N������ނ̈ꗗ�ɂ��̋�ނ�ǉ��B
			ki01->RegistStackedGuzai(this);

			//�����t���[���Ŏ��Ȃ��悤�ɂ���B
			ki01->ChangeGrabState(false);
		}
	}
	if (g_pad[1]->IsTrigger(enButtonA) && m_isCooked == true && whichPlayerGet == 2) {
		if (state == 1 && kit2Pl02 < 100.0f && returned == false) {
			ChangeModel(TypeNo);
			//�������������������
			if (TypeNo == 1) {
				m_scale = { 0.7f,1.0f,0.7f };
			}
			Kitchen* ki02 = FindGO<Kitchen>("kitchen02");
			//�L�b�`���ɒu������ނ̎�ނ��v���C���[���ɕۑ�
			pl02->GuzaiNo[ki02->GetStackNum()] = TypeNo;
			//�v���C���[�͉��������Ă��Ȃ�
			pl02->have = 0;
			//�ς񂾑w����1����
			ki02->PlusStack();
			//���̋�ނ͒u����Ă���
			put = 1;
			//�����͎�����Ă��Ȃ�
			state = 0;
			//�^�[�Q�e�B���O���Ă�����ނ��^��ł���Œ��͕ʂ̋�ނ��^�[�Q�e�B���O�������Ȃ����߁A�����ŏ������B
			//�v���C���[�̓^�[�Q�b�g���Ă��Ȃ��ɂ���B
			targeted = false;
			pl02->SetTarget(targeted);
			//�_�~�[���o���Ă��邩���o���Ă��Ȃ��ɂ��Ď�����o��悤�ɂ���
			isSetTargetDummy = false;
			//�L�b�`����Y���W�{60 * �ς񂾋�ސ� ���グ��B
			m_position = ki02->GetKitchenPos();
			m_position.y += ki02->GetStackNum() * 60;
			m_skinModelRender->SetPosition(m_position);

			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/poka02.wav", false);
			se->SetVolume(3.0f);
			se->Play(false);

			//�L�b�`���ɂ���X�^�b�N������ނ̈ꗗ�ɂ��̋�ނ�ǉ��B
			ki02->RegistStackedGuzai(this);

			//�����t���[���Ŏ��Ȃ��悤�ɂ���B
			ki02->ChangeGrabState(false);
		}
	}
}

void Guzai::TargetingNPopDummy()
{
		//��ނƂ̋��������ȉ��@�Ł@�v���C���[�͉������b�N���Ă��Ȃ�������B
		//�߂��̋�ނ��^�[�Q�b�g���A�v���C���[�̃^�[�Q�b�g��Ԃ�TRUE�ɁB
		if (guzai2Pl01 < TargetRangeNear && pl01->GetTargetState() == false && !targeted && put == 0) {
			whichPlayerTargetMe = 1;
			targeted = true;
			pl01->SetTarget(targeted);
		}
		if (guzai2Pl02 < TargetRangeNear && pl02->GetTargetState() == false && !targeted && put == 0) {
			whichPlayerTargetMe = 2;
			targeted = true;
			pl02->SetTarget(targeted);
		}

		//�^�[�Q�b�g������ނ��_�~�[���o���Ă��Ȃ�������B
		//�����傫���_�~�[����ނƔ��悤�ɏo���B�i�F�͌�Ő^�����ɂ���̂łȂ�ł������j
		if (whichPlayerTargetMe != 0 && isSetTargetDummy == false) {
			if (whichPlayerTargetMe == 1) {
				//SkinModelRender* targetDummyOnGuzai01 = NewGO<SkinModelRender>(1, "targetdummy01");
				targetDummy01 = NewGO<SkinModelRender>(1, "targetdummy01");
				targetDummy01->Init(NowModelPath, nullptr, enModelUpAxisZ, m_position);
				targetDummy01->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				targetDummy01->SetFrontCulling("FrontCulling");
				targetDummy01->SetPosition(m_position);
				targetDummy01->SetScale(m_dummyScale);
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/select07.wav", false);
				se->SetVolume(0.2f);
				se->Play(false);
				isSetTargetDummy = true;
			}
			if (whichPlayerTargetMe == 2) {
				//SkinModelRender* targetDummyOnGuzai02 = NewGO<SkinModelRender>(1, "targetdummy02");
				targetDummy02 = NewGO<SkinModelRender>(1, "targetdummy02");
				targetDummy02->Init(NowModelPath, nullptr, enModelUpAxisZ, m_position);
				targetDummy02->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				targetDummy02->SetFrontCulling("FrontCulling");
				targetDummy02->SetPosition(m_position);
				targetDummy02->SetScale(m_dummyScale);
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/select07.wav", false);
				se->SetVolume(0.2f);
				se->Play(false);
				isSetTargetDummy = true;
			}
		}

		//�����Ń^�[�Q�b�g���Ă�����ނ�����ȏ㗣�ꂽ��
		//�_�~�[�������āA�v���C���[����TargetingState��targeted�����̒l�ɖ߂��Ă��B
		if (guzai2Pl01 >= TargetRangeFar && pl01->GetTargetState() == true && targeted == true) {
			if (whichPlayerTargetMe == 1) {
				//SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
				//targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
				if (targetDummy01 != nullptr) {
					decrementTime--;
					if (decrementTime == 0) {
						DeleteGO(targetDummy01);
						targeted = false;
						pl01->SetTarget(targeted);
						isSetTargetDummy = false;
						decrementTime = holdTime;
						whichPlayerTargetMe = 0;
					}
				}
			}
		}
		if (guzai2Pl02 >= TargetRangeFar && pl02->GetTargetState() == true && targeted == true) {
			if (whichPlayerTargetMe == 2) {
				//SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
				//targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
				if (targetDummy02 != nullptr) {
					decrementTime--;
					if (decrementTime == 0) {
						DeleteGO(targetDummy02);
						targeted = false;
						pl02->SetTarget(targeted);
						isSetTargetDummy = false;
						decrementTime = holdTime;
						whichPlayerTargetMe = 0;
					}
				}
			}
		}
}
void Guzai::SetGuzaiOkiba()
{
	//1P���̏���

	//��ނ��v���C���[�Ɏ�����Ă���Ƃ��ɁAA�{�^���������ꂽ��c
	if (g_pad[0]->IsTrigger(enButtonA) && state == 1 && whichPlayerGet == 1) {

		//1P���̋�ޒu����̔ԍ���4�`7�Ȃ̂ŁA���͈̔͂Œ��ׂ�B
		for (int i = 4; i < 8; i++) {

			//��ޒu����ɃZ�b�g�\���ǂ����m�F����B
			if (m_guzaiOkiba->FindKitchenSet(i) == true && m_guzaiOkiba->FindGuzaiSet(i) == false && m_guzaiOkibaSet == false) {

				//�Z�b�g�\�Ȃ�΋�ޒu����ɃZ�b�g���ꂽ���Ƃ�`���A���g�̍��W���Z�b�g���ꂽ��ޒu����ɂ���B
				m_guzaiOkiba->GuzaiSet(i, true);
				m_position = m_guzaiOkiba->GetKitchenPos(i);
				if (m_isCooked == true) {
					m_position.y += 60.0f;
				}
				m_guzaiOkibaSet = true;
				m_setKitchenNum = i;
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/poka02.wav", false);
				se->SetVolume(3.0f);
				se->Play(false);
				//�v���C���[�����������Ă��Ȃ���Ԃɂ���B
				pl01->have = 0;
				targeted = false;
				pl01->SetTarget(targeted);
				isSetTargetDummy = false;
				decrementTime = holdTime;
				state = 0;
			}
		}
	}
	//2P���̏��� 1P�Ƃقړ���
	if (g_pad[1]->IsTrigger(enButtonA) && state == 1 && whichPlayerGet == 2) {
		//2P���̋�ޒu����̔ԍ���0�`4�Ȃ̂ŁA���͈̔͂Œ��ׂ�B
		for (int i = 0; i < 4; i++) {
			
			if (m_guzaiOkiba->FindKitchenSet(i) == true && m_guzaiOkiba->FindGuzaiSet(i) == false && m_guzaiOkibaSet == false) {
			
				m_guzaiOkiba->GuzaiSet(i, true);
				m_position = m_guzaiOkiba->GetKitchenPos(i);
				if (m_isCooked == true) {
					m_position.y += 60.0f;
				}
			
				m_guzaiOkibaSet = true;
				m_setKitchenNum = i;
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/poka02.wav", false);
				se->SetVolume(3.0f);
				se->Play(false);
				pl02->have = 0;
				targeted = false;
				pl02->SetTarget(targeted);
				isSetTargetDummy = false;
				decrementTime = holdTime;
				state = 0;
			}
		}
	}
}

void Guzai::GetGuzaiOkiba()
{
	//��ޒu����ɃZ�b�g����Ă�����c
	if (m_guzaiOkibaSet == true) {
		//�Z�b�g����Ă�����ޒu����Ɏ��o���ꂽ���Ƃ�`����B
		m_guzaiOkiba->GuzaiSet(m_setKitchenNum, false);
		//�����Ď��g�����o���ꂽ���Ƃɂ���B
		m_guzaiOkibaSet = false;
		m_setKitchenNum = 9;

		canPutOnGuzaiOkiba = false;

		playerGene->MinusNoHavingDishCounter();
	}
}

void Guzai::Cooking()
{
	//���g����ޒu����ɃZ�b�g����Ă��āA��������Ă��炸�A�_�~�[���o���Ă���Ƃ��B
	if (m_guzaiOkibaSet == true && m_isCooked == false && isSetTargetDummy == true) {
		//1P���̏���
		//1P����B�{�^����������Ă��Ď��g�̃Z�b�g�ꏊ��1P���������ꍇ�c
		if (g_pad[0]->IsPress(enButtonB) && m_setKitchenNum >= 4 && pl01->have <= 0) {
			
			//�����Ă��鎞�Ԃ��C���N�������g
			m_hold01++;
			pl01->StopMove01(true);
			pl01->SetMoveSpeed({ 0.0f,0.0f,0.0f });
			//�����o�Ă��Ȃ�������B
			if (m_soundFlag01 == false) {
				//�����̐i�݋���������[�^�[
				m_meter = NewGO<Meter>(0);
				Vector3 pos = m_position;
				pos.x -= 350.0f;
				pos.y += 300.0f;
				pos.z += 20.0f;
				m_meter->SetPosition(pos);
				//����炷
				m_cookingSe = NewGO<CSoundSource>(0);
				m_cookingSe->Init(L"Assets/sound/cutting_a_onion_speedy.wav", false);
				m_cookingSe->SetVolume(1.0f);
				m_cookingSe->Play(true);
				m_soundFlag01 = true;
			}
			//���[�^�[����������
			Vector3 Scale = m_meter->GetScale();
			Scale.x -= 1.4f / 60.0f;
			m_meter->SetScale(Scale);
			if (m_hold01 % 10 == 0) {
				Vector3 pos = m_position;
				pos.x -= 100.0f;
				pos.y += 100.0f;
				
			}
			//�����������Ԃ܂ŉ����ꂽ��c
			if (m_hold01 > m_cookingTime) {
				//������̃��f���ɕύX�B
				ChangeModel(TypeNo);
				m_isCooked = true;
				m_position.y += 50.0f;
				//���̂܂܂��ƒ����O�̃_�~�[���c��̂ň�U�_�~�[�������B
				//SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
				if (targetDummy01 != nullptr) {
					DeleteGO(targetDummy01);
					targeted = false;
					pl01->SetTarget(targeted);
					isSetTargetDummy = false;
					whichPlayerTargetMe = 0;
				}
				//�����o�Ă�����B
				if (m_soundFlag01 == true) {
					DeleteGO(m_meter);
					//���������B
					DeleteGO(m_cookingSe);
					m_soundFlag01 = false;
				}
				//������悤�ɂ���B
				pl01->StopMove01(false);
			}
		}
		else {
			//�{�^���𗣂�����^�C�}�[��0�ɖ߂�B
			m_hold01 = 0;
			//������悤�ɂ���B
			pl01->StopMove01(false);
			//�����o�Ă�����B
			if (m_soundFlag01 == true) {
				DeleteGO(m_meter);
				//���������B
				DeleteGO(m_cookingSe);
				m_soundFlag01 = false;
			}
		}

		//2P���̏���
		if (g_pad[1]->IsPress(enButtonB) && m_setKitchenNum < 4 && pl02->have <= 0) {
			
			m_hold02++;
			pl02->StopMove01(true);
			pl02->SetMoveSpeed({ 0.0f,0.0f,0.0f });
			////�����o�Ă��Ȃ�������B
			if (m_soundFlag02 == false) {
				m_meter = NewGO<Meter>(0);
				Vector3 pos = m_position;
				pos.x += 250.0f;
				pos.y += 300.0f;
				pos.z += 20.0f;
				m_meter->SetPosition(pos);
				//����炷
				m_cookingSe = NewGO<CSoundSource>(0);
				m_cookingSe->Init(L"Assets/sound/cutting_a_onion_speedy.wav", false);
				m_cookingSe->SetVolume(1.0f);
				m_cookingSe->Play(true);
				m_soundFlag02 = true;
			}
			Vector3 Scale = m_meter->GetScale();
			Scale.x -= 1.4f / 60.0f;
			m_meter->SetScale(Scale);
			if (m_hold02 > m_cookingTime) {
				
				ChangeModel(TypeNo);
				m_isCooked = true;
				m_position.y += 50.0f;
				
				//SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
				if (targetDummy02 != nullptr) {
					DeleteGO(targetDummy02);

					targeted = false;
					pl02->SetTarget(targeted);
					isSetTargetDummy = false;
					whichPlayerTargetMe = 0;
				}
				//�����o�Ă�����B
				if (m_soundFlag02 == true) {
					//���������B
					DeleteGO(m_cookingSe);
					m_soundFlag02 = false;
					DeleteGO(m_meter);
				}
				pl02->StopMove01(false);
			}
		}
		else {
			pl02->StopMove01(false);
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
	
	
	if (whichPlayerGet == 1) {
		if (g_pad[0]->IsTrigger(enButtonA)					//A�{�^����������
			&& state == 1									//���̋�ނ�������Ă���
			&& m_trashCan[0]->GetCanTrash()) {				//�S�~���͎̂Ă�p�ӂ��ł��Ă��邩�i�����I�Ɂj
			isSetOnTrashCan = true;							//�S�~���Ŏ̂Ă鏀��
		}
		if (isSetOnTrashCan == true) {
			DeleteGO(this);
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/dumping.wav", false);
			se->SetVolume(2.0f);
			se->Play(false);
			pl01->have = 0;
			targeted = false;
			pl01->SetTarget(targeted);

			m_trashCan[0]->ChangeMovingState(true);
		}
	}
	if (whichPlayerGet == 2) {
		if (g_pad[1]->IsTrigger(enButtonA)
			&& state == 1
			&& m_trashCan[1]->GetCanTrash()) {
			isSetOnTrashCan = true;
		}
		if (isSetOnTrashCan == true) {
			DeleteGO(this);
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/dumping.wav", false);
			se->SetVolume(2.0f);
			se->Play(false);
			pl02->have = 0;
			targeted = false;
			pl02->SetTarget(targeted);
			m_trashCan[1]->ChangeMovingState(true);
		}
	}
}

void Guzai::Rotation()
{
	//�L�b�`���ɃZ�b�g����Ă���Ƃ��B
	if (put == 1) {

		//��]����
		angle += 2.0f;
		if (angle > 360.0f) {
			angle = 0.0f;
		}
		m_rotation.SetRotationDeg(Vector3::AxisY, angle);

	}
	//�L�b�`���ɃZ�b�g����Ă��Ȃ��Ƃ��B
	else
	{
		//�v���C���[����ނ��������Ƃ��̋�ނ̒Ǐ]��]�B
		if (state == 1) {
			if (whichPlayerGet == 1) {
				//�v���C���[�������Ă�������ɉ�]����̂ŁA�v���C���[�̈ړ����x���Q�Ƃ���B
				Vector3 pl01MSpeed = pl01->GetNormalMoveSpeed();
				angle = atan2(pl01MSpeed.x, pl01MSpeed.z);
				m_rotation.SetRotation(Vector3::AxisY, angle);
			}
			if (whichPlayerGet == 2) {
				Vector3 pl02MSpeed = pl02->GetNormalMoveSpeed();
				angle = atan2(pl02MSpeed.x, pl02MSpeed.z);
				m_rotation.SetRotation(Vector3::AxisY, angle);
			}
		}
		else {
			//�v���C���[�������Ă��Ȃ��Ƃ��͉�]�����Z�b�g�B
			m_rotation = Quaternion::Identity;
		}

	}
}

void Guzai::Update()
{
	//�v���C���[��������Update�֐����X���[
	if (playerGene->GetPlayerGeneState() == true) {
		return;
	}

	Vector3 plPos01 = pl01->GetPosition();
	Vector3 plPos02 = pl02->GetPosition();
	Vector3 kitchen01Pos = ki01->GetKitchenPos();
	Vector3 kitchen02Pos = ki02->GetKitchenPos();

	//��ނ���v���C���[�܂ł̋���
	guzai2Pl01 = (m_position.x - plPos01.x) * (m_position.x - plPos01.x) + (m_position.y - plPos01.y) * (m_position.y - plPos01.y) + (m_position.z - plPos01.z) * (m_position.z - plPos01.z);
	guzai2Pl01 = sqrt(guzai2Pl01);

	//�L�b�`������v���C���[�̋���
	kit2Pl01 = (kitchen01Pos.x - plPos01.x) * (kitchen01Pos.x - plPos01.x) + (kitchen01Pos.y - plPos01.y) * (kitchen01Pos.y - plPos01.y) + (kitchen01Pos.z - plPos01.z) * (kitchen01Pos.z - plPos01.z);
	kit2Pl01 = sqrt(kit2Pl01);

	//��ނ���v���C���[�ւ̋���
	guzai2Pl02 = (m_position.x - plPos02.x) * (m_position.x - plPos02.x) + (m_position.y - plPos02.y) * (m_position.y - plPos02.y) + (m_position.z - plPos02.z) * (m_position.z - plPos02.z);
	guzai2Pl02 = sqrt(guzai2Pl02);

	//�L�b�`������v���C���[�ւ̋���
	kit2Pl02 = (kitchen02Pos.x - plPos02.x) * (kitchen02Pos.x - plPos02.x) + (kitchen02Pos.y - plPos02.y) * (kitchen02Pos.y - plPos02.y) + (kitchen02Pos.z - plPos02.z) * (kitchen02Pos.z - plPos02.z);
	kit2Pl02 = sqrt(kit2Pl02);

	//�g�}�g�ƃI�j�I���ȊO�͒������Ȃ��ł悢�B
	if (TypeNo != 4 && TypeNo != 5) {
		m_isCooked = true;
	}

	TargetingNPopDummy();

	ki01->ChangeGrabState(true);
	ki02->ChangeGrabState(true);

	GrabNPut();

	if (canPutOnGuzaiOkiba) {
		SetGuzaiOkiba();
	}

	canPutOnGuzaiOkiba = true;

	Cooking();

	SetOnTrashCan();

	Rotation();

	//�_�~�[�𓮂����悤
	if (isSetTargetDummy == true && state != 1) {
		if (whichPlayerTargetMe == 1) {
			//SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
			if (targetDummy01 != nullptr) {
				//������̃`�[�Y�̂݁A���̂܂܂��ƃ_�~�[���o�����Ƃ����f�����d�Ȃ��Ă��܂��̂ŏ�������y���W���グ��B
				//if (m_cooking == true && TypeNo == 0) {
				//	Vector3 SetPos = m_position;
				//	SetPos.y += 60.0f;
				//	targetDummy01->SetPosition(SetPos);
				//}

				//��ޒu����u���Ă���Ƃ��̓_�~�[�̈ʒu���グ��
				if (m_guzaiOkibaSet == true) {
					Vector3 SetPos = m_position;
					SetPos.y += 50.0f;
					targetDummy01->SetPosition(SetPos);
				}
				else {
					targetDummy01->SetPosition(m_position);
				}

			}
		}
		if (whichPlayerTargetMe == 2) {
			//SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
			if (targetDummy02 != nullptr) {
				/*if (m_cooking == true && TypeNo == 0) {
					Vector3 SetPos = m_position;
					SetPos.y += 55.0f;
					targetDummy02->SetPosition(SetPos);
				}*/
				if (m_guzaiOkibaSet == true) {
					Vector3 SetPos = m_position;
					SetPos.y += 50.0f;
					targetDummy02->SetPosition(SetPos);
				}
				else {
					targetDummy02->SetPosition(m_position);
				}
			}
		}
	}

	if (returned){
		if (state == 1) {
			if (whichPlayerGet == 1) {
				//��ނ̈ʒu���v���C���[�̏����O�ɂ���B
				Vector3 pl01MSpeed = pl01->GetNormalMoveSpeed();
				pl01MSpeed *= 90.0f;
				plPos01 += pl01MSpeed;
				SetPosition(plPos01);
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/putting_a_book2.wav", false);
				se->SetVolume(2.0f);
				se->Play(false);

				//��ޒu����ɒu������ł��܂��߂Â��ƃ_�~�[���o��悤�ɂ���B
				//SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
				if (targetDummy01 != nullptr) {
					DeleteGO(targetDummy01);
					isSetTargetDummy = false;
					decrementTime = holdTime;
					whichPlayerTargetMe = 0;
				}
			}
			if (whichPlayerGet == 2) {
				//plPos02.y += 100.0f;
				//SetPosition(plPos02);
				Vector3 pl02MSpeed = pl02->GetNormalMoveSpeed();
				pl02MSpeed *= 90.0f;
				plPos02 += pl02MSpeed;
				SetPosition(plPos02);
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/putting_a_book2.wav", false);
				se->SetVolume(2.0f);
				se->Play(false);

				//SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
				if (targetDummy02 != nullptr) {

					DeleteGO(targetDummy02);
					isSetTargetDummy = false;
					decrementTime = holdTime;
					whichPlayerTargetMe = 0;

				}
			}
		}
		returned = false;
	}


	//�L�b�`���ɍڂ��Ă�Ƃ�������Ɖ񂵂Ă݂�
	//if (put == 1) {

	//	//��]����
	//	angle += 2.0f;
	//	if (angle > 360.0f) {
	//		angle = 0.0f;
	//	}
	//	m_rotation.SetRotationDeg(Vector3::AxisY, angle);

	//}


	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	//��ޒu����ɒu����Ă���Ƃ��̈ʒu����
	if (m_guzaiOkibaSet == true) {
		Vector3 SetPos = m_position;
		SetPos.y += 50.0f;
		m_skinModelRender->SetPosition(SetPos);
	}
	else {
		m_skinModelRender->SetPosition(m_position);
	}
}