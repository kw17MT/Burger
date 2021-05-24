#include "stdafx.h"
#include "Meter.h"
#include "SkinModelRender.h"

Meter::Meter()
{

}

Meter::~Meter()
{
	DeleteGO(m_skinModelRender);
}

bool Meter::Start()
{
	m_lig.ambientLight.Set(0.0f, 100.0f, 0.0f);
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/gauge/gauge_red.tkm", nullptr, enModelUpAxisY, m_position, &m_lig);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_skinModelRender->SetRotation(m_rot);

	return true;
}

void Meter::Update()
{
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rot);
}