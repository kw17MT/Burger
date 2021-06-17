/*****************************************************************//**
 * \file   Path.h
 * \brief Path�N���X  
 * 
 * \author komura
 * \date   November 2020
 *********************************************************************/
#pragma once
struct Point {
	Vector3 s_vector = Vector3::Zero;				//���W
	int s_number = 0;								//�ԍ�
};

/**
 * \brief MovePath�Ŏg�p����p�X�N���X.
 */
class Path
{
public:
	/**
	 * \brief �R���X�g���N�^.
	 * 
	 */
	Path();
	/**
	 * \brief �f�X�g���N�^.
	 * 
	 */
	~Path();
	/**
	 * \brief �p�X�f�[�^�����[�h.
	 * 
	 * \param filePath �t�@�C���p�X
	 */
	void Load(const char* filePath,int guzaiNo);
	/**
	 * \brief �p�X�̃|�C���g�̐����擾.
	 * 
	 * \return �p�X�̃|�C���g�̐�
	 */
	int GetNumberPoint()
	{
		return m_pointList.size();
	}
	/**
	 * \brief �ŏ��̃|�C���g���擾.
	 * 
	 * \return �ŏ��̃|�C���g
	 */
	Point* GetFirstPoint()
	{
		return &m_pointList[0];
	}
	/**
	 * \brief ���W�����ԋ߂��|�C���g���擾.
	 * 
	 * \param pos ���W
	 * \return ���W�����ԋ߂��|�C���g
	 */
	Point* GetNearPoint(const Vector3& pos);
	/**
	 * \brief ���̃|�C���g���擾.
	 * 
	 * \param number ���݂̃|�C���g�̔ԍ�
	 * \return ���̃|�C���g
	 */
	Point* GetPoint(const int& number);

	/**
	 * @brief �����Ō�̃|�C���g���ǂ����B
	 * @param number ���݂̃|�C���g�̔ԍ�
	 * @return �Ō�̃|�C���g��������true
	*/
	bool GetIsFinalPoint(const int& number)
	{
		return number == m_pointList.size();
	}
private:
	std::map<int,Point> m_pointList;						//�|�C���g�̃��X�g
};

