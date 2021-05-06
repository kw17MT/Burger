#pragma once
#include "PathMove.h"
class SkinModelRender;
class Guzai;
class PlayerGene;
class PathMove;
class DishSpeedManeger;

class Dish : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_guzaiPos = Vector3::Zero;
	Vector3 m_scale = Vector3::One;

	bool isHavingGuzai = false;							//�����i���̎M�j�͋�ނ��悹�Ă��邩�B
	const int maxNum2Refill = 5;						//��[���J�n����ő�l		�Q��To
	bool isCompletedFirstPop = false;					//�S�Ă̎M�̏�ɋ�ނ�ݒu�ł�����
	

	std::unique_ptr<PathMove> m_pathMove;		//�ړ��������s���N���X�B

public:
	Dish() {}
	~Dish() {}

	void SetPosition(Vector3 pos) { m_position = pos; }
	void SetScale(Vector3 scale) { m_scale = scale; }
	void SetHavingState(bool state) { isHavingGuzai = state; }

	void Move();

	bool Start();
	void Update();

	SkinModelRender* m_skinModelRender;
	Guzai* m_guzai;
	PlayerGene* playerGene;
	DishSpeedManeger* m_speedManeger;
};

