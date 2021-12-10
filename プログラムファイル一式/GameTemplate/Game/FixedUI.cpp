#include "stdafx.h"
#include "FixedUI.h"
#include "FontRender.h"
#include "SpriteRender.h"
#include "SoundSource.h"
#include "GameDirector.h"
#include "CycleDirection.h"

namespace
{
	const Vector2 TIME_TEXT_POS = { -100,350 };
	const Vector2 TIME_NUMBER_POS = { 50, 350 };
	const Vector2 SCORE_ONE_POS = { -600,-250 };
	const Vector2 SCORE_TWO_POS = { 250, -250 };
	const Vector2 MISS_TEXT_ONE_POS = { -600.0f,-300.0f };
	const Vector2 MISS_TEXT_TWO_POS = { 250.0f,-300.0f };
	const Vector2 TIME_NUM_PIVOT = { 0.5f,0.5f };

	
	const Vector4 MAKE_RED = { 1.0f, 0.0f, 0.0f, 1.0f };
	const Vector4 LITTLE_COLOR_EXCEPT_RED = { 0.0f,0.02f,0.02f,0.0f };

	const int SCORE_TEXT_NUM = 2;
	const int MISS_TEXT_NUM = 2;
	const int SCORE_LEFT = 0;
	const int SCORE_RIGHT = 1;
	const int MISS_LEFT = 0;
	const int MISS_RIGHT = 1;
	const float SCALE_BIGGER = 1.5f;
	const float SE_VOLUME = 0.7f;
	const float REDUCE_SCALE = -0.01f;
	const int TEN = 10;
}

//�f�X�g���N�^
FixedUI::~FixedUI()
{
	//TIME�̌Œ蕶��������
	DeleteGO(m_textTime);
	//SCORE�̌Œ蕶��������
	for (int i = 0; i < SCORE_TEXT_NUM; i++) {
		DeleteGO(m_textScore[i]);
	}
	//�ς̎��ԕ\��������
	DeleteGO(m_time);
	//MISS�̌Œ蕶��������
	for (int i = 0; i < MISS_TEXT_NUM; i++) {
		DeleteGO(m_textMiss[i]);
	}

}

bool FixedUI::Start()
{
	//�e��\���e�L�X�g�ƈʒu����
	//����(����)
	m_textTime = NewGO<FontRender>(5);
	m_textTime->SetText(L"TIME : ");
	m_textTime->SetPosition(TIME_TEXT_POS);

	//�X�R�A��(����)
	m_textScore[SCORE_LEFT] = NewGO<FontRender>(5);
	m_textScore[SCORE_LEFT]->SetText(L"SCORE : ");
	m_textScore[SCORE_LEFT]->SetPosition(SCORE_ONE_POS);

	//�X�R�A�E(����)
	m_textScore[SCORE_RIGHT] = NewGO<FontRender>(5);
	m_textScore[SCORE_RIGHT]->SetText(L"SCORE : ");
	m_textScore[SCORE_RIGHT]->SetPosition(SCORE_TWO_POS);

	//�~�X�\��
	m_textMiss[MISS_LEFT] = NewGO<FontRender>(5);
	m_textMiss[MISS_LEFT]->SetText(L"MISS:");
	m_textMiss[MISS_LEFT]->SetPosition(MISS_TEXT_ONE_POS);
	m_textMiss[MISS_RIGHT] = NewGO<FontRender>(5);
	m_textMiss[MISS_RIGHT]->SetText(L"MISS:");
	m_textMiss[MISS_RIGHT]->SetPosition(MISS_TEXT_TWO_POS);

	//�c����
	m_time = NewGO<FontRender>(5);
	m_time->SetPivot(TIME_NUM_PIVOT);

	std::wstring fontRemainingTime;
	fontRemainingTime = std::to_wstring((int)m_remainingTime);
	
	//�c�莞�Ԃ��X�V����B
	m_time->SetText(fontRemainingTime.c_str());

	m_time->SetPosition(TIME_NUMBER_POS);

	return true;
}

void FixedUI::RemainingTimeColor()
{
	if (m_remainingTime < TEN) {
		//�ŏ�10�t���[���͐ԐF�ɂ���
		if (m_prevRemainingTime != (int)m_remainingTime) 
		{
			m_time->SetScale(SCALE_BIGGER);
			m_time->SetColor(MAKE_RED);
		}
		//10�t���[����ɂȂ�ΐԐF�ȊO�������������Ĕ��F�ɂ���B
		else
		{
			m_time->AddColorPoint(LITTLE_COLOR_EXCEPT_RED);
			m_time->AddFontScale(REDUCE_SCALE);
		}
	}
}

void FixedUI::Update()
{
	//�Q�[���v���C������Ȃ�������B
	if (!GetGameDirector().GetIsGamePlay())
	{
		//�������Ȃ��B
		return;
	}

	//�^�C�������ƃ^�C���A�b�v����
	//�ϐ�timer�̒l��60�ɂȂ�x�Ɏc����remainingTime����1�������Ă���
	//TODO �Q�[�����̎��Ԃ��v���Ă�B
	float gameTime = GameTime().GetFrameDeltaTime();

	m_prevRemainingTime = (int)m_remainingTime;
	m_remainingTime -= gameTime / 2.0f;
	//�c�莞�Ԃ�10�b�����ŁA1�b���Ƃɉ���炷
	if (m_remainingTime < TEN
		&& m_prevRemainingTime != (int)m_remainingTime) {
		//�����o���B
		m_timeSound = NewGO<CSoundSource>(0);
		m_timeSound->Init(L"Assets/sound/Time.wav", false);
		m_timeSound->SetVolume(SE_VOLUME);
		m_timeSound->Play(false);
	}

	////�^�C���A�b�v�t���O�𗧂Ă�
	if (m_remainingTime <= 0 && m_isTimeUp == false) {
		m_isTimeUp = true;
	}

	//�c���Ԃ̕ϊ��ƍX�V(int �� wstring �� const wchar_t*)
	//�c����LastTime��std::wstring�^�̕�����ɕϊ�����
	std::wstring fontRemainingTime;
	fontRemainingTime = std::to_wstring(static_cast<int>(m_remainingTime));
	//�c�莞�Ԃ��X�V����B
	m_time->SetText(fontRemainingTime.c_str());

	//�c���Ԃ����Ȃ��Ƃ��̉��o
	//�c��10�b�����ɂȂ�Ɗg��\�����k���A�F��ԐF���甒�F�ɕς��ċ����\���B
	if (m_remainingTime > 0) {
		RemainingTimeColor();
	}
}