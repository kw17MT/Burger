#pragma once
#include "GuzaiGene.h"
#include "effect/Effect.h"


class Guzai;
class FontRender;
class PopUp2D;

class SkinModelRender;
class Kitchen;
class Effect;

enum EnItem
{
	enNonItem = -1,
	enBuffItem = 0,
	enDebuffItem = 1,
	enItemNum = 2,
};

class Player : public IGameObject
{
private:
	//�v���C���[�̃p�����[�^
	Vector3 m_position = Vector3::Zero;								//���W
	Vector3 moveSpeed = Vector3::Zero;								//�ړ����x
	Vector3 saveMoveSpeed = Vector3::Zero;							//�v���C���[�̈ړ����x��ۑ�����x�N�g��
	Vector3 m_scale = Vector3::One;									//�X�P�[��
	Quaternion m_rotation = Quaternion::Identity;					//��]
	float angle = 0.0f;												//�p�x
	int playerNo = 0;												//�P�ō��A�Q�ŉE

	bool TargetingState = false;									//���A��ނ��^�[�Q�b�g���Ă��邩�B1�ȏ�^�[�Q�e�B���O���Ȃ��悤�ɁB
	int Distance = 0;

	//�G�t�F�N�g�֘A
	int moveCounter01 = 0;											//P1
	int moveCounter02 = 0;											//P2
	
	bool m_moveStop01 = false;										//��~�t���O�P
	bool m_moveStop02 = false;										//��~�t���O�Q

	const int m_maxNumCanSaveGuzaiType = 10;								//�v���C���[���ۑ��ł����ގ�ނ̑���

public:
	Player() {};
	~Player();
	bool Start();
	

	//�ړ������B
	void Update();

	//��ފi�[�p�z����X�ŏ�����
	void SetGuzaiNo9();

	//�Z�b�^�[
	void SetPlayerNo(int num) { playerNo = num; }
	void SetPosition(Vector3 pos) { m_position = pos; }
	void SetRotation(Quaternion rot) { m_rotation = rot; }
	void SetMoveSpeed(Vector3 speed) { moveSpeed = speed; }
	//���݃^�[�Q�e�B���O���Ă��邩�ǂ���
	void SetTarget(bool target) { TargetingState = target; }

	//�Q�b�^�\
	Vector3 GetPosition() { return m_position; }
	//���݂̃^�[�Q�e�B���O��Ԃ�Ԃ��B
	bool GetTargetState() { return TargetingState; }
	//�v���C���[�̐��K�����ꂽ�ړ����x�����
	Vector3 GetNormalMoveSpeed() { return saveMoveSpeed; }
	int GetMaxNumCanSaveGuzaiType() { return m_maxNumCanSaveGuzaiType; }

	//�ړ��s��ݒ�P
	void StopMove01(bool tf);
	//�ړ��s��ݒ�Q
	void StopMove02(bool tf);

	//�ړ��͈͂̐������s��
	void RestrictPos();

	//��ԍŌ�ɃL�b�`���ɐς񂾋�ނ̋L�^������
	void ClearLatestGuzaiNo(int num) { GuzaiNo[num] = 9; }

	//�v���C���[����ނ������Ă��邩�B�P�Ȃ��ނ������Ă���B�Q�Ȃ�n���o�[�K�[�������Ă���B-1�ŃL�b�`������͂Ƃ����
	int have = 0;
	
	//�ςݏグ�Ă����ނ̎�ނ��i�[���Ă����B
	int GuzaiNo[10];

	Kitchen* m_kitchen = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
	Effect* m_effect01 = nullptr;
	Effect* m_effect02 = nullptr;
};


