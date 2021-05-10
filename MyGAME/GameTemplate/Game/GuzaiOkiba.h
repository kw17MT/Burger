#pragma once

class Level;
class Guzai;
class Player;
class PlayerGene;

class SkinModelRender;
class Kitchen;


class GuzaiOkiba : public IGameObject
{
private:
	Vector3 m_kitchenPos[8];					//��ޒu����̍��W
	Vector3 m_kitchenScale = { 0.2f,0.2f,0.2f };
	int m_kitchenNo;							//��ޒu����̔ԍ�
	Vector3 m_playerPos[2];						//�v���C���[�̍��W
	float m_distance[8];						//�v���C���[�Ƌ�ޒu����̋���
	int m_guzaiNo;								//��ނ̔ԍ�(���)
	bool m_kitchenSet[8] = { false };			//��ޒu����ɃZ�b�g�\���H true�ŃZ�b�g�\ false�ŃZ�b�g�s�\
	bool m_guzaiSet[8] = { false };				//��ޒu����̃Z�b�g�� true�Œu����Ă��� false�Œu����Ă��Ȃ�
	bool m_targeted01 = false;					//1P���^�[�Q�b�g�����H
	bool m_targeted02 = false;					//2P���^�[�Q�b�g�����H
	Vector3 m_targetPos01 = Vector3::Zero;		//1P���A�N�Z�X�\�ȋ�ޒu����̍��W
	Vector3 m_targetPos02 = Vector3::Zero;		//2P���A�N�Z�X�\�ȋ�ޒu����̍��W
	float m_targetDistance01;					//1P���A�N�Z�X�\�ȋ�ޒu����̍��W��1P�̋���
	float m_targetDistance02;					//2P���A�N�Z�X�\�ȋ�ޒu����̍��W��2P�̋���
	int m_targetNo01;							//1P���A�N�Z�X�\�ȋ�ޒu����̔ԍ�
	int m_targetNo02;							//2P���A�N�Z�X�\�ȋ�ޒu����̔ԍ�

public:
	GuzaiOkiba();
	~GuzaiOkiba();
	bool Start();
	void Update();

	//�󂯎����2�̃x�N�g���̋�����Ԃ��֐�
	float TargetDistance(Vector3 v1, Vector3 v2);

	//�v���C���[�Ƌ�ޒu����̋����𑪂�֐�
	void PlayerDistance();

	//�v���C���[���ǂ̋�ޒu����ɃA�N�Z�X�o���邩���߂�֐�
	void Targeted();

	//��ޒu����̃Z�b�g�\�󋵂���� �����ɋ�ޒu����̔ԍ������(0�`7)
	bool FindKitchenSet(int num) { return m_kitchenSet[num]; }

	//��ޒu����̏�Ԃ���� �����ɋ�ޒu����̔ԍ������(0�`7) true�ŋ�ނ��u����Ă��� false�Œu����Ă��Ȃ�
	bool FindGuzaiSet(int num) { return m_guzaiSet[num]; }

	//��ޒu����̏�Ԃ�ύX�������Ƃ�`����֐� �����������ɋ�ޒu����̔ԍ������(0�`7) �������͋�ރZ�b�g������true ��ގ��o����false
	void GuzaiSet(int num, bool tf) { m_guzaiSet[num] = tf; }

	//��ޒu����̍��W����� �����ɋ�ޒu����̔ԍ������(0�`7)
	Vector3 GetKitchenPos(int num) { return m_kitchenPos[num]; }


	Player* pl01 = nullptr;
	Player* pl02 = nullptr;
	Guzai* guzai = nullptr;
	Kitchen* stock[8];
	SkinModelRender* m_kitchenRender[8];
	SkinModelRender* m_guzaiRender01;		//1P���^�[�Q�b�g���ɃA�N�Z�X�\�ȋ�ޒu����ɏo�����f��
	SkinModelRender* m_guzaiRender02;		//2P���^�[�Q�b�g���ɃA�N�Z�X�\�ȋ�ޒu����ɏo�����f��
};

