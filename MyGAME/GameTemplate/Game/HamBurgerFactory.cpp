#include "stdafx.h"
#include "HamBurgerFactory.h"

HamBurgerFactory::HamBurgerFactory()
{
	//�n���o�[�K�[�̃f�[�^�����B
	//�O�D�`�[�Y�@
	//�P�D�G�b�O�@
	//�Q�D���^�X�@
	//�R�D�p�e�@
	//�S�D�g�}�g
	//�T�D�I�j�I��  ���ǉ����
	//�U�D�x�[�R���@���ǉ����

	HamBurger cheese;
	cheese.push_back(3);
	cheese.push_back(0);
	cheese.push_back(2);
	m_hamBurgers[enCheeseBurger] = cheese;

	HamBurger tomato;
	tomato.push_back(3);
	tomato.push_back(4);
	tomato.push_back(4);
	tomato.push_back(2);
	m_hamBurgers[enTomatoBurger] = tomato;

	HamBurger egg;
	egg.push_back(2);
	egg.push_back(4);
	egg.push_back(1);
	egg.push_back(3);
	m_hamBurgers[enEggBurger] = egg;
	
	//�ȉ��A�ǉ����j���[
	//���ʂ̃o�[�K�[
	HamBurger basic;
	basic.push_back(3); //�p�e�B
	m_hamBurgers[enBasicBurger] = basic;
	
	//�_�u���o�[�K�[
	HamBurger double_bur;
	double_bur.push_back(3); //�p�e�B
	double_bur.push_back(3); //�p�e�B
	m_hamBurgers[enDoubleBurger] = double_bur;

	//��؃o�[�K�[
	HamBurger vegetable;
	vegetable.push_back(4); //�g�}�g
	vegetable.push_back(5); //�I�j�I��
	m_hamBurgers[enVegetableBurger] = vegetable;

	//�x�[�R���o�[�K�[
	HamBurger bacon;
	bacon.push_back(2); //���^�X
	bacon.push_back(0); //�`�[�Y
	bacon.push_back(6); //�x�[�R��
	m_hamBurgers[enBaconBurger] = bacon;

	//BLT�o�[�K�[
	HamBurger blt;
	blt.push_back(4); //�g�}�g
	blt.push_back(2); //���^�X
	blt.push_back(2); //���^�X
	blt.push_back(6); //�x�[�R��
	m_hamBurgers[enBLTBurger] = blt;

	//�I�j�I���o�[�K�[
	HamBurger onion;
	onion.push_back(5); //�I�j�I��
	onion.push_back(4); //�g�}�g
	onion.push_back(5); //�I�j�I��
	onion.push_back(0); //�`�[�Y
	onion.push_back(3); //�p�e�B
	m_hamBurgers[enOnionBurger] = onion;

	//�n�C�J�����[�o�[�K�[
	HamBurger highcal;
	highcal.push_back(6); //�x�[�R��
	highcal.push_back(0); //�`�[�Y
	highcal.push_back(3); //�p�e�B
	highcal.push_back(0); //�`�[�Y
	highcal.push_back(1); //�G�b�O
	m_hamBurgers[enHighcalBurger] = highcal;

	//�I���I�j�I���o�[�K�[
	HamBurger ononion;
	ononion.push_back(6); //�x�[�R��
	ononion.push_back(0); //�`�[�Y
	ononion.push_back(5); //�I�j�I��
	ononion.push_back(5); //�I�j�I��
	ononion.push_back(5); //�I�j�I��
	m_hamBurgers[enOnOnionBurger] = ononion;

}