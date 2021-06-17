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
	//�X�e�[�g
	enum EnState {
		enState_Idle,
		enState_Change,			//�؂�ւ�
		enState_End				//�I���
	};
	EnState m_currentState;		//�X�e�[�g

	int m_currentPage = 0;		//���̃y�[�W
	int m_nextWidth = 1200;		//���̉��̒���
	int m_nextHeight = 700;		//���̏c�̒���

public:
	/**
	 * @brief �摜�̏�����
	*/
	OperationExplanation();

	~OperationExplanation();

	//�X�V�����B
	void Update();
private:
	Fade* m_fade = nullptr;		//�t�F�[�h
	SpriteData m_spriteData[6];	//�X�v���C�g�̃f�[�^
	SpriteRender* m_spriteRender;
};