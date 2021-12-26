#include "stdafx.h"
#include "EmotionUm.h"
#include "SpriteRender.h"

EmotionUm::~EmotionUm()
{
	DeleteGO(m_um);
}

bool EmotionUm::Start()
{
	m_um = NewGO<SpriteRender>(0);
	m_um->Init("Assets/image/emotion/uum.dds", 80, 80);

	return true;
}

void EmotionUm::Update()
{
	m_um->SetPosition(m_position);
}