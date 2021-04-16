#pragma once

//�n���o�[�K�[�̎�ނ�ǉ�����Ƃ�enum�Ɏ�ނ�ǉ���Acpp���̃R���X�g���N�^��vector�ɋ�ނ̎�ނ�ǉ����Ă��B

enum EnHamBurger
{
	enNon = -1,	//�����Ȃ��B
	enCheeseBurger = 0,		//�`�[�Y�o�[�K�[�B
	enTomatoBurger,		//�g�}�g�o�[�K�[�B
	enEggBurger,		//�G�b�O�o�[�K�[�B
	//enTikimi
	enHamBurgerNum			//�n���o�[�K�[�̐��B
};

class Counter : public IGameObject
{
private:
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

	//�\���ł��郁�j���[�̎�ށB
	int menuNum = 3;

	//�O�D�`�[�Y�@�P�D�G�b�O�@�Q�D���^�X�@�R�D�p�e�@�S�D�g�}�g
	int const burger01[3] = { 3,0,2 };
	int const burger02[4] = { 3,4,4,2 };
	int const burger03[4] = { 2,4,1,3 };
	typedef std::vector<int> HamBurger;
	HamBurger m_hamBurgers[enHamBurgerNum];

	//�J�E���^�[�ԍ��@�P�����A�Q���E
	int CounterNo = 0;
	//���i�̃n���o�[�K�[��������̂��̕ϐ�
	int StackNum = 0;

public:
	//���f���f�[�^�Ȃǂ��������B
	Counter();
	//Delete�֐����Ăяo��������B
	void Update();
	//�o�[�K�[����������Ԃ�B�{�^���������Ɛf�f�J�n�B
	void Delete();
	void SetPosition(Vector3 pos) { m_charaCon.SetPosition(pos); }
	void SetCounterNo(int num) { CounterNo = num; }
	void SetStackNum(int num) { StackNum = num; }
	void SetStack0() { StackNum = 0; }

	//�������o�[�K�[���𒲂ׂ�B
	bool Judge();

	void Render(RenderContext& rc) { model.Draw(rc); }

	int Delay = 0;
};

