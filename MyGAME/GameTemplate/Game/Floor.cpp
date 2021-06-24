#include "stdafx.h"
#include "Floor.h"
#include "SkinModelRender.h"
#include "ShadowParam.h"

namespace
{
	const Vector3 AJUST_LIGHT_RIGHTER = { 4.5f,4.5f,4.5f };
}

Floor::~Floor()
{
	DeleteGO(m_skinModelRender);
}

bool Floor::Start()
{
	//���������߂đS�̓I�ɖ��邭����B
	m_lig.ambientLight.Set(AJUST_LIGHT_RIGHTER);

	//���f���̏�����
	m_skinModelRender = NewGO<SkinModelRender>(0);
	if (isRed) {
		m_skinModelRender->InitForRecieveShadow("Assets/modelData/floor/floor_red.tkm", nullptr, enModelUpAxisZ, m_position);
	}
	else {
		m_skinModelRender->InitForRecieveShadow("Assets/modelData/floor/floor_blue.tkm", nullptr, enModelUpAxisZ, m_position);
	}

	return true;
}

void Floor::Update()
{
	m_skinModelRender->SetPosition(m_position);
	//m_skinModelRender->SetScale({ 3.0f,3.0f,3.0f });
}