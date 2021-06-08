#pragma once
class Level;
class Guzai;
class Player;
class PlayerGene;
class SkinModelRender;
class Kitchen;
class Arrow;

class GuzaiOkiba : public IGameObject
{
private:
	Vector3 m_guzaiOkibaPos[8];						//��ޒu����̍��W
	Vector3 m_guzaiOkibaScale = Vector3::One;		//�L�b�`����
	int m_guzaiOkibaNo;								//��ޒu����̔ԍ�
	Vector3 m_playerPos[2];							//�v���C���[�̍��W
	float m_distance[8];							//�v���C���[�Ƌ�ޒu����̋���
	int m_guzaiType = 0;							//��ނ̔ԍ�(���)
	bool m_guzaiOkibaSet[8] = { false };			//��ޒu����ɃZ�b�g�\���H true�ŃZ�b�g�\ false�ŃZ�b�g�s�\
	bool m_guzaiSet[8] = { false };					//��ޒu����̃Z�b�g�� true�Œu����Ă��� false�Œu����Ă��Ȃ�
	bool m_targeted01 = false;						//1P���^�[�Q�b�g�����H
	bool m_targeted02 = false;						//2P���^�[�Q�b�g�����H
	Vector3 m_targetPos01 = Vector3::Zero;			//1P���A�N�Z�X�\�ȋ�ޒu����̍��W
	Vector3 m_targetPos02 = Vector3::Zero;			//2P���A�N�Z�X�\�ȋ�ޒu����̍��W
	float m_targetDistance01;						//1P���A�N�Z�X�\�ȋ�ޒu����̍��W��1P�̋���
	float m_targetDistance02;						//2P���A�N�Z�X�\�ȋ�ޒu����̍��W��2P�̋���
	int m_targetNo01;								//1P���A�N�Z�X�\�ȋ�ޒu����̔ԍ�
	int m_targetNo02;								//2P���A�N�Z�X�\�ȋ�ޒu����̔ԍ�
	Vector3 m_Arrow01Pos = { 0.0f,-1000.0f,0.0f };	//1P�p�̖��̍��W
	Vector3 m_Arrow02Pos = { 0.0f,-1000.0f,0.0f };	//2P�p�̖��̍��W
	Vector3 m_Arrow1Scale = Vector3::One;			//1P�p�̖��̊g�嗦
	Vector3 m_Arrow2Scale = Vector3::One;			//2P�p�̖��̊g�嗦
	float m_Arrow1ScaleSize = 1.0f;

public:
	GuzaiOkiba() {};
	~GuzaiOkiba();

	/**
	 * @brief 8�̋�ޒu����̃|�b�v�ƈʒu�̊m��
	 * @return true
	*/
	bool Start();

	/**
	 * @brief �߂���ޒu����̃^�[�Q�e�B���O�Ƃ���ɔ������̃|�b�v
	*/
	void Update();

	/**
	 * @brief �󂯎����2�̃x�N�g���̋�����Ԃ��֐�
	 * @param v1 �n�_�P
	 * @param v2 �n�_�Q
	 * @return 2�n�_�Ԃ̋���
	*/
	float TargetDistance(Vector3 v1, Vector3 v2);

	/**
	 * @brief �v���C���[�Ƌ�ޒu����̋����𑪂�֐�
	*/
	void PlayerDistance();

	/**
	 * @brief ��ޒu����ƃv���C���[�̋����𑪂�A�͈͓��̈�̋�ޒu����ɂ̂݃A�N�Z�X�\�ɂ���B
	*/
	void Targeted();

	/**
	 * @brief ��ޒu����̃Z�b�g�\�󋵂����
	 * @param num ��ޒu����̔ԍ������(0�`7)
	 * @return �Z�b�g�󋵂𓾂�
	*/
	bool FindKitchenSet(int num) { return m_guzaiOkibaSet[num]; }

	/**
	 * @brief ��ޒu����̏�Ԃ����
	 * @param num ��ޒu����̔ԍ������(0�`7)
	 * @return TRUE���u����Ă���AFALSE���u����Ă��Ȃ�
	*/
	bool FindGuzaiSet(int num) { return m_guzaiSet[num]; }

	/**
	 * @brief ��ޒu����̏�Ԃ�ύX�������Ƃ�`����֐�
	 * @param num ��ޒu����̔ԍ������(0�`7)
	 * @param tf ��ރZ�b�g������true ��ގ��o����false
	*/
	void GuzaiSet(int num, bool tf) { m_guzaiSet[num] = tf; }

	/**
	 * @brief ��ޒu����̍��W�����
	 * @param num �����ɋ�ޒu����̔ԍ������(0�`7)
	 * @return �u����̍��W
	*/
	Vector3 GetKitchenPos(int num) { return m_guzaiOkibaPos[num]; }

private:
	Player* m_player00 = nullptr;
	Player* m_player01 = nullptr;
	SkinModelRender* m_guzaiOkibaRender[8]{ nullptr };
	Arrow* m_arrow00 = nullptr;
	Arrow* m_arrow01 = nullptr;
};

