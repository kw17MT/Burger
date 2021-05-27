#pragma once
class Guzai;
//class Buff;
class DishGene;
class SkinModelRender;

#include <vector>

class GuzaiGene : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;
	const Vector3 m_scale = Vector3::Zero;
	static const int guzaiNum = 36 + 20;

	bool isCompletedSetGuzai = false;

	int emptyDishNumber[6];
	int emptyDishCounter = 0;
	const int LostNumber = 5;
	int m_guzaiNum = 0;					//��ނ̏o�Ă��鐔
	bool m_guzaiFlag[99] = { false };	//��ނ��o�Ă��邩�ǂ����̃t���O�B

	Vector3 m_setPos = Vector3::Zero;
public:
	GuzaiGene() {};
	~GuzaiGene();
	//������̍��W�ݒ�B
	bool Start();
	//��ނ𐶐�����B
	//�����_���ϐ���p���ăo�t���o�����ۂ������߂Ă���B
	void Update();

	bool GetInitialActionState() { return isCompletedSetGuzai; }

	//��ނ����݂��Ă��邩�H(�����ɔԍ������)
	bool GetGuzaiFlag(int number) { return m_guzaiFlag[number]; }

	//��ނ̑��ݏ�Ԃ�ύX�B(�����ɔԍ������)
	void SetGuzaiFlag(int number, bool tf) { m_guzaiFlag[number] = tf; }

	SkinModelRender* m_skinModelRender = nullptr;
	Guzai* m_guzai[99] = {nullptr};
	DishGene* m_dishGene = nullptr;
	//Buff* m_buff;
};
