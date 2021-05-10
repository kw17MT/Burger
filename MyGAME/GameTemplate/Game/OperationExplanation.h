#pragma once
#include"SpriteRender.h"

class Fade;

/// <summary>
/// �X�v���C�g�̃f�[�^
/// </summary>
struct SpriteData
{
	const char* fliePath = nullptr;		//�t�@�C���p�X
};

class OperationExplanation : public IGameObject
{
private:
	SpriteRender* m_spriteRender;
	//�X�e�[�g
	enum EnState {
		enState_Idle,
		enState_Change,			//�؂�ւ�
		enState_End				//�I���
	};
	EnState m_currentState;		//�X�e�[�g

	SpriteData m_spriteData[6];	//�X�v���C�g�̃f�[�^
	int m_currentPage = 0;		//���̃y�[�W

	//�����p
	int a = 1200;
	int b = 700;

	Fade* m_fade = nullptr;		//�t�F�[�h
public:
	OperationExplanation();
	~OperationExplanation();
	//�X�V�����B
	void Update();
};