#include "stdafx.h"
#include "Meter.h"
#include "SkinModelRender.h"

namespace 
{
	const int USING_LIGHT_NUMBER = 2;
}

Meter::~Meter()
{
	//���f���̏���
	DeleteGO(m_skinModelRender);
}

bool Meter::Start()
{

	m_skinModelRender = NewGO<SkinModelRender>(0);
	//�ʏ�`�惂�f���̏�����
	m_skinModelRender->InitAsGauge("Assets/modelData/gauge/gauge_red.tkm", nullptr, enModelUpAxisY, m_position, USING_LIGHT_NUMBER);
	//�e�p���f���̏�����
	m_skinModelRender->InitForCastShadow("Assets/modelData/gauge/gauge_red.tkm", nullptr, enModelUpAxisY, m_position);
	//���f���̌����𒲐�
	m_skinModelRender->SetRotation(m_rot);

	return true;
}

void Meter::Update()
{
	//�g�嗦�̕ύX
	m_skinModelRender->SetScale(m_scale);
	//�ʒu�̕ύX
	m_skinModelRender->SetPosition(m_position);
	//��]�̕ύX
	m_skinModelRender->SetRotation(m_rot);
}