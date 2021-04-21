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
#include "FontRender.h"
#include "CLevel2D.h"
#include "Result.h"
#include "SoundSource.h"
#include "PostEffectTest.h"
#include "ShadowTest.h"
#include "Ground.h"

#include "GameDirector.h"
//#include "PopUp2D.h"

namespace
{
	float  SCALER_COUNTDOWN_FONT_SCALE = 3.0f;
	float MAX_COUNTDOWN_FONT_SCALE = 4.0f;
}

Level level;
//Level2D level2D;

Game::Game()
{	
	//�����̕`��///////////////////////////////////////////////////////////////////////
	//FixedUI�N���X�̃A�b�v�f�[�g���ŕ\�����镶�����Œ肵�Ă���B
	ui = NewGO<FixedUI>(1,"ui");

	//���U���g�ɂ��ꂼ��nullptr�����Ă���
	//0 : ��������(���ꂾ����\��)
	//�ȉ��A���������łȂ��ꍇ
	//1 : �v���C���[1
	//2 : �v���C���[2

	for (int i = 0; i < 3; i++) {
		m_result[i] = nullptr;
	}

	////���s�\���p�X�v���C�g
	////�\������|�W�V�������`
	//win_loseLeft.Set(200.0f, 350.0f);
	//win_loseRight.Set(1080.0f,350.0f);

	//�J�E���^�[�̍쐬/////////////////////////////////////////////////////////////////
	//SetCounterNo�łǂ��瑤�̃J�E���^�[�����肷��B
	/*counter01 = NewGO<Counter>(1, "counter01");
	counter01->SetCounterNo(1);
	Vector3 PosCo01 = { 900.0f, 0.0f, 400.0f };
	counter01->SetPosition(PosCo01);

	counter02 = NewGO<Counter>(1, "counter02");
	counter02->SetCounterNo(2);
	Vector3 PosCo02 = { -900.0f, 0.0f, 400.0f };
	counter02->SetPosition(PosCo02);*/

	//�L�b�`���̍쐬///////////////////////////////////////////////////////////////////
	//�J�E���^�[�Ɠ��l�ɂǂ��瑤������B
	/*kitchen01 = NewGO<Kitchen>(0, "kitchen01");
	kitchen01->SetKitchenNo(1);
	Vector3 kiPos01 = { 900.0f, 0.0f, 0.0f };
	kitchen01->SetKitchenPos(kiPos01);

	kitchen02 = NewGO<Kitchen>(0, "kitchen02");
	kitchen02->SetKitchenNo(2);
	Vector3 kiPos02 = { -900.0f, 0.0f, 0.0f };
	kitchen02->SetKitchenPos(kiPos02);*/

	///////////////////////////////////////////////////////////////////////////////
	//�X�R�A
	//m_score = NewGO<Score>(0, "score");
	
	////�摜�̕`��/////////////////////////////////////////////////////////////////////
	////�������A�������j���[�̂�
	/*for (int i = 0; i < 3; i++) {
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

		const float shiftRight = 150.0f;

		Vector3 pos = { -150.0f,-200.0f,0.0f };
		pos.x += i * shiftRight;
		menu[i]->SetPosition(pos);
	}*/

	//NewGO<CLevel2D>(3);

	//�J�E���^�[�̍쐬/////////////////////////////////////////////////////////////////
	//SetCounterNo�łǂ��瑤�̃J�E���^�[�����肷��B
	//counter01 = NewGO<Counter>(1, "counter01");
	//counter01->SetCounterNo(1);
	//Vector3 PosCo01 = { 0.0f, 0.0f, 0.0f };
	//counter01->SetPosition(PosCo01);

	//counter02 = NewGO<Counter>(1, "counter02");
	//counter02->SetCounterNo(2);
	//Vector3 PosCo02 = { -900.0f, 0.0f, 400.0f };
	//counter02->SetPosition(PosCo02);

	////�L�b�`���̍쐬///////////////////////////////////////////////////////////////////
	////�J�E���^�[�Ɠ��l�ɂǂ��瑤������B
	//kitchen01 = NewGO<Kitchen>(0, "kitchen01");
	//kitchen01->SetKitchenNo(1);
	//Vector3 kiPos01 = { 900.0f, 0.0f, 0.0f };
	//kitchen01->SetKitchenPos(kiPos01);

	//kitchen02 = NewGO<Kitchen>(0, "kitchen02");
	//kitchen02->SetKitchenNo(2);
	//Vector3 kiPos02 = { -900.0f, 0.0f, 0.0f };
	//kitchen02->SetKitchenPos(kiPos02);

	/////////////////////////////////////////////////////////////////////////////////
	
	

	////�v���C���[�̃��f�����쐬x2//////////////////////////////////////////////////////////
	/*player[0] = NewGO<ModelRender>(0, "player01");
	player[0]->SetPlayerNo(1);
	player[1] = NewGO<ModelRender>(0, "player02");
	player[1]->SetPlayerNo(2);*/

	//��ނƃo�t�𐶐���//////////////////////////////////////////////////////////////////
	/*generator01 = NewGO<ObjectGene>(1, "gene01");
	generator01->SetGeneNo(1);
	Vector3 PosGene01 = { 500.0f,100.0f,-500.0f };
	generator01->SetPosition(PosGene01);

	generator02 = NewGO<ObjectGene>(1, "gene02");
	generator02->SetGeneNo(2);
	Vector3 PosGene02 = { -300.0f,100.0f,-500.0f };
	generator02->SetPosition(PosGene02);*/

	////�o�t�A�C�e�����Ƃ������ɃA�C�R����z�u�B////////////////////////////////////////////
	//if (player[0]->stateBuff()) {
	//	Buff[0] = NewGO<SpriteRender>(2);
	//	Buff[0]->Init("Assets/Image/icon_speedup.dds", 128, 128);
	//	Vector3 pos = { -500.0f,350.0f,0.0f };
	//	Buff[0]->SetPosition(pos);
	//}

	level.Init("Assets/level/level_mirror.tkl", [&](ObjectData& objectData) {
		if (wcscmp(objectData.name, L"CounterPos01") == 0) {
			counter01 = NewGO<Counter>(0, "counter01");
			counter01->SetCounterNo(1);
			counter01->SetPosition(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"CounterPos02") == 0) {
			counter02 = NewGO<Counter>(0, "counter02");
			counter02->SetCounterNo(2);
			counter02->SetPosition(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"KitchenPos01") == 0) {
			kitchen01 = NewGO<Kitchen>(0, "kitchen01");
			kitchen01->SetKitchenNo(1);
			kitchen01->SetKitchenPos(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"KitchenPos02") == 0) {
			kitchen02 = NewGO<Kitchen>(0, "kitchen02");
			kitchen02->SetKitchenNo(2);
			kitchen02->SetKitchenPos(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"PlayerPos01") == 0) {
			player[0] = NewGO<ModelRender>(0, "player01");
			player[0]->SetPlayerNo(1);
			player[0]->SetPosition(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"PlayerPos02") == 0) {
			player[1] = NewGO<ModelRender>(0, "player02");
			player[1]->SetPlayerNo(2);
			player[1]->SetPosition(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"GeneratorPos01") == 0) {
			generator01 = NewGO<ObjectGene>(0, "gene01");
			generator01->SetGeneNo(1);
			generator01->SetPosition(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"GeneratorPos02") == 0) {
			generator02 = NewGO<ObjectGene>(0, "gene02");
			generator02->SetGeneNo(2);
			generator02->SetPosition(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"Conveyor") == 0) {
			return false;
		}
		if (wcscmp(objectData.name, L"Floor") == 0) {
			return true;
		}
		/*if (wcscmp(objectData.name, L"WayPoint011") == 0) {
			return false;
		}
		if (wcscmp(objectData.name, L"WayPoint012") == 0) {
			return false;
		}
		if (wcscmp(objectData.name, L"WayPoint013") == 0) {
			return false;
		}
		if (wcscmp(objectData.name, L"WayPoint014") == 0) {
			return false;
		}
		if (wcscmp(objectData.name, L"WayPoint021") == 0) {
			return false;
		}
		if (wcscmp(objectData.name, L"WayPoint022") == 0) {
			return false;
		}
		if (wcscmp(objectData.name, L"WayPoint023") == 0) {
			return false;
		}
		if (wcscmp(objectData.name, L"WayPoint024") == 0) {
			return false;
		}*/
		else {
			return true;
		}
		});

	////���x��2D�̍\�z
	//level2D.Init("Assets/level2D/level2D.casl", [&](Level2DObjectData& objectData2D) {return false; });

	//�����̕`��///////////////////////////////////////////////////////////////////////
	//FixedUI�N���X�̃A�b�v�f�[�g���ŕ\�����镶�����Œ肵�Ă���B
	//ui = NewGO<FixedUI>(2);

	NewGO<CLevel2D>(3, "clevel2d");

	//�X�R�A�̕\��/////////////////////////////////////////////////////////////////////
	m_score = NewGO<Score>(2, "score");

	//�|�X�g�G�t�F�N�g�̃e�X�g�p���f���B
	postTest =  NewGO<PostEffectTest>(5);

	//�V���h�E�̃e�X�g�p�̃��f��
	shadowTest = NewGO<ShadowTest>(5);

	//������������ALevel��Floor��return false �ɂ��邱�ƁB
	//���V���h�E���V�[�o�[�B
	ground = NewGO<Ground>(0);

	//�J�E���g�_�E�����J�n����Ƃ������Ƃ�ݒ肷��B
	GetGameDirector().SetGameScene(enGameCountDown);

	m_font = NewGO<FontRender>(5);

	/*m_popup2D_1 = NewGO<PopUp2D>(20);
	m_popup2D_1->SetEnSelf(enPlayer01);

	m_popup2D_2 = NewGO<PopUp2D>(20);
	m_popup2D_2 -> SetEnSelf(enPlayer02);*/
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
	for (int i = 0; i < 2; i++) {
		DeleteGO(m_result[i]);
	}
	DeleteGO(generator01);
	DeleteGO(generator02);
	DeleteGO(m_score);
}

bool Game::Start()
{
	return true;
}

void Game::Update()
{
	//�J�E���g�_�E������B
	CountDown();

	level.Draw();

	//�^�C���A�b�v���ɍs������
	//���ʂ̕\��
	if (ui->GetIsTimeUp() == true && GetTimeUp() == false) {
		
		//���������̂Ƃ�(ResultP1 = 0,ResultP2 = 0�̂Ƃ�)�A1�������\��
		if (m_score->ResultP1 == m_score->ResultP2) {
			m_result[0] = NewGO<Result>(1, "result");
			m_result[0]->SetSprite(0); //0 : ��������
			m_result[0]->SetSpritePos(0); //�������炢�̈ʒu
		}

		//���s�����܂��Ă���Ƃ�(enum�̕Ԃ������l���قȂ�Ƃ�),2����\��
		else if (m_score->ResultP1 != m_score->ResultP2) {
			//�v���C���[1
			if (m_score->ResultP1 == 1) {
				m_result[1] = NewGO<Result>(1, "result");
				m_result[1]->SetSprite(1); //1 : ����
				m_result[1]->SetSpritePos(1); //1 : �E��
			}
			if (m_score->ResultP1 == 2) {
				m_result[1] = NewGO<Result>(1, "result");
				m_result[1]->SetSprite(2); //2 : �s�k
				m_result[1]->SetSpritePos(1); //1 : �E��
			}

			//�v���C���[2
			if (m_score->ResultP2 == 1) {
				m_result[2] = NewGO<Result>(1, "result");
				m_result[2]->SetSprite(1); //1 : ����
				m_result[2]->SetSpritePos(2); //2 :����
			}
			if (m_score->ResultP2 == 2) {
				m_result[2] = NewGO<Result>(1, "result");
				m_result[2]->SetSprite(2); //2 : �s�k
				m_result[2]->SetSpritePos(2); //2 :����
			}

		}
		//game���̃^�C���A�b�v�t���O�𗧂Ă�
		SetTimeUp();
	}
	
}

void Game::CountDown()
{
	//�J�E���g�_�E��������Ȃ�������B
	if (!GetGameDirector().GetIsGameCountDown())
	{
		//�������Ȃ��B
		return;
	}


	//TODO GameTime�ɂ���B
	m_timer -= 1.0f / 120.0f;

	if (m_timer <= 0.0f)
	{
		//�J�E���g�_�E�����I�����A�Q�[�����J�n�������Ƃ�ݒ肷��B
		GetGameDirector().SetGameScene(enGamePlay);
		DeleteGO(m_font);
		return;
	}

	
	std::wstring number;
	if (m_timer < 1.0f)
	{
		number = L"Start";
	}
	else {
		number = std::to_wstring(int(m_timer));
	}
	float scale = MAX_COUNTDOWN_FONT_SCALE;
	scale -= SCALER_COUNTDOWN_FONT_SCALE * (m_timer - int(m_timer));

	m_font->SetText(number.c_str());
	m_font->SetColor({ 1.0f,0.0f,0.0f,0.0f });
	m_font->SetPivot({ 0.5f, 0.5f });
	m_font->SetPosition({ -100, 200 });
	m_font->SetScale(scale);

}