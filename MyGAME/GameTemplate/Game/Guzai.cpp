#include "stdafx.h"
#include "Guzai.h"
#include "math.h"
#include "Kitchen.h"
#include "GuzaiGene.h"
//#include "PathMove.h"
#include "SkinModelRender.h"
#include "Player.h"
#include "PlayerGene.h"
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
		/*m_skinModelRender->ChangeModel("Assets/modelData/gu/egg.tkm");
		NowModelPath = "Assets/modelData/gu/egg.tkm";*/
		m_skinModelRender->ChangeModel("Assets/modelData/food/egg.tkm");
		NowModelPath = "Assets/modelData/food/egg.tkm";
		break;
	case 2:
		m_skinModelRender->ChangeModel("Assets/modelData/gu/lettuce.tkm");
		NowModelPath = "Assets/modelData/gu/lettuce.tkm";
		break;
	case 3:
		m_skinModelRender->ChangeModel("Assets/modelData/gu/patty.tkm");
		NowModelPath = "Assets/modelData/gu/patty.tkm";
		break;
	case 4:
		//���f�������ւ�
		m_skinModelRender->ChangeModel("Assets/modelData/food/tomato.tkm");
		m_skinModelRender->SetScale(m_scale);
		NowModelPath = "Assets/modelData/food/tomato.tkm";
		break;
	}
	
	m_skinModelRender->SetNewModel();
}

void Guzai::Move()
{
	////������Ă��Ȃ��@���@��x���u����Ă��Ȃ�
	//if (state == 0 && put == 0) {
	//	//�ړ�������B
	//	SetPosition(m_pathMove.get()->Move());
	//	//�Ō�̃|�C���g�܂œ��B������B
	//	if (m_pathMove.get()->GetIsFinalPoint())
	//	{
	//		////�폜����B
	//		//DeleteGO(this);
	//	}
	//}
}

bool Guzai::Start()
{
	pl01 = FindGO<Player>("player01");
	pl02 = FindGO<Player>("player02");
	ki01 = FindGO<Kitchen>("kitchen01");
	ki02 = FindGO<Kitchen>("kitchen02");
	playerGene = FindGO<PlayerGene>("playerGene");
	m_guzaiGene = FindGO<GuzaiGene>("guzaiGene");

	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/gu/cheese.tkm",nullptr, enModelUpAxisZ, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<int> rand(0, 4);

	TypeNo = rand(mt);

	switch (TypeNo) {
	case 0:
		/*m_skinModelRender->ChangeModel("Assets/modelData/gu/cheese.tkm");
		NowModelPath = "Assets/modelData/gu/cheese.tkm";*/
		m_skinModelRender->ChangeModel("Assets/modelData/food/cheese.tkm");
		NowModelPath = "Assets/modelData/food/cheese.tkm";
		break;
	case 1:
		/*m_skinModelRender->ChangeModel("Assets/modelData/gu/egg.tkm");
		NowModelPath = "Assets/modelData/gu/egg.tkm";*/
		m_skinModelRender->ChangeModel("Assets/modelData/food/egg.tkm");
		NowModelPath = "Assets/modelData/food/egg.tkm";
		break;
	case 2:
		m_skinModelRender->ChangeModel("Assets/modelData/gu/lettuce.tkm");
		NowModelPath = "Assets/modelData/gu/lettuce.tkm";
		break;
	case 3:
		m_skinModelRender->ChangeModel("Assets/modelData/gu/patty.tkm");
		NowModelPath = "Assets/modelData/gu/patty.tkm";
		break;
	case 4:
		//���f�������ւ�
		/*m_skinModelRender->ChangeModel("Assets/modelData/gu/tomato.tkm");
		NowModelPath = "Assets/modelData/gu/tomato.tkm";*/
		m_skinModelRender->ChangeModel("Assets/modelData/food/tomato.tkm");
		m_skinModelRender->SetScale(m_scale);
		NowModelPath = "Assets/modelData/food/tomato.tkm";
		break;
	}

	m_skinModelRender->SetNewModel();

	//m_pathMove = std::make_unique<PathMove>();
	//m_pathMove.get()->Init(m_position, MOVESPEED, enNormalLane);

	return true;
}

void Guzai::GrabNPut()
{
	Vector3 plPos01 = pl01->GetPosition();
	Vector3 plPos02 = pl02->GetPosition();
	
	//A�{�^�����������Ƃ��A�v���C���[�͉��������Ă��Ȃ��@��苗�����߂��ʒu�ɂ���B
	if (g_pad[0]->IsTrigger(enButtonA)) {
		if (pl01->have == 0 && guzai2Pl01 < 150.0f && targeted == true) {
			state = 1;
			pl01->have = 1;
			whichPlayerGet = 1;

			////�ǂ�����Ƃ�����������ɘA������A���v���C���[�ŋ��L
			//m_guzaiGene->RegisterEmptyDishNumber(dishNumber);
			////�t�B�[���h���炢����ނ��Ƃ��Ă��邩������
			//m_guzaiGene->AddEmptyDishCounter();

			playerGene->AddNoHavingDishCounter();
		}
	}
	if (g_pad[1]->IsTrigger(enButtonA)) {
		if (pl02->have == 0 && guzai2Pl02 < 150.0f && targeted == true) {
			state = 1;
			pl02->have = 1;
			whichPlayerGet = 2;

			/*m_guzaiGene->RegisterEmptyDishNumber(dishNumber);
			m_guzaiGene->AddEmptyDishCounter();*/

			playerGene->AddNoHavingDishCounter();
		}
	}

	//������Ă������ނ̈ʒu���v���C���[�̏�ɂ���B
	if (state == 1) {
		if (whichPlayerGet == 1) {
			plPos01.y += 100.0f;
			SetPosition(plPos01);

			//�^�[�Q�b�g�p�̃_�~�[�������B
			SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
			m_scale -= expantionRate;
			DeleteGO(targetDummy01);

			

		}
		if (whichPlayerGet == 2) {
			plPos02.y += 100.0f;
			SetPosition(plPos02);

			//�^�[�Q�b�g�p�̃_�~�[�������B
			SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
			m_scale -= expantionRate;
			DeleteGO(targetDummy02);

			
		}
	}

	//B�{�^���������ăL�b�`�����߂��ɂ�������A���ς܂�Ă��鐔�ɉ����Ă����ꏊ��ς���B
	//�L�b�`�����̃X�^�b�N�����C���N�������g�B�L�b�`�����ŋ�ނ�NewGO�B
	if (g_pad[0]->IsTrigger(enButtonB)) {
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
	if (g_pad[1]->IsTrigger(enButtonB)) {
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
		if (guzai2Pl01 < TargetRangeNear && pl01->GetTargetState() == false && !targeted) {
			whichPlayerTargetMe = 1;
			targeted = true;
			pl01->SetTarget(targeted);
		}
		if (guzai2Pl02 < TargetRangeNear && pl02->GetTargetState() == false && !targeted) {
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
				targetDummyOnGuzai01->InitShader("Assets/shader/model.fx", "VSMain", "FrontCulling", DXGI_FORMAT_R32G32B32A32_FLOAT);
				//targetdummyOnGuzai01->modeldata.m_psEntryPointFunc = "FrontCulling";
				targetDummyOnGuzai01->SetPosition(m_position);
				m_scale.x += 0.3f; m_scale.y += 0.3f; m_scale.z += 0.3f;
				targetDummyOnGuzai01->SetScale(m_scale/*{ 1.3f,1.3f,1.3f }*/);

				isSetTargetDummy = true;
			}
			if (whichPlayerTargetMe == 2) {
				SkinModelRender* targetDummyOnGuzai02 = NewGO<SkinModelRender>(1, "targetdummy02");
				targetDummyOnGuzai02->Init(NowModelPath, nullptr, enModelUpAxisZ, m_position);
				targetDummyOnGuzai02->InitShader("Assets/shader/model.fx", "VSMain", "FrontCulling", DXGI_FORMAT_R32G32B32A32_FLOAT);
				//targetdummyOnGuzai02->modeldata.m_psEntryPointFunc = "FrontCulling";
				targetDummyOnGuzai02->SetPosition(m_position);
				m_scale.x += 0.3f; m_scale.y += 0.3f; m_scale.z += 0.3f;
				targetDummyOnGuzai02->SetScale({ m_scale/*1.3f,1.3f,1.3f*/ });
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

	
	TargetingNPopDummy();

	GrabNPut();

	Move();

	//�_�~�[�𓮂����悤
	if (isSetTargetDummy == true && state != 1) {
		if (whichPlayerTargetMe == 1) {
			SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
			if (targetDummy01 != nullptr) {
				targetDummy01->SetPosition(m_position);
			}
		}
		if (whichPlayerTargetMe == 2) {
			SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
			if (targetDummy02 != nullptr) {
				targetDummy02->SetPosition(m_position);
			}
		}
	}

	m_skinModelRender->SetPosition(m_position);
}