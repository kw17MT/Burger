#pragma once
#include "GuzaiGene.h"

class Guzai;
class FontRender;
class PopUp2D;

class SkinModelRender;
class Kitchen;

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
	PopUp2D* m_popUp = nullptr;

	//�v���C���[�̃p�����[�^
	//���W
	Vector3 m_position = Vector3::Zero;
	//�|�b�v�A�b�v�̍��W
	Vector3 m_popUpPosition = Vector3::Zero;
	//��]
	Quaternion m_rotation = Quaternion::Identity;
	//�X�P�[��
	Vector3 m_scale = Vector3::One;
	//�p�x
	float angle = 0.0f;
	//�ړ����x
	Vector3 moveSpeed = Vector3::Zero;
	//�v���C���[�̈ړ����x��ۑ�����x�N�g��
	Vector3 saveMoveSpeed = Vector3::Zero;

	//�P�ō��A�Q�ŉE
	int playerNo = 0;

	////�o�t�̌��ʂ��L�����ǂ����B
	//bool Buff = false;
	////�o�t�̗L�����ԁB
	//int BuffTime = 120;
	//���A��ނ��^�[�Q�b�g���Ă��邩�B1�ȏ�^�[�Q�e�B���O���Ȃ��悤�ɁB
	bool TargetingState = false;

	EnItem m_enItem = enNonItem;

	int Distance = 0;

public:
	Player();
	~Player();
	//���f���A�����蔻��A���No.���i�[����z����X�ŏ�����
	//���̏������R���X�g���N�^����Start�֐��ɕύX���܂����B
	bool Start();
	void SetPlayerNo(int num) { playerNo = num; }

	//�ړ������B
	void Update();

	/*void SetBuffAffect(bool buff) { Buff = buff; }
	bool stateBuff() { return Buff; }*/

	//��ފi�[�p�z����X�ŏ�����
	void SetGuzaiNo9();

	//void SetPosition(Vector3 pos) { m_charaCon.SetPosition(pos); }
	//���g�̎����W�����L�����R���ɓn���ď������Ă��炤���߂ɕύX���܂����B
	void SetPosition(Vector3 pos) { m_position.x = pos.x, m_position.y = pos.y, m_position.z = pos.z; }
	void SetRotation(Quaternion rot) { m_rotation = rot; }
	//�L�����R���̍��W �� �v���C���[���g�̍��W���擾����悤�ɕύX
	Vector3 GetPosition() { return m_position; }

	//�ړ��͈͂̐������s��
	void RestrictPos();

	//���݃^�[�Q�e�B���O���Ă��邩�ǂ���
	void SetTarget(bool target) { TargetingState = target; }
	//���݂̃^�[�Q�e�B���O��Ԃ�Ԃ��B
	bool GetTargetState() { return TargetingState; }

	void GrabFromKitchen();

	void ClearLatestGuzaiNo(int num) { GuzaiNo[num] = 9; }

	/*const EnItem GetEnItem() const
	{
		return m_enItem;
	}

	void SetEnItem(EnItem enItem)
	{
		if (m_enItem == enNonItem)
		{
			GuzaiGene* gg;
			if (playerNo == 1)
			{
				gg = FindGO<GuzaiGene>("gene01");
			}
			else if (playerNo == 2)
			{
				gg = FindGO<GuzaiGene>("gene02");
			}
			else {
				return;
			}
			if (m_enItem == enDebuffItem)
			{
				gg->DeBuffnum = 0;
			}
			else if (m_enItem == enBuffItem)
			{
				gg->Buffnum = 0;
			}
		}
		m_enItem = enItem;
	}*/

	void UseItem();

	//�v���C���[�̐��K�����ꂽ�ړ����x�����
	Vector3 GetNormalMoveSpeed() { return saveMoveSpeed; }

	//�v���C���[����ނ������Ă��邩�B�P�Ȃ��ނ������Ă���B�Q�Ȃ�n���o�[�K�[�������Ă���B
	int have = 0;
	
	//�ςݏグ�Ă����ނ̎�ނ��i�[���Ă����B
	int GuzaiNo[10];

	enum enAnimationCrips
	{
		enAnimation_Idle,
		enAnimation_Run,
		enAnimation_Cut,			//�g�}�g��؂�Ƃ���������
		enAnimation_Cook,			//�o�[�K�[�����Ƃ��g������
		enAnimation_HaveIdle,
		enAnimation_HaveRun,
		enAnimation_Num
	};

	AnimationClip animationClips[enAnimation_Num];

	Kitchen* m_kitchen;
	SkinModelRender* m_skinModelRender;
};


