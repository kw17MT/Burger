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

//�f�X�g���N�^
Guzai::~Guzai()
{
	DeleteGO(m_skinModelRender);
}

Vector3 Guzai::GetPosition()
{
	return m_position;
}

void Guzai::SetPosition(Vector3 pos)
{
	m_position = pos;
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
	//std::uniform_int_distribution<int> rand(0, 4);
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
		m_skinModelRender->SetScale(m_scale);
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
	
	//A�{�^�����������Ƃ��A�v���C���[�͉��������Ă��Ȃ��@��苗�����߂��ʒu�ɂ���B
	if (g_pad[0]->IsTrigger(enButtonA)) {
		if (pl01->have == 0 && guzai2Pl01 < 150.0f && targeted == true && put == 0) {
			GetGuzaiOkiba();
			state = 1;
			pl01->have = 1;
			
			whichPlayerGet = 1;


			playerGene->AddNoHavingDishCounter();
		}
	}
	if (g_pad[1]->IsTrigger(enButtonA)) {
		if (pl02->have == 0 && guzai2Pl02 < 150.0f && targeted == true && put == 0) {
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
			plPos01.y += 100.0f;
			SetPosition(plPos01);

			//��ޒu����ɒu������ł��܂��߂Â��ƃ_�~�[���o��悤�ɂ���B
			SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
			if (targetDummy01 != nullptr) {
				DeleteGO(targetDummy01);
				m_scale -= expantionRate;
				//targeted = false;
				//pl01->SetTarget(targeted);
				isSetTargetDummy = false;
				decrementTime = holdTime;
				whichPlayerTargetMe = 0;
			}
			//�^�[�Q�b�g�p�̃_�~�[�������B
			//SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
			//m_scale -= expantionRate;
			//DeleteGO(targetDummy01);

			

		}
		if (whichPlayerGet == 2) {
			plPos02.y += 100.0f;
			SetPosition(plPos02);

			SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
			if (targetDummy02 != nullptr) {

				DeleteGO(targetDummy02);
				m_scale -= expantionRate;
				//targeted = false;
				//pl02->SetTarget(targeted);
				isSetTargetDummy = false;
				decrementTime = holdTime;
				whichPlayerTargetMe = 0;

			}
			//�^�[�Q�b�g�p�̃_�~�[�������B
			//SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
			//m_scale -= expantionRate;
			//DeleteGO(targetDummy02);

			
		}
	}

	//B�{�^���������ăL�b�`�����߂��ɂ�������A���ς܂�Ă��鐔�ɉ����Ă����ꏊ��ς���B
	//�L�b�`�����̃X�^�b�N�����C���N�������g�B�L�b�`�����ŋ�ނ�NewGO�B
	if (g_pad[0]->IsTrigger(enButtonB) && m_cooking == true) {
		if (state == 1 && kit2Pl01 < 100.0f) {
			Kitchen* ki01 = FindGO<Kitchen>("kitchen01");
			//�L�b�`���ɒu������ނ̎�ނ��v���C���[���ɕۑ�
			pl01->GuzaiNo[ki01->GetStackNum()] = TypeNo;
			ki01->PlusStack();

			pl01->have = 0;
		

			//�^�[�Q�e�B���O���Ă�����ނ��^��ł���Œ��͕ʂ̋�ނ��^�[�Q�e�B���O�������Ȃ����߁A�����ŏ������B
			targeted = false;
			pl01->SetTarget(targeted);
			isSetTargetDummy = false;
			decrementTime = holdTime;

			//��ނ̏��������B
			DeleteGO(this);
			//��ނ̃��f���������B
			//DeleteGO(m_skinModelRender);
		}
	}
	if (g_pad[1]->IsTrigger(enButtonB) && m_cooking == true) {
		if (state == 1 && kit2Pl02 < 100.0f) {
			Kitchen* ki02 = FindGO<Kitchen>("kitchen02");

			pl02->GuzaiNo[ki02->GetStackNum()] = TypeNo;
			ki02->PlusStack();

			pl02->have = 0;
			

			targeted = false;
			pl02->SetTarget(targeted);
			isSetTargetDummy = false;
			decrementTime = holdTime;

			DeleteGO(this);
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
				SkinModelRender* targetDummyOnGuzai01 = NewGO<SkinModelRender>(1, "targetdummy01");
				targetDummyOnGuzai01->Init(NowModelPath, nullptr, enModelUpAxisZ, m_position);
				targetDummyOnGuzai01->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				targetDummyOnGuzai01->SetFrontCulling("FrontCulling");
				targetDummyOnGuzai01->SetPosition(m_position);
				m_scale.x += 0.3f; m_scale.y += 0.3f; m_scale.z += 0.3f;
				targetDummyOnGuzai01->SetScale(m_scale);
				isSetTargetDummy = true;
			}
			if (whichPlayerTargetMe == 2) {
				SkinModelRender* targetDummyOnGuzai02 = NewGO<SkinModelRender>(1, "targetdummy02");
				targetDummyOnGuzai02->Init(NowModelPath, nullptr, enModelUpAxisZ, m_position);
				targetDummyOnGuzai02->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				targetDummyOnGuzai02->SetFrontCulling("FrontCulling");
				targetDummyOnGuzai02->SetPosition(m_position);
				m_scale.x += 0.3f; m_scale.y += 0.3f; m_scale.z += 0.3f;
				targetDummyOnGuzai02->SetScale({ m_scale });
				isSetTargetDummy = true;
			}
		}

		//�����Ń^�[�Q�b�g���Ă�����ނ�����ȏ㗣�ꂽ��
		//�_�~�[�������āA�v���C���[����TargetingState��targeted�����̒l�ɖ߂��Ă��B
		if (guzai2Pl01 >= TargetRangeFar && pl01->GetTargetState() == true && targeted == true) {
			if (whichPlayerTargetMe == 1) {
				SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
				if (targetDummy01 != nullptr) {
					decrementTime--;
					if (decrementTime == 0) {
						DeleteGO(targetDummy01);
						m_scale -= expantionRate;
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
				SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
				if (targetDummy02 != nullptr) {
					decrementTime--;
					if (decrementTime == 0) {
						DeleteGO(targetDummy02);
						m_scale -= expantionRate;
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

	//��ނ��v���C���[�Ɏ�����Ă���Ƃ��ɁAB�{�^���������ꂽ��c
	if (g_pad[0]->IsTrigger(enButtonB) && state == 1 && whichPlayerGet == 1) {

		//1P���̋�ޒu����̔ԍ���4�`7�Ȃ̂ŁA���͈̔͂Œ��ׂ�B
		for (int i = 4; i < 8; i++) {

			//��ޒu����ɃZ�b�g�\���ǂ����m�F����B
			if (m_guzaiOkiba->FindKitchenSet(i) == true && m_guzaiOkiba->FindGuzaiSet(i) == false && m_guzaiOkibaSet == false) {

				//�Z�b�g�\�Ȃ�΋�ޒu����ɃZ�b�g���ꂽ���Ƃ�`���A���g�̍��W���Z�b�g���ꂽ��ޒu����ɂ���B
				m_guzaiOkiba->GuzaiSet(i, true);
				m_position = m_guzaiOkiba->GetKitchenPos(i);
				if (m_cooking == true) {
					m_position.y += 60.0f;
				}
				m_guzaiOkibaSet = true;
				m_setKitchenNum = i;
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
	if (g_pad[1]->IsTrigger(enButtonB) && state == 1 && whichPlayerGet == 2) {
		//2P���̋�ޒu����̔ԍ���0�`4�Ȃ̂ŁA���͈̔͂Œ��ׂ�B
		for (int i = 0; i < 4; i++) {
			
			if (m_guzaiOkiba->FindKitchenSet(i) == true && m_guzaiOkiba->FindGuzaiSet(i) == false && m_guzaiOkibaSet == false) {
			
				m_guzaiOkiba->GuzaiSet(i, true);
				m_position = m_guzaiOkiba->GetKitchenPos(i);
				if (m_cooking == true) {
					m_position.y += 60.0f;
				}
			
				m_guzaiOkibaSet = true;
				m_setKitchenNum = i;

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

		playerGene->MinusNoHavingDishCounter();
	}
}

void Guzai::Cooking()
{
	//���g����ޒu����ɃZ�b�g����Ă��āA��������Ă��炸�A�_�~�[���o���Ă���Ƃ��B
	if (m_guzaiOkibaSet == true && m_cooking == false && isSetTargetDummy == true) {
		//1P���̏���
		//1P����B�{�^����������Ă��Ď��g�̃Z�b�g�ꏊ��1P���������ꍇ�c
		if (g_pad[0]->IsPress(enButtonB) && m_setKitchenNum >= 4) {
			//�����Ă��鎞�Ԃ��C���N�������g
			m_hold01++;
			//�����������Ԃ܂ŉ����ꂽ��c
			if (m_hold01 > m_cookingTime) {
				//������̃��f���ɕύX�B
				ChangeModel(TypeNo);
				m_cooking = true;
				m_position.y += 50.0f;
				//���̂܂܂��ƒ����O�̃_�~�[���c��̂ň�U�_�~�[�������B
				SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
				if (targetDummy01 != nullptr) {
					DeleteGO(targetDummy01);
					m_scale -= expantionRate;
					targeted = false;
					pl01->SetTarget(targeted);
					isSetTargetDummy = false;
					whichPlayerTargetMe = 0;
				}
			}
		}
		else {
			//�{�^���𗣂�����^�C�}�[��0�ɖ߂�B
			m_hold01 = 0;
		}

		//2P���̏���
		if (g_pad[1]->IsPress(enButtonB) && m_setKitchenNum < 4) {
			
			m_hold02++;
			
			if (m_hold02 > m_cookingTime) {
				
				ChangeModel(TypeNo);
				m_cooking = true;
				m_position.y += 50.0f;
				
				SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
				if (targetDummy02 != nullptr) {
					DeleteGO(targetDummy02);
					m_scale -= expantionRate;
					targeted = false;
					pl02->SetTarget(targeted);
					isSetTargetDummy = false;
					whichPlayerTargetMe = 0;
				}
			}
		}
		else {
			
			m_hold02 = 0;
		}
	}
}

void Guzai::SetOnTrashCan() {
	if (g_pad[0]->IsTrigger(enButtonB) 
		&& state == 1
		&& m_trashCan[0]->GetCanTrash()) {
		isSetOnTrashCan = true;
	}
	if (isSetOnTrashCan == true) {
		decrementTime--;
		if (decrementTime <= 10) {
			DeleteGO(this);

			pl01->have = 0;
			targeted = false;
			pl01->SetTarget(targeted);
		}
	}

	if (g_pad[1]->IsTrigger(enButtonB) 
		&& state == 1
		&& m_trashCan[1]->GetCanTrash()) {
		isSetOnTrashCan = true;
	}
	if (isSetOnTrashCan == true) {
		decrementTime--;
		if (decrementTime <= 10) {
			DeleteGO(this);

			pl02->have = 0;
			targeted = false;
			pl02->SetTarget(targeted);
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
		m_cooking = true;
	}

	TargetingNPopDummy();

	GrabNPut();

	SetGuzaiOkiba();

	Cooking();

	SetOnTrashCan();

	//�_�~�[�𓮂����悤
	if (isSetTargetDummy == true && state != 1) {
		if (whichPlayerTargetMe == 1) {
			SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
			if (targetDummy01 != nullptr) {
				//������̃`�[�Y�̂݁A���̂܂܂��ƃ_�~�[���o�����Ƃ����f�����d�Ȃ��Ă��܂��̂ŏ�������y���W���グ��B
				if (m_cooking == true && TypeNo == 0) {
					Vector3 SetPos = m_position;
					SetPos.y += 60.0f;
					targetDummy01->SetPosition(SetPos);
				}
				//��ޒu����u���Ă���Ƃ��̓_�~�[�̈ʒu���グ��
				else if (m_guzaiOkibaSet == true) {
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
			SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
			if (targetDummy02 != nullptr) {
				if (m_cooking == true && TypeNo == 0) {
					Vector3 SetPos = m_position;
					SetPos.y += 55.0f;
					targetDummy02->SetPosition(SetPos);
				}
				else if(m_guzaiOkibaSet == true){
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

	//�L�b�`���ɍڂ��Ă�Ƃ�������Ɖ񂵂Ă݂�
	if (put == 1) {

		//��]����
		angle += 2.0f;
		if (angle > 360.0f) {
			angle = 0.0f;
		}
		m_rotation.SetRotationDeg(Vector3::AxisY, angle);

	}


	m_skinModelRender->SetRotation(m_rotation);

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