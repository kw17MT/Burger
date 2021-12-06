#pragma once
#include "HamBurgerFactory.h"
#include "CLevel2D.h"
class SkinModelRender;
class PlayerGene;
class SpriteRender;
class Burger;
class CSoundSource;
class Player;
class Kitchen;

class Counter : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;					//�J�E���^�[�̈ʒu���W
	Vector3 m_burgerPos = Vector3::Zero;				//�o�[�K�[�̈ʒu�ݒ�p�̍��W
	Vector3 m_spritePos = { 500.0f,-200.0f,0.0f };		//�n���o�[�K�[�̐���\�����������̈ʒu���W

	bool m_burgerCorrectFlag = false;					//��o���ꂽ�o�[�K�[�������Ă���t���O�B
	bool m_burgerMistakeFlag = false;					//��o���ꂽ�o�[�K�[���Ԉ���Ă���t���O�B
	bool m_spriteFlag = false;							//����摜���o�Ă��邩
	std::array<std::array<bool, 5>, 4> m_spriteCompareFlagTrue = { false };								//�v�f5�̔z���4���@���@5��4�s
	std::array<std::array<bool, 5>, 4> m_spriteCompareFlagFalse = { false };
	bool m_bonusPoint = false;							//�{�[�i�X�|�C���g�̃t���O

	int m_spriteTime = 0;								//����摜���o������
	std::array<std::array<int, 5>, 4> m_guzaiJudge = { 2 };
	int m_menuNum = 3;									//�\���ł��郁�j���[�̎�ށB
	int m_counterNo = 0;								//�J�E���^�[�ԍ��@�O�����A�P���E
	int m_stackNum = 0;									//���i�̃n���o�[�K�[��������̂��̕ϐ��A�X�R�A�Ɏg�p����
	int m_delay = 0;									//�x������

public:
	Counter() {};
	~Counter();

	/**
	 * @brief ���f���̏������A�n���o�[�K�[�̏����擾�A�K�v�ȃI�u�W�F�N�g�̑{���Ǝ擾
	 * @return true
	*/
	bool Start();
	
	/**
	 * @brief �n���o�[�K�[���ǂ����邩�̑I��
	*/
	void Update();

	/**
	 * @brief �n�_�P�ƒn�_�Q�̋������͂���
	 * @param pos1 �n�_�P
	 * @param pos2 �n�_�Q
	 * @return �Q�n�_�Ԃ̋���
	*/
	float CalcDistance(Vector3 pos1, Vector3 pos2);

	/**
	 * @brief �J�E���^�[�ɋ߂��Ƃ����A�{�^��������A�n���o�[�K�[�̔���ƃX�R�A�̑��������邩�̔���
	*/
	void JudgeAndDelete();

	/**
	 * @brief �J�E���^�[�̍��W�ݒ�
	 * @param pos �V�������W
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }

	/**
	 * @brief �J�E���^�[�̃i���o�����O���s��
	 * @param num �J�E���^�[�̃i���o�[�@�O�����A�P���E
	*/
	void SetCounterNo(int num) { m_counterNo = num; }

	/**
	 * @brief ���i�̃n���o�[�K�[����������̂����L�^���s��
	 * @param num �n���o�[�K�[�̑w��
	*/
	void SetStackNum(int num) { m_stackNum = num; }

	/**
	 * @brief �L�^���Ă����n���o�[�K�[�̑w�����O�ŏ���������B
	*/
	void SetStack0() { m_stackNum = 0; }

	/**
	 * @brief �������n���o�[�K�[�����ׂ�B
	 * @return ��������TRUE�A�ԈႢ��FALSE
	*/
	bool Judge();

	/**
	 * @brief ���݃L�b�`���Őς�ł����ނƃ��j���[�̋�ނ����A���^�C���Ŕ��肵�A����Ă�����o�c�}�[�N�A�����Ă�����`�F�b�N�}�[�N�����j���[��ɏo���B
	*/
	void HamBurgerCompare();

	/**
	 * @brief �\�����Ă���3�̃n���o�[�K�[���擾�B
	 * @return 
	*/
	const EnHamBurger* GetShowHamBurgers() const 
	{
		return m_showHamBurgers;
	}

	/**
	 * @brief �{�[�i�X�_�������邩�ǂ����ݒ肷��B
	 * @param �����遁TRUE�A�����Ȃ���FALSE
	*/
	void SetBonusPoint(bool giveBonus) { m_bonusPoint = giveBonus; }

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
	
	EnHamBurger m_showHamBurgers[enHamBurgerNum];					//�\�����Ă���n���o�[�K�[�̔z��B
	Kitchen* m_kitchen = nullptr;						//�Ή�����L�b�`��
	CLevel2D* m_level2d = nullptr;						//���x���QD
	Player* m_player = nullptr;							//�Ή�����v���C���[
	SkinModelRender* m_skinModelRender = nullptr;		//�J�E���^�[�̃��f��
	SpriteRender* m_spriteJudge = nullptr;				//MISS��CORRECT�̕����\���p
	std::array<std::array<SpriteRender*, 5>, 4> m_spriteCompare = { nullptr };
};