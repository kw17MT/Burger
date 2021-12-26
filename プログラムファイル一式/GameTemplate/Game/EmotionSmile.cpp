#include "stdafx.h"
#include "EmotionSmile.h"
#include "SpriteRender.h"

EmotionSmile::~EmotionSmile()
{
	DeleteGO(m_smile);
}

bool EmotionSmile::Start()
{
	m_smile = NewGO<SpriteRender>(0);
	m_smile->Init("Assets/image/emotion/smile.dds", 80, 80);
	return true;
}

void EmotionSmile::Update()
{
	m_smile->SetPosition(m_position);

	if (m_turnLikeWatch)
	{
		m_angle += 2.0f;
		m_rot.SetRotationDegZ(m_angle);
		if (m_angle >= 30.0f)
		{
			m_turnLikeWatch = false;
		}
	}
	else
	{
		m_angle -= 2.0f;
		m_rot.SetRotationDegZ(m_angle);
		if (m_angle <= -30.0f)
		{
			m_turnLikeWatch = true;
		}
	}

	m_smile->SetRotation(m_rot);
}