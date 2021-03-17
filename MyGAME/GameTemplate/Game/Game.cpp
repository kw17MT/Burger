#include "stdafx.h"
#include "Game.h"

#include "Level.h"
#include "ModelRender.h"
#include "FixedUI.h"
#include "SpriteRender.h"
#include "Guzai.h"
#include "ObjectGene.h"
#include "Kitchen.h"
#include "Counter.h"
#include "Score.h"

Game::Game()
{
	//�����̕`��///////////////////////////////////////////////////////////////////////
	//FixedUI�N���X�̃A�b�v�f�[�g���ŕ\�����镶�����Œ肵�Ă���B
	ui = NewGO<FixedUI>(1);

	//�J�E���^�[�̍쐬/////////////////////////////////////////////////////////////////
	//SetCounterNo�łǂ��瑤�̃J�E���^�[�����肷��B
	counter01 = NewGO<Counter>(1, "counter01");
	counter01->SetCounterNo(1);
	Vector3 PosCo01 = { 900.0f, 0.0f, 400.0f };
	counter01->SetPosition(PosCo01);

	counter02 = NewGO<Counter>(1, "counter02");
	counter02->SetCounterNo(2);
	Vector3 PosCo02 = { -900.0f, 0.0f, 400.0f };
	counter02->SetPosition(PosCo02);

	//�L�b�`���̍쐬///////////////////////////////////////////////////////////////////
	//�J�E���^�[�Ɠ��l�ɂǂ��瑤������B
	kitchen01 = NewGO<Kitchen>(0, "kitchen01");
	kitchen01->SetKitchenNo(1);
	Vector3 kiPos01 = { 900.0f, 0.0f, 0.0f };
	kitchen01->SetKitchenPos(kiPos01);

	kitchen02 = NewGO<Kitchen>(0, "kitchen02");
	kitchen02->SetKitchenNo(2);
	Vector3 kiPos02 = { -900.0f, 0.0f, 0.0f };
	kitchen02->SetKitchenPos(kiPos02);

	///////////////////////////////////////////////////////////////////////////////
	score = NewGO<Score>(0, "score");

	
	//�摜�̕`��///////////////////////////////////////////////////////////////////////
	//�������A�������j���[�̂�
	for (int i = 0; i < 3; i++) {
		menu[i] = NewGO<SpriteRender>(2);
		switch (i) {
		case 0:
			menu[i]->Init("Assets/Image/burger_cheese_new.dds", 128, 256);
			break;
		case 1:
			menu[i]->Init("Assets/Image/burger_tomato.dds", 128, 256);
			break;
		case 2:
			menu[i]->Init("Assets/Image/burger_egg.dds", 128, 256);
			break;
		}

		const float ShiftRight = 150.0f;

		Vector3 pos = { -150.0f,-200.0f,0.0f };
		pos.x += i * ShiftRight;
		menu[i]->SetPosition(pos);
	}

	//�v���C���[�̃��f�����쐬x2//////////////////////////////////////////////////////////
	player[0] = NewGO<ModelRender>(0, "player01");
	player[0]->SetPlayerNo(1);
	player[1] = NewGO<ModelRender>(0, "player02");
	player[1]->SetPlayerNo(2);

	//��ނƃo�t�𐶐���//////////////////////////////////////////////////////////////////
	generator01 = NewGO<ObjectGene>(1, "gene01");
	generator01->SetGeneNo(1);
	Vector3 PosGene01 = { 500.0f,100.0f,-500.0f };
	generator01->SetPosition(PosGene01);

	generator02 = NewGO<ObjectGene>(1, "gene02");
	generator02->SetGeneNo(2);
	Vector3 PosGene02 = { -300.0f,100.0f,-500.0f };
	generator02->SetPosition(PosGene02);

	//�o�t�A�C�e�����Ƃ������ɃA�C�R����z�u�B////////////////////////////////////////////
	if (player[0]->stateBuff()) {
		Buff[0] = NewGO<SpriteRender>(2);
		Buff[0]->Init("Assets/Image/icon_speedup.dds", 128, 128);
		Vector3 pos = { -500.0f,350.0f,0.0f };
		Buff[0]->SetPosition(pos);
	}
}

Game::~Game()
{
	DeleteGO(ui);
	DeleteGO(counter01);
	DeleteGO(counter02);
	DeleteGO(kitchen01);
	DeleteGO(kitchen02);
	for (int i = 0; i < 3;i++) {
		DeleteGO(menu[i]);
	}
	for (int i = 0; i < 2;i++) {
		DeleteGO(Buff[i]);
	}
	for (int i = 0; i < 2;i++) {
		DeleteGO(player[i]);
	}
	DeleteGO(generator01);
	DeleteGO(generator02);
	DeleteGO(score);
}

void Game::Update()
{
	
}