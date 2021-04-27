#include "stdafx.h"
#include "Dish.h"
#include "SkinModelRender.h"
#include "Level.h"

bool Dish::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/gu/egg.tkm", nullptr, enModelUpAxisZ, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);

	SetScale({ 1.0f,0.2f,1.0f });

	return true;
}

void Dish::Update()
{
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPosition(m_position);
}