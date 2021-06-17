#include "stdafx.h"
#include "OperationExplanation.h"
#include "Fade.h"
#include "Game.h"

namespace
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;

	const int EXPLANE_NUMBER_1 = 0;
	const int EXPLANE_NUMBER_2 = 1;
	const int EXPLANE_NUMBER_3 = 2;
	const int EXPLANE_NUMBER_4 = 3;
	const int EXPLANE_NUMBER_5 = 4;
	const int EXPLANE_NUMBER_6 = 5;

	const int SHRINK_RATE_WIDTH = 80;
	const int SHRINK_RATE_HEIGHT = 60;
}

OperationExplanation::OperationExplanation()
{
	//�����X�e�[�g
	m_currentState = enState_Idle;
	//�t�@�C���p�X
	m_spriteData[EXPLANE_NUMBER_1].fliePath = "Assets/Image/title.dds";
	m_spriteData[EXPLANE_NUMBER_2].fliePath = "Assets/Image/title.dds";
	m_spriteData[EXPLANE_NUMBER_3].fliePath = "Assets/Image/title.dds";
	m_spriteData[EXPLANE_NUMBER_4].fliePath = "Assets/Image/title.dds";
	m_spriteData[EXPLANE_NUMBER_5].fliePath = "Assets/Image/title.dds";
	m_spriteData[EXPLANE_NUMBER_6].fliePath = "Assets/Image/title.dds";
	//�X�v���C�g�����_�[������
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init(m_spriteData[0].fliePath, WIDTH, HEIGHT);

	//�K������t�F�[�h
	m_fade = FindGO<Fade>("fade");
}

OperationExplanation::~OperationExplanation()
{
	DeleteGO(m_spriteRender);
}

void OperationExplanation::Update()
{
	switch (m_currentState)
	{
	case enState_Change:
		//�؂�ւ�
		m_nextWidth -= SHRINK_RATE_WIDTH;
		m_nextHeight -= SHRINK_RATE_HEIGHT;
		m_spriteRender->Init(m_spriteData[m_currentPage].fliePath, m_nextWidth, m_nextHeight);
		m_currentPage++;
		m_currentState = enState_Idle;
		break;
	case enState_End:
		//�J��
		if (m_fade == nullptr) {
			m_fade = NewGO<Fade>(0, "fade");
		}
		if (m_fade->GetState() == enState_Wait) {
			NewGO<Game>(0, "game");
			m_fade->SetState(enState_In);
			DeleteGO(this);
		}
		break;
	default:
		//����
		if (m_fade == nullptr) {
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				if (m_currentPage < EXPLANE_NUMBER_6) {
					m_currentState = enState_Change;
				}
				else {
					m_currentState = enState_End;
				}
			}
			return;
		}
		m_fade = FindGO<Fade>("fade");
		break;
	}
}