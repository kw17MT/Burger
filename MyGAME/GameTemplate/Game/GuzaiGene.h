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
	static const int guzaiNum = 36;

	bool isCompletedSetGuzai = false;

	int emptyDishNumber[6];
	int emptyDishCounter = 0;
	const int LostNumber = 5;

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

	SkinModelRender* m_skinModelRender;
	Guzai* m_guzai[guzaiNum] = {nullptr};
	DishGene* m_dishGene;
	//Buff* m_buff;
};
