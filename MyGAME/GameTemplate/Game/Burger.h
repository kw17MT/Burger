#pragma once
#include "effect/Effect.h"
class Counter;
class CSoundSourse;
class Effect;
class Player;
class SkinModelRender;
class TrashCan;

class Burger : public IGameObject
{
private:
	const Vector3 m_burgerScale = { 10.0f, 10.0f, 10.0f };	//�n���o�[�K�[�̊g�嗦
	const Vector3 m_10TimesBigger = { 10.0f,10.0f,10.0f };	//�傫����10�{���邽�߂̂���
	Vector3 m_position = Vector3::Zero;						//�n���o�[�K�[�̈ʒu
	Vector3 m_beHadPos = Vector3::Zero;						//�n���o�[�K�[�������ꂽ���̈ʒu�ݒ�p

	int m_burgerNo = 0;										//�ǂ��炪�������o�[�K�[���B�O���PP�A�P���QP
	int m_decrementTime = 20;								//�S�~���ɃZ�b�g�������ɏ�����܂ł̒x������
	int m_deleteTimer = 0;									//�{�^���������Ńo�[�K�[�������悤�ɂ��邽�߁B
	bool m_burgerExist = false;								//�P�̎��ɏ��Delete(),ClearNo()��

	bool m_isSetOnTrashCan = false;							//�S�~���ɃZ�b�g���ꂽ��
	bool m_putOnCounter = false;							//�L�b�`���ɂ��邩�ǂ����A�L�b�`���̏�Ɉʒu�����킹�邽�߂̕ϐ�

public:
	Burger() {}
	~Burger();
	void Update();

	/**
	 * @brief ���f���̏������A�K�v�ȃC���X�^���X�̏���T���Ď���Ă���B
	 * @return true
	*/
	bool Start();
	
	/**
	 * @brief �n���o�[�K�[��������
	*/
	void GrabBurger();

	/**
	 * @brief �o�[�K�[���������ہA�J�E���^�[�ɐς�ł�����ނ̎�ނ��������B
	 *�v���C���[�ɕۑ����Ă����A�n���o�[�K�[���\�������ނ��ŏ������B	
	*/
	void ClearNo();

	/**
	 * @brief �n���o�[�K�[�̍��W�̃Z�b�^�[
	 * @param pos �ʒu���W
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }
	
	/**
	 * @brief �o�[�K�[�͂ǂ��瑤�̂�
	 * @param num �O�A���@�P�A�E
	*/
	void SetBurgerNo(int num) { m_burgerNo = num; }

	/**
	 * @brief �S�~���ɃZ�b�g���ăn���o�[�K�[�������B
	*/
	void SetOnTrashCan();

	/**
	 * @brief �J�E���^�[�ɒu�������ǂ����̃Z�b�^�[
	 * @param state �J�E���^�\�ɒu������TRUE�B
	*/
	void SetPutOnCounterState(bool state) { m_putOnCounter = state; }
	
	/**
	 * @brief �v���C���[���
	*/
	enum enPlayerState {
		enFullKitchen = -1,		//�L�b�`������t�̏�ԂŃ��[���̏ォ��͂Ƃ�Ȃ����A��ޒu���ꂩ�L�b�`���ォ��͂Ƃ��悤�ɂ���̂ɕK�v
		enNothing,				//���������Ă��Ȃ�
		enHaveGuzai,			//��ނ������Ă�����
		enHaveBurger,			//�n���o�[�K�[�������Ă�����
		enStateNum,				//�Ȃ肦���Ԃ̐�
	};
	
	Counter* m_counter = nullptr;
	Effect* m_effect = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
	Player* m_player = nullptr;
	TrashCan* m_trashCan = nullptr;
};