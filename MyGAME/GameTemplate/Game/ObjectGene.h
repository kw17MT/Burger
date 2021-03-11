#pragma once
class Guzai;
class Buff;

class ObjectGene : public IGameObject
{
private:
	//Generator�p�̃��f��
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

	//�W�F�l���[�^�[�̔ԍ��B1���E�A2����
	int GeneNo = 0;

public:
	ObjectGene();
	bool Start();
	void Update();
	void SetPosition(Vector3 pos);
	Vector3 GetPosition();
	void SetGeneNo(int num) { GeneNo = num; }

	int timer = 0;
	int Buffnum = 0;

	Guzai* m_guzai;
	Buff* m_buff;
};
