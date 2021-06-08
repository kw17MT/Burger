#include "stdafx.h"
#include "Player.h"
#include "Guzai.h"
#include "FontRender.h"
#include "PathFactory.h"

#include "GameDirector.h"
#include "PopUp2D.h"

#include "SkinModelRender.h"
#include "Kitchen.h"

namespace
{
	float DEBUFFDISTANCE = 100.0f * 100.0f;
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_effect01);
	DeleteGO(m_effect02);
}

bool Player::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	if (playerNo == 1) {
		m_skinModelRender->Init(
			"Assets/modelData/Chef/ChefRed/Chef01.tkm",
			"Assets/modelData/Chef/ChefRed/Chef_1.tks",
			enModelUpAxisZ,
			m_position
		);
	}
	else {
		m_skinModelRender->Init(
			"Assets/modelData/Chef/ChefBlue/Chef02.tkm",
			"Assets/modelData/Chef/ChefRed/Chef_1.tks",
			enModelUpAxisZ,
			m_position
		);
	}

	m_skinModelRender->InitShader(
		"Assets/shader/model.fx",
		"VSMain",
		"VSSkinMain",
		DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	m_scale = { 0.3f,0.4f,0.3f };
	m_skinModelRender->SetScale(m_scale);

	//��ރi���o�[�z��̂��ׂĂ̗v�f��9�ŏ�����
	for (int i = 0; i < 10; i++) {
		GuzaiNo[i] = 9;
	}

	if (playerNo == 1) {
		m_kitchen = FindGO<Kitchen>("kitchen00");
	}
	if (playerNo == 2) {
		m_kitchen = FindGO<Kitchen>("kitchen01");
	}

	//�G�t�F�N�g�̏�����
	//P1
	m_effect01 = NewGO<Effect>(0);
	m_effect01->Init(u"Assets/effect/dust.efk");
	m_effect01->SetScale({ 10.0f,10.0f,10.0f });
	//P2
	m_effect02 = NewGO<Effect>(0);
	m_effect02->Init(u"Assets/effect/dust.efk");
	m_effect02->SetScale({ 10.0f,10.0f,10.0f });

	return true;
}

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

		//�G�t�F�N�g�Đ�
		//�ړ����Ȃ����I�ɔ���
		moveCounter01 += 1;
		if (moveSpeed.x != 0) {
			if (moveCounter01 % 12 == 11 ) {
				m_effect01->SetPosition(m_position);
				m_effect01->Play(0);
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
		
		//�G�t�F�N�g�Đ�
		//�ړ����Ȃ����I�ɔ���
		moveCounter02 += 1;
		if (moveSpeed.x != 0) {
			if (moveCounter02 % 12 == 11) {
				m_effect02->SetPosition(m_position);
				m_effect02->Play(0);
			}
		}

		if (moveCounter02 > 60) {
			moveCounter02 = 0;
		}


	}

	m_skinModelRender->SetScale(m_scale);

	m_effect01->Update();
	m_effect02->Update();
}
