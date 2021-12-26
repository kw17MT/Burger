#include "stdafx.h"
#include "EmotionCry.h"
#include "SpriteRender.h"

namespace
{
	const Vector3 EXPAND_RATE = { 0.01f,0.01f,0.01f };
	const Vector3 MAX_EXPANDED_SIZE = { 1.1f,1.1f,1.1f };
}

EmotionCry::~EmotionCry()
{
	DeleteGO(m_cry);
}

bool EmotionCry::Start()
{
	m_cry = NewGO<SpriteRender>(0);
	m_cry->Init("Assets/image/emotion/cry.dds", 80, 80);
	
	return true;
}

void EmotionCry::Update()
{
	if (m_isExpand)
	{
		m_scale += EXPAND_RATE;
		if (m_scale.x >= MAX_EXPANDED_SIZE.x)
		{
			m_scale = MAX_EXPANDED_SIZE;
			m_isExpand = false;
		}
	}
	else
	{
		m_scale -= EXPAND_RATE;
		if (m_scale.x <= 1.0f)
		{
			m_scale = Vector3::One;
			m_isExpand = true;
		}
	}

	m_cry->SetScale(m_scale);
	m_cry->SetPosition(m_position);
}