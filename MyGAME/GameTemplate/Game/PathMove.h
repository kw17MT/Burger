#pragma once
#include "PathFactory.h"
#include "DishManager.h"

class CycleDirection;

enum enMoveState
{
	enNone,		//�������Ȃ��B
	enStart,	//�����ĂȂ��B
	enMove,		//�����Ă�B
	enFinal		//�ŏI�|�C���g���B�B
};

enum EnCycleDirection
{
	enNormal,
	enReverse
};

class PlayerGene;
class Path;
class CSoundSourse;
struct Point;
class PathMove
{
public:
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="pos">���W�B</param>
	/// <param name="move">�ړ����x�B</param>
	/// <param name="enLane">���[���̎�ށB</param>
	/// <param name="guzaiNo">�����E���B</param>
	void Init(const Vector3& pos, const float move, EnLane enLane);

	void ChangeMoveSpeed(float move) { m_moveSpeed = move; }
	/// <summary>
	/// �ړ�������B
	/// </summary>
	/// <returns>�ړ�������̍��W�B</returns>
	const Vector3& Move();

	EnLane GetLane()
	{
		return m_enLane;
	}

	//�ŏI�|�C���g�܂ł��������H
	bool GetIsFinalPoint()
	{
		return m_enMoveState == enFinal;
	}

	/**
	 * @brief ���A�ǂ��������ɗ���Ă��邩
	 * @return ����Ă������
	*/
	EnCycleDirection GetCycleDirection()
	{
		return m_cycleDirection;
	}

	//�q�ɒ񋟂����o�[�K�[�̐����K�萔�ɒB������A����������ς���B
	void SwitchCycleDirection();

private:
	Vector3 	m_moveVector;		//�ړ��x�N�g���B
	Vector3 m_position;
	int m_guzaiNo = 0;
	const int Num2ChangeCycle = 1;
	const int m_wayPointNum = 36;
	float m_moveSpeed;
	int m_submitedBurgerNum = 0;

	EnLane m_enLane = enNonLane;
	enMoveState m_enMoveState = enStart;
	EnCycleDirection m_cycleDirection = enNormal;

	CycleDirection* m_directSprite[3] = { nullptr };					//��]�����X�v���C�g
	Path* m_path = nullptr;											//�p�X�B
	Point* m_point = nullptr;										//���������Ă�|�C���g�B
	PlayerGene* m_playerGene = nullptr;
};

