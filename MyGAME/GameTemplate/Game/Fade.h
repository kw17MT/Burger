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
	SpriteRender* m_spriteRender;
	float m_alpha = 0.0f;	//�A���t�@�l
public:
	Fade();
	~Fade();
	//�X�V�����B
	void Update();

	

	float GetAlpha()
	{
		return m_alpha;
	}

	/// <summary>
	/// �X�e�[�g�ݒ�
	/// </summary>
	/// <param name="state">�X�e�[�g</param>
	void SetState(EnState state)
	{
		m_state = state;
	}
	/// <summary>
	/// �X�e�[�g�擾
	/// </summary>
	/// <returns>�X�e�[�g</returns>
	EnState GetState() const
	{
		return m_state;
	}
private:
	EnState m_state;	//�X�e�[�g
};
