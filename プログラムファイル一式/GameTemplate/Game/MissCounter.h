#pragma once
class SpriteRender;
class Level2D;
class Result;
#include "Level2D.h"

class MissCounter : public IGameObject
{
private:
	int m_pl1MissCount = 0;								//�v���C���[�P�̃~�X��				
	int m_pl2MissCount = 0;								//�v���C���[�Q�̃~�X��

	bool m_pl1Win = false;								//�v���C���[1�͏�������
	bool m_pl2Win = false;								//�v���C���[2�͏�������
	bool m_shouldChangeFilePath = false;				//�ǂꂩ�̉摜��ς���ׂ���
	bool m_isGameSet = false;							//�Q�[�����I��������
public:
	~MissCounter();

	/**
	 * @brief ���x����p�����摜�̔z�u
	 * @return true
	*/
	bool Start();

	/**
	 * @brief �v���C���[�̃~�X���ɉ����ĉ摜��ύX����BWIN,LOSE�̌��ʔ��\��
	*/
	void Update();

	/**
	 * @brief �v���C���[�P�̃~�X�������Z����
	*/
	void AddPl1MissCount() { m_pl1MissCount++; }
	
	/**
	 * @brief �v���C���[�Q�̃~�X�������Z����
	*/
	void AddPl2MissCount() { m_pl2MissCount++; }

	/**
	 * @brief �ǂꂩ�̉摜��ύX����ׂ���
	 * @param state TRUE������ׂ�
	*/
	void ChangeMarkState(bool state) { m_shouldChangeFilePath = state; }

	/**
	 * @brief �l�p�̉摜���o�c�̉摜�ɕς���B
	*/
	void TurnSquareIntoCross();

	/**
	 * @brief ���ʂ̉摜���o��������B
	*/
	void PopResultSprite();

private:
	Level2D m_level2D;											//���x���QD�̎擾�p
	std::array<Result*, 2> m_result = {nullptr};				//���U���g�\������摜�擾�p
	std::array<SpriteRender*, 6> m_spriteRender = { nullptr };	//�~�X�J�E���^�[�p�̉摜
};

