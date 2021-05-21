#include "stdafx.h"
#include "Player.h"
#include "Guzai.h"
#include "FontRender.h"
#include "PathFactory.h"

#include "GameDirector.h"
#include "PopUp2D.h"

#include "SkinModelRender.h"
#include "Kitchen.h"
//#include "effect/Effect.h"

namespace
{
	float DEBUFFDISTANCE = 100.0f * 100.0f;
}

Player::Player()
{

}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_shadow);
}

bool Player::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//if (playerNo == 1) {
		m_skinModelRender->Init(
			"Assets/modelData/Chef/ChefRed/Chef01.tkm",
			"Assets/modelData/Chef/ChefRed/Chef_1.tks",
			enModelUpAxisZ,
			m_position
		);
//	}
	//else {
	/*	m_skinModelRender->Init(
			"Assets/modelData/Chef/ChefBlue/Chef02.tkm",
			"Assets/modelData/Chef/ChefRed/Chef_1.tks",
			enModelUpAxisZ,
			m_position
		);
	}*/

	m_skinModelRender->InitShader(
		"Assets/shader/model.fx",
		"VSMain",
		"VSSkinMain",
		DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	m_shadow = NewGO<SkinModelRender>(0);
	m_shadow->Init(
		"Assets/modelData/Chef/ChefRed/Chef01.tkm",
		"Assets/modelData/Chef/ChefRed/Chef_1.tks",
		enModelUpAxisZ,
		m_position
	);
	m_shadow->InitShader(
		"Assets/shader/demodel.fx",
		"VSMain",
		"VSSkinMain",
		DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	m_scale = { 0.3f,0.4f,0.3f };
	m_shadowScale = { 0.4f,0.01f,0.4f };
	m_skinModelRender->SetScale(m_scale);
	m_shadow->SetScale(m_shadowScale);
	m_shadow->SetPosition(m_position);
	//�����ŃA�j���[�V�����̃��[�h���s��
	animationClips[enAnimation_Idle].Load("Assets/animData/swing2.tka");
	/*animationClips[enAnimation_Run].Load("");
	animationClips[enAnimation_Cut].Load("");
	animationClips[enAnimation_Cook].Load("");
	animationClips[enAnimation_HaveIdle].Load("");
	animationClips[enAnimation_HaveRun].Load("");*/


	animationClips[enAnimation_Idle].SetLoopFlag(true);
	/*animationClips[enAnimation_Run].SetLoopFlag(true);
	animationClips[enAnimation_Cut].SetLoopFlag(true);
	animationClips[enAnimation_Cook].SetLoopFlag(true);
	animationClips[enAnimation_HaveIdle].SetLoopFlag(true);
	animationClips[enAnimation_HaveRun].SetLoopFlag(true);*/

	m_skinModelRender->InitAnimation(animationClips, enAnimation_Num);

	m_skinModelRender->PlayAnimation(enAnimation_Idle);

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

	if (playerNo == 1) {
		m_kitchen = FindGO<Kitchen>("kitchen01");
	}
	if (playerNo == 2) {
		m_kitchen = FindGO<Kitchen>("kitchen02");
	}

	//�G�t�F�N�g�̏�����
	//P1
	//m_effect01.Init(u"Assets/effect/dust.efk");
	m_effect01.Init(u"Assets/effect/dust.efk");
	m_effect01.SetScale({ 10.0f,10.0f,10.0f });
	//P2
	m_effect02.Init(u"Assets/effect/dust.efk");
	m_effect02.SetScale({ 10.0f,10.0f,10.0f });

	return true;
}

/// <summary>
/// ���f����ύX����Ƃ��Ɏg��
/// �ύX�������Ȃ��ӏ���nullptr
/// </summary>
/// <param name="ModelPath">���f���̃p�X</param>
/// <param name="ShaderPath">�V�F�[�_�[�̃p�X</param>

void Player::SetGuzaiNo9()
{
	for (int i = 0;i < 10;i++)
	{
		GuzaiNo[i] = 9;
	}
}

void Player::RestrictPos()
{
	if (playerNo == 1) {
		if (m_position.x > 1300) {
			m_position.x = 1300;
		}
		if (m_position.x < 900) {
			m_position.x = 900;
		}
		if (m_position.z > 190) {
			m_position.z = 190;
		}
		if (m_position.z < -530) {
			m_position.z = -530;
		}
	}
	if (playerNo == 2) {
		if (m_position.x > -900) {
			m_position.x = -900;
		}
		if (m_position.x < -1300) {
			m_position.x = -1300;
		}
		if (m_position.z > 190) {
			m_position.z = 190;
		}
		if (m_position.z < -530) {
			m_position.z = -530;
		}
	}

}

void Player::GrabFromKitchen()
{
	
}
void Player::StopMove01(bool tf)
{ 
	m_moveStop01 = tf;
}
void Player::StopMove02(bool tf)
{
	m_moveStop02 = tf;
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
		if (m_moveStop01 == true || m_moveStop02 == true || fabsf(LStickXP1) < 0.001f && fabsf(LStickZP1) < 0.001f) {
			//return; //return����ƈȉ��̏�����������΂����Update�̍Ō�ɂ����Ă��܂��B
		}
		else {
			//��̓��͒l�������p�����߂�(���W�A���p)
			angle = atan2(LStickXP1, LStickZP1);
			//�c���܂��̉�]�����߂�(���W�A���p�������ɓn������SetRotation)
			m_rotation.SetRotation(AxisYP1, -angle);

			m_skinModelRender->SetRotation(m_rotation);
		}

		////�o�t�̌��ʂ����Ă��邩�m�F��ړ����x�����߁A�ړ�������B
		//if (Buff == true) {
		//	moveSpeed.x = g_pad[0]->GetLStickXF() * -20.0f;
		//	moveSpeed.z = g_pad[0]->GetLStickYF() * -20.0f;

		//	BuffTime--;
		//	if (BuffTime == 0) {
		//		Buff = false;
		//		BuffTime = 120;
		//	}
		//}
		//if (Buff == false) {
		//	moveSpeed.x = g_pad[0]->GetLStickXF() * -10.0f;
		//	moveSpeed.z = g_pad[0]->GetLStickYF() * -10.0f;
		//}

		if (m_moveStop01 == false && m_moveStop02 == false) {
			moveSpeed.x = g_pad[0]->GetLStickXF() * -10.0f;
			moveSpeed.z = g_pad[0]->GetLStickYF() * -10.0f;
		}
		if(m_moveStop01 == true || m_moveStop02 == true)
		{
			moveSpeed.x = 0.0f;
			moveSpeed.y = 0.0f;
			moveSpeed.z = 0.0f;
		}

		m_position += moveSpeed;
		
		//�v���C���[���ړ����Ă������ړ����x��ۑ���������B
		if (moveSpeed.x != 0.0f || moveSpeed.z != 0.0f) {
			saveMoveSpeed = moveSpeed;
			saveMoveSpeed.Normalize();
		}

		RestrictPos();

		m_skinModelRender->SetPosition(m_position);
		m_shadow->SetPosition(m_position);

		//�G�t�F�N�g�Đ�
		//�ړ����Ȃ����I�ɔ���
		moveCounter01 += 1;
		if (moveSpeed.x != 0) {
			if (moveCounter01 % 12 == 11 ) {
				m_effect01.SetPosition(m_position);
				m_effect01.Play(0);
			}
		}

		if (moveCounter01 > 60) {
			moveCounter01 = 0;
		}
		

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
		if ( m_moveStop01 == true || m_moveStop02 == true || fabsf(LStickXP2) < 0.001f && fabsf(LStickZP2) < 0.001f) {
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
		/*if (Buff == true) {
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
		}*/

	/*	moveSpeed.x = g_pad[1]->GetLStickXF() * -10.0f;
		moveSpeed.z = g_pad[1]->GetLStickYF() * -10.0f;*/

		if (m_moveStop01 == false && m_moveStop02 == false) {
			moveSpeed.x = g_pad[1]->GetLStickXF() * -10.0f;
			moveSpeed.z = g_pad[1]->GetLStickYF() * -10.0f;
		}
		if(m_moveStop01 == true || m_moveStop02 == true)
		{
			moveSpeed.x = 0.0f;
			moveSpeed.y = 0.0f;
			moveSpeed.z = 0.0f;
		}
		m_position += moveSpeed;

		//�v���C���[���ړ����Ă������ړ����x��ۑ���������B
		if (moveSpeed.x != 0.0f || moveSpeed.z != 0.0f) {
			saveMoveSpeed = moveSpeed;
			saveMoveSpeed.Normalize();
		}

		RestrictPos();

		m_skinModelRender->SetPosition(m_position);
		m_shadow->SetPosition(m_position);

		//�G�t�F�N�g�Đ�
		//�ړ����Ȃ����I�ɔ���
		moveCounter02 += 1;
		if (moveSpeed.x != 0) {
			if (moveCounter02 % 12 == 11) {
				m_effect02.SetPosition(m_position);
				m_effect02.Play(0);
			}
		}

		if (moveCounter02 > 60) {
			moveCounter02 = 0;
		}


	}
	//�A�C�e���g�p�����B
	UseItem();

	////�e�X�g:�|�b�v�A�b�v���f���̕ύX
	//if (m_popUp->GetEnState() == enNone) {
	//	m_popUp->SetEnState(enNearFood);
	//	m_popUp->ChangeModel();
	//}

	m_skinModelRender->SetScale(m_scale);
	m_shadow->SetScale(m_shadowScale);

	//�|�b�v�A�b�v�p���W�ݒ�
	Vector3 playerToPopUp = { 200.0f,100.0f,0.0f };
	m_popUpPosition = m_position;
	m_popUpPosition = m_popUpPosition + playerToPopUp;
	m_popUp->SetPosition(m_popUpPosition);

	m_effect01.Update();
	m_effect02.Update();

}

void Player::UseItem()
{
	//A�{�^�������ĂȂ�������B
	if (!g_pad[0]->IsTrigger(enButtonA))
	{
		return;
	}

	GuzaiGene* gene;

	if (playerNo == 1)
	{
		gene = FindGO<GuzaiGene>("gene01");
	}
	else if (playerNo == 2)
	{
		gene = FindGO<GuzaiGene>("gene02");
	}
	else {
		return;
	}

	//�o�t�A�C�e�������Ă鎞�B
	/*if (m_enItem == enBuffItem)
	{
		m_enItem = enNonItem;
		SetBuffAffect(true);
		gene->Buffnum = 0;

	}*/
	//�f�o�t�A�C�e�������Ă鎞�B
	//else if (m_enItem == enDebuffItem)
	//{
	//	auto path = PathFactory::GetInstance().GetPath(enDeBuffLane, playerNo);
	//	Vector3 pos = path->GetFirstPoint()->s_vector;
	//	if ((m_position/*m_charaCon.GetPosition()*/ - pos).LengthSq() < DEBUFFDISTANCE)
	//	{
	//		m_enItem = enNonItem;

	//		//DeBuff* deBuff = NewGO<DeBuff>(0, "debuff");
	//		//deBuff->SetBuffNo(playerNo);
	//		//deBuff->SetPosition(m_position/*m_charaCon.GetPosition()*/);
	//		//deBuff->m_isDeBuffLane = true;

	//		gene->DeBuffnum = 0;
	//	}
	//}
}
