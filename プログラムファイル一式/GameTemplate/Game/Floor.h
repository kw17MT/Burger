#pragma once
class SkinModelRender;
#include "SkinModelRender.h"

class Floor : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;				//���̈ʒu
	Vector3 m_scale = Vector3::One;					//���̊g�嗦

	bool m_isRed = false;								//�Ԃ����ɂ��邩�ǂ���

public:
	~Floor();

	/**
	 * @brief ���f���̏��������s��
	 * @return true
	*/
	bool Start();

	/**
	 * @brief �ʒu�̍X�V���s��
	*/
	void Update();

	/**
	 * @brief �V�����ʒu��ݒ肷��B
	 * @param pos �V�����ʒu
	*/
	void SetPosition(const Vector3 pos) { m_position = pos; }

	/**
	 * @brief �Ԃ����ɂ��邩�����ɂ��邩
	 * @param filePath ���f���̃t�@�C���p�X
	*/
	void ChangeModel(const char* filePath) { m_skinModelRender->ChangeModel(filePath); }

	/**
	 * @brief �Ԃ������ǂ����ݒ肷��
	 * @param red TRUE���ԁ@FALSE����
	*/
	void SetRed(const bool red) { m_isRed = red; }

	void SetScale(const Vector3 scale) { m_scale = scale; }

private:
	SkinModelRender* m_skinModelRender = nullptr;		//���p���f��
};

