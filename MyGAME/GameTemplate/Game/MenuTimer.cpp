#include "stdafx.h"
#include "MenuTimer.h"
#include "SkinModelRender.h"
#include "GameDirector.h"


namespace
{
	const Vector3 MAKE_MODEL_GREEN = { 0.0f, 100.0f, 0.0f };

	const float DEFAULT_TIMER_SCALE_X = 2.8f;
	const float TIMER_TURN_YELLOW_POINT = 0.9f;
	const float MAKE_YELLOW_AMOUNT = 0.001f;
	const float MAKE_RED_AMOUNT = 0.4f;
	const float TIMER_DECREASE_RATE = 0.001f;
	const float GOOD_AMOUNT_OF_RED = 2.0f;
	const float TIMER_TURN_RED_POINT = 1.0f;
}
MenuTimer::~MenuTimer()
{
	DeleteGO(m_skinModelRender);
}

bool MenuTimer::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//�ʏ�`��p���f���̏�����
	m_skinModelRender->Init("Assets/modelData/gauge/gauge_red.tkm", nullptr, enModelUpAxisY, m_position);
	//���f���̌����̒���
	m_skinModelRender->SetRotation(m_rot);
	return true;
}

void MenuTimer::ResetTimerParam()
{
	//�g�嗦�������̏�Ԃɂ���B
	m_scale.x = DEFAULT_TIMER_SCALE_X;
	//�ΐF�ɂ���
	//m_lig.ambientLight.Set(MAKE_MODEL_GREEN);
	m_isTimeUp = false;
}


void MenuTimer::Update()
{
	//�Q�[�����Q�[�����J�n����Ă��Ȃ����
	if (GetGameDirector().GetGameScene() != enGamePlay) {
		//�������Ȃ��B
		return;
	}

	//���t���[���^�C�}�[�̊g�嗦��X�̂݉����Ă����B
	m_scale.x -= TIMER_DECREASE_RATE ;
	//timer--;

	//�Q�[�W�̑傫�������وȏ�ł���Ƃ��Ԑ����𑫂� = ���X�ɉ��F�ɂ��Ă���
	if (m_scale.x >= TIMER_TURN_YELLOW_POINT) {
		//m_lig.ambientLight.x += MAKE_YELLOW_AMOUNT;
		//�ԐF�����x�ǂ��Ȃ�����
		/*if (m_lig.ambientLight.x >= GOOD_AMOUNT_OF_RED) {
			m_lig.ambientLight.x = GOOD_AMOUNT_OF_RED;
		}*/
	}
	//�Q�[�W�̐F��Ԃ��������|�C���g�܂ŏk��������
	if (m_scale.x < TIMER_TURN_RED_POINT) {
		//�Ђ�����A�ΐF�����𔲂��Ă����B
		//m_lig.ambientLight.y -= MAKE_RED_AMOUNT;
		//if (m_lig.ambientLight.y <= 0.0f) {
		//	m_lig.ambientLight.y = 0.0f;
		//}
	}

	//�^�C�}�[�̏k�ڂ�0�ɂȂ����灁�c�ʂ���������
	if (m_scale.x <= 0.0f) {
		m_isTimeUp = true;
	}

	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rot);
	m_skinModelRender->SetPosition(m_position);
}