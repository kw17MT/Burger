#pragma once
#include "PathMove.h"
class SkinModelRender;
class Guzai;
class PlayerGene;
class PathMove;


class Dish : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_guzaiPos = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	bool isHavingGuzai = false;
	//������WayPoint�̉��Ԗڂ̎M�Ȃ̂�
	int myNumber = 0;
	
	//��[���J�n����ő�l		�Q��To
	const int maxNum2Refill = 5;
	//�S�Ă̎M�̏�ɋ�ނ�ݒu�ł�����
	bool isCompletedFirstPop = false;
	//PlayerGene�ɋ�ނ������Ă��Ȃ��M�̐������邪�A�킴�킴�����Ɏ����Ă���B
	//��̎M��ɋ�ނ��o������AnoHavingDish�����������������A��x�s���Ă��܂��ƁA1������[�ł��Ȃ��Ȃ邽�ߕK�v�B
	int totalNoHavingDish = 0;
	

	std::unique_ptr<PathMove> m_pathMove;		//�ړ��������s���N���X�B

public:
	Dish() {}
	~Dish() {}

	void SetPosition(Vector3 pos) { m_position = pos; }
	void SetScale(Vector3 scale) { m_scale = scale; }
	void SetHavingState(bool state) { isHavingGuzai = state; }
	void SetMyNumber(int num) { myNumber = num; }

	void Move();

	bool Start();
	void Update();

	

	SkinModelRender* m_skinModelRender;
	Guzai* m_guzai;
	PlayerGene* playerGene;
};

