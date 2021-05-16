#include "stdafx.h"
#include "Game.h"
#include "Level.h"
#include "FixedUI.h"
#include "SpriteRender.h"
#include "Guzai.h"
#include "GuzaiGene.h"
#include "GuzaiOkiba.h"
#include "Kitchen.h"
#include "Counter.h"
#include "Score.h"
#include "FontRender.h"
#include "CLevel2D.h"
#include "Result.h"
#include "SoundSource.h"
#include "PostEffectTest.h"
#include "TrashCan.h"

//#include "ShadowTest.h"
#include "Ground.h"


#include "GameDirector.h"

#include "Player.h"
#include "PlayerGene.h"

#include  "DishGene.h"
#include "DishSpeedManeger.h"

#include "effect/effect.h"
#include "Floor.h"
#include "Arrow.h"

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

	playerGene = NewGO<PlayerGene>(0, "playerGene");
	dishGene = NewGO<DishGene>(0,"dishGene");
	m_speedManeger = NewGO<DishSpeedManeger>(0, "speedManeger");

	////���s�\���p�X�v���C�g
	////�\������|�W�V�������`
	//win_loseLeft.Set(200.0f, 350.0f);
	//win_loseRight.Set(1080.0f,350.0f);

	////�o�t�A�C�e�����Ƃ������ɃA�C�R����z�u�B////////////////////////////////////////////
	//if (player[0]->stateBuff()) {
	//	Buff[0] = NewGO<SpriteRender>(2);
	//	Buff[0]->Init("Assets/Image/icon_speedup.dds", 128, 128);
	//	Vector3 pos = { -500.0f,350.0f,0.0f };
	//	Buff[0]->SetPosition(pos);
	//}

	level.Init("Assets/level/level_new4.tkl", [&](ObjectData& objectData) {
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
			playerGene->SetPlayer01Pos(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"PlayerPos02") == 0) {
			playerGene->SetPlayer02Pos(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"Conveyor") == 0) {
			return false;
		}
		if (wcscmp(objectData.name, L"FloorBlue") == 0) {
			
			return false;
		}
		if (wcscmp(objectData.name, L"FloorRed") == 0) {
			return false;
		}
		
		if (wcscmp(objectData.name, L"TrashLeft") == 0) {
			m_trashCan[0] = NewGO<TrashCan>(0, "trashcan01");
			m_trashCan[0]->SetTrashCanNum(1);
			m_trashCan[0]->SetPosition(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"TrashRight") == 0) {
			m_trashCan[1] = NewGO<TrashCan>(0, "trashcan02");
			m_trashCan[1]->SetTrashCanNum(2);
			m_trashCan[1]->SetPosition(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"floorLeft") == 0) {
			floor_l = NewGO<Floor>(0);
			floor_l->SetRed(true);
			floor_l->SetPosition(objectData.Pos);
			return true;
		}
		if (wcscmp(objectData.name, L"floorRight") == 0) {
			floor_r = NewGO<Floor>(0);
			floor_r->SetRed(false);
			floor_r->SetPosition(objectData.Pos);
			return true;
		}

		else {
			return true;
		}
		});

	//��ޒu����̕\��
	guzaiOkiba = NewGO<GuzaiOkiba>(0, "GuzaiOkiba");

	

	////���x��2D�̍\�z
	//level2D.Init("Assets/level2D/level2D.casl", [&](Level2DObjectData& objectData2D) {return false; });

	NewGO<CLevel2D>(3, "clevel2d");


	//�X�R�A�̕\��/////////////////////////////////////////////////////////////////////
	m_score = NewGO<Score>(2, "score");

	//�|�X�g�G�t�F�N�g�̃e�X�g�p���f���B
	//postTest =  NewGO<PostEffectTest>(5);

	//�V���h�E�̃e�X�g�p�̃��f��
	//shadowTest = NewGO<ShadowTest>(5);

	//������������ALevel��Floor��return false �ɂ��邱�ƁB
	//���V���h�E���V�[�o�[�B
	//ground = NewGO<Ground>(0);

	//�J�E���g�_�E�����J�n����Ƃ������Ƃ�ݒ肷��B
	GetGameDirector().SetGameScene(enGameCountDown);

	m_font = NewGO<FontRender>(5);
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
	DeleteGO(guzaiGene);
	DeleteGO(guzaiOkiba);
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

	//m_timer -= 1.0f / 60.0f;

	//m_timer -= 1.0f / 120.0f;
	m_timer -= 1.0f / 60.0f; //��ʂ̃��t���b�V�����[�g��60Hz�������̂ŕύX



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
	
	//�J�n���̃J�E���g�_�E���ɉ����ĉ���炷�B
	if (m_timer < 1.0f && m_soundFlag00 == false) {
		//����炷
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/basketball_buzzer1.wav", false);
		se->SetVolume(2.0f);
		se->Play(false);
		m_soundFlag00 = true;
	}
	else if (m_timer < 2.0f && m_soundFlag01 == false) {
		//����炷
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/Time.wav", false);
		se->SetVolume(2.0f);
		se->Play(false);
		m_soundFlag01 = true;
	}
	else if (m_timer < 3.0f && m_soundFlag02 == false) {
		//����炷
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/Time.wav", false);
		se->SetVolume(2.0f);
		se->Play(false);
		m_soundFlag02 = true;
	}
	else if (m_timer < 3.9f && m_soundFlag03 == false) {
		//����炷
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/Time.wav", false);
		se->SetVolume(2.0f);
		se->Play(false);
		m_soundFlag03 = true;
	}

}