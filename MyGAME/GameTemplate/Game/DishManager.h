#pragma once

/**
 * @brief �M�̈ړ��₻�̌�����ݒ肷��B
*/
class DishManager
{
private:
	const int m_dishNum = 36;
	bool m_isSpeedUp = false;											//�M�̈ړ����x���X�s�[�h�A�b�v�����邩
	float m_timeTillSpeedUp = 0.0f;										//�X�s�[�h�A�b�v�܂ł̎���
	float m_activeTimeForSpeedUp = 0.0f;								//�X�s�[�h�A�b�v�̗L������
	int m_completedChangeDirectionNum = 0;								//�M�̌����𔽓]�������񐔁i�M�̖��������邱�Ƃ����m���邽�߁j

	bool m_letChangeDirection = false;									//�M�̓���������ύX�����邩
		
	static DishManager* instance;										//DishManager�̃C���X�^���X�B
public:
	/**
	 * @brief DishManager�̃C���X�^���X�𓾂�
	 * @return 
	*/
	static DishManager& GetInstance()
	{
		static DishManager instance;
		return instance;
	}

	/**
	 * @brief DishManager�̃C���X�^���X���쐬����B
	*/
	void CreateInstance()
	{
		instance = new DishManager;
	}

	/**
	 * @brief DishManager�̃C���X�^���X��j������B
	*/
	void DeleteInstance()
	{
		delete instance;
	}

	/**
	 * @brief �X�s�[�h�A�b�v�����s���邩�Ԃ��B
	 * @return TRUE���X�s�[�h�A�b�v�AFALSE�����ʂ̃X�s�[�h
	*/
	bool GetSpeedUpState()
	{
		return m_isSpeedUp; 
	}

	/**
	 * @brief �X�s�[�h�A�b�v���Ă��邩�̏�Ԃ��t�ɂ���B
	*/
	void SwitchSpeedUpState()
	{
		//�X�s�[�h�A�b�v���Ȃ��
		if (m_isSpeedUp == true) {
			//�ʏ�X�s�[�h��
			m_isSpeedUp = false;
		}
		//�ʏ�X�s�[�h�Ȃ��
		else {
			//�X�s�[�h�A�b�v��
			m_isSpeedUp = true;
		}
	}

	/**
	 * @brief �X�s�[�h�A�b�v�܂ł̎��Ԃ�ݒ肷��
	 * @param timeTillSpeedUp �X�s�[�h�A�b�v�܂ł̎���
	*/
	void SetTimeTillSpeedUp(float timeTillSpeedUp)
	{
		m_timeTillSpeedUp = timeTillSpeedUp;
	}

	/**
	 * @brief �X�s�[�h�A�b�v�̗L�����Ԃ�ݒ�
	 * @param time �X�s�[�h�A�b�v�̗L������
	*/
	void SetActiveTimeForSpeedUp(float time)
	{
		m_activeTimeForSpeedUp = time;
	}

	/**
	 * @brief �X�s�[�h
	 * @return 
	*/
	float GetTimeTillSpeedUp()
	{
		return m_timeTillSpeedUp;
	}

	/**
	 * @brief �X�s�[�h�A�b�v�̗L�����Ԃ�Ԃ�
	 * @return �X�s�[�h�A�b�v�̗L������
	*/
	float GetActiveTimeForSpeedUp()
	{
		return m_activeTimeForSpeedUp;
	}

	/**
	 * @brief �X�s�[�h�A�b�v�܂ł̎��Ԃ��Q�[���^�C���Ō��炵�Ă���
	 * @param gameTime �Q�[���^�C��
	*/
	void DecreaseTimeTillSpeedUp(float gameTime)
	{
		m_timeTillSpeedUp -= gameTime;
	}

	/**
	 * @brief �X�s�[�h�A�b�v�̗L�����Ԃ��Q�[���^�C���Ō��炵�Ă���
	 * @param gameTime �Q�[���^�C��
	*/
	void DecreaseActiveTimeForSpeedUp(float gameTime) {
		m_activeTimeForSpeedUp -= gameTime;
	}

	/**
	 * @brief �M�̉�]�̌�����ύX���邩�ǂ�����ݒ肷��B
	 * @param changeOrder ������ς��邩�ǂ���
	*/
	void SetOrderChangeDirection(bool changeOrder)
	{
		m_letChangeDirection = changeOrder;
	}

	/**
	 * @brief �M�̉�]�̌�����ς���ׂ����ǂ�����Ԃ��B
	 * @return TRUE���ς���I
	*/
	bool GetIsOrderedDirection()
	{
		return m_letChangeDirection;
	}

	/**
	 * @brief �������ς�����M�̑������v�Z����B�i�C���N�������g�j
	*/
	void AddCompletedChangeDirectionNum()
	{
		m_completedChangeDirectionNum++;
	}

	/**
	 * @brief �������ς�����M�̑��������Z�b�g����
	*/
	void ResetCompletedChangeDirectionNum()
	{
		m_completedChangeDirectionNum = 0;
	}

	/**
	 * @brief �S���̎M�̌������ς�������ǂ���
	 * @return TRUE���I������B
	*/
	bool JudgeChangedAllDirection()
	{
		return m_dishNum == m_completedChangeDirectionNum;
	}
};

