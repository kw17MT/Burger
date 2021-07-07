#include "stdafx.h"
#include "Meter.h"
#include "SkinModelRender.h"

Meter::~Meter()
{
	//���f���̏���
	DeleteGO(m_skinModelRender);
}

bool Meter::Start()
{
	//���C�g��p���ẴQ�[�W�̐F�̕ύX
	//m_lig.ambientLight.Set(0.0f, 100.0f, 0.0f);
	//�Q�[�W�̃��f���̏�����
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//�ʏ�`�惂�f���̏�����
	m_skinModelRender->Init("Assets/modelData/gauge/gauge_red.tkm", nullptr, enModelUpAxisY, m_position);
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