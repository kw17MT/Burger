#pragma once

enum EnOrder {
	enDoNothing,
	enStartRefill,
	enOrderNum
};

class GuzaiManager
{
private:
	static GuzaiManager* instance;
	
	int m_emptyDishNum = 0;							//��̎M�̐�
	int m_refilledGuzaiNum = 0;						//��[������ނ̐�
	const int m_numToStartRefill = 5;				//��[���J�n�����ނ̐�

	EnOrder m_enOrder = enDoNothing;
public:
	/**
	 * @brief �C���X�^���X�̎擾
	 * @return ��ފǗ��̃C���X�^���X
	*/
	static GuzaiManager& GetInstance()
	{
		static GuzaiManager instance;
		return instance;
	}

	/**
	 * @brief �C���X�^���X�̍쐬
	*/
	static void CreateInstance()
	{
		instance = new GuzaiManager;
	}

	/**
	 * @brief �C���X�^���X�̍폜
	*/
	static void DeleteInstance()
	{
		delete instance;
	}

	/**
	 * @brief �֐��̌Ăяo�����A��̎M����[�J�n���鐔�ɒB���Ă�����A�J�n�̍��}�s���B
	*/
	void JudgeToOrderRefill()
	{
		if (m_emptyDishNum >= m_numToStartRefill) {
		m_enOrder = enStartRefill;
		}
	}

	/**
	 * @brief �������Ȃ��悤�ɂƂ������߂ɐݒ肷��B
	*/
	void SetNothingOrder()
	{
		m_enOrder = enDoNothing;
	}

	/**
	 * @brief ��̎M�̐��𐔂���
	*/
	void AddEmptyDishNum() 
	{
		m_emptyDishNum++;
	}

	int GetEmptyDishNum()
	{
		return m_emptyDishNum;
	}

	/**
	 * @brief ��[�����������񐔂��L�^����i�C���N�������g�j
	*/
	void AddRefilledGuzaiNum()
	{
		m_refilledGuzaiNum++;
	}

	/**
	 * @brief ��[�����������񐔂�Ԃ��B
	 * @return ��[������������
	*/
	int GetRefilledGuzaiNum()
	{
		return m_refilledGuzaiNum;
	}

	/**
	 * @brief ��̎M�̐��ƕ�[�����񐔂��O�Ń��Z�b�g����B
	*/
	void ResetParamAboutDishAndRefill()
	{
		m_refilledGuzaiNum = 0;
		m_emptyDishNum = 0;
	}

	/**
	 * @brief ��[�𖽗߂���Ă��邩
	 * @return TRUE�����߂��ꂽ�@FALSE������ĂȂ�
	*/
	bool IsOrderedRefill() const
	{
		if (m_emptyDishNum >= m_numToStartRefill) {
			return m_enOrder == enStartRefill;
		}

		return false;
	}
};

static inline GuzaiManager& GetGuzaiManager()
{
	return GuzaiManager::GetInstance();
}