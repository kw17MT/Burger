#include "stdafx.h"
#include "Result.h"
#include "SpriteRender.h"
#include "FixedUI.h"

Result::~Result()
{
	DeleteGO(this);
}

void Result::DecideDDS()
{

	//spriteNum�̒l�ɉ����ď������Ɏg�p����DDS��U�蕪����
	switch (spriteNum) {
	case 0: //��������
		m_spriteRender = NewGO<SpriteRender>(1);
		m_spriteRender->Init("Assets/Image/draw.dds", wideth, height);
		break;
	case 1: //����
		m_spriteRender = NewGO<SpriteRender>(1);
		m_spriteRender->Init("Assets/Image/win.dds", wideth, height);
		break;
	case 2: //�s�k
		m_spriteRender = NewGO<SpriteRender>(1);
		m_spriteRender->Init("Assets/Image/lose.dds", wideth, height);
		break;
	default:
		break;
	}

}

void Result::DecidePos()
{
	//positionNum�̒l�ɉ����ĕ\���ʒu��U�蕪����
	switch (positionNum) {
	case 0: //�������� : ��ʒ������炢
		m_spriteRender->SetPosition(center);
		break;
	case 1: //����
		m_spriteRender->SetPosition(left);
		break;
	case 2://�E��
		m_spriteRender->SetPosition(right);
		break;
	default:
		break;
	}
}

bool Result::Start()
{
	//�����A���A�E�̉摜�\���ʒu�p�ϐ���ݒ�
	center.Set(0.0f,0.0f,0.0f);
	left.Set(0.0f + 300.0f, 0.0f,0.0f);
	right.Set(0.0f - 300.0f, 0.0f,0.0f);

	//UI������
	m_ui = FindGO<FixedUI>("ui");

	return true;
}

void Result::Update()
{
	if (m_ui->GetIsTimeUp() && GetIsTimeUp() == false) {
		//�ǂݍ���dds������
		DecideDDS();
		//�X�v���C�g��\������ʒu������
		DecidePos();
		//�^�C���A�b�v�t���O�𗧂Ă�
		SetIsTimeUp();
	
	}

	//3�~�X�ɂȂ�����摜�\��
	if (isReach3Miss) {
		//�ǂݍ���dds������
		DecideDDS();
		DecidePos();
	}
}