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
	bool GetDishGeneState() const { return m_dishGeneState; }
	
	/**
	 * @brief �����ɎM�̔ԍ������邱�Ƃł��̔ԍ��̃|�W�V������Ԃ��B
	 * @param number �M�̔ԍ�
	 * @return �M�̔ԍ��ɑΉ������ʒu���W
	*/
	Vector3 GetDishPositionBasedNumber(int number);

	/**
	 * @brief ��ނ��~���Ă��������������H
	 * @return 
	*/
	bool GetFallingSound() const { return m_fallingSoundFlag; }

	/**
	 * @brief ��ނ��~���Ă���������������ݒ�
	 * @param playingSound �����������ǂ���
	*/
	void SetFallingSound(bool playingSound) { m_fallingSoundFlag = playingSound; }

private:
	std::array<Dish*, m_dishMaxNum> m_Dish = { nullptr };
};

