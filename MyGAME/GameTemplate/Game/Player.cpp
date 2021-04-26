#include "stdafx.h"
#include "Player.h"
#include "Guzai.h"
#include "FontRender.h"


#include "PathFactory.h"
#include "DeBuff.h"

#include "GameDirector.h"
#include "PopUp2D.h"

#include "SkinModelRender.h"

namespace
{
	float DEBUFFDISTANCE = 100.0f * 100.0f;
}

Player::Player()
{

}

Player::~Player()
{
	DeleteGO(m_popUp);
}

bool Player::Start()
{
	//
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init(
		"Assets/modelData/unityChan.tkm",
		"Assets/modelData/unityChan.tks",
		enModelUpAxisZ,
		m_position
	);

	m_skinModelRender->InitShader(
		"Assets/shader/model.fx",
		"VSMain",
		"VSSkinMain",
		DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	//m_skinModelRender->InitLight(g_lig);

	//

	//���f���̏���������
	//�������p�f�[�^�̍\�z
	//ModelInitData modeldata;
	//modeldata.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	//modeldata.m_fxFilePath = "Assets/shader/model.fx";

	//modeldata.m_vsEntryPointFunc = "VSMain";
	//modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	//modeldata.m_modelUpAxis = enModelUpAxisZ;

	//modeldata.m_expandConstantBuffer = &g_lig;
	//modeldata.m_expandConstantBufferSize = sizeof(g_lig);
	//modeldata.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//m_skeleton.Init("Assets/modelData/unityChan.tks");
	//modeldata.m_skeleton = &m_skeleton;

	//model.Init(modeldata);
	//�������I���//

	//�L�����R���̏�����
	//m_charaCon.Init(40.0f, 100.0f, m_position);

	//��ރi���o�[�z��̂��ׂĂ̗v�f��9�ŏ�����
	for (int i = 0; i < 10; i++) {
		GuzaiNo[i] = 9;
	}

	//�|�b�v�A�b�v�p�\��
	m_popUp = NewGO<PopUp2D>(20, "popup");
	if (playerNo != 0) {
		if (playerNo == 1) {
			m_popUp->SetEnSelf(enPlayer01);
		}
		else if (playerNo == 2) {
			m_popUp->SetEnSelf(enPlayer02);
		}
	}

	return true;
}

/// <summary>
/// ���f����ύX����Ƃ��Ɏg��
/// �ύX�������Ȃ��ӏ���nullptr
/// </summary>
/// <param name="ModelPath">���f���̃p�X</param>
/// <param name="ShaderPath">�V�F�[�_�[�̃p�X</param>
void Player::GiveData(const char* ModelPath, const char* ShaderPath)
{
	ModelInitData modeldata;

	modeldata.m_tkmFilePath = ModelPath;

	modeldata.m_fxFilePath = "Assets/shader/model.fx";
	if (ShaderPath != nullptr) {
		modeldata.m_fxFilePath = ShaderPath;
	}

	//model.Init(modeldata);
}

void Player::SetGuzaiNo9()
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
Vector3 Player::GetPosition()
{
	return m_position;
}

void Player::Update()
{
	m_skinModelRender->SetPosition(m_position);

	//�Q�[���v���C������Ȃ�������B
	if (!GetGameDirector().GetIsGamePlay())
	{
		//�������Ȃ��B
		return;
	}

	//�X�P���g�����X�V�B
	//m_skeleton.Update(model.GetWorldMatrix());

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

			m_skinModelRender->SetRotation(m_rotation);
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
		if (Buff == false) {
			moveSpeed.x = g_pad[0]->GetLStickXF() * -10.0f;
			moveSpeed.z = g_pad[0]->GetLStickYF() * -10.0f;
		}

		/*if (setPos == 0) {
			Vector3 Pos1 = { 900.0f, 0.0f, 0.0f };
			m_charaCon.SetPosition(Pos1);
			setPos = 1;
		}*/

		m_position += moveSpeed;

		m_skinModelRender->SetPosition(m_position);
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

			m_skinModelRender->SetRotation(m_rotation);
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

		m_position += moveSpeed;

		m_skinModelRender->SetPosition(m_position);
	}
	//�A�C�e���g�p�����B
	UseItem();
	//Vector3 plPos = m_charaCon.GetPosition();


	//m_charaCon.Execute(moveSpeed, 1.0f);

	//m_position = m_charaCon.Execute(moveSpeed, 1.0f);


	////�e�X�g:�|�b�v�A�b�v���f���̕ύX
	//if (m_popUp->GetEnState() == enNone) {
	//	m_popUp->SetEnState(enNearFood);
	//	m_popUp->ChangeModel();
	//}

	//�|�b�v�A�b�v�p���W�ݒ�
	Vector3 playerToPopUp = { 200.0f,100.0f,0.0f };
	m_popUpPosition = m_position;
	m_popUpPosition = m_popUpPosition + playerToPopUp;
	m_popUp->SetPosition(m_popUpPosition);


	//model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void Player::UseItem()
{
	//A�{�^�������ĂȂ�������B
	if (!g_pad[0]->IsTrigger(enButtonA))
	{
		return;
	}

	ObjectGene* gene;

	if (playerNo == 1)
	{
		gene = FindGO<ObjectGene>("gene01");
	}
	else if (playerNo == 2)
	{
		gene = FindGO<ObjectGene>("gene02");
	}
	else {
		return;
	}

	//�o�t�A�C�e�������Ă鎞�B
	if (m_enItem == enBuffItem)
	{
		m_enItem = enNonItem;
		SetBuffAffect(true);
		gene->Buffnum = 0;

	}
	//�f�o�t�A�C�e�������Ă鎞�B
	else if (m_enItem == enDebuffItem)
	{
		auto path = PathFactory::GetInstance().GetPath(enDeBuffLane, playerNo);
		Vector3 pos = path->GetFirstPoint()->s_vector;
		if ((m_position/*m_charaCon.GetPosition()*/ - pos).LengthSq() < DEBUFFDISTANCE)
		{
			m_enItem = enNonItem;

			DeBuff* deBuff = NewGO<DeBuff>(0, "debuff");
			deBuff->SetBuffNo(playerNo);
			deBuff->SetPosition(m_position/*m_charaCon.GetPosition()*/);
			deBuff->m_isDeBuffLane = true;

			gene->DeBuffnum = 0;
		}
	}
}
