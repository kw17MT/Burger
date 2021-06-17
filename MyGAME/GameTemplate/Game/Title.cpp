#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"

namespace
{
	const int SPRITE_WIDTH = 1280;
	const int SPRITE_HEIGHT = 720;

	const int PLAYER_ONE_PAD = 0;
}

Title::~Title()
{
	DeleteGO(m_spriteRender);
}

bool Title::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init("Assets/Image/Title_512.dds", 1280, 720);

	return true;
}

void Title::Update()
{
	if (m_fade == nullptr) {
		if (g_pad[PLAYER_ONE_PAD]->IsTrigger(enButtonA))
		{
			//�t�F�[�h
			m_fade = NewGO<Fade>(0, "fade");
		}
		return;
	}
	//�^���ÂɂȂ�����J��
	if (m_fade->GetState() == enState_Wait) {
		//�^���ÂɂȂ肫�����i�K�Ń^�C�g���̃X�v���C�g���폜
		DeleteGO(m_spriteRender);
		//�t�F�[�h�C���Ɉڍs
		m_fade->SetState(enState_In);
		//�Q�[���𐶐�
		NewGO<Game>(0, "game");
		//DeleteGO(this);
	}

	//�t�F�[�h�p�摜�̕s�����x��0�ȉ��ɂȂ����Ƃ��Ƀt�F�[�h�摜�ƃ^�C�g�����g���폜
	if (m_fade->GetState() == enState_In && m_fade->GetAlpha() <= 0.0f) {
		DeleteGO(m_fade);
		DeleteGO(this);
	}

}