#pragma once
#include"SpriteRender.h"

//�X�e�[�g
enum EnState {
	enState_In,		//�t�F�[�h�C��
	enState_Out,	//�t�F�[�h�A�E�g
	enState_Wait,	//�ҋ@
};


class Fade : public IGameObject
{
private:	
	SpriteRender* m_spriteRender = nullptr;					//�摜
	float m_alpha = 0.0f;									//�A���t�@�l
public:
	Fade();
	~Fade();
	//�X�V�����B
	void Update();

	/**
	 * @brief �A���t�@�l��Ԃ�
	 * @return �����x
	*/
	float GetAlpha()
	{
		return m_alpha;
	}
	
	/**
	 * @brief �X�e�[�g�ݒ�
	 * @param state ���
	*/
	void SetState(EnState state)
	{
		m_state = state;
	}
	
	/**
	 * @brief �X�e�[�g�擾
	 * @return �X�e�[�g
	*/
	EnState GetState() const
	{
		return m_state;
	}
private:
	EnState m_state;	//�X�e�[�g
};
