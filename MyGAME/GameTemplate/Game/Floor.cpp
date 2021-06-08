#include "stdafx.h"
#include "Floor.h"
#include "SkinModelRender.h"

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
	if(isRed) {
		m_skinModelRender->Init("Assets/modelData/floor/floor_red.tkm", nullptr, enModelUpAxisZ, m_position, &m_lig);
	}
	else {
		m_skinModelRender->Init("Assets/modelData/floor/floor_blue.tkm", nullptr, enModelUpAxisZ, m_position, &m_lig);
	}
	m_skinModelRender->InitShader("Assets/shader/demodel.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	return true;
}

void Floor::Update()
{
	m_skinModelRender->SetPosition(m_position);
}