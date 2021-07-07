#include "stdafx.h"
#include "Player.h"
#include "Guzai.h"
#include "FontRender.h"
#include "PathFactory.h"
#include "GameDirector.h"
#include "SkinModelRender.h"
#include "Kitchen.h"

namespace
{
	const Vector3 EFFECT_SCALE = { 10.0f,10.0f,10.0f };
	const Vector3 FRONT_DIRECTION = { 0.0f,0.0f,1.0f };
	const Vector3 RIGHT_DIRECTION = { 1.0f,0.0f,0.0f };
	const Vector3 PLYAER_SPEED_ZERO = Vector3::Zero;

	const int KITCHEN_NAME_SIZE = 10;
	const int PLAYER_NUMBER_ONE = 0;
	const int PLAYER_NUMBER_TWO = 1;
	const int MAX_NUM_TO_STACK_GUZAI = 10;
	const int STACK_EMPTY = 9;
	const int PLAYER_1_RESTRECTED_POS_X_MIN = 900;
	const int PLAYER_2_RESTRECTED_POS_X_MIN = -1300;
	const int PLAYER_1_RESTRECTED_POS_X_MAX = 1300;
	const int PLAYER_2_RESTRECTED_POS_X_MAX = -900;
	const int PLAYER_RESTRECTED_POS_Z_MIN = -530;
	const int PLAYER_RESTRECTED_POS_Z_MAX = 190;
	const int EFFECT_POP_RATE = 12;
	const int EFFECT_POP = 11;
	const int EFFECT_TIMER_MAX = 60;

	const float AJUST_PLAYER_SPEED = -10.0f;
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_effect);
}

bool Player::Start()
{
	//���f���̕`��
	m_skinModelRender = NewGO<SkinModelRender>(0);

	if (m_playerNo == PLAYER_NUMBER_ONE) {
		//�ʏ�`��p
		m_skinModelRender->InitForRecieveShadow(
			"Assets/modelData/Chef/ChefRed/Chef01.tkm",
			"Assets/modelData/Chef/ChefRed/Chef_1.tks",
			enModelUpAxisZ,
			m_position
		);
		//�e�`��p
		m_skinModelRender->InitForCastShadow(
			"Assets/modelData/Chef/ChefRed/Chef01.tkm",
			"Assets/modelData/Chef/ChefRed/Chef_1.tks",
			enModelUpAxisZ,
			m_position
		);

		
	}
	else {
		//�ʏ�`��p
		m_skinModelRender->InitForRecieveShadow(
			"Assets/modelData/Chef/ChefBlue/Chef02.tkm",
			"Assets/modelData/Chef/ChefRed/Chef_1.tks",
			enModelUpAxisZ,
			m_position
		);
		//�e�`��p
		m_skinModelRender->InitForCastShadow(
			"Assets/modelData/Chef/ChefBlue/Chef02.tkm",
			"Assets/modelData/Chef/ChefRed/Chef_1.tks",
			enModelUpAxisZ,
			m_position
		);
	}

	//�g�嗦�̒���
	m_skinModelRender->SetScale(m_scale);

	//�O�̂��ߋ�ރi���o�[�z��̂��ׂĂ̗v�f�������Ȃ���Ԃɏ�����
	SetGuzaiEmpty();

	//�v���C���[�ԍ���p���đΉ�����I�u�W�F�N�g���������邽�߂̔ԍ�
	int endNo = m_playerNo;
	//string�^�ɕς���char�ɕϊ����邽�߂̏���������B
	std::string endNo_string = std::to_string(endNo);
	//�s�ωӏ����`
	char kitchenName[KITCHEN_NAME_SIZE] = "kitchen0";
	//���[�ԍ�������ǉ�����
	strcat_s(kitchenName, endNo_string.c_str());
	//����̃L�b�`�����擾�B
	Kitchen* kitchen = FindGO<Kitchen>(kitchenName);

	//�G�t�F�N�g�̏�����
	m_effect = NewGO<Effect>(0);
	m_effect->Init(u"Assets/effect/dust.efk");
	m_effect->SetScale(EFFECT_SCALE);

	return true;
}

void Player::SetGuzaiEmpty()
{
	for (int i = 0;i < MAX_NUM_TO_STACK_GUZAI;i++)
	{
		m_guzaiNo[i] = STACK_EMPTY;
	}
}

void Player::RestrictPos()
{
	//���W��p���ăv���C���[�̈ړ��͈͂��Ǘ�����B
	if (m_playerNo == PLAYER_NUMBER_ONE) {
		if (m_position.x > PLAYER_1_RESTRECTED_POS_X_MAX) {
			m_position.x = PLAYER_1_RESTRECTED_POS_X_MAX;
		}
		if (m_position.x < PLAYER_1_RESTRECTED_POS_X_MIN) {
			m_position.x = PLAYER_1_RESTRECTED_POS_X_MIN;
		}
		if (m_position.z > PLAYER_RESTRECTED_POS_Z_MAX) {
			m_position.z = PLAYER_RESTRECTED_POS_Z_MAX;
		}
		if (m_position.z < PLAYER_RESTRECTED_POS_Z_MIN) {
			m_position.z = PLAYER_RESTRECTED_POS_Z_MIN;
		}
	}
	if (m_playerNo == PLAYER_NUMBER_TWO) {
		if (m_position.x > PLAYER_2_RESTRECTED_POS_X_MAX) {
			m_position.x = PLAYER_2_RESTRECTED_POS_X_MAX;
		}
		if (m_position.x < PLAYER_2_RESTRECTED_POS_X_MIN) {
			m_position.x = PLAYER_2_RESTRECTED_POS_X_MIN;
		}
		if (m_position.z > PLAYER_RESTRECTED_POS_Z_MAX) {
			m_position.z = PLAYER_RESTRECTED_POS_Z_MAX;
		}
		if (m_position.z < PLAYER_RESTRECTED_POS_Z_MIN) {
			m_position.z = PLAYER_RESTRECTED_POS_Z_MIN;
		}
	}
}

void Player::PlayerRotation()
{
	//��]����
	//���g�̏�ƉE���`(�����낵�Ȃ̂�)
	Vector3 frontDirP1 = FRONT_DIRECTION;
	frontDirP1.Normalize();
	Vector3 rightDirP1 = RIGHT_DIRECTION;
	rightDirP1.Normalize();

	//��]���̌���
	Vector3 AxisYP1;
	AxisYP1.Cross(frontDirP1, rightDirP1);

	//���������Ɖ��s�����ւ̓��͂��󂯎��
	float LStickXP1 = g_pad[m_playerNo]->GetLStickXF();
	float LStickZP1 = g_pad[m_playerNo]->GetLStickYF() * -1.0f; //���s�����̋t�]��-1.0f���|���ĕ␳

	if (fabsf(LStickXP1) < 0.001f && fabsf(LStickZP1) < 0.001f) {
		//return; //return����ƈȉ��̏�����������΂����Update�̍Ō�ɂ����Ă��܂��B
	}
	else {
		//��̓��͒l�������p�����߂�(���W�A���p)
		m_angle = atan2(LStickXP1, LStickZP1);
		//�c���܂��̉�]�����߂�(���W�A���p�������ɓn������SetRotation)
		m_rotation.SetRotation(AxisYP1, -m_angle);
	}
}

void Player::RestrictMove()
{
	if (m_moveStop == false) {
		m_moveSpeed.x = g_pad[m_playerNo]->GetLStickXF() * AJUST_PLAYER_SPEED;
		m_moveSpeed.z = g_pad[m_playerNo]->GetLStickYF() * AJUST_PLAYER_SPEED;
	}
	if (m_moveStop == true)
	{
		m_moveSpeed = PLYAER_SPEED_ZERO;
	}

	m_position += m_moveSpeed;

	//�v���C���[���ړ����Ă������ړ����x��ۑ���������B
	if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f) {
		m_saveMoveSpeed = m_moveSpeed;
		m_saveMoveSpeed.Normalize();
	}
}

void Player::PopWalkingEffect()
{
	//�G�t�F�N�g�Đ�
	//�ړ����Ȃ����I�ɔ���
	m_moveCounter++;
	if (m_moveSpeed.x != 0) {
		if (m_moveCounter % EFFECT_POP_RATE == EFFECT_POP) {
			m_effect->SetPosition(m_position);
			m_effect->Play(0);
		}
	}

	if (m_moveCounter > EFFECT_TIMER_MAX) {
		m_moveCounter = 0;
	}
}

void Player::Update()
{
	//�J�E���g�_�E�����ł��A�v���C���[�̏����ʒu�͌Œ肵�Ă����������߁B
	m_skinModelRender->SetPosition(m_position);

	//�Q�[���v���C������Ȃ�������B
	if (!GetGameDirector().GetIsGamePlay())
	{
		//�������Ȃ��B
		return;
	}

	PlayerRotation();


	RestrictMove();

	//RestrictPos();

	PopWalkingEffect();

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);
	m_effect->Update();
}