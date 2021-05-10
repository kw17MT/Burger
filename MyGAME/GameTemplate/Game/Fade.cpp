#include "stdafx.h"
#include "Fade.h"

Fade::Fade()
{
	m_spriteRender = NewGO<SpriteRender>(20);
	m_spriteRender->Init("Assets/Image/title.dds", 1280, 720);
	//����
	m_spriteRender->SetColor(0, 0, 0, m_alpha);
	//�t�F�[�h�A�E�g
	m_state = enState_Out;
}

Fade::~Fade()
{
	DeleteGO(m_spriteRender);
}

void Fade::Update()
{
	switch (m_state)
	{
	case enState_In:
		m_alpha -= 0.01f;
		//�C��������폜
		if (m_alpha <= 0.0f) {
			DeleteGO(this);
		}
		break;
	case enState_Out:
		m_alpha += 0.01f;
		//�^���Âőҋ@
		if (m_alpha >= 1.0f) {
			m_state = enState_Wait;
		}
		break;
	}
	//�J���[�͍������Ă�B
	m_spriteRender->SetColor(0, 0, 0, m_alpha);
}