#pragma once
class Player;

class PlayerGene : public IGameObject
{
private:
	Vector3 m_player01Pos = { 1000.0f,0.0f,0.0f };									//�v���C���[1�̏����ʒu
	Vector3 m_player02Pos = { -1000.0f, 0.0f, 0.0f };								//�v���C���[2�̏����ʒu
	Quaternion m_player01Rot = Quaternion::Identity;								//�v���C���[1�̉�]							
	Quaternion m_player02Rot = Quaternion::Identity;								//�v���C���[2�̉�]
	
	bool m_isWorking = true;														//�v���C���[�����킪�ғ������@�ғ����Ȃ�v���C���[�������I����Ă��Ȃ�

public:
	~PlayerGene();

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
	 * @brief �v���C���[������d�����
	 * @return true = �����Ă�, false = �~�܂��Ă�B
	*/
	bool GetPlayerGeneState() const { return m_isWorking; }

private:
	std::array<Player*, 2> m_player = { nullptr };				//�o��������v���C���[���f��
};