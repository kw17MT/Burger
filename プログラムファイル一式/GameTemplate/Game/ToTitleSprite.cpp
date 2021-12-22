#include "stdafx.h"
#include "ToTitleSprite.h"
#include "SpriteRender.h"

namespace
{
	const float CHANGE_RATE = 0.03f;
}

ToTitleSprite::~ToTitleSprite()
{
	DeleteGO(m_sprite);
}

bool ToTitleSprite::Start()
{
	m_sprite = NewGO<SpriteRender>(0);
	m_sprite->Init("Assets/image/pressAToTitle.dds", 300, 300, "ReturnTitle");
	m_sprite->SetPosition({ -50.0f,-50.0f,0.0f });
	m_sprite->SetAlphaInShader(m_alpha);

	return true;
}

void ToTitleSprite::Update()
{

	if (m_addAlpha)
	{
		m_alpha += CHANGE_RATE;
		if (m_alpha >= 1.0f)
		{
			m_alpha = 1.0f;
			m_addAlpha = false;
		}
	}
	else
	{
		m_alpha -= CHANGE_RATE;
		if (m_alpha <= 0.3f)
		{
			m_alpha = 0.3f;
			m_addAlpha = true;
		}
	}

	m_sprite->SetAlphaInShader(m_alpha);
}