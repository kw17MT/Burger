#include "stdafx.h"
#include "Result.h"
#include "SpriteRender.h"
#include "FixedUI.h"
#include "GameDirector.h"

Result::~Result()
{
	//DeleteGO(this);
	DeleteGO(m_spriteRender);
}

void Result::DecideDDS()
{
	//spriteNum�̒l�ɉ����ď������Ɏg�p����DDS��U�蕪����
	switch (spriteNum) {
	case 0: //��������
		//m_spriteRender = NewGO<SpriteRender>(1);
		m_spriteRender->Init("Assets/Image/draw.dds", wideth*0.75f, height*0.75f);
		break;
	case 1: //����
		//m_spriteRender = NewGO<SpriteRender>(1);
		m_spriteRender->Init("Assets/Image/win.dds", wideth*0.75f, height*0.75f);
		break;
	case 2: //�s�k
		//m_spriteRender = NewGO<SpriteRender>(1);
		m_spriteRender->Init("Assets/Image/lose.dds", wideth*0.5f, height*0.5f);
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
	m_spriteRender = NewGO<SpriteRender>(1);
	
	//�����A���A�E�̉摜�\���ʒu�p�ϐ���ݒ�
	center.Set(0.0f,0.0f,0.0f);
	left.Set(0.0f + 450.0f, 0.0f,0.0f);
	right.Set(0.0f - 450.0f, 0.0f,0.0f);

	//UI������
	if (m_ui == nullptr) {
		m_ui = FindGO<FixedUI>("ui");
	}

	if (m_ui->GetIsTimeUp() && isTimeUp == false) {
		//�ǂݍ���dds������
		DecideDDS();
		//�X�v���C�g��\������ʒu������
		DecidePos();
		//�^�C���A�b�v�t���O�𗧂Ă�
		isTimeUp = true;
	}

	//3�~�X�ɂȂ�����摜�\��
	if (isReach3Miss) {
		//�ǂݍ���dds������
		DecideDDS();
		DecidePos();
	}

	m_spriteRender->SetPivot({0.5f,0.5f});
	m_spriteRender->SetScale({ 1.0f * m_scaleRate,1.0f * m_scaleRate,1.0f });
	m_spriteRender->SetColor({ 1.0f,1.0f,1.0f,m_alpha });

	return true;
}

void Result::Update()
{
	m_scaleRate -= 0.08f;
	if (m_scaleRate <= 1.0f) {
		m_scaleRate = 1.0f;
	}

	m_alpha += 0.03f;
	if (m_alpha >= 1.0f) {
		m_alpha = 1.0f;
	}



//	if (tf == true) {
//		return;
//	}
//	if (m_ui->GetIsTimeUp() && GetIsTimeUp() == false) {
//		//�ǂݍ���dds������
//		DecideDDS();
//		//�X�v���C�g��\������ʒu������
//		DecidePos();
//		//�^�C���A�b�v�t���O�𗧂Ă�
//		SetIsTimeUp();
//	
//	}
//
//	//3�~�X�ɂȂ�����摜�\��
//	if (isReach3Miss) {
//		//�ǂݍ���dds������
//		DecideDDS();
//		DecidePos();
//	}
//	tf = true;

	m_spriteRender->SetColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_spriteRender->SetScale({ 1.0f * m_scaleRate,1.0f * m_scaleRate,1.0f });

}