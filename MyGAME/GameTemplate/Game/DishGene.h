#pragma once
class Level;
class Dish;
class Guzai;

struct DishData {
	Vector3 s_dishPosition;
	int s_number;
};

class DishGene : public IGameObject
{
private:
	int DishNum = 0;
	bool DishGeneState = true;
	
	static const int dishNum = 37;

	std::map<int, DishData> m_dishData;
public:

	DishGene() {};
	~DishGene();

	bool Start();
	bool GetDishGeneState() { return DishGeneState; }
	//�����ɎM�̔ԍ������邱�Ƃł��̔ԍ��̃|�W�V������Ԃ��B
	Vector3 GetDishPositionBasedNumber(int number);

	Dish* m_Dish[dishNum];
};

