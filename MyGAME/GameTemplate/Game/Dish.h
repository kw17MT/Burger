#pragma once
#include "PathMove.h"
class SkinModelRender;
class Guzai;
class PlayerGene;
class PathMove;
class DishSpeedManeger;
class CSoundSource;
class DishGene;
class GuzaiGene;

class Dish : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_guzaiPos = Vector3::Zero;
	Vector3 m_scale = Vector3::One;

	bool isHavingGuzai = false;							//�����i���̎M�j�͋�ނ��悹�Ă��邩�B
	const int maxNum2Refill = 5;						//��[���J�n����ő�l		�Q��To
	bool isCompletedFirstPop = false;					//�S�Ă̎M�̏�ɋ�ނ�ݒu�ł�����
	float m_guzaiYPos = 1000.0f;						//��ނ̍����B
	int m_guzaiTimer = 0;
	bool m_soundFlag = false;
	int m_guzaiNo;

	std::unique_ptr<PathMove> m_pathMove;		//�ړ��������s���N���X�B


	Light m_lig;
public:
	Dish() {}
	~Dish();

	void SetPosition(Vector3 pos) { m_position = pos; }
	void SetScale(Vector3 scale) { m_scale = scale; }
	void SetHavingState(bool state) { isHavingGuzai = state; }
	enCycleDirection GetCycleDirection() { return m_pathMove->GetCycleDirection(); }

	void Move();

	bool Start();
	void Update();

	SkinModelRender* m_skinModelRender;
	Guzai* m_guzai = nullptr;
	Guzai* m_guza[10];
	int haveNum = 0;
	PlayerGene* playerGene;
	DishSpeedManeger* m_speedManeger;
	CSoundSource* m_se;
	DishGene* m_dishGene;
	GuzaiGene* m_guzaiGene;
};

