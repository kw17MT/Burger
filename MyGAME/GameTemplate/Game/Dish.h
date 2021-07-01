#pragma once
#include <vector>
#include "PathMove.h"
class SkinModelRender;
class Guzai;
class PlayerGene;
class PathMove;
class CSoundSource;
class DishGene;

class Dish : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;					//�M�̈ʒu
	Vector3 m_guzaiPos = Vector3::Zero;					//��ɏ�������ނ̈ʒu
	Vector3 m_scale = Vector3::One;						//�M�̊g����

	bool m_isHavingGuzai = false;						//�����i���̎M�j�͋�ނ��悹�Ă��邩�B
	const int m_maxNum2Refill = 5;						//��[���J�n����ő�l		�Q��To
	bool m_isCompletedFirstPop = false;					//�S�Ă̎M�̏�ɋ�ނ�ݒu�ł�����
	float m_guzaiYPos = 1000.0f;						//��ނ̍����B
	int m_guzaiTimer = 0;								//��ނ���POP������Ƃ��ɒx���𐶂����������
	bool m_soundFlag = false;							//���A����炵�Ă��邩
	int m_guzaiNo = 0;									//��ނ͉��Ԗڂ̈ʒu�Ɋi�[����Ă��邩

	std::unique_ptr<PathMove> m_pathMove;				//�ړ��������s���N���X�B

	Light m_lig;										//�M�Ǝ��̃��C�g
public:
	Dish() {}
	~Dish();

	/**
	 * @brief ���f���̏������ƎM�Ǝ��̃��C�g�̐ݒ�
	 * @return true
	*/
	bool Start();
	void Update();

	/**
	 * @brief �V�����ʒu�̐ݒ�
	 * @param pos �V�����ʒu
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }

	/**
	 * @brief �V�����g�嗦�̐ݒ�
	 * @param scale �V�����g�嗦
	*/
	void SetScale(Vector3 scale) { m_scale = scale; }

	/**
	 * @brief ���̎M�͋�ނ������Ă��邩�ǂ����̐ݒ�
	 * @param state TRUE�������Ă���AFALSE�������Ă��Ȃ��B
	*/
	void SetHavingState(bool state) { m_isHavingGuzai = state; }

	/**
	 * @brief		�C�����C������
	 * @return 
	*/
	//EnCycleDirection GetCycleDirection() { return m_pathMove->GetCycleDirection(); }

	/**
	 * @brief �M���g�Ə�̋�ނ̈ړ��������Ȃ��B
	*/
	void Move();

private:
	SkinModelRender* m_skinModelRender = nullptr;			//��ނ̃��f��
	PlayerGene* m_playerGene = nullptr;						//�v���C���[������
	CSoundSource* m_se = nullptr;							//SE�p
	DishGene* m_dishGene = nullptr;							//�M������
	std::vector<Guzai*> m_guzai;							//��ނ̊i�[�ꏊ
};

