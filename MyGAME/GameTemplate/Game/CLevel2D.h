#pragma once

#include  "HamBurgerFactory.h"

class SpriteRender;
class MenuTimer;
class MissCounter;
class Counter;
#include "Level2D.h"

static const int SHOW_HAMBURGER_NUMBER = 3;

/// <summary>
/// ���x��2D�����̃T���v���N���X�B
/// </summary>
class CLevel2D : public IGameObject
{
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	//�s�v
	//Level2D����n���ꂽname(�p�X�̈ꕔ�j��p����SpriteRender�Ŏg��const char*�^�����B
	//const char* MakePathFromName(const char* name);

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

	//�n���o�[�K�[����v���Ă��邩�ǂ������擾
	bool GetIsMatchHamBurger(int* numbers, int size, int counterNo);
private:
	Level2D m_level2D;		//���x��2D�B
	//Sprite m_sprite;			//�X�v���C�g�B
	Vector3 m_position;		//���W�B
	Vector3 m_scale;		//�傫���B

	SpriteRender* sprite[enHamBurgerNum];



	//3�̃X�v���C�g�̍��W�B
	Vector3 m_spritePositions[SHOW_HAMBURGER_NUMBER];

	//�\�����Ă���n���o�[�K�[�̔z��B
	EnHamBurger m_showHamBurgers[SHOW_HAMBURGER_NUMBER];

	//�n���o�[�K�[�X�v���C�g�̃f�[�^�B�n���o�[�K�[�̐������p�ӂ���B
	Level2DObjectData m_level2DObjectDatas[enHamBurgerNum];

	MenuTimer* m_menuTimer[2];
	MissCounter* m_missCounter;
	Counter* m_counter01;
	Counter* m_counter02;
};