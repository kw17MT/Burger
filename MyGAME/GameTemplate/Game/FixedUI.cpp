#include "stdafx.h"
#include "FixedUI.h"
#include "FontRender.h"
#include "SpriteRender.h"
#include "SoundSource.h"
#include "GameDirector.h"
#include "CycleDirection.h"

//�f�X�g���N�^
FixedUI::~FixedUI()
{
	DeleteGO(TextTime);

	for (int i = 0; i < 2; i++) {
		DeleteGO(TextScore[i]);
	}

	DeleteGO(Time);
	
	for (int i = 0; i < 2; i++) {
		DeleteGO(TextMiss[i]);
	}

}

bool FixedUI::Start()
{
	//�e��\���e�L�X�g�ƈʒu����
	//����(����)
	TextTime = NewGO<FontRender>(5);
	TextTime->SetText(L"TIME : ");
	TextTime->SetPosition(posTime);

	//�X�R�A��(����)
	TextScore[0] = NewGO<FontRender>(5);
	TextScore[0]->SetText(L"SCORE : ");
	TextScore[0]->SetPosition(posScore01);

	//�X�R�A�E(����)
	TextScore[1] = NewGO<FontRender>(5);
	TextScore[1]->SetText(L"SCORE : ");
	TextScore[1]->SetPosition(posScore02);

	//�~�X�\��
	TextMiss[0] = NewGO<FontRender>(5);
	TextMiss[0]->SetText(L"MISS:");
	TextMiss[0]->SetPosition(posMiss01);
	TextMiss[1] = NewGO<FontRender>(5);
	TextMiss[1]->SetText(L"MISS:");
	TextMiss[1]->SetPosition(posMiss02);

	//�c����
	Time = NewGO<FontRender>(5);
	Time->SetPivot({ 0.5f,0.5f });

	std::wstring fontRemainingTime;
	fontRemainingTime = std::to_wstring(remainingTime);
	
	//�c�莞�Ԃ��X�V����B
	Time->SetText(fontRemainingTime.c_str());

	Time->SetPosition(posLastTime);

	return true;
}

void FixedUI::RemainingTimeColor()
{
	if (remainingTime < 10) {
		if (timer < 10) {
			const float Scale = 1.5f;
			const Vector4 RED = { 1.0f, 0.0f, 0.0f, 1.0f };
			Time->SetScale(Scale);
			Time->SetColor(RED);
		}
		if (timer >= 10) {
			const float reduceScale = -0.01f;
			const Vector4 addColorExceptRed = { 0.0f,0.02f,0.02f,0.0f };
			Time->AddColorPoint(addColorExceptRed);
			Time->AddFontScale(reduceScale);
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
	timer++;
	if (timer >= 60) {
		if (remainingTime > 0) {
			remainingTime--;
		}
		if (remainingTime < 10) {
			//�����o���B
			timeSound = NewGO<CSoundSource>(0);
			timeSound->Init(L"Assets/sound/Time.wav", false);
			timeSound->SetVolume(0.7f);
			timeSound->Play(false);
		}
		timer = 0;
	}
	////�^�C���A�b�v�t���O�𗧂Ă�
	if (remainingTime <= 0 && isTimeUp == false) {
		isTimeUp = true;
	}

	//�c���Ԃ̕ϊ��ƍX�V(int �� wstring �� const wchar_t*)
	//�c����LastTime��std::wstring�^�̕�����ɕϊ�����
	std::wstring fontRemainingTime;
	fontRemainingTime = std::to_wstring(remainingTime);
	//�c�莞�Ԃ��X�V����B
	Time->SetText(fontRemainingTime.c_str());

	//�c���Ԃ����Ȃ��Ƃ��̉��o
	//�c��10�b�����ɂȂ�Ɗg��\�����k���A�F��ԐF���甒�F�ɕς��ċ����\���B
	if (remainingTime > 0) {
		RemainingTimeColor();
	}
}