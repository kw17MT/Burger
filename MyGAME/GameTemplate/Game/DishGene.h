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
	int m_popedDishNum = 0;						//�M�����o���Ă��邩�B		
	bool m_dishGeneState = true;				//�M������͉ғ����Ă��邩FALSE���S���̎M���o���I����
	static const int m_dishMaxNum = 36;			//�o���M�̍ő吔
	bool m_setSoundFlag = false;				//�M�ɋ�ނ��u�����Ƃ��ɖ鉹���łĂ��邩
	bool m_fallingSoundFlag = false;			//��ނ��~���ė���Ƃ��ɖ鉹���łĂ��邩

	std::map<int, DishData> m_dishData;
public:
	DishGene() {};
	~DishGene();

	/**
	 * @brief 	�쐬�������x����p���āA�M���|�b�v������ʒu�������A�o���B
	 * @return true
	*/
	bool Start();

	/**
	 * @brief ���ݎM�̐�����͓����Ă��邩
	 * @return FALSE���o���I���Ď~�܂��Ă���ATRUE�������Ă���
	*/
	bool GetDishGeneState() { return m_dishGeneState; }
	
	/**
	 * @brief �����ɎM�̔ԍ������邱�Ƃł��̔ԍ��̃|�W�V������Ԃ��B
	 * @param number �M�̔ԍ�
	 * @return �M�̔ԍ��ɑΉ������ʒu���W
	*/
	Vector3 GetDishPositionBasedNumber(int number);

	/**
	 * @brief �M�ɋ�ނ��u���ꂽ�����������H
	 * @return FALSE���Ȃ��Ă��Ȃ��B
	*/
	bool GetSetSound() { return m_setSoundFlag; }

	/**
	 * @brief ��ނ��~���Ă��������������H
	 * @return 
	*/
	bool GetFallingSound() { return m_fallingSoundFlag; }

	/**
	 * @brief �M�ɋ�ނ��u���ꂽ������������ݒ�B
	 * @param tf �����������ǂ���
	*/
	void SetSetSound(bool tf) { m_setSoundFlag = tf; }

	/**
	 * @brief ��ނ��~���Ă���������������ݒ�
	 * @param tf �����������ǂ���
	*/
	void SetFallingSound(bool tf) { m_fallingSoundFlag = tf; }

private:
	//Dish* m_Dish[m_dishMaxNum] = { nullptr };
	std::array<Dish*, m_dishMaxNum> m_Dish = { nullptr };
};

