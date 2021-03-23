#include "stdafx.h"
#include "FixedUI.h"

void FixedUI::Update()
{
	Font fontTime;
	//�J���[
	Vector4 color = { 1.0f,1.0f,1.0,1.0f };
	//TIME�̕���
	fontTime.Begin(renderContext);
	fontTime.Draw(L"TIME :", posTime, color, 0.0f, 1.0f, { 0.0f, 0.0f });
	fontTime.End(renderContext);
	//�v���C���[1��ITEM����
	fontTime.Begin(renderContext);
	fontTime.Draw(L"ITEM", posItem01, color, 0.0f, 1.0f, { 0.0f, 0.0f });
	fontTime.End(renderContext);
	//�v���C���[2��ITEM����
	fontTime.Begin(renderContext);
	fontTime.Draw(L"ITEM", posItem02, color, 0.0f, 1.0f, { 0.0f, 0.0f });
	fontTime.End(renderContext);
	//�v���C���[1��SCORE����
	fontTime.Begin(renderContext);
	fontTime.Draw(L"SCORE :", posScore01, color, 0.0f, 1.0f, { 0.0f, 0.0f });
	fontTime.End(renderContext);
	//�v���C���[2��SCORE����
	fontTime.Begin(renderContext);
	fontTime.Draw(L"SCORE :", posScore02, color, 0.0f, 1.0f, { 0.0f, 0.0f });
	fontTime.End(renderContext);

	//�^�C����������
	//�ϐ�timer�̒l��60�ɂȂ�x�Ɏc����LastTime����1�������Ă���
	//Font Timer;
	timer++;
	if (timer == 60) {
		if (LastTime > 0) {
			LastTime--;
		}
		timer = 0;
	}

	


	//�c����LastTime��std::wstring�^�̕�����ɕϊ�����
	std::wstring fontLastTime;
	fontLastTime = std::to_wstring(LastTime);

	//�c���Ԃ̕\��
	fontTime.Begin(renderContext);
	fontTime.Draw(fontLastTime.c_str(), posLastTime, color, 0.0f, 1.0f, { 0.0f, 0.0f });
	fontTime.End(renderContext);

}