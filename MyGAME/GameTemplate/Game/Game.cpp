#include "stdafx.h"
#include "Game.h"
#include "Title.h"
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
#include "GameDirector.h"
#include "Player.h"
#include "PlayerGene.h"
#include  "DishGene.h"
#include "DishSpeedManeger.h"
#include "effect/effect.h"
#include "Floor.h"
#include "Arrow.h"
#include "CycleDirection.h"

namespace
{
	float  SCALER_COUNTDOWN_FONT_SCALE = 3.0f;
	float MAX_COUNTDOWN_FONT_SCALE = 4.0f;
}

Game::Game()
{	
	
}

Game::~Game()
{
	if (m_countSprite != nullptr) {
		DeleteGO(m_countSprite);
	}

	DeleteGO(floor_r);
	DeleteGO(floor_l);
	
	for (int i = 0; i < 3; i++) {
		if (m_result[i] != nullptr) {
			DeleteGO(m_result[i]);
		}
	}

	DeleteGO(ui);
	DeleteGO(playerGene);
	DeleteGO(dishGene);
	DeleteGO(m_speedManeger);
	DeleteGO(guzaiGene);
	DeleteGO(guzaiOkiba);
	DeleteGO(m_score);
	DeleteGO(m_bgm);

	for (int i = 0; i < 2; i++) {
		DeleteGO(m_trashCan[i]);
	}

	for (int i = 0; i < 3; i++) {
		DeleteGO(m_directionSprite[i]);
	}

	/*for (int i = 0; i < 2; i++) {
		DeleteGO(player[i]);
	}*/

	DeleteGO(counter01);
	DeleteGO(counter02);
	DeleteGO(kitchen01);
	DeleteGO(kitchen02);
	DeleteGO(m_level2D);
	DeleteGO(m_level);

}

bool Game::Start()
{
	//NewGO<CLevel2D>(3, "clevel2d");
	m_level2D = NewGO<CLevel2D>(3, "clevel2d");
	m_level = NewGO<Level>(0, "level");

	//���U���g�ɂ��ꂼ��nullptr�����Ă���
	//0 : ��������(���ꂾ����\��)
	//�ȉ��A���������łȂ��ꍇ
	//1 : �v���C���[1
	//2 : �v���C���[2
	for (int i = 0; i < 3; i++) {
		m_result[i] = nullptr;
	}

	playerGene = NewGO<PlayerGene>(0, "playerGene");
	dishGene = NewGO<DishGene>(0, "dishGene");
	m_speedManeger = NewGO<DishSpeedManeger>(0, "speedManeger");

	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init(L"Assets/sound/BGM/BGM1.wav", false);
	m_bgm->SetVolume(1.0f);
	m_bgm->Play(true);

	////���s�\���p�X�v���C�g
	////�\������|�W�V�������`
	//win_loseLeft.Set(200.0f, 350.0f);
	//win_loseRight.Set(1080.0f,350.0f);

	m_level->Init("Assets/level/level_new4.tkl", [&](ObjectData& objectData) {
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
	guzaiGene = NewGO<GuzaiGene>(0, "GuzaiGene");


	////���x��2D�̍\�z
	//level2D.Init("Assets/level2D/level2D.casl", [&](Level2DObjectData& objectData2D) {return false; });

	//UI
	ui = NewGO<FixedUI>(1, "ui");

	//�X�R�A�̕\��/////////////////////////////////////////////////////////////////////
	m_score = NewGO<Score>(2, "score");

	//�J�E���g�_�E���p�X�v���C�g�̏�����
	m_countSprite = NewGO<SpriteRender>(20,"count");					//�J�E���g�_�E���p�@�I������Delete�����
	Vector2 ctPivot = { 0.5f,0.5f };
	Vector3 ctPosition = { 0.0f,100.0f,0.0f };
	m_countSprite->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
	m_countSprite->SetPivot(ctPivot);
	m_countSprite->SetPosition(ctPosition);

	//�R���x�A��]����
	m_directionSprite[0] = NewGO<CycleDirection>(0, "dirsp1");
	m_directionSprite[0]->SetDirection(Forward);				//�E��]
	m_directionSprite[0]->SetSide(Left);						//��
	m_directionSprite[1] = NewGO<CycleDirection>(0, "dirsp2");
	m_directionSprite[1]->SetDirection(Reverse);				//����]
	m_directionSprite[1]->SetSide(Right);						//�E
	m_directionSprite[2] = NewGO<CycleDirection>(0, "dirspfixed");
	m_directionSprite[2]->SetDirection(FixedForward);			//�Œ�\��
	m_directionSprite[2]->SetSide(Up);							//��ʏ㕔

	//�J�E���g�_�E�����J�n����Ƃ������Ƃ�ݒ肷��B
	GetGameDirector().SetGameScene(enGameCountDown);

	return true;
}

void Game::Update()
{
	OutputDebugStringA("beforeUpdate\n");
	//�J�E���g�_�E������B
	OutputDebugStringA("bforCountDown\n");
	CountDown();
	OutputDebugStringA("aftCountDown\n");

	OutputDebugStringA("bforLevelDraw\n");
	//m_level->Draw();
	OutputDebugStringA("aftLevelDraw\n");

	//�^�C���A�b�v���ɍs������
	//���ʂ̕\��
	OutputDebugStringA("bforShowResult\n");
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
		OutputDebugStringA("aftShowResult\n");
		//game���̃^�C���A�b�v�t���O�𗧂āA�Q�[���V�[�������U���g�Ɉڍs����
		OutputDebugStringA("bforSetTimeUp\n");
		SetTimeUp();
		OutputDebugStringA("aftSetTimeUp\n");

		OutputDebugStringA("bforSetGameScene\n");
		GetGameDirector().SetGameScene(enResult);
		OutputDebugStringA("aftSetGameScene\n");
		////�Q�[���I����ʒm
		//GetGameDirector().SetGameScene(enGameEnd);

	}

	//���U���g���Ƀ{�^���������ƃ^�C�g���Ɉڍs
	if (GetGameDirector().GetGameScene() == enResult) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			GetGameDirector().SetGameScene(enNonScene);
			NewGO<Title>(0, "title");
			DeleteGO(this);
		}
	}

	/*if (GetGameDirector().GetGameScene() == enGamePlay) {
		if (g_pad[0]->IsTrigger(enButtonRB1)) {
			GetGameDirector().SetGameScene(enPause);
		}
	}

	if (GetGameDirector().GetGameScene() == enPause) {
		if (g_pad[0]->IsTrigger(enButtonRB1)) {
			GetGameDirector().SetGameScene(enGamePlay);
		}
	}*/

	OutputDebugStringA("afterUpdate\n");
}

void Game::CountDown()
{
	OutputDebugStringA("bforIsGameCountDown\n");
	//�J�E���g�_�E��������Ȃ�������B
	if (!GetGameDirector().GetIsGameCountDown())
	{
		//�������Ȃ��B
		return;
	}
	OutputDebugStringA("aftIsGammeCountDown\n");


	//TODO GameTime�ɂ���B

	//m_timer -= 1.0f / 60.0f;

	//m_timer -= 1.0f / 120.0f;
	m_timer -= 1.0f / 60.0f; //��ʂ̃��t���b�V�����[�g��60Hz�������̂ŕύX


	OutputDebugStringA("bforSetGameScene\n");
	//�X�v���C�g�̕s�����x��0�ɂȂ�����Q�[���X�^�[�g
	if (m_timer <= 0.0f && alpha <= 0.0f){
		//�J�E���g�_�E�����I�����A�Q�[�����J�n�������Ƃ�ݒ肷��B
		GetGameDirector().SetGameScene(enGamePlay);
		DeleteGO(m_font);
		
		//�X�v���C�g�폜
		DeleteGO (m_countSprite);
		m_countSprite = nullptr;

		return;
	}
	OutputDebugStringA("aftSetGameScene\n");

	/*std::wstring number;
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
	m_font->SetScale(scale);*/

	//�X�v���C�g�ύX����
	OutputDebugStringA("bforSpriteChange\n");
	if (m_countSprite == nullptr)
	{

	}
	else if (m_timer <= 4.0f && m_timer > 3.0 && changeCount == 3 && a == 0) {
		OutputDebugStringA("Image3\n");
		m_countSprite->Init("Assets/Image/3.dds", 512, 512);
		alpha = 0.0f;
		scaleRate = 2.0f;
		fadeOut = false;
		changeCount--;
		OutputDebugStringA("afterImage3\n");
		a++;
	}
	else if (m_timer <= 3.0f && m_timer > 2.0 && changeCount == 2 && a == 1) {
		OutputDebugStringA("Image2\n");
		m_countSprite->Init("Assets/Image/2.dds", 512, 512);
		alpha = 0.0f;
		scaleRate = 2.0f;
		fadeOut = false;
		changeCount--;
		OutputDebugStringA("afterImage2\n");
		a++;
	}
	else if (m_timer <= 2.0f && m_timer > 1.0 && changeCount == 1 && a == 2) {
		DeleteGO(m_countSprite);
		m_countSprite = nullptr;
		m_countSprite = NewGO<SpriteRender>(20, "count");
		Vector2 ctPivot = { 0.5f,0.5f };
		Vector3 ctPosition = { 0.0f,100.0f,0.0f };
		m_countSprite->SetColor(1.0f, 1.0f, 1.0f, 0.0f);

		m_countSprite->SetPivot(ctPivot);
		m_countSprite->SetPosition(ctPosition);
		OutputDebugStringA("Image1\n");
		m_countSprite->Init("Assets/Image/1.dds", 512, 512);
		OutputDebugStringA("1\n");
		alpha = 0.0f;
		OutputDebugStringA("2\n");
		scaleRate = 2.0f;
		OutputDebugStringA("3\n");
		fadeOut = false;
		OutputDebugStringA("4\n");
		changeCount--;
		OutputDebugStringA("afterImage1\n");
		a++;
	}
	else if (m_timer <= 1.0f && m_timer > 0.0 && changeCount == 0 && a == 3) {
		OutputDebugStringA("ImageStart\n");
		m_countSprite->Init("Assets/Image/start.dds", 512, 512);
		alpha = 0.0f;
		scaleRate = 2.0f;
		fadeOut = false;
		changeCount--;
		OutputDebugStringA("afterImageStart\n");
		a++;
	}

	OutputDebugStringA("aftSpriteChange\n");

	//�J�E���g�_�E������(�X�v���C�g)
	//�t�F�[�h�C���A�A�E�g����
	if (fadeOut == false) {
		alpha += 1.5f / 60.0f;
	}
	else {
		if (changeCount == -1) {	//�X�^�[�g�̕\���������������Ă��炤
			alpha -= 2.5f / 60.0f;
		}
		else {
			alpha -= 1.5f / 60.0f;
		}
	}

	if (alpha > 1.0f) {
		alpha = 1.0f;
		fadeOut = true;
	}
	else if (alpha < 0.0f) {
		alpha = 0.0f;
	}

	//�X�P�[���k������
	scaleRate -= 2.0f / 60.0f;
	if (scaleRate < 1.0f) {
		scaleRate = 1.0f;
	}

	OutputDebugStringA("bforSound\n");
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
	OutputDebugStringA("aftSound\n");

	m_ctScale = { scaleRate,scaleRate,1.0f };

	m_countSprite->SetColor(1.0f, 1.0f, 1.0f, alpha);
	m_countSprite->SetScale(m_ctScale);

	OutputDebugStringA("\n");
}