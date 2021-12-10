#include "stdafx.h"
#include "Floor.h"
#include "SkinModelRender.h"

Floor::~Floor()
{
	DeleteGO(m_skinModelRender);
}

bool Floor::Start()
{
	//���f���̏�����
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//�ԐF�̏����o���Ȃ��
	if (m_isRed) {
		m_skinModelRender->InitForRecieveShadow("Assets/modelData/floor/floor_red.tkm", nullptr, enModelUpAxisZ, m_position);
	}
	//�F�̏����o���Ȃ��
	else {
		m_skinModelRender->InitAsFloor("Assets/modelData/floor/floor_blue.tkm", nullptr, enModelUpAxisZ, m_position);
	}

	return true;
}
 
void Floor::Update()
{
	//�ʒu���X�V
	m_skinModelRender->SetPosition(m_position);
	//�g�嗦���X�V
	m_skinModelRender->SetScale(m_scale);
}