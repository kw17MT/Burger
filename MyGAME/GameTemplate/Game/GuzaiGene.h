#pragma once
class Guzai;
class DishGene;
class SkinModelRender;

#include <vector>

class GuzaiGene : public IGameObject
{
private:
	static const int m_guzaiNum = 36 + 20;

	int m_emptyDishNumber[6];						//��̎M�̔ԍ���ۑ����Ă����B
	int m_emptyDishCounter = 0;						//��������̎M�����邩�B
	const int m_lostNumber = 5;						//��[���J�n�����̎M�̐�
	bool m_guzaiFlag[99] = { false };				//��ނ��o�Ă��邩�ǂ����̃t���O�B

	Vector3 m_setPos = Vector3::Zero;
public:
	GuzaiGene() {};
	~GuzaiGene();
	bool Start();
	void Update();

	/**
	 * @brief ��ނ��i�[����Ă���z��Ɉ����œ��肵�āA���ꂪ���݂��Ă��邩�ǂ�����Ԃ�
	 * @param number �z��̗v�f�ԍ�
	 * @return ���݂��Ă��遁TRUE�B
	*/
	bool GetGuzaiFlag(int number) { return m_guzaiFlag[number]; }

	/**
	 * @brief ���̈����̗v�f�ɂ͋�ނ̃f�[�^���i�[����Ă��邩�ݒ肷��B
	 * @param number �v�f�̔ԍ�
	 * @param tf ���݂��遁TRUE�B
	*/
	void SetGuzaiFlag(int number, bool tf) { m_guzaiFlag[number] = tf; }

	Guzai* m_guzai[99] = {nullptr};
};
