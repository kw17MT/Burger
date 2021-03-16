#include "stdafx.h"
#include "ModelRender.h"
#include "Guzai.h"


ModelRender::ModelRender()
{
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	modeldata.m_fxFilePath = "Assets/shader/model.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_modelUpAxis = enModelUpAxisZ;

	modeldata.m_expandConstantBuffer = &g_lig;
	modeldata.m_expandConstantBufferSize = sizeof(g_lig);

	m_skeleton.Init("Assets/modelData/unityChan.tks");
	modeldata.m_skeleton = &m_skeleton;

	model.Init(modeldata);

	//��ރi���o�[�z��̂��ׂĂ̗v�f��9�ŏ�����
	m_charaCon.Init(40.0f, 100.0f, g_vec3Zero);
	for (int i = 0; i < 10; i++) {
		GuzaiNo[i] = 9;
	}
}

/// <summary>
/// ���f����ύX����Ƃ��Ɏg��
/// �ύX�������Ȃ��ӏ���nullptr
/// </summary>
/// <param name="ModelPath">���f���̃p�X</param>
/// <param name="ShaderPath">�V�F�[�_�[�̃p�X</param>
void ModelRender::GiveData(const char* ModelPath, const char* ShaderPath)
{
	ModelInitData modeldata;

	modeldata.m_tkmFilePath = ModelPath;
	
	modeldata.m_fxFilePath = "Assets/shader/model.fx";
	if (ShaderPath != nullptr) {
		modeldata.m_fxFilePath = ShaderPath;
	}

	model.Init(modeldata);
}

void ModelRender::SetGuzaiNo9()
{
	for (int i = 0;i < 10;i++)
	{
		GuzaiNo[i] = 9;
	}
}

Vector3 ModelRender::GetPosition()
{
	Vector3 Pos = m_charaCon.GetPosition();
	return Pos;
}

void ModelRender::Update()
{
	//�X�P���g�����X�V�B
	m_skeleton.Update(model.GetWorldMatrix());

	Vector3 moveSpeed;

	//�o�t�̌��ʂ����Ă��邩�m�F��ړ����x�����߁A�ړ�������B
	if (playerNo == 1) {
		if (Buff == true) {
			moveSpeed.x = g_pad[0]->GetLStickXF() * -20.0f;
			moveSpeed.z = g_pad[0]->GetLStickYF() * -20.0f;

			BuffTime--;
			if (BuffTime == 0) {
				Buff = false;
				BuffTime = 120;
			}
		}
		if(Buff == false) {
			moveSpeed.x = g_pad[0]->GetLStickXF() * -10.0f;
			moveSpeed.z = g_pad[0]->GetLStickYF() * -10.0f;
		}

		if (setPos == 0) {
			Vector3 Pos1 = { 900.0f, 0.0f, 0.0f };
			m_charaCon.SetPosition(Pos1);
			setPos = 1;
		}
	}
	if (playerNo == 2) {
		if (Buff == true) {
			moveSpeed.x = g_pad[1]->GetLStickXF() * -20.0f;
			moveSpeed.z = g_pad[1]->GetLStickYF() * -20.0f;

			BuffTime--;
			if (BuffTime == 0) {
				Buff = false;
				BuffTime = 120;
			}
		}
		if (Buff == false) {
			moveSpeed.x = g_pad[1]->GetLStickXF() * -10.0f;
			moveSpeed.z = g_pad[1]->GetLStickYF() * -10.0f;
		}

		if (setPos == 0) {
			Vector3 Pos2 = { -900.0f, 0.0f, 0.0f };
			m_charaCon.SetPosition(Pos2);
			setPos = 1;
		}
	}

	Vector3 plPos = m_charaCon.GetPosition();

	m_charaCon.Execute(moveSpeed, 1.0f);
	model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);
}

