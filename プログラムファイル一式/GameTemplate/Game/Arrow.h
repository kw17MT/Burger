#pragma once
#include "SkinModelRender.h"

/**
 * @brief ��ޒu����̋߂��Ƀv���C���[������Əo������B
 * �����ڂ̃T�|�[�g���s���I�u�W�F�N�g
*/
class Arrow : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	int m_timer = 0;
	float m_setYPos = 0.0f;
	bool m_scaleMaxFlag = false;
	bool m_scaleMinFlag = false;
public:
	Arrow() {}
	~Arrow();

	/**
	 * @brief ���̃��f���̏�����
	 * @return true
	*/
	bool Start();

	/**
	 * @brief �㉺�ɓ����Ȃ��畂�V������
	*/
	void Update();
	
	/**
	 * @brief �������W�ɂ���ď㉺������B
	*/
	void Float();

	/**
	 * @brief �g�又��
	*/
	void Expansion();

	/**
	 * @brief �k������
	*/
	void Shrink();

	/**
	 * @brief �V�����|�W�V�����̐ݒ�
	 * @param pos �V�����ʒu���W
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }

	/**
	 * @brief �V�����X�P�[���̐ݒ�
	 * @param scale �V�����X�P�[��
	*/
	void SetScale(Vector3 scale) { m_scale = scale; }

	/**
	 * @brief �g�嗦���ő�ɂȂ�����̃t���O���擾����
	 * @return �g�嗦�͍ő�ɂȂ�����
	*/
	bool GetScaleMax() const { return m_scaleMaxFlag; }

	/**
	 * @brief �g�嗦���ŏ��ɂȂ�����̃t���O���擾����
	 * @return �g�嗦�͍ŏ��ɂȂ�����
	*/
	bool GetScaleMin() const { return m_scaleMinFlag; }

private:
	SkinModelRender* m_skinModelRender = nullptr;		//���̃��f��
};

