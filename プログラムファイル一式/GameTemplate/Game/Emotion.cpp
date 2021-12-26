#include "stdafx.h"
#include "Emotion.h"
#include "SpriteRender.h"

Emotion::~Emotion()
{
	DeleteGO(m_hukidashi);
}

bool Emotion::Start()
{

	m_hukidashi = NewGO<SpriteRender>(0);
	m_hukidashi->Init("Assets/image/emotion/hukidasi.dds", 160, 160);

	return true;
}

void Emotion::Update()
{
	m_hukidashi->SetPosition(m_position);
}