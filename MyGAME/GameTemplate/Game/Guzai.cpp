#include "stdafx.h"
#include "Guzai.h"
//#include "ModelRender.h"
#include "math.h"
#include "Kitchen.h"
#include "ObjectGene.h"
#include "SpriteRender.h"
#include <ctime>
#include <cstdlib>

#include "PathMove.h"
#include<random>

#include "Player.h"
#include "SkinModelRender.h"

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
	/*DeleteGO(pl01);
	DeleteGO(pl02);
	DeleteGO(ki01);
	DeleteGO(ki02);*/

	/*if (GuzaiNo == 1) {
		SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
		if (targetDummy01 != nullptr) {
			DeleteGO(targetDummy01);
		}
	}
	if (GuzaiNo == 2) {
		SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
		if (targetDummy02 != nullptr) {
			DeleteGO(targetDummy02);
		}
	}*/

	DeleteGO(m_skinModelRender);
}

Vector3 Guzai::GetPosition()
{
	/*Vector3 Pos = m_charaCon.GetPosition();
	return Pos;*/
	return m_position;
}

void Guzai::SetPosition(Vector3 pos)
{
	//m_charaCon.SetPosition(pos);
	m_position = pos;
}


void Guzai::ChangeGuzai(int num)
{
	TypeNo = num;

	switch (TypeNo) {
	case 0:
		//modeldata.m_tkmFilePath = "Assets/modelData/gu/cheese.tkm";
		m_skinModelRender->ChangeModel("Assets/modelData/gu/cheese.tkm");
		NowModelPath = "Assets/modelData/gu/cheese.tkm";
		break;
	case 1:
		//modeldata.m_tkmFilePath = "Assets/modelData/gu/egg.tkm";
		m_skinModelRender->ChangeModel("Assets/modelData/gu/egg.tkm");
		NowModelPath = "Assets/modelData/gu/egg.tkm";
		break;
	case 2:
		//modeldata.m_tkmFilePath = "Assets/modelData/gu/lettuce.tkm";
		m_skinModelRender->ChangeModel("Assets/modelData/gu/lettuce.tkm");
		NowModelPath = "Assets/modelData/gu/lettuce.tkm";
		break;
	case 3:
		//modeldata.m_tkmFilePath = "Assets/modelData/gu/patty.tkm";
		m_skinModelRender->ChangeModel("Assets/modelData/gu/patty.tkm");
		NowModelPath = "Assets/modelData/gu/patty.tkm";
		break;
	case 4:
		//modeldata.m_tkmFilePath = "Assets/modelData/gu/tomato.tkm";
		m_skinModelRender->ChangeModel("Assets/modelData/gu/tomato.tkm");
		NowModelPath = "Assets/modelData/gu/tomato.tkm";
		break;
	}
	
	m_skinModelRender->SetNewModel();
}

void Guzai::Move()
{
	//Vector3 GuzaiPos = m_charaCon.GetPosition();

	//TODO ��ނ̈ړ��B
	/*if (GuzaiNo == 1) {
		//������Ă��Ȃ��@���@��x���u����Ă��Ȃ�
		if (state == 0 && put == 0) {
			Vector3 moveSpeed = { 0.0f,0.0f,0.0f };
			
			timer++;
			if (timer < 500) {
				moveSpeed.z = 2.0f;
			}
			if (timer >= 500 && timer < 600) {
				moveSpeed.x = 2.0f;
			}
			if (timer >= 600) {
				moveSpeed.z = -2.0f;
			}
			//TODO �����ŋ�ނ��폜���Ă�B
			if (GuzaiPos.z < -850.0f) {
				timer = 0;
				DeleteGO(this);
				Guzai* targetdummy01 = FindGO<Guzai>("targetdummy01");
				if (targetdummy01 != nullptr) {
					DeleteGO(targetdummy01);
				}
			}
			m_charaCon.Execute(moveSpeed, 1.0f);
		}
	}
	if (GuzaiNo == 2) {
		//������Ă��Ȃ��@���@��x���u����Ă��Ȃ�
		if (state == 0 && put == 0) {
			Vector3 moveSpeed = { 0.0f,0.0f,0.0f };
			timer++;
			if (timer < 500) {
				moveSpeed.z = 2.0f;
			}
			if (timer >= 500 && timer < 600) {
				moveSpeed.x = -2.0f;
			}
			if (timer >= 600) {
				moveSpeed.z = -2.0f;
			}
			if (GuzaiPos.z < -850.0f) {
				timer = 0;
				DeleteGO(this);
			}
			m_charaCon.Execute(moveSpeed, 1.0f);
		}
	}*/

	//������Ă��Ȃ��@���@��x���u����Ă��Ȃ�
	if (state == 0 && put == 0) {
		//�ړ�������B
		/*m_charaCon.*/SetPosition(m_pathMove.get()->Move());
		//�Ō�̃|�C���g�܂œ��B������B
		if (m_pathMove.get()->GetIsFinalPoint())
		{
			//�폜����B
			DeleteGO(this);
			//DeleteGO(m_skinModelRender);
		}
	}
}

bool Guzai::Start()
{
	pl01 = FindGO<Player/*ModelRender*/>("player01");
	pl02 = FindGO<Player/*ModelRender*/>("player02");
	ki01 = FindGO<Kitchen>("kitchen01");
	ki02 = FindGO<Kitchen>("kitchen02");

	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/gu/cheese.tkm",nullptr, enModelUpAxisZ, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	//m_skinModelRender->InitLight(g_lig);

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<int> rand(0, 4);

	TypeNo = rand(mt);

	////�����łǂ̋�ނ�����Ă��邩�����߂�B
	//std::srand(time(NULL));
	//TypeNo = rand() % 5;

	switch (TypeNo) {
	case 0:
		//modeldata.m_tkmFilePath = "Assets/modelData/gu/cheese.tkm";
		m_skinModelRender->ChangeModel("Assets/modelData/gu/cheese.tkm");
		NowModelPath = "Assets/modelData/gu/cheese.tkm";
		break;
	case 1:
		//modeldata.m_tkmFilePath = "Assets/modelData/gu/egg.tkm";
		m_skinModelRender->ChangeModel("Assets/modelData/gu/egg.tkm");
		NowModelPath = "Assets/modelData/gu/egg.tkm";
		break;
	case 2:
		//modeldata.m_tkmFilePath = "Assets/modelData/gu/lettuce.tkm";
		m_skinModelRender->ChangeModel("Assets/modelData/gu/lettuce.tkm");
		NowModelPath = "Assets/modelData/gu/lettuce.tkm";
		break;
	case 3:
		//modeldata.m_tkmFilePath = "Assets/modelData/gu/patty.tkm";
		m_skinModelRender->ChangeModel("Assets/modelData/gu/patty.tkm");
		NowModelPath = "Assets/modelData/gu/patty.tkm";
		break;
	case 4:
		//modeldata.m_tkmFilePath = "Assets/modelData/gu/tomato.tkm";
		m_skinModelRender->ChangeModel("Assets/modelData/gu/tomato.tkm");
		NowModelPath = "Assets/modelData/gu/tomato.tkm";
		break;
	}


	m_skinModelRender->SetNewModel();

	//modeldata.m_fxFilePath = "Assets/shader/model.fx";

	//modeldata.m_vsEntryPointFunc = "VSMain";
	//modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	//modeldata.m_expandConstantBuffer = &g_lig;
	//modeldata.m_expandConstantBufferSize = sizeof(g_lig);

	//modeldata.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//modeldata.m_modelUpAxis = enModelUpAxisY;

	//model.Init(modeldata);

	//Vector3 pos = { 0.0f,0.0f,-1000.0f };

	//m_charaCon.Init(0.0f, 0.0f, pos);



	m_pathMove = std::make_unique<PathMove>();
	m_pathMove.get()->Init(m_position/*m_charaCon.GetPosition()*/, MOVESPEED, enNormalLane, GuzaiNo);


	return true;
}

void Guzai::GrabNPut()
{
	if (GuzaiNo == 1) {
		Vector3 plPos = pl01->GetPosition();

		//A�{�^�����������Ƃ��A�v���C���[�͉��������Ă��Ȃ��@��苗�����߂��ʒu�ɂ���B
		if (g_pad[0]->IsTrigger(enButtonA)) {
			if (pl01->have == 0 && guzai2Pl < 150.0f && targeted == true) {
				state = 1;
				pl01->have = 1;
			}
		}
		//������Ă������ނ̈ʒu���v���C���[�̏�ɂ���B
		if (state == 1) {
			plPos.y += 100.0f;
			SetPosition(plPos);

			//�^�[�Q�b�g�p�̃_�~�[�������B
			SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
			DeleteGO(targetDummy01);
		}

		//B�{�^���������ăL�b�`�����߂��ɂ�������A���ς܂�Ă��鐔�ɉ����Ă����ꏊ��ς���B
		//�L�b�`�����̃X�^�b�N�����C���N�������g�B�L�b�`�����ŋ�ނ�NewGO�B
		if (g_pad[0]->IsTrigger(enButtonB)) {
			if (state == 1 && kit2Pl < 100.0f) {
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
	}

	if (GuzaiNo == 2) {
		Vector3 plPos = pl02->GetPosition();

		//A�{�^�����������Ƃ��A�v���C���[�͉��������Ă��Ȃ��@100���߂��ʒu�ɂ���B
		if (g_pad[1]->IsTrigger(enButtonA)) {
			if (pl02->have == 0 && guzai2Pl < 150.0f && targeted == true) {
				state = 1;
				pl02->have = 1;
			}
		}
		//������Ă������ނ̈ʒu���v���C���[�̏�ɂ���B
		if (state == 1) {
			plPos.y += 100.0f;
			SetPosition(plPos);

			//�^�[�Q�b�g�p�̃_�~�[�������B
			SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
			DeleteGO(targetDummy02);
		}

		//B�{�^���������ăL�b�`�����߂��ɂ�������A���ς܂�Ă��鐔�ɉ����Ă����ꏊ��ς���B
		//�L�b�`�����̃X�^�b�N�����C���N�������g�B�L�b�`�����ŋ�ނ�NewGO�B
		if (g_pad[1]->IsTrigger(enButtonB)) {
			if (state == 1 && kit2Pl < 100.0f) {
				Kitchen* ki02 = FindGO<Kitchen>("kitchen02");
				//�L�b�`���ɒu������ނ̎�ނ��v���C���[���ɕۑ�
				pl02->GuzaiNo[ki02->GetStackNum()] = TypeNo;
				ki02->PlusStack();

				pl02->have = 0;

				//�^�[�Q�e�B���O���Ă�����ނ��^��ł���Œ��͕ʂ̋�ނ��^�[�Q�e�B���O�������Ȃ����߁A�����ŏ������B
				targeted = false;
				pl02->SetTarget(targeted);
				isSetTargetDummy = false;
				decrementTime = holdTime;

				//��ނ̏��������B
				DeleteGO(this);
				//��ނ̃��f���������B
				//DeleteGO(m_skinModelRender);
			}
		}
	}
}

void Guzai::TargetingNPopDummy()
{
	//Vector3 GuzaiPos = m_charaCon.GetPosition();

	if (GuzaiNo == 1) {
		//��ނƂ̋��������ȉ��@�Ł@�v���C���[�͉������b�N���Ă��Ȃ�������B
			//�߂��̋�ނ��^�[�Q�b�g���A�v���C���[�̃^�[�Q�b�g��Ԃ�TRUE�ɁB
		if (guzai2Pl < TargetRangeNear && pl01->GetTargetState() == false) {
			targeted = true;
			pl01->SetTarget(targeted);
		}
		//�^�[�Q�b�g������ނ��_�~�[���o���Ă��Ȃ�������B
		//�����傫���_�~�[����ނƔ��悤�ɏo���B�i�F�͌�Ő^�����ɂ���̂łȂ�ł������j
		if (targeted == 1 && isSetTargetDummy == false) {
			SkinModelRender* targetDummyOnGuzai01 = NewGO<SkinModelRender>(1, "targetdummy01");
			targetDummyOnGuzai01->Init(NowModelPath, nullptr, enModelUpAxisZ, m_position);
			targetDummyOnGuzai01->InitShader("Assets/shader/model.fx", "VSMain", "FrontCulling", DXGI_FORMAT_R32G32B32A32_FLOAT);
			//targetdummyOnGuzai01->modeldata.m_psEntryPointFunc = "FrontCulling";
			targetDummyOnGuzai01->SetPosition(m_position/*GuzaiPos*/);
			targetDummyOnGuzai01->SetScale({ 1.3f,1.3f,1.3f });
			
			isSetTargetDummy = true;

		}

		//�����ň��ȏ㗣��ăv���C���[�͉�������^�[�Q�b�g���Ă�����iif���̌��̏����͕ʂ̋�ނɉe����^����̂�h�����߁B
		//�_�~�[�������āA�v���C���[����TargetingState��targeted�����̒l�ɖ߂��Ă��B
		if (guzai2Pl >= TargetRangeFar && pl01->GetTargetState() == true && targeted == true) {
			SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
			if (targetDummy01 != nullptr) {
				decrementTime--;
				if (decrementTime == 0) {
					DeleteGO(targetDummy01);
					//DeleteGO(sp01);
					targeted = false;
					pl01->SetTarget(targeted);
					isSetTargetDummy = false;
					decrementTime = holdTime;
				}
			}
		}
	}
	if (GuzaiNo == 2) {
		//��ނƂ̋��������ȉ��@�Ł@�v���C���[�͉������b�N���Ă��Ȃ�������B
			//�߂��̋�ނ��^�[�Q�b�g���A�v���C���[�̃^�[�Q�b�g��Ԃ�TRUE�ɁB
		if (guzai2Pl < TargetRangeNear && pl02->GetTargetState() == false) {
			targeted = true;
			pl02->SetTarget(targeted);
		}
		//�^�[�Q�b�g������ނ��_�~�[���o���Ă��Ȃ�������B
		//�����傫���_�~�[����ނƔ��悤�ɏo���B�i�F�͌�Ő^�����ɂ���̂łȂ�ł������j
		if (targeted == 1 && isSetTargetDummy == false) {
			SkinModelRender* targetDummyOnGuzai02 = NewGO<SkinModelRender>(1, "targetdummy02");
			targetDummyOnGuzai02->Init(NowModelPath, nullptr, enModelUpAxisZ, m_position);
			targetDummyOnGuzai02->InitShader("Assets/shader/model.fx", "VSMain", "FrontCulling", DXGI_FORMAT_R32G32B32A32_FLOAT);
			//targetdummyOnGuzai02->modeldata.m_psEntryPointFunc = "FrontCulling";
			targetDummyOnGuzai02->SetPosition(m_position/*GuzaiPos*/);
			targetDummyOnGuzai02->SetScale({ 1.3f,1.3f,1.3f });
			isSetTargetDummy = true;
		}

		//�����ň��ȏ㗣��ăv���C���[�͉�������^�[�Q�b�g���Ă�����iif���̌��̏����͕ʂ̋�ނɉe����^����̂�h�����߁B
		//�_�~�[�������āA�v���C���[����TargetingState��targeted�����̒l�ɖ߂��Ă��B
		if (guzai2Pl >= TargetRangeFar && pl02->GetTargetState() == true && targeted == true) {
			SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
			if (targetDummy02 != nullptr) {
				decrementTime--;
				if (decrementTime == 0) {
					DeleteGO(targetDummy02);
					targeted = false;
					pl02->SetTarget(targeted);
					isSetTargetDummy = false;
					decrementTime = holdTime;
				}
			}
		}
	}
}

void Guzai::Update()
{
	if (GuzaiNo == 1) {
		Vector3 plPos = pl01->GetPosition();
		//Vector3 GuzaiPos = m_charaCon.GetPosition();
		Vector3 kitchen01Pos = ki01->GetKitchenPos();

		//��ނ���v���C���[�܂ł̋���
		guzai2Pl = (m_position/*GuzaiPos*/.x - plPos.x) * (/*GuzaiPos*/m_position.x - plPos.x) + (/*GuzaiPos*/m_position.y - plPos.y) * (/*GuzaiPos*/m_position.y - plPos.y) + (/*GuzaiPos*/m_position.z - plPos.z) * (/*GuzaiPos*/m_position.z - plPos.z);
		guzai2Pl = sqrt(guzai2Pl);

		//�L�b�`������v���C���[�̋���
		kit2Pl = (kitchen01Pos.x - plPos.x) * (kitchen01Pos.x - plPos.x) + (kitchen01Pos.y - plPos.y) * (kitchen01Pos.y - plPos.y) + (kitchen01Pos.z - plPos.z) * (kitchen01Pos.z - plPos.z);
		kit2Pl = sqrt(kit2Pl);
		
		if (isSetFirstPos == false) {
			ObjectGene* gene01 = FindGO<ObjectGene>("gene01");
			SetPosition(gene01->GetPosition());

			isSetFirstPos = true;
		}

		TargetingNPopDummy();

		//PopTargetingIcon();

		GrabNPut();

		Move();
		
		//�_�~�[�𓮂����悤
		if (isSetTargetDummy == true && state != 1) {
			SkinModelRender* targetDummy01 = FindGO<SkinModelRender>("targetdummy01");
			if (targetDummy01 != nullptr) {
				targetDummy01->SetPosition(m_position/*GuzaiPos*/);
			}
		}
	}

	if (GuzaiNo == 2) {
		Vector3 plPos = pl02->GetPosition();
		//Vector3 GuzaiPos = m_charaCon.GetPosition();
		Vector3 kitchen02Pos = ki02->GetKitchenPos();

		//��ނ���v���C���[�ւ̋���
		guzai2Pl = (m_position/*GuzaiPos*/.x - plPos.x) * (/*GuzaiPos*/m_position.x - plPos.x) + (/*GuzaiPos*/m_position.y - plPos.y) * (/*GuzaiPos*/m_position.y - plPos.y) + (/*GuzaiPos*/m_position.z - plPos.z) * (/*GuzaiPos*/m_position.z - plPos.z);
		guzai2Pl = sqrt(guzai2Pl);

		//�L�b�`������v���C���[�ւ̋���
		kit2Pl = (kitchen02Pos.x - plPos.x) * (kitchen02Pos.x - plPos.x) + (kitchen02Pos.y - plPos.y) * (kitchen02Pos.y - plPos.y) + (kitchen02Pos.z - plPos.z) * (kitchen02Pos.z - plPos.z);
		kit2Pl = sqrt(kit2Pl);

		if (isSetFirstPos == false) {
			ObjectGene* gene02 = FindGO<ObjectGene>("gene02");
			SetPosition(gene02->GetPosition());
			isSetFirstPos = true;
		}

		TargetingNPopDummy();
		
		GrabNPut();

		Move();

		//�_�~�[�𓮂����悤
		if (isSetTargetDummy == true && state != 1) {
			SkinModelRender* targetDummy02 = FindGO<SkinModelRender>("targetdummy02");
			if (targetDummy02 != nullptr) {
				targetDummy02->SetPosition(m_position/*GuzaiPos*/);
			}
		}
	}
	//model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, GuzaiScale);
	m_skinModelRender->SetPosition(m_position);
}