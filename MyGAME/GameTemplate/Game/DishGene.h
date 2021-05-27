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
	
	static const int dishNum = 36;

	std::map<int, DishData> m_dishData;

	bool m_setSoundFlag = false;		//�M�ɋ�ނ��u�����Ƃ��ɖ鉹
	bool m_fallingSoundFlag = false;	//��ނ��~���ė���Ƃ��ɖ鉹
public:

	DishGene() {};
	~DishGene();

	bool Start();
	bool GetDishGeneState() { return DishGeneState; }
	//�����ɎM�̔ԍ������邱�Ƃł��̔ԍ��̃|�W�V������Ԃ��B
	Vector3 GetDishPositionBasedNumber(int number);

	//�M�ɋ�ނ��u���ꂽ�����������H
	bool GetSetSound() { return m_setSoundFlag; }
	//��ނ��~���Ă��������������H
	bool GetFallingSound() { return m_fallingSoundFlag; }
	//�M�ɋ�ނ��u���ꂽ������������ݒ�B
	void SetSetSound(bool tf) { m_setSoundFlag = tf; }
	//��ނ��~���Ă���������������ݒ�B
	void SetFallingSound(bool tf) { m_fallingSoundFlag = tf; }

	Dish* m_Dish[dishNum] = { nullptr };
};

