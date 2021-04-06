#include "stdafx.h"
#include "ModelRender.h"
#include "Guzai.h"
#include "FontRender.h"

ModelRender::ModelRender()
{
	
}

ModelRender::~ModelRender()
{
	
}

bool ModelRender::Start()
{
	//���f���̏���������
	//�������p�f�[�^�̍\�z
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
	//�������I���//

	//�L�����R���̏�����
	m_charaCon.Init(40.0f, 100.0f, m_position);

	//��ރi���o�[�z��̂��ׂĂ̗v�f��9�ŏ�����
	for (int i = 0; i < 10; i++) {
		GuzaiNo[i] = 9;
	}

	return true;
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

//Vector3 ModelRender::GetPosition()
//{
//	Vector3 Pos = m_charaCon.GetPosition();
//	return Pos;
//}
Vector3 ModelRender::GetPosition()
{
	return m_position;
}

void ModelRender::Update()
{
	//�X�P���g�����X�V�B
	m_skeleton.Update(model.GetWorldMatrix());

	//P1�̏���
	if (playerNo == 1) {
		
		//��]����
		
		//���g�̏�ƉE���`(�����낵�Ȃ̂�)
		Vector3 frontDirP1 = { 0.0f,0.0f,1.0f };
		frontDirP1.Normalize();
		Vector3 rightDirP1 = { 1.0f,0.0f,0.0f };
		rightDirP1.Normalize();
		
		//��]���̌���
		Vector3 AxisYP1;
		AxisYP1.Cross(frontDirP1, rightDirP1);

		//���������Ɖ��s�����ւ̓��͂��󂯎��
		float LStickXP1 = g_pad[0]->GetLStickXF() * 1.0f;
		float LStickZP1 = g_pad[0]->GetLStickYF() * -1.0f; //���s�����̋t�]��-1.0f���|���ĕ␳

		//��]�����邩�ǂ����̃`�F�b�N(�X�e�B�b�N�̓��͂����邩�ǂ������`�F�b�N)
		if (fabsf(LStickXP1) < 0.001f && fabsf(LStickZP1) < 0.001f) {
			//return; //return����ƈȉ��̏�����������΂����Update�̍Ō�ɂ����Ă��܂��B
		}
		else {
			//��̓��͒l�������p�����߂�(���W�A���p)
			angle = atan2(LStickXP1, LStickZP1);
			//�c���܂��̉�]�����߂�(���W�A���p�������ɓn������SetRotation)
			m_rotation.SetRotation(AxisYP1, -angle);
		}
		
		//�o�t�̌��ʂ����Ă��邩�m�F��ړ����x�����߁A�ړ�������B
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

		/*if (setPos == 0) {
			Vector3 Pos1 = { 900.0f, 0.0f, 0.0f };
			m_charaCon.SetPosition(Pos1);
			setPos = 1;
		}*/
	}
	//P2�̏���
	if (playerNo == 2) {
		
		//��]����
		
		//���g�̏�ƉE���`(�����낵�Ȃ̂�)
		Vector3 frontDirP2 = { 0.0f,0.0f,1.0f };
		frontDirP2.Normalize();
		Vector3 rightDirP2 = { 1.0f,0.0f,0.0f };
		rightDirP2.Normalize();
		
		//��]���̌���
		Vector3 AxisYP2;
		AxisYP2.Cross(frontDirP2, rightDirP2);
		
		//���������Ɖ��s�����ւ̓��͂��󂯎��
		float LStickXP2 = g_pad[1]->GetLStickXF() * 1.0f;
		float LStickZP2 = g_pad[1]->GetLStickYF() * -1.0f; //���s�����̋t�]��-1.0f���|���ĕ␳

		//��]�����邩�ǂ����̃`�F�b�N(�X�e�B�b�N�̓��͂����邩�ǂ������`�F�b�N)
		if (fabsf(LStickXP2) < 0.001f && fabsf(LStickZP2) < 0.001f) {
			//return; //return����ƈȉ��̏�����������΂����Update�̍Ō�ɂ����Ă��܂��B
		}
		else {
			//��̓��͒l�������p�����߂�(���W�A���p)
			angle = atan2(LStickXP2, LStickZP2);
			//�c���܂��̉�]�����߂�(���W�A���p�������ɓn������SetRotation)
			m_rotation.SetRotation(AxisYP2, -angle);
		}
		
		//�o�t�̌��ʂ����Ă��邩�m�F��ړ����x�����߁A�ړ�������B
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

		/*if (setPos == 0) {
			Vector3 Pos2 = { -900.0f, 0.0f, 0.0f };
			m_charaCon.SetPosition(Pos2);
			setPos = 1;
		}*/
	}

	//Vector3 plPos = m_charaCon.GetPosition();
	
	m_position = m_charaCon.Execute(moveSpeed, 1.0f);

	model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

