#include "stdafx.h"
#include "Score.h"
#include "Counter.h"
#include "FixedUI.h"
#include "FontRender.h"
#include "SoundSource.h"

bool Score::Start()
{

	m_ui = FindGO<FixedUI>("ui");

	Score[0] = NewGO<FontRender>(5);
	Score[0]->SetText(L"0");
	Score[0]->SetPosition(Score01Pos);

	Score[1] = NewGO<FontRender>(5);
	Score[1]->SetText(L"0");
	Score[1]->SetPosition(Score02Pos);

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

void Score::AddScoreNChangeColor() {

	//�v���C���[�P�̂��߂̂���
	Score01 = BasePoint01 * 100;
	nowScore01 = std::to_wstring(Score01);
	//�O�t���[���̃X�R�A�ƌ��݂̃X�R�A�������łȂ��Ƃ�
	if (wcscmp(nowScore01.c_str(), prevScore01.c_str()) != 0) {
		Vector4 RED = { 1.0f,0.0f,0.0f,1.0f };
		//�X�R�A�̐F��ԐF�ɂ���B
		Score[0]->SetColor(RED);
		//�O�t���[���̃X�R�A���L�^����B
		prevScore01 = nowScore01;
		//����炷�B
		moneySound = NewGO<CSoundSource>(0);
		moneySound->Init(L"Assets/sound/Money.wav", false);
		moneySound->SetVolume(0.7f);
		moneySound->Play(false);
		//�����̐F��ԐF���珙�X�ɔ��F�ɂ��鏀��������B
		isChangeColor01 = true;
	}

	//���݂̃X�R�A��\������B
	Score[0]->SetText(nowScore01.c_str());
	//�X�R�A�̐F��ς��Ȃ���΂Ȃ�Ȃ��Ȃ��
	if (isChangeColor01 == true) {
		//�ԐF�ȊO�̗v�f�������������Ă����B
		Vector4 addColorExceptRed = { 0.0f,0.01f,0.01f,0.0f };
		Score[0]->AddColorPoint(addColorExceptRed);
		//RBG���ׂĂ̐F��1.0f�ȏ�ɂȂ�����F�̕ύX����߂�B
		//operator==
		if (Score[0]->GetColorVolume() >= 1.0f) {
			isChangeColor01 = false;
		}
	}

	//�v���C���[�Q�̂��߂̂���
	Score02 = BasePoint02 * 100;
	nowScore02 = std::to_wstring(Score02);
	//�����łȂ��Ƃ�
	if (wcscmp(nowScore02.c_str(), prevScore02.c_str()) != 0) {
		Vector4 RED = { 1.0f,0.0f,0.0f,1.0f };
		Score[1]->SetColor(RED);
		prevScore02 = nowScore02;

		//����炷�B
		moneySound = NewGO<CSoundSource>(0);
		moneySound->Init(L"Assets/sound/Money.wav", false);
		moneySound->SetVolume(0.7f);
		moneySound->Play(false);

		isChangeColor02 = true;
	}

	Score[1]->SetText(nowScore02.c_str());
	if (isChangeColor02 == true) {
		Vector4 addColorExceptRed = { 0.0f,0.01f,0.01f,0.0f };
		Score[1]->AddColorPoint(addColorExceptRed);
		if (Score[1]->GetColorVolume() >= 1.0f) {
			isChangeColor02 = false;
		}
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

	AddScoreNChangeColor();
}