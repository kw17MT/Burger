#pragma once
class Player;

class PlayerGene : public IGameObject
{
private:
	Vector3 m_player01Pos = { 1000.0f,0.0f,0.0f };									//�v���C���[1�̏����ʒu
	Vector3 m_player02Pos = { -1000.0f, 0.0f, 0.0f };								//�v���C���[2�̏����ʒu
	Quaternion m_player01Rot = Quaternion::Identity;								//�v���C���[1�̉�]							
	Quaternion m_player02Rot = Quaternion::Identity;								//�v���C���[2�̉�]

	int m_playerNum = 0;															//���l�v���C���[�𐶐��������̐�
	int m_noHavingDishCounter = 0;													//��̎M�̐�
	int m_refilledNum = 0;															//��[�ł�����ނ̐�
	int m_submitBurgerNum = 0;														//��o�����o�[�K�[�̐�
	int m_changeCycleNum = 0;														//����[�������BDish�Ŏg�p�B���ꂪmaxNum2Refill�Ɠ��l�ɂȂ�ƕ�[�������Ӗ����AnoHavingDish�ArefilledNum���O�ŏ���������B
	
	bool m_isGameSet = false;														//�Q�[�����I��������
	bool m_isWorking = true;														//�v���C���[�����킪�ғ������@�ғ����Ȃ�v���C���[�������I����Ă��Ȃ�

public:
	~PlayerGene();
	
	bool Start() { return true; }

	/**
	 * @brief �v���C���[��2�̏o���B
	*/
	void Update();

	/**
	 * @brief �v���C���[�P�̈ʒu��ς���
	 * @param pos �V�����ʒu���W
	*/
	void SetPlayer01Pos(Vector3 pos) { m_player01Pos = pos; }

	/**
	 * @brief �v���C���[�Q�̈ʒu��ς���
	 * @param pos �V�����ʒu���W
	*/
	void SetPlayer02Pos(Vector3 pos) { m_player02Pos = pos; }

	/**
	 * @brief ��̎M�͂������邩��Ԃ�
	 * @return ��̎M�̐�
	*/
	int GetNoHavingDishCounter() { return m_noHavingDishCounter; }

	/**
	 * @brief ��̎M�̐���1����
	*/
	void AddNoHavingDishCounter() { m_noHavingDishCounter++; }

	/**
	 * @brief ��̎M�̐���1�����@��ޒu����Ŏg���B
	*/
	void MinusNoHavingDishCounter() { m_noHavingDishCounter--; }

	/**
	 * @brief ��[�������ɋ�̎M���O�ɖ߂�
	*/
	void ResetNohavingDishCounter() { m_noHavingDishCounter = 0; }

	/**
	 * @brief ��[���������M�̐���Ԃ�
	 * @return ��[���������M�̐�
	*/
	int GetRefilledNum() { return m_refilledNum; }

	/**
	 * @brief ��[���������M�̐��������
	*/
	void AddRefilledNum() { m_refilledNum++; }

	/**
	 * @brief ��[�������ɕ�[�����M���O�ɖ߂�
	*/
	void ResetRefilledNum() { m_refilledNum = 0; }

	/**
	 * @brief ��o�����o�[�K�[�̐���1����
	*/
	void AddSubmitBurgerNum() { m_submitBurgerNum++; }

	/**
	 * @brief ��o�����o�[�K�[�̐���Ԃ�
	 * @return ��o�����o�[�K�[�̐�
	*/
	int GetSubmitBurgerNum() { return m_submitBurgerNum; }

	/**
	 * @brief ��o�����n���o�[�K�[�̐������Z�b�g����B
	*/
	void ResetSubmitBurgerNum() { m_submitBurgerNum = 0; }	

	/**
	 * @brief �����ς����񐔂��C���N�������g����B
	*/
	void AddChangeCycleNum() { m_changeCycleNum++; }

	/**
	 * @brief �����ς����񐔂�Ԃ�
	 * @return �����ς�����
	*/
	int GetChangeCycleNum() { return m_changeCycleNum; }

	/**
	 * @brief �����ς����񐔂����Z�b�g����B
	*/
	void ResetChangeCycleNum() { m_changeCycleNum = 0; }

	/**
	 * @brief �v���C���[������d�����
	 * @return true = �����Ă�, false = �~�܂��Ă�B
	*/
	bool GetPlayerGeneState() { return m_isWorking; }

	/**
	 * @brief �Q�[���͏I����Ă��邩�Ԃ�
	 * @return TRUE���I����Ă���
	*/
	bool GetIsGameSet() { return m_isGameSet; }

	/**
	 * @brief �Q�[�����I����Ă��邩�ǂ�����ݒ肷��B
	 * @param state �Q�[�����I����Ă��邩�ǂ���
	*/
	void SetIsGameSet(bool state) { m_isGameSet = state; }

private:
	Player* m_player[2] = { nullptr };
};

