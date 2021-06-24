#pragma once
#include "effect/Effect.h"
class Guzai;
class FontRender;
class PopUp2D;
class SkinModelRender;
class Kitchen;
class Effect;

class Player : public IGameObject
{
private:
	//�v���C���[�̃p�����[�^
	Vector3 m_position = Vector3::Zero;								//�v���C���[�̍��W
	Vector3 m_moveSpeed = Vector3::Zero;							//�v���C���[�̈ړ����x
	Vector3 m_saveMoveSpeed = Vector3::Zero;						//�v���C���[�̈ړ����x��ۑ�����x�N�g��
	Vector3 m_scale = { 0.3f,0.4f,0.3f };							//�v���C���[�̃X�P�[��
	Quaternion m_rotation = Quaternion::Identity;					//�v���C���[�̉�]

	float m_angle = 0.0f;											//�v���C���[�̊p�x

	int m_playerNo = 0;												//�O�ō��A�P�ŉE
	int m_have = enNothing;											//�v���C���[����ނ������Ă��邩�B�P�Ȃ��ނ������Ă���B�Q�Ȃ�n���o�[�K�[�������Ă���B-1�ŃL�b�`������͂Ƃ����
	int m_guzaiNo[10];												//�ςݏグ�Ă����ނ̎�ނ��i�[���Ă����B
	int m_moveCounter = 0;											//P1
	const int m_maxNumCanSaveGuzaiType = 10;						//�v���C���[���ۑ��ł����ގ�ނ̑���

	bool m_targetingState = false;									//���A��ނ��^�[�Q�b�g���Ă��邩�B1�ȏ�^�[�Q�e�B���O���Ȃ��悤�ɁB
	bool m_moveStop = false;										//��~�t���O�P

public:
	Player() {};
	~Player();

	/**
	 * @brief ���f���A�������̃G�t�F�N�g�̏�����
	 * @return true
	*/
	bool Start();
	
	/**
	 * @brief ��Ɉړ��̏���
	*/
	void Update();

	/**
	 * @brief �v���C���[���̋�ފi�[�p�z����X�ŏ�����
	*/
	void SetGuzaiNo9();

	/**
	 * @brief �v���C���[�̔ԍ���ݒ�
	 * @param num �O�����@�P���E
	*/
	void SetPlayerNo(int num) { m_playerNo = num; }

	/**
	 * @brief �V�����ʒu�̐ݒ�
	 * @param pos �V�����ʒu
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }

	/**
	 * @brief �V������]�̐ݒ�
	 * @param rot �V������]
	*/
	void SetRotation(Quaternion rot) { m_rotation = rot; }

	/**
	 * @brief �V�����ړ����x�̐ݒ�
	 * @param speed �V�����ړ����x
	*/
	void SetMoveSpeed(Vector3 speed) { m_moveSpeed = speed; }

	/**
	 * @brief �����͉������^�[�Q�b�g���Ă��邩
	 * @param target TRUE�����Ă���
	*/
	void SetTarget(bool target) { m_targetingState = target; }

	/**
	 * @brief �v���C���[�̏�Ԃ�ݒ肷��
	 * @param state ��Ԃ̔ԍ��B�񋓌^enPlayerState���Q��
	*/
	void SetPlayerState(int state) { m_have = state; };

	void SetPlayerStackedGuzais(int num, int guzaiType) { m_guzaiNo[num] = guzaiType; }

	/**
	 * @brief ���݂̈ʒu��Ԃ�
	 * @return ���݂̈ʒu
	*/
	Vector3 GetPosition() { return m_position; }
	
	/**
	 * @brief ���݂̃^�[�Q�e�B���O��Ԃ�Ԃ��B
	 * @return �^�[�Q�e�B���O��ԁ@TRUE�����Ă���
	*/
	bool GetTargetState() { return m_targetingState; }

	/**
	 * @brief �v���C���[�̐��K�����ꂽ�ړ����x�����
	 * @return �v���C���[�̐��K�����ꂽ�ړ����x
	*/
	Vector3 GetNormalMoveSpeed() { return m_saveMoveSpeed; }

	/**
	 * @brief �v���C���[���ۑ��ł����ނ̎�ނ̑���
	 * @return ���̂Ƃ���10��
	*/
	int GetMaxNumCanSaveGuzaiType() { return m_maxNumCanSaveGuzaiType; }

	/**
	 * @brief �v���C���[�̏�Ԃ�Ԃ��B
	 * @return enPlayerState���Q��
	*/
	int GetPlayerState() { return m_have; }

	/**
	 * @brief ���̒i���ɂ͉��̋�ނ�ς�ł���̂���Ԃ�
	 * @param num �ς�ł����ނ̒i���̏ꏊ�i0~4)
	 * @return true
	*/
	int GetPlayerStackedGuzais(int num) { return m_guzaiNo[num]; }

	/**
	 * @brief �ςݏグ�Ă����ނ��ׂĂ̏���n��
	 * @return  �ςݏグ�Ă����ނ��ׂĂ̏��
	*/
	int* GetPlayerStackedGuzais() { return m_guzaiNo; }

	/**
	 * @brief �ړ��s��ݒ�
	 * @param tf TRUE���ړ��ł��Ȃ��@FALSE���ړ��ł���
	*/
	void StopMove(bool tf) { m_moveStop = tf; }

	/**
	 * @brief ���W�ɂ��ړ��͈͂̐������s��
	*/
	void RestrictPos();
	
	/**
	 * @brief ��ԍŌ�ɃL�b�`���ɐς񂾋�ނ̋L�^������
	 * @param num ���������ӏ��̗v�f�ԍ�
	*/
	void ClearSpecificGuzaiNo(int num) { m_guzaiNo[num] = 9; }

	/**
	 * @brief �v���C���[�̏��
	*/
	enum enPlayerState {
		enFullKitchen = -1,		//�L�b�`������t�̏�ԂŃ��[���̏ォ��͂Ƃ�Ȃ����A��ޒu���ꂩ�L�b�`���ォ��͂Ƃ��悤�ɂ���̂ɕK�v
		enNothing,				//���������Ă��Ȃ�
		enHaveGuzai,			//��ނ������Ă�����
		enHaveBurger,			//�n���o�[�K�[�������Ă�����
		enStateNum,				//�Ȃ肦���Ԃ̐�
	};

private:
	Kitchen* m_kitchen = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
	Effect* m_effect = nullptr;
};


