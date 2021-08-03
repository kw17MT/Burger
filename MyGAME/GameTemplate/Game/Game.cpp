#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "Level.h"
#include "FixedUI.h"
#include "SpriteRender.h"
#include "Guzai.h"
#include "GuzaiOkiba.h"
#include "Kitchen.h"
#include "Counter.h"
#include "Score.h"
#include "FontRender.h"
#include "CLevel2D.h"
#include "Result.h"
#include "SoundSource.h"
#include "TrashCan.h"
#include "GameDirector.h"
#include "Player.h"
#include "PlayerGene.h"
#include "DishGene.h"
#include "effect/effect.h"
#include "Floor.h"
#include "Arrow.h"
#include "CycleDirection.h"
#include "CountDown.h"
#include "DishManager.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include "Conveyor.h"
#include "LightManager.h"


namespace
{
	const Vector2 COUNTDOWN_PIVOT = { 0.5f,0.5f };
	const Vector3 COUNTDOWN_POS = { 0.0f,100.0f,0.0f };
	const Vector4 COUNTDOWN_START_COLOR = { 1.0f,1.0f,1.0f,0.0f };

	float SCALER_COUNTDOWN_FONT_SCALE = 3.0f;
	float MAX_COUNTDOWN_FONT_SCALE = 4.0f;

	const int RESULT_SPRITE_NUM = 3;
	const int TRASHCAN_NUM = 2;
	const int DIRECTION_SPRITE_NUM = 3;
	const int SET_NUMBER_FOR_PLAYER_ONE = 0;
	const int SET_NUMBER_FOR_PLAYER_TWO = 1;
	const int DIRECTION_SPRITE_LEFT = 0;
	const int DIRECTION_SPRITE_RIGHT = 1;
	const int DIRECTION_SPRITE_UP = 2;
	const int TRASHCAN_LEFT = 0;
	const int TRASHCAN_RIGHT = 1;
	const int RESULT_DRAW = 0;
	const int RESULT_WIN = 1;
	const int RESULT_LOSE = 2;
	const int RESULT_FOR_PLAYER_ONE = 1;
	const int RESULT_FOR_PLAYER_TWO = 2;
	const int COUNTDOWN_SPRITE_WIDTH = 512;
	const int COUNTDOWN_SPRITE_HEIGHT = 512;
	const int COUNTDOWN_PHASE_ONE = 1;
	const int COUNTDOWN_PHASE_TWO = 2;
	const int COUNTDOWN_PHASE_THREE = 3;
	const int COUNTDOWN_PHASE_END = 4;
	const int AJUST_TIMER_SPEED = 2;
	const int SAME_NAME = 0;
	const int PLAYER_ONE_CONTROLLER = 0;

	const float COUNTDOWN_PHASE1_START = 4.0f;
	const float COUNTDOWN_PHASE1_END = 3.0f;
	const float COUNTDOWN_PHASE2_START = 3.0f;
	const float COUNTDOWN_PHASE2_END = 2.0f;
	const float COUNTDOWN_PHASE3_START = 2.0f;
	const float COUNTDOWN_PHASE3_END = 1.0f;
	const float COUNTDOWN_PHASE_FINAL_START = 1.0f;
	const float COUNTDOWN_PHASE_FINAL_END = 0.0f;
	const float COUNTDOWN_SHRINK_SPEED = 2.0f / 60.0f;
	const float COUNTDOWN_START_SCALE = 2.0f;
	const float SE_VOLUME = 1.0f;
}

Game::~Game()
{
	if (m_countDown != nullptr) {
		DeleteGO(m_countDown);
	}

	DeleteGO(floor_r);
	DeleteGO(floor_l);
	
	for (int i = 0; i < RESULT_SPRITE_NUM; i++) {
		if (m_result[i] != nullptr) {
			DeleteGO(m_result[i]);
		}
	}

	DeleteGO(ui);
	DeleteGO(playerGene);
	DeleteGO(dishGene);
	DeleteGO(guzaiOkiba);
	DeleteGO(m_score);
	DeleteGO(m_bgm);

	for (int i = 0; i < TRASHCAN_NUM; i++) {
		DeleteGO(m_trashCan[i]);
	}

	for (int i = 0; i < DIRECTION_SPRITE_NUM; i++) {
		DeleteGO(m_directionSprite[i]);
	}

	DeleteGO(counter00);
	DeleteGO(counter01);
	DeleteGO(kitchen00);
	DeleteGO(kitchen01);
	DeleteGO(m_level2D);
	DeleteGO(m_level);
	DeleteGO(m_conveyor);
	DeleteGO(ui);
}

bool Game::Start()
{
	//2D�̃��x���̕\���i���j���[3��MISS�̎l�p6���j
	m_level2D = NewGO<CLevel2D>(3, "clevel2d");
	//3D�̃��x���̕\���i�R���x�A�̂݁A���Ƃ͖��O��NewGO���Ă���j
	m_level = NewGO<Level>(0, "level");
	//�v���C���[�̐�������쐬
	playerGene = NewGO<PlayerGene>(0, "playerGene");
	//�M�̐�������쐬
	dishGene = NewGO<DishGene>(0, "dishGene");
	//���x���𗘗p�����I�u�W�F�N�g�̔z�u
	m_level->Init("Assets/level/level.tkl", [&](ObjectData& objectData) {
		//�J�E���^�[�̃I�u�W�F�N�g�i���j���o��
		if (wcscmp(objectData.name, L"CounterPos01") == SAME_NAME) {
			counter00 = NewGO<Counter>(0, "counter00");
			counter00->SetCounterNo(SET_NUMBER_FOR_PLAYER_ONE);
			counter00->SetPosition(objectData.Pos);
			return true;
		}
		//�J�E���^�[�̃I�u�W�F�N�g�i�E�j���o��
		if (wcscmp(objectData.name, L"CounterPos02") == SAME_NAME) {
			counter01 = NewGO<Counter>(0, "counter01");
			counter01->SetCounterNo(SET_NUMBER_FOR_PLAYER_TWO);
			counter01->SetPosition(objectData.Pos);
			return true;
		}
		//�L�b�`���i���j���o��
		if (wcscmp(objectData.name, L"KitchenPos01") == SAME_NAME) {
			kitchen00 = NewGO<Kitchen>(0, "kitchen00");
			kitchen00->SetKitchenNo(SET_NUMBER_FOR_PLAYER_ONE);
			kitchen00->SetKitchenPos(objectData.Pos);
			return true;
		}
		//�L�b�`���i�E�j���o��
		if (wcscmp(objectData.name, L"KitchenPos02") == SAME_NAME) {
			kitchen01 = NewGO<Kitchen>(0, "kitchen01");
			kitchen01->SetKitchenNo(SET_NUMBER_FOR_PLAYER_TWO);
			kitchen01->SetKitchenPos(objectData.Pos);
			return true;
		}
		//�v���C���[1���o���ʒu���W���擾����B
		if (wcscmp(objectData.name, L"PlayerPos01") == SAME_NAME) {
			playerGene->SetPlayer01Pos(objectData.Pos);
			return true;
		}
		//�v���C���[2���o���ʒu���W���擾����
		if (wcscmp(objectData.name, L"PlayerPos02") == SAME_NAME) {
			playerGene->SetPlayer02Pos(objectData.Pos);
			return true;
		}
		//�R���x�A�̃��f�����o���B
		if (wcscmp(objectData.name, L"Conveyor") == SAME_NAME) {
			m_conveyor = NewGO<Conveyor>(0);
			m_conveyor->SetPosition(objectData.Pos);
			return true;
		}
		//�S�~���i���j���o���B
		if (wcscmp(objectData.name, L"TrashLeft") == SAME_NAME) {
			m_trashCan[TRASHCAN_LEFT] = NewGO<TrashCan>(0, "trashcan00");
			m_trashCan[TRASHCAN_LEFT]->SetTrashCanNum(SET_NUMBER_FOR_PLAYER_ONE);
			m_trashCan[TRASHCAN_LEFT]->SetPosition(objectData.Pos);
			return true;
		}
		//�S�~���i�E�j���o���B
		if (wcscmp(objectData.name, L"TrashRight") == SAME_NAME) {
			m_trashCan[TRASHCAN_RIGHT] = NewGO<TrashCan>(0, "trashcan01");
			m_trashCan[TRASHCAN_RIGHT]->SetTrashCanNum(SET_NUMBER_FOR_PLAYER_TWO);
			m_trashCan[TRASHCAN_RIGHT]->SetPosition(objectData.Pos);
			return true;
		}
		//���i���j���o���B
		if (wcscmp(objectData.name, L"floorLeft") == SAME_NAME) {
			floor_l = NewGO<Floor>(0);
			floor_l->SetRed(true);
			floor_l->SetPosition(objectData.Pos);
			return true;
		}
		//���i�E�j���o���B
		if (wcscmp(objectData.name, L"floorRight") == SAME_NAME) {
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
	//��ނ̐����A��[���Ǘ��������
	//UI�S�ʂ��o������
	ui = NewGO<FixedUI>(1, "ui");
	//�X�R�A�̕\�����s������
	m_score = NewGO<Score>(2, "score");
	//�J�E���g�_�E���p�X�v���C�g�̏�����
	m_countDown = NewGO<CountDown>(1, "countdown");

	//�R���x�A��]�����̉摜��3���o���B
	m_directionSprite[DIRECTION_SPRITE_LEFT] = NewGO<CycleDirection>(0, "dirsp1");
	m_directionSprite[DIRECTION_SPRITE_LEFT]->SetDirection(Reverse);				//�E��]
	m_directionSprite[DIRECTION_SPRITE_LEFT]->ChangeSpriteReverse();
	m_directionSprite[DIRECTION_SPRITE_LEFT]->SetSide(Left);						//��

	m_directionSprite[DIRECTION_SPRITE_RIGHT] = NewGO<CycleDirection>(0, "dirsp2");
	m_directionSprite[DIRECTION_SPRITE_RIGHT]->SetDirection(Forward);				//����]
	m_directionSprite[DIRECTION_SPRITE_RIGHT]->ChangeSpriteForward();
	m_directionSprite[DIRECTION_SPRITE_RIGHT]->SetSide(Right);						//�E

	m_directionSprite[DIRECTION_SPRITE_UP] = NewGO<CycleDirection>(0, "dirspfixed");
	m_directionSprite[DIRECTION_SPRITE_UP]->SetDirection(FixedForward);				//�Œ�\��
	m_directionSprite[DIRECTION_SPRITE_UP]->SetSide(Up);							//��ʏ㕔

	//BGM���Ȃ炷�B
	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init(L"Assets/sound/BGM/BGM1.wav", false);
	m_bgm->SetVolume(SE_VOLUME);
	m_bgm->Play(true);


	//�f�v�X�V���h�E�m�F�p�̏��쐬
	//�������Ɓ@DeleteGO�����ĂȂ�
	/*m_depthTest = NewGO<Floor>(0);
	Vector3 depthPos = { -700.0f,200.0f,-500.0f };
	m_depthTest->SetPosition(depthPos);
	Vector3 depthScale = { 0.2f,1.0f,0.1f };
	m_depthTest->SetScale(depthScale);*/

	
	return true;
}

void DishSpeedUp()
{
	//�M�̃X�s�[�h�A�b�v�܂ł̎��Ԃ�0�ȉ��ł����
	if (DishManager::GetInstance().GetTimeTillSpeedUp() <= 0) {
		//�����_���Ȑ����擾����B
		std::random_device rnd;
		std::mt19937 mt(rnd());
		std::uniform_int_distribution<int> rand(9, 15);
		////10~20�܂ł̐������擾����B
		float TimeTillSpeedUp = static_cast<float>(rand(mt));
		//�X�s�[�h�A�b�v�܂ł̎��Ԃ�ݒ肵�Ă��B
		DishManager::GetInstance().SetTimeTillSpeedUp(TimeTillSpeedUp);
		float TimeForSpeedUp = TimeTillSpeedUp / 3.0f;
		//�X�s�[�h�A�b�v�܂ł̎��Ԃ�ݒ肵�Ă��B
		DishManager::GetInstance().SetActiveTimeForSpeedUp(TimeForSpeedUp);
	}
	//�X�s�[�h�A�b�v�܂ł̎��Ԃ��ݒ肳��Ă���or�c���Ă���Ȃ��
	else {
		//1�t���[���ɂ����鎞�Ԃ��擾
		float gameTime = GameTime().GetFrameDeltaTime();
		//1�b��1�ւ炵�Ă����B
		DishManager::GetInstance().DecreaseTimeTillSpeedUp(gameTime);
		//�X�s�[�h�A�b�v�܂ł̎��Ԃ��O�ɂȂ�����
		if (DishManager::GetInstance().GetTimeTillSpeedUp() <= 0.0f) {
			//���݂̃X�s�[�h�A�b�v�̏�Ԃ��t�ɂ���B
			DishManager::GetInstance().SwitchSpeedUpState();
		}
	}
	//���݃X�s�[�h�A�b�v���Ȃ��
	if (DishManager::GetInstance().GetSpeedUpState() == true) {
		float gameTime = GameTime().GetFrameDeltaTime();
		//�Q�[���^�C����p���ăX�s�[�h�A�b�v�̗L�����Ԃ����炵�Ă����B
		DishManager::GetInstance().DecreaseActiveTimeForSpeedUp(gameTime);
		//�X�s�[�h�A�b�v�̗L�����Ԃ��Ȃ��Ȃ�����
		if (DishManager::GetInstance().GetActiveTimeForSpeedUp() <= 0.0f) {
			//���݂̃X�s�[�h�A�b�v�̏�Ԃ��t�ɂ���B�i���ʂ̑��x�ɂ���j
			DishManager::GetInstance().SwitchSpeedUpState();
		}
	}
}

void Game::DoWhenTimeUp()
{
	//���ʂ̕\��
	if (ui->GetIsTimeUp() == true && GetTimeUp() == false) {

		//���������̂Ƃ�(ResultP1 = 0,ResultP2 = 0�̂Ƃ�)�A1�������\��
		if (m_score->ResultP1 == m_score->ResultP2) {
			m_result[RESULT_DRAW] = NewGO<Result>(1, "result");
			m_result[RESULT_DRAW]->SetSprite(RESULT_DRAW);									//0 : ��������
			m_result[RESULT_DRAW]->SetSpritePos(RESULT_DRAW);								//�������炢�̈ʒu
		}
		//���s�����܂��Ă���Ƃ�(enum�̕Ԃ������l���قȂ�Ƃ�),2����\��
		else if (m_score->ResultP1 != m_score->ResultP2) {
			//�v���C���[1
			if (m_score->ResultP1 == RESULT_WIN) {
				m_result[RESULT_FOR_PLAYER_ONE] = NewGO<Result>(1, "result");
				m_result[RESULT_FOR_PLAYER_ONE]->SetSprite(RESULT_WIN);						//1 : ����
				m_result[RESULT_FOR_PLAYER_ONE]->SetSpritePos(RESULT_FOR_PLAYER_ONE);		//1 : �E��
			}
			if (m_score->ResultP1 == RESULT_LOSE) {
				m_result[RESULT_FOR_PLAYER_ONE] = NewGO<Result>(1, "result");
				m_result[RESULT_FOR_PLAYER_ONE]->SetSprite(RESULT_LOSE);					//2 : �s�k
				m_result[RESULT_FOR_PLAYER_ONE]->SetSpritePos(RESULT_FOR_PLAYER_ONE);		//1 : �E��
			}

			//�v���C���[2
			if (m_score->ResultP2 == RESULT_WIN) {
				m_result[RESULT_FOR_PLAYER_TWO] = NewGO<Result>(1, "result");
				m_result[RESULT_FOR_PLAYER_TWO]->SetSprite(RESULT_WIN);						//1 : ����
				m_result[RESULT_FOR_PLAYER_TWO]->SetSpritePos(RESULT_FOR_PLAYER_TWO);		//2 :����
			}
			if (m_score->ResultP2 == RESULT_LOSE) {
				m_result[RESULT_FOR_PLAYER_TWO] = NewGO<Result>(1, "result");
				m_result[RESULT_FOR_PLAYER_TWO]->SetSprite(RESULT_LOSE);					//2 : �s�k
				m_result[RESULT_FOR_PLAYER_TWO]->SetSpritePos(RESULT_FOR_PLAYER_TWO);		//2 :����
			}

		}
		//game���̃^�C���A�b�v�t���O�𗧂āA�Q�[���V�[�������U���g�Ɉڍs����
		SetTimeUp();

		GetGameDirector().SetGameScene(enResult);
		//�Q�[���I����ʒm
	}
}

void Game::Update()
{
	//�^�C���A�b�v���ɍs������
	DoWhenTimeUp();

	//���܂ɎM�̑��x���オ�鏈���B�����_���������������߂�Update�֐��ɏ����Ȃ��Ă͂Ȃ�Ȃ�
	DishSpeedUp();

	//���U���g���Ƀv���C���[1��A�{�^���������ƃ^�C�g���Ɉڍs
	if (GetGameDirector().GetGameScene() == enResult) {
		if (g_pad[PLAYER_ONE_CONTROLLER]->IsTrigger(enButtonA)) {
			GetGameDirector().SetGameScene(enNonScene);
			NewGO<Title>(0, "title");
			DeleteGO(this);
		}
	}

	//�ڐ��̈ʒu�̍X�V
	LightManager::GetInstance().UpdateEyePos();
}