#pragma once

#include  "HamBurgerFactory.h"

class SpriteRender;
class MenuTimer;
class MissCounter;
class Counter;
class CSoundSource;
class CLevel2D;
class Level;
#include "Level2D.h"

static const int SHOW_HAMBURGER_SPECIES = 11;
static const int SHOW_HAMBURGER_NUMBER = 3;

/// <summary>
/// ���x��2D�����̃T���v���N���X�B
/// </summary>
class CLevel2D : public IGameObject
{
	~CLevel2D();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	//���ɕ\������n���o�[�K�[�����߂邨(�L�E�ցE�M)�I
	void Roulette(int number);

	//�n���o�[�K�[�̉摜��\�����邨�I
	void ShowHamBurger(int number,EnHamBurger enHamBurger);
public:
	//�\�����Ă���3�̃n���o�[�K�[���擾�B
	EnHamBurger* GetShowHamBurgers()
	{
		return m_showHamBurgers;
	}

	//

	/**
	 * @brief �n���o�[�K�[����v���Ă��邩�ǂ������擾
	 * @param numbers �ςݏグ����ނ̎�ށB
	 * @param size �n���o�[�K�[�̑w��
	 * @param counterNo ���ꂽ�n���o�[�K�[�̔ԍ�
	 * @return TRUE�����ׂĈ�v�AFALSE���ǂ���������
	*/
	bool GetIsMatchHamBurger(int* numbers, int size, int counterNo);

	/**
	 * @brief �摜�𓮂����֐��B
	 * @param number �摜�̏�� enMenuSlideState
	*/
	void SpriteSet(int number);

	/**
	 * @brief �摜�̈ړ��ʂ��擾
	 * @param i �ړ���
	 * @return 
	*/
	float GetSlideAmount(int i) { return m_slideAmount[i]; }

	enum enMenuSlideState {
		enStop,
		enSlideUp,
		enSlideDown,
		enSlideStateNum
	};

private:
	Level2D m_level2D;										//���x��2D�B
	//Vector3 m_position;									//���W�B
	//Vector3 m_scale;										//�傫���B
	Vector3 m_slidePos[SHOW_HAMBURGER_NUMBER];				//���j���[���ォ���ɃX���C�h�ړ�
	float m_slideAmount[SHOW_HAMBURGER_NUMBER] = { 0.0f };	//�摜�̏㉺�ړ���
	int m_slide[SHOW_HAMBURGER_NUMBER] = { 0 };			//���j���[�摜�̃X���C�h�t���O�B0�œ����Ȃ��A1�ŏ�ɃX���C�h�A2�ŉ��ɃX���C�h�B
	bool m_TimeUpSet[2] = { false };					//���j���[�̃^�C���I�[�o�[�����H
	SpriteRender* sprite[enHamBurgerNum] = {nullptr};
	int m_randNum[SHOW_HAMBURGER_NUMBER] = { 0 };


	//3�̃X�v���C�g�̍��W�B
	Vector3 m_spritePositions[SHOW_HAMBURGER_NUMBER];

	//�\�����Ă���n���o�[�K�[�̔z��B
	EnHamBurger m_showHamBurgers[SHOW_HAMBURGER_SPECIES];

	//�n���o�[�K�[�X�v���C�g�̃f�[�^�B�n���o�[�K�[�̐������p�ӂ���B
	Level2DObjectData m_level2DObjectDatas[enHamBurgerNum];
	MenuTimer* m_menuTimer[2] = { nullptr, nullptr };
	MissCounter* m_missCounter = nullptr;
	Counter* m_counter00 = nullptr;
	Counter* m_counter01 = nullptr;
	CSoundSource* m_slideSe[3] = { nullptr, nullptr, nullptr };
};