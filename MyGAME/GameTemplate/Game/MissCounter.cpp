#include "stdafx.h"
#include "MissCounter.h"
#include "SpriteRender.h"
#include "Level2D.h"
#include "Result.h"

namespace
{
	const int PHOTO_SIZE_WIDTH = 36;
	const int PHOTO_SIZE_HEIGHT = 36;
	const int PHOTO_NAME_SIZE = 6;
	const int PHOTO_NAME_NUMBER = 6;
	const int AJUST_ARRAY_NUMBER = 1;
	const int PLAYER_1_FAR_RIGHT = 0;
	const int PLAYER_1_MIDDLE = 1;
	const int PLAYER_1_FAR_LEFT = 2;
	const int PLAYER_2_FAR_RIGHT = 3;
	const int PLAYER_2_MIDDLE = 4;
	const int PLAYER_2_FAR_LEFT = 5;
	const int PLAYER_1_MISS_ONE = 4;
	const int PLAYER_1_MISS_TWO = 5;
	const int PLAYER_1_MISS_THREE = 6;
	const int PLAYER_2_MISS_ONE = 1;
	const int PLAYER_2_MISS_TWO = 2;
	const int PLAYER_2_MISS_THREE = 3;
	const int PLAYER_BOTH_SIDE = 0;
	const int PLAYER_1_SIDE = 1;
	const int PLAYER_2_SIDE = 2;
	const int DRAW_DRAW = 0;
	const int DRAW_WIN = 1;
	const int DRAW_LOSE = 2;
	const int PLAYER_1_RESULT = 0;
	const int PLAYER_2_RESULT = 1;
	const int RESULT_DRAW = 0;
	const int AJUST_ARRAY_MISS_NUMBER = 3;
}

MissCounter::~MissCounter()
{
	//�~�X�J�E���g�摜������
	for (int i = 0; i < 6; i++) {
		DeleteGO(m_spriteRender[i]);
	}
	//���U���g�摜���o�Ă��������
	for (int i = 0; i < 2; i++) {
		if (m_result[i] != nullptr) {
			DeleteGO(m_result[i]);
		}
	}
}

bool MissCounter::Start()
{
	//���x����p�����摜�̕\��
	m_level2D.Init("Assets/level2D/level2D_add.casl", [&](Level2DObjectData& objdata) {
		//SQUARE�����Ă���摜���������ꍇ
		if (strncmp(objdata.name, "square", PHOTO_NAME_SIZE) == 0 ) {
			//���̉摜�̃i���o�����O���擾
			int num = atoi(&objdata.name[PHOTO_NAME_NUMBER]);
			//�i���o�����O���P����Ȃ̂ŁA�z��擪����i�[���邽�߂ɐ��l�𒲐�
			m_spriteRender[num - AJUST_ARRAY_NUMBER] = NewGO<SpriteRender>(0);
			//�摜�̏�����
			m_spriteRender[num - AJUST_ARRAY_NUMBER]->Init("Assets/Image/square.dds", PHOTO_SIZE_WIDTH, PHOTO_SIZE_HEIGHT);
			//���̉摜�����x���̈ʒu�̒ʂ�ɒu��
			m_spriteRender[num - AJUST_ARRAY_NUMBER]->SetPosition(objdata.position);

			return true;
		}
		else {
			return true;
		}
		});

	return true;
}

void MissCounter::TurnSquareIntoCross()
{
	//�ǂꂩ�̉摜�Ƀo�c��t��������ׂ����B
	if (m_shouldChangeFilePath) {
		//�~�X�̐��ɉ����Ăǂ��Ƀo�c��t���邩���߂�
		//�v���C���[�P�̕��̔�����s���B�~�X���Ɣz��̗v�f�ԍ������v�����邽�ߐ��l�𒲐�
		switch (m_pl1MissCount + AJUST_ARRAY_MISS_NUMBER) {
			//�~�X���P�񂵂Ă�����o�c���摜�ɕς���
		case PLAYER_1_MISS_ONE:
			m_spriteRender[PLAYER_1_FAR_RIGHT]->Init("Assets/Image/squareCross.dds", PHOTO_SIZE_WIDTH, PHOTO_SIZE_HEIGHT);
			break;
			//�~�X���Q�񂵂Ă�����o�c���摜�ɕς���
		case PLAYER_1_MISS_TWO:
			m_spriteRender[PLAYER_1_MIDDLE]->Init("Assets/Image/squareCross.dds", PHOTO_SIZE_WIDTH, PHOTO_SIZE_HEIGHT);
			break;
			//�~�X���R�񂵂Ă�����o�c���摜�ɕς���
		case PLAYER_1_MISS_THREE:
			m_spriteRender[PLAYER_1_FAR_LEFT]->Init("Assets/Image/squareCross.dds", PHOTO_SIZE_WIDTH, PHOTO_SIZE_HEIGHT);
			//�QP�����������Ƃ�m�点��
			m_pl2Win = true;
			break;
		}
		//�v���C���[�Q�̕��̔�����s��
		switch (m_pl2MissCount) {
		case PLAYER_2_MISS_ONE:
			m_spriteRender[PLAYER_2_FAR_RIGHT]->Init("Assets/Image/squareCross.dds", PHOTO_SIZE_WIDTH, PHOTO_SIZE_HEIGHT);
			break;
		case PLAYER_2_MISS_TWO:
			m_spriteRender[PLAYER_2_MIDDLE]->Init("Assets/Image/squareCross.dds", PHOTO_SIZE_WIDTH, PHOTO_SIZE_HEIGHT);
			break;
		case PLAYER_2_MISS_THREE:
			m_spriteRender[PLAYER_2_FAR_LEFT]->Init("Assets/Image/squareCross.dds", PHOTO_SIZE_WIDTH, PHOTO_SIZE_HEIGHT);
			m_pl1Win = true;
			break;
		}

		//�t���I�킽�̂�false�ɖ߂�
		m_shouldChangeFilePath = false;
	}
}

void MissCounter::PopResultSprite()
{
	//�����ɏ�����
	if (m_pl1Win == true && m_pl2Win == true) {
		m_result[RESULT_DRAW] = NewGO<Result>(0);
		m_result[RESULT_DRAW]->SetSprite(DRAW_DRAW);					//Draw�̉摜��\��
		m_result[RESULT_DRAW]->SetSpritePos(PLAYER_BOTH_SIDE);			//�����ɕ`��
		m_result[RESULT_DRAW]->Reach3Miss(true);
		m_isGameSet = true;
	}
	//1PWIN
	else if (m_pl1Win) {
		m_result[PLAYER_1_RESULT] = NewGO<Result>(0);
		m_result[PLAYER_1_RESULT]->SetSprite(DRAW_WIN);					//Win�̉摜��`��
		m_result[PLAYER_1_RESULT]->SetSpritePos(PLAYER_1_SIDE);			//�����ɕ`��
		m_result[PLAYER_1_RESULT]->Reach3Miss(true);
		m_result[PLAYER_2_RESULT] = NewGO<Result>(0);
		m_result[PLAYER_2_RESULT]->SetSprite(DRAW_LOSE);				//Lose�̉摜��`��
		m_result[PLAYER_2_RESULT]->SetSpritePos(PLAYER_2_SIDE);			//�E���ɕ`��
		m_result[PLAYER_2_RESULT]->Reach3Miss(true);

		m_isGameSet = true;
	}
	//2PWIN
	else if (m_pl2Win) {
		m_result[PLAYER_1_RESULT] = NewGO<Result>(0);
		m_result[PLAYER_1_RESULT]->SetSprite(DRAW_LOSE);				//Lose�̉摜��`��
		m_result[PLAYER_1_RESULT]->SetSpritePos(PLAYER_1_SIDE);			//�����ɕ`��
		m_result[PLAYER_1_RESULT]->Reach3Miss(true);
		m_result[PLAYER_2_RESULT] = NewGO<Result>(0);
		m_result[PLAYER_2_RESULT]->SetSprite(DRAW_WIN);					//Win�̉摜��`��
		m_result[PLAYER_2_RESULT]->SetSpritePos(PLAYER_2_SIDE);			//�E���ɕ`��
		m_result[PLAYER_2_RESULT]->Reach3Miss(true);
		m_isGameSet = true;
	}
}

void MissCounter::Update()
{
	//�Q�[�����I����Ă�����
	if (m_isGameSet == true) {
		return;
	}
	
	//�l�p�摜���o�c�ɕς���ׂ����ǂ������肷��
	TurnSquareIntoCross();

	//���ʉ摜���o�������邩�ǂ����̔�����s���B
	PopResultSprite();
}