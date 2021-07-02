#include "stdafx.h"
#include "Conveyor.h"
#include "SkinModelRender.h"

bool Conveyor::Start()
{
	//�R���x�A�̃C���X�^���X�쐬
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//�V���h�E���V�[�o�\�Ƃ��ď�����
	m_skinModelRender->InitForRecieveShadow("Assets/modelData/conveyor/Conveyor.tkm", nullptr, enModelUpAxisZ, m_position, nullptr);

	return true;
}

void Conveyor::Update()
{
	//�ʒu�̐ݒ�
	m_skinModelRender->SetPosition(m_position);
	//�g�嗦�̐ݒ�
	m_skinModelRender->SetScale(m_scale);
}