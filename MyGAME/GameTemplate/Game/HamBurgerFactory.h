#pragma once

typedef std::vector<int> HamBurger;

enum EnHamBurger
{
	enNon = -1,	//�����Ȃ��B
	enCheeseBurger = 0,		//�`�[�Y�o�[�K�[�B
	enTomatoBurger,		//�g�}�g�o�[�K�[�B
	enEggBurger,		//�G�b�O�o�[�K�[�B
	//���L�ǉ����j���[
	enBasicBurger,		//���ʂ̃n���o�[�K�[(1)
	enDoubleBurger,		//�_�u���o�[�K�[(2)
	enVegetableBurger,	//��؃o�[�K�[(2)
	enBaconBurger,		//�x�[�R���o�[�K�[(3)
	enBLTBurger,		//BLT�o�[�K�[(4)
	enOnionBurger,		//�I�j�I���o�[�K�[(5)
	enHighcalBurger,	//�n�C�J�����[�o�[�K�[(5)
	enOnOnionBurger,	//�I���I�j�I���o�[�K�[(5)
	enHamBurgerNum			//�n���o�[�K�[�̐��B
};

class HamBurgerFactory
{
private:
	HamBurgerFactory();
	~HamBurgerFactory() {}

public:
	static HamBurgerFactory& GetInstance()
	{
		static HamBurgerFactory instance;
		return instance;
	}

	//�n���o�[�K�[���擾�B
	HamBurger& GetHamBurger(EnHamBurger enHamBurger)
	{
		return m_hamBurgers[enHamBurger];
	}
private:
	//�n���o�[�K�[�̔z��B
	HamBurger m_hamBurgers[enHamBurgerNum];

};

//�n���o�[�K�[�t�@�N�g���[�̃C���X�^���X���擾�B
static inline HamBurgerFactory& GetHamBurgerFactory()
{
	return HamBurgerFactory::GetInstance();
}
