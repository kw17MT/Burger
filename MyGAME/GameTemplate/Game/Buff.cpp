#include "stdafx.h"
#include "Buff.h"
#include "ModelRender.h"
#include "ObjectGene.h"

Buff::Buff() 
{
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	modeldata.m_fxFilePath = "Assets/shader/model.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_expandConstantBuffer = &g_lig;
	modeldata.m_expandConstantBufferSize = sizeof(g_lig);

	modeldata.m_modelUpAxis = enModelUpAxisY;

	m_skeleton.Init("Assets/modelData/unityChan.tks");
	modeldata.m_skeleton = &m_skeleton;

	model.Init(modeldata);

	Vector3 pos = { 0.0f,100.0f,-500.0f };

	m_charaCon.Init(0.0f, 0.0f, pos);
}

bool Buff::Start()
{
	return true;
}

Vector3 Buff::GetPosition()
{
	Vector3 Pos = m_charaCon.GetPosition();
	return Pos;
}

void Buff::SetPosition(Vector3 pos)
{
	m_charaCon.SetPosition(pos);
}

void Buff::Update()
{
	//�X�P���g�����X�V�B
	m_skeleton.Update(model.GetWorldMatrix());

	if (BuffNo == 1) {
		Vector3 BuffPos = m_charaCon.GetPosition();
		ModelRender* pl01 = FindGO<ModelRender>("player01");
		Vector3 plPos01 = pl01->GetPosition();

		wait--;
		if (wait <= 0) {
			if (state == 0 && put == 0) {
				Vector3 moveSpeed = { 0.0f,0.0f,0.0f };
				time++;
				if (time < 500) {
					moveSpeed.z = 2.0f;
				}
				if (time >= 500 && time < 600) {
					moveSpeed.x = 2.0f;
				}
				if (time >= 600) {
					moveSpeed.z = -2.0f;
				}
				if (BuffPos.z < -1000.0f) {
					time = 0;
					DeleteGO(this);
				}
				m_charaCon.Execute(moveSpeed, 1.0f);
				wait = 0;
			}
		}

		float Buff2Pl = (BuffPos.x - plPos01.x) * (BuffPos.x - plPos01.x) + (BuffPos.y - plPos01.y) * (BuffPos.y - plPos01.y) + (BuffPos.z - plPos01.z) * (BuffPos.z - plPos01.z);
		Buff2Pl = sqrt(Buff2Pl);

		//A�{�^�����������Ƃ��A�v���C���[�͉��������Ă��Ȃ��@100���߂��ʒu�ɂ���B
		if (g_pad[0]->IsTrigger(enButtonA) && pl01->have == 0) {
			if (Buff2Pl < 150.0f) {
				pl01->SetBuffAffect(true);
				DeleteGO(this);
			}
		}
	}
	if (BuffNo == 2) {
		Vector3 BuffPos = m_charaCon.GetPosition();
		ModelRender* pl02 = FindGO<ModelRender>("player02");
		Vector3 plPos02 = pl02->GetPosition();

		wait--;
		if (wait <= 0) {
			if (state == 0 && put == 0) {
				Vector3 moveSpeed = { 0.0f,0.0f,0.0f };
				time++;
				if (time < 500) {
					moveSpeed.z = 2.0f;
				}
				if (time >= 500 && time < 600) {
					moveSpeed.x = -2.0f;
				}
				if (time >= 600) {
					moveSpeed.z = -2.0f;
				}
				if (BuffPos.z < -1000.0f) {
					time = 0;
					DeleteGO(this);
				}
				m_charaCon.Execute(moveSpeed, 1.0f);
				wait = 0;
			}
		}

		float Buff2Pl = (BuffPos.x - plPos02.x) * (BuffPos.x - plPos02.x) + (BuffPos.y - plPos02.y) * (BuffPos.y - plPos02.y) + (BuffPos.z - plPos02.z) * (BuffPos.z - plPos02.z);
		Buff2Pl = sqrt(Buff2Pl);

		//A�{�^�����������Ƃ��A�v���C���[�͉��������Ă��Ȃ��@100���߂��ʒu�ɂ���B
		if (g_pad[1]->IsTrigger(enButtonA) && pl02->have == 0) {
			if (Buff2Pl < 150.0f) {
				pl02->SetBuffAffect(true);
				DeleteGO(this);
			}
		}
	}

	model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);
}