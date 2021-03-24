#include "stdafx.h"
#include "Score.h"
#include "Counter.h"
#include "FixedUI.h"

bool Score::Start()
{

	m_ui = FindGO<FixedUI>("ui");

	return true;
}

void Score::SetResult() {
	//��������
	if (Score01 == Score02) {
		ResultP1 = enResultP1_draw;
		ResultP2 = enResultP2_draw;
	}
	//�v���C���[1�̏���(=�v���C���[2�̔s�k)
	else if (Score01 > Score02) {
		ResultP1 = enResultP1_win;
		ResultP2 = enResultP2_lose;
	}
	//�v���C���[2�̏���(=�v���C���[1�̔s�k)
	else if (Score01 < Score02) {
		ResultP1 = enResultP1_lose;
		ResultP2 = enResultP2_win;
	}
}


void Score::Update()
{
	
	if (m_ui->GetIsTimeUp() == true && GetIsTimeUp() == false) {
		//�^�C���A�b�v���A�v���C���[���ꂼ��ɏ��s�̏�Ԃ��L�^����
		SetResult();
		//score���̃^�C���A�b�v�t���O��true�ɂ���(�����1�񂾂��ɂ���)
		SetIsTimeUp();
	}


	//�O�P�͂PP�́A�O�Q�͂QP�̃X�R�A
	Font score01;
	Font score02;
	Vector4 color = { 1.0f,1.0f,1.0,1.0f };

	Score01 = BasePoint01 * 100;
	std::wstring str01;
	str01 = std::to_wstring(Score01);

	Score02 = BasePoint02 * 100;
	std::wstring str02;
	str02 = std::to_wstring(Score02);

	score01.Begin(renderContext);
	score01.Draw(str01.c_str(), { -400.0f,-300.0f }, color, 0.0f, 1.0f, { 0.0f, 0.0f });
	score01.End(renderContext);

	score02.Begin(renderContext);
	score02.Draw(str02.c_str(), { 550.0f,-300.0f }, color, 0.0f, 1.0f, { 0.0f, 0.0f });
	score02.End(renderContext);
}