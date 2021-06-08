#include "stdafx.h"
#include "HamBurgerFactory.h"

HamBurgerFactory::HamBurgerFactory()
{
	//�n���o�[�K�[�̋�ގ�ޔԍ��B
	//�O�D�`�[�Y�@
	//�P�D�G�b�O�@
	//�Q�D���^�X�@
	//�R�D�p�e�@
	//�S�D�g�}�g
	//�T�D�I�j�I�� 
	//�U�D�x�[�R���@

	HamBurger cheese;
	cheese.push_back(3); //�R�D�p�e
	cheese.push_back(0); //�O�D�`�[�Y
	cheese.push_back(2); //�Q�D���^�X�@
	m_hamBurgers[enCheeseBurger] = cheese;

	HamBurger tomato;
	tomato.push_back(3); //�R�D�p�e
	tomato.push_back(4); //�S�D�g�}�g
	tomato.push_back(4); //�S�D�g�}�g
	tomato.push_back(2); //�Q�D���^�X�@
	m_hamBurgers[enTomatoBurger] = tomato;

	HamBurger egg;
	egg.push_back(2); //�Q�D���^�X�@
	egg.push_back(4); //�S�D�g�}�g
	egg.push_back(1); //�P�D�G�b�O
	egg.push_back(3); //�R�D�p�e
	m_hamBurgers[enEggBurger] = egg;
	
	//���ʂ̃o�[�K�[
	HamBurger basic;
	basic.push_back(3); //�p�e
	m_hamBurgers[enBasicBurger] = basic;
	
	//�_�u���o�[�K�[
	HamBurger double_bur;
	double_bur.push_back(3); //�p�e
	double_bur.push_back(3); //�p�e
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