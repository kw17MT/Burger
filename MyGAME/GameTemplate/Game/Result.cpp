#include "stdafx.h"
#include "Result.h"
#include "SpriteRender.h"
#include "FixedUI.h"
#include "GameDirector.h"

namespace
{
	const int DRAW = 0;
	const int WIN = 1;
	const int LOSE = 2;

	const float AJUST_SPRITE_SCALE = 0.75f;
	const float AJUST_SPRITE_HALF = 0.5f;
	const float SHRINK_RATE = 0.08f;
	const float ALPHA_INCREASE_RATE = 0.03f;
	const float FIXED_SCALE_ONE_Z = 1.0f;
}

Result::~Result()
{
	DeleteGO(m_spriteRender);
}

void Result::DecideDDS()
{
	//spriteNum�̒l�ɉ����ď������Ɏg�p����DDS��U�蕪����
	switch (m_spriteNum) {
	case DRAW:
		m_spriteRender->Init("Assets/Image/draw.dds", m_wideth * AJUST_SPRITE_SCALE, m_height * AJUST_SPRITE_SCALE);
		break;
	case WIN:
		m_spriteRender->Init("Assets/Image/win.dds", m_wideth * AJUST_SPRITE_SCALE, m_height * AJUST_SPRITE_SCALE);
		break;
	case LOSE: 
		m_spriteRender->Init("Assets/Image/lose.dds", m_wideth * AJUST_SPRITE_HALF, m_height * AJUST_SPRITE_HALF);
		break;
	default:
		break;
	}
}

void Result::DecidePos()
{
	//positionNum�̒l�ɉ����ĕ\���ʒu��U�蕪����
	switch (m_positionNum) {
	case DRAW: //�������� : ��ʒ������炢
		m_spriteRender->SetPosition(m_center);
		break;
	case WIN: //����
		m_spriteRender->SetPosition(m_left);
		break;
	case LOSE://�E��
		m_spriteRender->SetPosition(m_right);
		break;
	default:
		break;
	}
}

bool Result::Start()
{
	m_spriteRender = NewGO<SpriteRender>(1);

	//UI������
	if (m_ui == nullptr) {
		m_ui = FindGO<FixedUI>("ui");
	}

	if (m_ui->GetIsTimeUp()) {
		//�ǂݍ���dds������
		DecideDDS();
		//�X�v���C�g��\������ʒu������
		DecidePos();
	}

	//3�~�X�ɂȂ�����摜�\��
	if (m_isReach3Miss) {
		//�ǂݍ���dds������
		DecideDDS();
		DecidePos();
	}

	m_spriteRender->SetPivot(m_pivot);
	m_spriteRender->SetScale({m_scaleRate, m_scaleRate, FIXED_SCALE_ONE_Z });
	m_spriteRender->SetColor(m_color);

	return true;
}

void Result::Update()
{
	m_scaleRate -= SHRINK_RATE;
	if (m_scaleRate <= 1.0f) {
		m_scaleRate = 1.0f;
	}

	m_alpha += ALPHA_INCREASE_RATE;
	if (m_alpha >= 1.0f) {
		m_alpha = 1.0f;
	}
	m_color.w = m_alpha;
	m_spriteRender->SetColor(m_color);
	m_spriteRender->SetScale({m_scaleRate,m_scaleRate,FIXED_SCALE_ONE_Z });
}