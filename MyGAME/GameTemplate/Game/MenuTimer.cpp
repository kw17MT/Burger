#include "stdafx.h"
#include "MenuTimer.h"
#include "SkinModelRender.h"
#include "GameDirector.h"
#include "LightManager.h"


namespace
{
	const float DEFAULT_TIMER_SCALE_X = 2.8f;
	const float TIMER_TURN_YELLOW_POINT = 1.7f;
	const float TIMER_TURN_RED_POINT = 0.9f;
	const float TIMER_DECREASE_RATE = 0.001f;
	const float STIRRING_AMOUNT = 0.03f;
	const float MAX_STIRRING = 1.2f;
	const float MIN_STIRRING = 1.0f;
}

MenuTimer::~MenuTimer()
{
	DeleteGO(m_skinModelRender);
}

bool MenuTimer::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//�ʏ�`��p���f���̏�����
	m_skinModelRender->InitAsGauge("Assets/modelData/gauge/gauge_red.tkm", nullptr, enModelUpAxisY, m_position, m_gaugeNumber);
	//���f���̌����̒���
	m_skinModelRender->SetRotation(m_rot);
	return true;
}

void MenuTimer::ResetTimerParam(int lightNumber)
{
	//�g�嗦�������̏�Ԃɂ���B
	m_scale.x = DEFAULT_TIMER_SCALE_X;
	//�ԐF�ɐݒ肵�����Ƃ��Ȃ��������Ƃ�
	m_completedMakeRed = false;
	//���F�ɐݒ肵�����Ƃ��Ȃ��������Ƃ�
	m_completedMakeYellow = false;
	//�Q�[�W��ΐF�ɐݒ肵�Ȃ���
	LightManager::GetInstance().MakeGaugeLightGreen(lightNumber);
	//�u���[���������Ȃ��悤�ɂ���
	m_skinModelRender->SetApplyBlur(false);
	//�^�C���A�b�v�t���O�������l�ɖ߂�
	m_isTimeUp = false;
}

void MenuTimer::StirringGauge()
{
	//��Ɍۓ�������
	if (m_stirringBigger) {
		m_scale.z += STIRRING_AMOUNT;
		if (m_scale.z >= MAX_STIRRING) m_stirringBigger = false;
	}
	//�ۓ������ɖ߂�
	if (!m_stirringBigger) {
		m_scale.z -= STIRRING_AMOUNT;
		if (m_scale.z <= MIN_STIRRING) m_stirringBigger = true;
	}
}

void MenuTimer::Update()
{
	//�Q�[�����Q�[�����J�n����Ă��Ȃ����
	if (GetGameDirector().GetGameScene() != enGamePlay) {
		//�������Ȃ��B
		return;
	}

	//���t���[���^�C�}�[�̊g�嗦��X�̂݉����Ă����B
	m_scale.x -= TIMER_DECREASE_RATE;

	//�Q�[�W�̑傫�������ȉ��ɂȂ�Ɖ��F�ɂ���
	if (m_scale.x <= TIMER_TURN_YELLOW_POINT && !m_completedMakeYellow) {
		//�Q�[�W��p���C�g�����F�ɂ���
		LightManager::GetInstance().MakeGaugeLightYellow(m_gaugeNumber);
		//���F�ɂ������Ƃ��L�^
		m_completedMakeYellow = true;
	}
	//�Q�[�W�̑傫�������ȉ��ɂȂ�ƐԐF�ɂ���
	if (m_scale.x <= TIMER_TURN_RED_POINT && !m_completedMakeRed) {
		//�����\���̂��߂Ƀu���[����������
		m_skinModelRender->SetApplyBlur(true);
		//�����\���̂��߂Ɍۓ�������
		StirringGauge();
		//�Q�[�W��p���C�g��ԐF�ɂ���
		LightManager::GetInstance().MakeGaugeLightRed(m_gaugeNumber);
	}

	//�^�C�}�[�̏k�ڂ�0�ɂȂ����灁�c�ʂ���������
	if (m_scale.x <= 0.0f) {
		//�^�C���A�b�v�������Ƃ��L�^
		m_isTimeUp = true;
		//�u���[�������Ȃ��悤�ɂ���
		m_skinModelRender->SetApplyBlur(false);
	}
	//��]�̍X�V
	m_skinModelRender->SetRotation(m_rot);
	//�g�嗦�̍X�V
	m_skinModelRender->SetScale(m_scale);
	//�ʒu�̍X�V
	m_skinModelRender->SetPosition(m_position);
}