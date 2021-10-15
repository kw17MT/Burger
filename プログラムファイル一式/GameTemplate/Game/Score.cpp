#include "stdafx.h"
#include "Score.h"
#include "Counter.h"
#include "FixedUI.h"
#include "FontRender.h"
#include "SoundSource.h"

namespace
{
	const Vector4 ADD_COLOR_AMOUNT_EXCEPT_RED = { 0.0f,0.01f,0.01f,0.0f };

	const int SCORE_POP_NUM = 2;
	const int SCORE_FOR_PLAYER_ONE = 0;
	const int SCORE_FOR_PLAYER_TWO = 1;

	const int SCORE_BASE_POINT = 100;
	const float SE_VOLUME = 0.7f;
}

Score::~Score()
{
	for (int i = 0; i < SCORE_POP_NUM; i++) {
		DeleteGO(m_score[i]);
	}
}

bool Score::Start()
{

	m_ui = FindGO<FixedUI>("ui");

	m_score[SCORE_FOR_PLAYER_ONE] = NewGO<FontRender>(5);
	m_score[SCORE_FOR_PLAYER_ONE]->SetText(L"0");
	m_score[SCORE_FOR_PLAYER_ONE]->SetPosition(m_score00Pos);

	m_score[SCORE_FOR_PLAYER_TWO] = NewGO<FontRender>(5);
	m_score[SCORE_FOR_PLAYER_TWO]->SetText(L"0");
	m_score[SCORE_FOR_PLAYER_TWO]->SetPosition(m_score01Pos);

	return true;
}

void Score::SetResult() {
	//��������
	if (m_score00 == m_score01) {
		ResultP1 = enResultP1_draw;
		ResultP2 = enResultP2_draw;
	}
	//�v���C���[1�̏���(=�v���C���[2�̔s�k)
	else if (m_score00 > m_score01) {
		ResultP1 = enResultP1_win;
		ResultP2 = enResultP2_lose;
	}
	//�v���C���[2�̏���(=�v���C���[1�̔s�k)
	else if (m_score00 < m_score01) {
		ResultP1 = enResultP1_lose;
		ResultP2 = enResultP2_win;
	}
}

void Score::AddScoreNChangeColor() {

	//�v���C���[�P�̂��߂̂���
	m_score00 = m_basePoint00 * SCORE_BASE_POINT;
	m_nowScore00 = std::to_wstring(m_score00);
	//�O�t���[���̃X�R�A�ƌ��݂̃X�R�A�������łȂ��Ƃ�
	if (wcscmp(m_nowScore00.c_str(), m_prevScore00.c_str()) != 0) {
		Vector4 RED = { 1.0f,0.0f,0.0f,1.0f };
		//�X�R�A�̐F��ԐF�ɂ���B
		m_score[SCORE_FOR_PLAYER_ONE]->SetColor(RED);
		//�O�t���[���̃X�R�A���L�^����B
		m_prevScore00 = m_nowScore00;
		//����炷�B
		m_moneySound = NewGO<CSoundSource>(0);
		m_moneySound->Init(L"Assets/sound/Money.wav", false);
		m_moneySound->SetVolume(SE_VOLUME);
		m_moneySound->Play(false);
		//�����̐F��ԐF���珙�X�ɔ��F�ɂ��鏀��������B
		m_isChangeColor00 = true;
	}

	//���݂̃X�R�A��\������B
	m_score[SCORE_FOR_PLAYER_ONE]->SetText(m_nowScore00.c_str());
	//�X�R�A�̐F��ς��Ȃ���΂Ȃ�Ȃ��Ȃ��
	if (m_isChangeColor00 == true) {
		//�ԐF�ȊO�̗v�f�������������Ă����B
		m_score[SCORE_FOR_PLAYER_ONE]->AddColorPoint(ADD_COLOR_AMOUNT_EXCEPT_RED);
		//RBG���ׂĂ̐F��1.0f�ȏ�ɂȂ�����F�̕ύX����߂�B
		if (m_score[SCORE_FOR_PLAYER_ONE]->GetColorVolume() >= 1.0f) {
			m_isChangeColor00 = false;
		}
	}

	//�v���C���[�Q�̂��߂̂���
	m_score01 = m_basePoint01 * SCORE_BASE_POINT;
	m_nowScore01 = std::to_wstring(m_score01);
	//�����łȂ��Ƃ�
	if (wcscmp(m_nowScore01.c_str(), m_prevScore01.c_str()) != 0) {
		Vector4 RED = { 1.0f,0.0f,0.0f,1.0f };
		m_score[SCORE_FOR_PLAYER_TWO]->SetColor(RED);
		m_prevScore01 = m_nowScore01;

		//����炷�B
		m_moneySound = NewGO<CSoundSource>(0);
		m_moneySound->Init(L"Assets/sound/Money.wav", false);
		m_moneySound->SetVolume(SE_VOLUME);
		m_moneySound->Play(false);

		m_isChangeColor01 = true;
	}

	m_score[SCORE_FOR_PLAYER_TWO]->SetText(m_nowScore01.c_str());
	if (m_isChangeColor01 == true) {
		m_score[SCORE_FOR_PLAYER_TWO]->AddColorPoint(ADD_COLOR_AMOUNT_EXCEPT_RED);
		if (m_score[SCORE_FOR_PLAYER_TWO]->GetColorVolume() >= 1.0f) {
			m_isChangeColor01 = false;
		}
	}
}


void Score::Update()
{
	if (m_ui->GetIsTimeUp() == true && m_isTimeUp == false) {
		//�^�C���A�b�v���A�v���C���[���ꂼ��ɏ��s�̏�Ԃ��L�^����
		SetResult();
		//score���̃^�C���A�b�v�t���O��true�ɂ���(�����1�񂾂��ɂ���)
		SetIsTimeUp();
	}
	AddScoreNChangeColor();
}