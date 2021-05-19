#pragma once

//�n���o�[�K�[�̎�ނ�ǉ�����Ƃ�enum�Ɏ�ނ�ǉ���Acpp���̃R���X�g���N�^��vector�ɋ�ނ̎�ނ�ǉ����Ă��B

//enum EnHamBurger
//{
//	enNon = -1,	//�����Ȃ��B
//	enCheeseBurger = 0,		//�`�[�Y�o�[�K�[�B
//	enTomatoBurger,		//�g�}�g�o�[�K�[�B
//	enEggBurger,		//�G�b�O�o�[�K�[�B
//	//enTikimi
//	enHamBurgerNum			//�n���o�[�K�[�̐��B
//};

#include "HamBurgerFactory.h"
#include "CLevel2D.h"
class SkinModelRender;
class PlayerGene;
class SpriteRender;
class Burger;
class CSoundSource;

class Counter : public IGameObject
{
private:
	Vector3 m_counterPos;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_burgerPos = Vector3::Zero;
	bool m_burgerCorrectFlag = false;		//��o���ꂽ�o�[�K�[�������Ă���t���O�B
	bool m_burgerMistakeFlag = false;		//��o���ꂽ�o�[�K�[���Ԉ���Ă���t���O�B

	Vector3 m_spritePos01 = { 500.0f,-200.0f,0.0f };
	Vector3 m_spritePos02 = { -500.0f,-200.0f,0.0f };
	bool m_spriteFlag01 = false;
	bool m_spriteFlag02 = false;
	int m_spriteTime01 = 0;
	int m_spriteTime02 = 0;

	bool m_spriteCompareFlagTrue[4][5] = { false };		//���j���[�ƈ�v���Ă���Ƃ��̉摜�\���t���O
	bool m_spriteCompareFlagFalse[4][5] = { false };	//���j���[�ƕs��v�̂Ƃ��̉摜�\���t���O
	int m_guzaiJudge[4][5] = { 2 };						//�ς܂ꂽ��ނ������Ă��邩�H0,����Ă���B1,�����Ă���B2,�ς܂�Ă��Ȃ��B

	//�\���ł��郁�j���[�̎�ށB
	int menuNum = 3;

	//�O�D�`�[�Y�@�P�D�G�b�O�@�Q�D���^�X�@�R�D�p�e�@�S�D�g�}�g

	/*int const burger01[3] = { 3,0,2 };
	int const burger02[4] = { 3,4,4,2 };
	int const burger03[4] = { 2,4,1,3 };
	typedef std::vector<int> HamBurger;
	HamBurger m_hamBurgers[enHamBurgerNum];*/

	//int const burger01[3] = { 3,0,2 };
	//int const burger02[4] = { 3,4,4,2 };
	//int const burger03[4] = { 2,4,0,3 };


	//�J�E���^�[�ԍ��@�P�����A�Q���E
	int CounterNo = 0;
	//���i�̃n���o�[�K�[��������̂��̕ϐ�
	int StackNum = 0;

public:
	//���f���f�[�^�Ȃǂ��������B
	Counter();
	bool Start();
	//Delete�֐����Ăяo��������B
	void Update();
	//�o�[�K�[����������Ԃ�B�{�^���������Ɛf�f�J�n�B
	void Delete();
	void SetPosition(Vector3 pos) { m_counterPos = pos; m_position = pos; }
	void SetCounterNo(int num) { CounterNo = num; }
	//���i�̃n���o�[�K�[����������̂����L�^���邽�߂̊֐��B
	void SetStackNum(int num) { StackNum = num; }
	void SetStack0() { StackNum = 0; }

	//�������o�[�K�[���𒲂ׂ�B
	bool Judge();
	void HamBurgerCompare();
	//�\�����Ă���3�̃n���o�[�K�[���擾�B
	EnHamBurger* GetShowHamBurgers()
	{
		return m_showHamBurgers;
	}
	//�\�����Ă���n���o�[�K�[�̔z��B
	EnHamBurger m_showHamBurgers[11];

	int Delay = 0;

	PlayerGene* m_playerGene;
	SkinModelRender* m_skinModelRender;
	SpriteRender* m_spriteJudge01;
	SpriteRender* m_spriteJudge02;
	SpriteRender* m_spriteCompare[4][5];	//���j���[�ƈ�v���Ă��邩�̉摜��\��
};