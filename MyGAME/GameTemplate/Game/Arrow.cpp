#include "stdafx.h"
#include "Arrow.h"
#include "SkinModelRender.h"

namespace 
{
	const int TIMER_MAX = 50;
	const int TIMER_MIDDLE = 25;
	const float CHANGE_VOLUME_POS = 1.0f;
	const float CHANGE_VOLUME_SCALE = 0.1f;
}

Arrow::~Arrow()
{
	DeleteGO(m_skinModelRender);
}

bool Arrow::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//�ʏ탂�f���̏�����
	m_skinModelRender->Init("Assets/modelData/Arrow/Arrow_Yellow.tkm", nullptr, enModelUpAxisZ, m_position);
	//�V���h�E�L���X�g�p�̏�����
	m_skinModelRender->InitForCastShadow("Assets/modelData/Arrow/Arrow_Yellow.tkm", nullptr, enModelUpAxisZ, m_position);
	return true;
}

void Arrow::Float()
{
	m_timer++;
	//y���W����ɂ��Ă���
	if (m_timer < TIMER_MIDDLE) {
		m_position.y += CHANGE_VOLUME_POS;
	}
	//y���W�����ɂ��Ă���
	if (m_timer >= TIMER_MIDDLE && m_timer <= TIMER_MAX) {
		m_position.y -= CHANGE_VOLUME_POS;
	}
	//�^�C�}�[���O�ɂ���B
	if(m_timer > TIMER_MAX) {
		m_timer = 0;
	}
}

void Arrow::Expansion()
{
	//���g�̊g�嗦�͍ŏ��łȂ����Ƃ�ݒ肷��B
	m_scaleMinFlag = false;
	//�g�債�Ă����B
	m_scale.x += CHANGE_VOLUME_SCALE;
	m_scale.y += CHANGE_VOLUME_SCALE;
	m_scale.z += CHANGE_VOLUME_SCALE;

	//�g�嗦�̂ǂꂩ���P�ȏ�ɂȂ�΁A���ׂĂ̊g�嗦���P�ɂ���B
	if (m_scale.x > 1.0f || m_scale.y > 1.0f || m_scale.z > 1.0f) {
		m_scale = Vector3::One;
		m_scaleMaxFlag = true;
	}
}

void Arrow::Shrink()
{
	//���g�̊g�嗦�͍ő�łȂ����Ƃ�ݒ肷��B
	m_scaleMaxFlag = false;
	//�k�����Ă���
	m_scale.x -= CHANGE_VOLUME_SCALE;
	m_scale.y -= CHANGE_VOLUME_SCALE;
	m_scale.z -= CHANGE_VOLUME_SCALE;

	//�g�嗦�̂ǂꂩ���O�����ɂȂ�΁A���ׂĂ̊g�嗦���O�ɂ���B
	if (m_scale.x < 0.0f || m_scale.y < 0.0f || m_scale.z < 0.0f) {
		m_scale = Vector3::Zero;
		m_scaleMinFlag = true;
	}
}

void Arrow::Update()
{
	//���V����
	Float();
	//�ʒu�ݒ�
	m_skinModelRender->SetPosition(m_position);
	//�g�嗦�ݒ�
	m_skinModelRender->SetScale(m_scale);
}