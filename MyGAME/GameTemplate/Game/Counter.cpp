#include "stdafx.h"
#include "Counter.h"
#include "Burger.h"
#include "Kitchen.h"
#include "Score.h"
#include "CLevel2D.h";
#include "PlayerGene.h"
#include "Player.h"
#include "SkinModelRender.h"
#include "SpriteRender.h"
#include "SoundSource.h"
#include "GameDirector.h"
#include "effect/Effect.h"
#include "DishManager.h"

namespace
{
	const Vector3 JUDGEMARK_LEFT_POS = { -95.0f,-255.0f,0.0f };
	const Vector3 JUDGEMARK_RIGHT_POS = { -155.0f,-255.0f,0.0f };

	const int ROWS_NUM = 4;						//�s
	const int COLUMNS_NUM = 5;					//��
	const int GUZAI_TYPE_NONE = 2;
	const int KITCHEN_NAME_SIZE = 10;
	const int PLAYER_NAME_SIZE = 9;
	const int TRASHCAN_NAME_SIZE = 11;
	const int BURGER_NAME_SIZE = 9;
	const int SPRITE_HEIGHT = 100;
	const int SPRITE_WIDTH = 100;
	const int SPRITE_CHECK_SCALE = 30;
	const int SPRIRE_BATSU_SCALE = 40;
	const int COUNTER_NUMBER_ZERO = 0;
	const int COUNTER_NUMBER_ONE = 1;
	const int STACK_NONE = 9;
	const int MAX_DELAY_NUM = 60;
	const int MAX_STACK_NUM = 5;
	const int CORRECT = 1;
	const int FAULT = 0;
	const int NOTHING = 2;
	const int SPRITE_MAX_TIMER = 60;
	const int GUZAI_CORRECT = 1;
	const int GUZAI_FAILE = 0;

	const float DISTANCE_TO_FIND_COUNTER = 100.0f;
	const float SE_VOLUME = 0.7f;
	const float MOVE_AMOUNT_LITTLE = 10.0f;
	const float AJUST_HEIGHT_FOR_JUDGEMARK = 30.0f;
	const float AJUST_POSITION_X_FOR_JUDGEMARK = 120.0f;
	const float BONUS_RATIO = 2.0f;
}


Counter::~Counter()
{
	DeleteGO(m_skinModelRender);
	
	if (m_spriteJudge != nullptr) {
		DeleteGO(m_spriteJudge);
	}

	for (int i = 0; i < ROWS_NUM; i++) {
		for (int j = 0; j < COLUMNS_NUM; j++) {
			if (m_spriteCompareFlagFalse[i][j] || m_spriteCompareFlagTrue[i][j]) {
				DeleteGO(m_spriteCompare[i][j]);
			}
		}
	}
}

bool Counter::Start()
{
	//�J�E���^�[�̃��f�������������āA���肷��n���o�[�K�[�̎�ނ��i�[���Ă���
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/counter/counter.tkm", nullptr, enModelUpAxisZ, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_showHamBurgers[0] = enCheeseBurger;
	m_showHamBurgers[1] = enTomatoBurger;
	m_showHamBurgers[2] = enEggBurger;
	m_showHamBurgers[3] = enBasicBurger;
	m_showHamBurgers[4] = enDoubleBurger;
	m_showHamBurgers[5] = enVegetableBurger;
	m_showHamBurgers[6] = enBaconBurger;
	m_showHamBurgers[7] = enBLTBurger;
	m_showHamBurgers[8] = enOnionBurger;
	m_showHamBurgers[9] = enHighcalBurger;
	m_showHamBurgers[10] = enOnOnionBurger;

	//��ނ̐ς܂ꂽ�����ς܂�Ă��Ȃ���Ԃɂ���
	for (int i = 0; i < ROWS_NUM; i++) {
		for (int j = 0; j < COLUMNS_NUM; j++) {
			m_guzaiJudge[i][j] = GUZAI_TYPE_NONE;
		}
	}

	//string�^�ɕς���char�ɕϊ����邽�߂̏���������B
	std::string endNo_string = std::to_string(m_counterNo);
	//�s�ωӏ����`
	char kitchenName[KITCHEN_NAME_SIZE] = "kitchen0";
	char playerName[PLAYER_NAME_SIZE] = "player0";
	char trashcanName[TRASHCAN_NAME_SIZE] = "trashcan0";
	//���[�ԍ�������ǉ�����
	strcat_s(kitchenName, endNo_string.c_str());
	strcat_s(playerName, endNo_string.c_str());
	strcat_s(trashcanName, endNo_string.c_str());

	m_level2d = FindGO<CLevel2D>("clevel2d");
	m_player = FindGO<Player>(playerName);
	m_kitchen = FindGO<Kitchen>(kitchenName);
	m_playerGene = FindGO<PlayerGene>("playerGene");

	//�n���o�[�K�[�̃|�W�V�������J�E���^�[�̈ʒu�ɂ��邽�߁B
	m_burgerPos = m_position;

	return true;
}

//���ʂ���Ƃ���
bool Counter::Judge()
{
	return m_level2d->GetIsMatchHamBurger(m_player->GetPlayerStackedGuzais(), m_stackNum, m_counterNo + 1);
}

//�o�[�K�[���ŏI�I�ɏ����ăX�R�A�𔭐�������B
//�J�E���^�[�ɋ߂��Ƃ����A�{�^���������Ƃ�������ڂ��ď����B
void Counter::Delete()
{
	//�v���C���[�̏�񂪎擾�ł��Ă��Ȃ������Ƃ�
	if (m_player == nullptr) {
		//string�^�ɕς���char�ɕϊ����邽�߂̏���������B
		std::string endNo_string = std::to_string(m_counterNo);
		//�s�ωӏ����`
		char playerName[PLAYER_NAME_SIZE] = "player0";
		//���[�ԍ�������ǉ�����
		strcat_s(playerName, endNo_string.c_str());

		m_player = FindGO<Player>(playerName);
	}

	Vector3 plPos = m_player->GetPosition();

	//�J�E���^�[����v���C���[�̋���
	float pl2Counter = (plPos.x - m_position.x) * (plPos.x - m_position.x) + (plPos.y - m_position.y) * (plPos.y - m_position.y) + (plPos.z - m_position.z) * (plPos.z - m_position.z);
	pl2Counter = sqrt(pl2Counter);

	//�v���C���[���o�[�K�[�������Ă�����
	if (m_player->GetPlayerState() == enHaveBurger) {
		//string�^�ɕς���char�ɕϊ����邽�߂̏���������B
		std::string endNo_string = std::to_string(m_counterNo);
		//�s�ωӏ����`
		char burgerName[BURGER_NAME_SIZE] = "burger0";
		//���[�ԍ�������ǉ�����
		strcat_s(burgerName, endNo_string.c_str());
		//�ꏊ�ɑΉ������n���o�[�K�[��T��
		Burger* burger = FindGO<Burger>(burgerName);

		//�J�E���^�[�ɒu������
		//�ł����n���o�[�K�[�̑g����Judge�֐��Œ��ׂ�B
		if (g_pad[m_counterNo]->IsTrigger(enButtonA) && pl2Counter < DISTANCE_TO_FIND_COUNTER) {
			burger->SetPutOnCounterState(true);
			//�o�[�K�[�������Ă���ꍇ
			if (Judge() == true) {
				m_burgerCorrectFlag = true;
				//�摜���܂��o�Ă��Ȃ��Ƃ�
				if (m_spriteFlag == false) {
					m_spriteJudge = NewGO<SpriteRender>(0);
					m_spriteJudge->Init("Assets/Image/BurgerJudgeMark/Correct.dds", SPRITE_WIDTH, SPRITE_HEIGHT);
					//�|�W�V������Ή�������
					if (m_counterNo == COUNTER_NUMBER_ONE) {
						//�J�E���^�\�i���o�[��1�̎��i�E�̎��j�Ax���W�𔽓]������B
						m_spritePos.x *= -1;
					}
					m_spriteJudge->SetPosition(m_spritePos);
					m_spriteFlag = true;
					//����炷
					CSoundSource* se = NewGO<CSoundSource>(0);
					se->Init(L"Assets/sound/crrect_answer2.wav", false);
					se->SetVolume(SE_VOLUME);
					se->Play(false);
					//���̋��No.��ۑ����邽�߁A�X�ŏ������B
					m_player->SetGuzaiNo9();
				}
			}
			else {
				m_burgerMistakeFlag = true;
				if (m_spriteFlag == false) {
					m_spriteJudge = NewGO<SpriteRender>(0);
					m_spriteJudge->Init("Assets/Image/BurgerJudgeMark/Miss.dds", SPRITE_WIDTH, SPRITE_HEIGHT);
					if (m_counterNo == COUNTER_NUMBER_ONE) {
						//�J�E���^�\�i���o�[��1�̎��i�E�̎��j�Ax���W�𔽓]������B
						m_spritePos.x *= -1;
					}
					m_spriteJudge->SetPosition(m_spritePos);
					m_spriteFlag = true;

					//����炷
					CSoundSource* se = NewGO<CSoundSource>(0);
					se->Init(L"Assets/sound/blip01.wav", false);
					se->SetVolume(SE_VOLUME);
					se->Play(false);
					m_player->SetGuzaiNo9();
				}
			}
		}

		//�n���o�[�K�[�����݂��Ă���
		if (burger != nullptr) {
			//�o�[�K�[�������Ă���ꍇ
			if (m_burgerCorrectFlag == true) {
				m_delay++;
				//�o�[�K�[�𓮂����B
				m_burgerPos.z += MOVE_AMOUNT_LITTLE;
				burger->SetPosition(m_burgerPos);
				//�u��������t���[����ɏ���
				if (m_delay == MAX_DELAY_NUM) {
					//�����Őςݏグ�Ă���ނ̐���Score�ɓn���Ă�����B
					Score* sco = FindGO<Score>("score");
					if (m_counterNo == COUNTER_NUMBER_ZERO) {
						if (m_bonusPoint == true) {
							sco->SetBasePoint01(m_stackNum * BONUS_RATIO);
							m_bonusPoint = false;
						}
						else {
							sco->SetBasePoint01(m_stackNum);
						}
					}
					if (m_counterNo == COUNTER_NUMBER_ONE) {
						if (m_bonusPoint == true) {
							sco->SetBasePoint02(m_stackNum * BONUS_RATIO);
							m_bonusPoint = false;
						}
						else {
							sco->SetBasePoint02(m_stackNum);
						}
					}

					//�v���C���[�͉��������Ă��Ȃ���Ԃɂ���B
					m_player->SetPlayerState(enNothing);
					//Delay�������l�ɖ߂�
					m_delay = 0;
					//�n���o�[�K�[�̑w����0�ɂ��ǂ��B
					m_stackNum = 0;
					//�M�̓����������t�ɂ����閽�߂𔭐M����B
					DishManager::GetInstance().SetOrderChangeDirection(true);
					//���̃n���o�[�K�[�̂��߂ɁA�J�E���^�[�̍��W�ɏ���������B
					m_burgerPos = m_position;
					//�ꉞFALSE�ɂ��Ă����B
					m_burgerCorrectFlag = false;
					//�n���o�[�K�[�������B
					DeleteGO(burger);
				}
			}
			//�o�[�K�[���Ԉ���Ă���ꍇ�B
			if (m_burgerMistakeFlag == true) {
				m_delay++;
				//�o�[�K�[�𓮂����B
				if (m_counterNo == COUNTER_NUMBER_ZERO) {
					m_burgerPos.x += MOVE_AMOUNT_LITTLE;
				}
				if (m_counterNo == COUNTER_NUMBER_ONE) {
					m_burgerPos.x -= MOVE_AMOUNT_LITTLE;
				}
				burger->SetPosition(m_burgerPos);

				if (m_delay == MAX_DELAY_NUM) {
					m_player->SetPlayerState(enNothing);
					DeleteGO(burger);
					m_delay = 0;

					m_burgerMistakeFlag = false;
					m_stackNum = 0;
					m_burgerPos = m_position;
				}
			}
		}
	}
}

void Counter::HamBurgerCompare()
{
	CLevel2D* l2 = FindGO<CLevel2D>("clevel2d");
	//1P���̏���
	if (m_counterNo == COUNTER_NUMBER_ZERO) {
		for (int i = 2; i > m_counterNo; i--) {
			HamBurger hamburger = GetHamBurgerFactory().GetHamBurger(m_showHamBurgers[i]);
			//��ނ��L�b�`���ɐς�ł��Ȃ��Ƃ��c
			for (int k = 0; k < MAX_STACK_NUM; k++) {
				if (m_player->GetPlayerStackedGuzais(k) == STACK_NONE) {
					//�摜���o�Ă���Ώ���
					if (m_spriteCompareFlagTrue[i + 1][k] == true || m_spriteCompareFlagFalse[i + 1][k] == true) {
						DeleteGO(m_spriteCompare[i + 1][k]);
						m_spriteCompareFlagTrue[i + 1][k] = false;
						m_spriteCompareFlagFalse[i + 1][k] = false;
					}
				}
			}
			//���j���[�ƍ����Ă��邩���ׂ�
			for (int j = 0; j < hamburger.size(); j++) {
				//�ς�łȂ���Ή������Ȃ��B
				if (m_player->GetPlayerStackedGuzais(j) == STACK_NONE) {
					m_guzaiJudge[i + 1][j] = NOTHING;
				}
				else {
					if (m_player->GetPlayerStackedGuzais(j) == hamburger[j]) {
						//���j���[�ƈ�v
						m_guzaiJudge[i + 1][j] = CORRECT;
					}
					else {
						//���j���[�ƕs��v
						m_guzaiJudge[i + 1][j] = FAULT;
					}
				}

				Vector3 SetPos = JUDGEMARK_LEFT_POS ;
				SetPos.x += i * AJUST_POSITION_X_FOR_JUDGEMARK;
				SetPos.y += j * AJUST_HEIGHT_FOR_JUDGEMARK;
				SetPos.y += l2->GetSlideAmount(i);
				//���j���[�ƈ�v���Ă��邩�Ō��߂�B
				switch (m_guzaiJudge[i+1][j])
				{
					
				case GUZAI_FAILE: {
					//��v�̉摜���o�Ă���Ώ����B
					if (m_spriteCompareFlagTrue[i + 1][j] == true) {
						DeleteGO(m_spriteCompare[i + 1][j]);
						m_spriteCompareFlagTrue[i + 1][j] = false;
					}
					//�s��v�̉摜���o�Ă��Ȃ���Ώo���B
					if (m_spriteCompareFlagFalse[i + 1][j] == false) {
						m_spriteCompare[i + 1][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i + 1][j]->Init("Assets/Image/JudgeMark/Batsu_White_Black512.dds", SPRIRE_BATSU_SCALE, SPRIRE_BATSU_SCALE);
						m_spriteCompare[i + 1][j]->SetPosition(SetPos);
						m_spriteCompareFlagFalse[i + 1][j] = true;
					}
				}break;
				case GUZAI_CORRECT: {
					//�s��v�̉摜���o�Ă���Ώ����B
					if (m_spriteCompareFlagFalse[i + 1][j] == true) {
						DeleteGO(m_spriteCompare[i + 1][j]);
						m_spriteCompareFlagFalse[i + 1][j] = false;
					}
					//��v�̉摜���o�Ă��Ȃ���Ώo���B
					if (m_spriteCompareFlagTrue[i + 1][j] == false) {
						m_spriteCompare[i + 1][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i + 1][j]->Init("Assets/Image/JudgeMark/Check_White_Red512.dds", SPRITE_CHECK_SCALE, SPRITE_CHECK_SCALE);
						m_spriteCompare[i + 1][j]->SetPosition(SetPos);
						m_spriteCompareFlagTrue[i + 1][j] = true;
					}
				}break;
				default:
					break;
				}
				//�`�F�b�N�}�[�N�̍��W���X�V�B
				if (m_spriteCompareFlagFalse[i + 1][j] == true || m_spriteCompareFlagTrue[i + 1][j] == true) {
					m_spriteCompare[i + 1][j]->SetPosition(SetPos);
				}
				//���łɏo�����`�F�b�N�摜�́A�o�[�K�[�̒i���𒴂��ď�������B
				for (int l = hamburger.size(); l < MAX_STACK_NUM; l++) {
					Vector3 SetPos = JUDGEMARK_LEFT_POS;
					SetPos.x += i * AJUST_POSITION_X_FOR_JUDGEMARK;
					SetPos.y += l * AJUST_HEIGHT_FOR_JUDGEMARK;
					SetPos.y += l2->GetSlideAmount(i);
					if (m_player->GetPlayerStackedGuzais(l) != STACK_NONE) {
						if (m_spriteCompareFlagFalse[i + 1][l] == true || m_spriteCompareFlagTrue[i + 1][l] == true) {

							DeleteGO(m_spriteCompare[i + 1][l]);
							m_spriteCompareFlagFalse[i + 1][l] = false;
							m_spriteCompareFlagTrue[i + 1][l] = false;
						}
					}
				}
			}
		}
	}
	//2P���̏���
	if (m_counterNo == COUNTER_NUMBER_ONE) {
		for (int i = 0; i < m_counterNo + 1; i++) {
			HamBurger hamburger = GetHamBurgerFactory().GetHamBurger(m_showHamBurgers[i]);
			for (int k = 0; k < MAX_STACK_NUM; k++) {
				if (m_player->GetPlayerStackedGuzais(k) == STACK_NONE) {
					if (m_spriteCompareFlagTrue[i][k] == true || m_spriteCompareFlagFalse[i][k] == true) {
						DeleteGO(m_spriteCompare[i][k]);
						m_spriteCompareFlagTrue[i][k] = false;
						m_spriteCompareFlagFalse[i][k] = false;
					}
				}
			}
			for (int j = 0; j < hamburger.size(); j++) {
				if (m_player->GetPlayerStackedGuzais(j) == STACK_NONE) {
					m_guzaiJudge[i][j] = NOTHING;
				}
				else {
					if (m_player->GetPlayerStackedGuzais(j) == hamburger[j]) {
						m_guzaiJudge[i][j] = CORRECT;
					}
					else {
						m_guzaiJudge[i][j] = FAULT;
					}
				}
				Vector3 SetPos = JUDGEMARK_RIGHT_POS;
				SetPos.x += i * AJUST_POSITION_X_FOR_JUDGEMARK;
				SetPos.y += j * AJUST_HEIGHT_FOR_JUDGEMARK;
				SetPos.y += l2->GetSlideAmount(i);
				switch (m_guzaiJudge[i][j])
				{
				case GUZAI_FAILE: {
					if (m_spriteCompareFlagTrue[i][j] == true) {
						DeleteGO(m_spriteCompare[i][j]);
						m_spriteCompareFlagTrue[i][j] = false;
					}
					if (m_spriteCompareFlagFalse[i][j] == false) {
						m_spriteCompare[i][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i][j]->Init("Assets/Image/JudgeMark/Batsu_White_Black512.dds", SPRIRE_BATSU_SCALE, SPRIRE_BATSU_SCALE);
						m_spriteCompare[i][j]->SetPosition(SetPos);
						m_spriteCompareFlagFalse[i][j] = true;
					}
				}break;
				case GUZAI_CORRECT: {
					if (m_spriteCompareFlagFalse[i][j] == true) {
						DeleteGO(m_spriteCompare[i][j]);
						m_spriteCompareFlagFalse[i][j] = false;
					}
					if (m_spriteCompareFlagTrue[i][j] == false) {
						m_spriteCompare[i][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i][j]->Init("Assets/Image/JudgeMark/Check_White_Blue512.dds", SPRITE_CHECK_SCALE, SPRITE_CHECK_SCALE);
						m_spriteCompare[i][j]->SetPosition(SetPos);
						m_spriteCompareFlagTrue[i][j] = true;
					}
				}break;
				default:
					break;
				}
				if (m_spriteCompareFlagFalse[i][j] == true || m_spriteCompareFlagTrue[i][j] == true) {
					m_spriteCompare[i][j]->SetPosition(SetPos);
				}
				for (int l = hamburger.size(); l < MAX_STACK_NUM; l++) {
					Vector3 SetPos = JUDGEMARK_RIGHT_POS;
					SetPos.x += i * AJUST_POSITION_X_FOR_JUDGEMARK;
					SetPos.y += l * AJUST_HEIGHT_FOR_JUDGEMARK;
					SetPos.y += l2->GetSlideAmount(i);
					if (m_spriteCompareFlagFalse[i][l] == true || m_spriteCompareFlagTrue[i][l] == true) {
						if (m_player->GetPlayerStackedGuzais(l) != STACK_NONE) {
							if (m_spriteCompareFlagFalse[i][l] == true || m_spriteCompareFlagTrue[i][l] == true) {

								DeleteGO(m_spriteCompare[i][l]);
								m_spriteCompareFlagFalse[i][l] = false;
								m_spriteCompareFlagTrue[i][l] = false;
							}
						}
					}
				}
			}
		}
	}
}

void Counter::Update()
{
	Delete();
	HamBurgerCompare();
	
	if (m_spriteFlag == true) {
		m_spriteTime++;
		if (m_spriteTime > SPRITE_MAX_TIMER) {
			DeleteGO(m_spriteJudge);
			m_spriteFlag = false;
			m_spriteTime = 0;
		}
	}

	m_skinModelRender->SetPosition(m_position);
}