#include "stdafx.h"
#include "CLevel2D.h"
#include "SpriteRender.h"
#include "MenuTimer.h"
#include "MissCounter.h"
#include "Counter.h"
#include "SoundSource.h"

namespace
{
	const Vector3 MENU_TIMER_LEFT_POS = { 480.0f,5.0f,750.0f };
	const Vector3 MENU_TIMER_RIGHT_POS = { -480.0f,5.0f,750.0f };
	const Vector3 MENU_SCALE = { 0.5f,0.5f,0.5f };

	const int SHOW_BURGER_RIGHT = 0;
	const int SHOW_BURGER_MIDDLE = 1;
	const int SHOW_BURGER_LEFT = 2;
	const int MENU_TIMER_LEFT = 0;
	const int MENU_TIMER_RIGHT = 1;
	const int MENU_TIMEOVER_LEFT = 0;
	const int MENU_TIMEOVER_RIGHT = 1;
	const int MENU_TIMER_NUM = 2;
	const int MENU_TIMEUP_LEFT = 0;
	const int MENU_TIMEUP_RIGHT = 1;
	const int COUNTER_NUMBER_ONE = 1;
	const int COUNTER_NUMBER_TWO = 2;
	const int SLIDE_RATE = 10.0f;

	const float SE_VOLUME = 2.0f;
	const float MAKE_MENU_BOTTOM = 350.0f;
}

CLevel2D::~CLevel2D()
{
	DeleteGO(m_missCounter);
	for (int i = 0; i < MENU_TIMER_NUM; i++) {
		DeleteGO(m_menuTimer[i]);
	}
	for (int i = 0; i < SHOW_HAMBURGER_NUMBER; i++) {
		DeleteGO(sprite[i]);
	}
}

bool CLevel2D::Start()
{
	m_counter00 = FindGO<Counter>("counter00");
	m_counter01 = FindGO<Counter>("counter01");
	//���x����ǂݍ��ށB
	//��ԍ����z���3�Ԗڂ̗v�f�A�E��1�Ԗڂ̗v�f
	
	m_level2D.Init("Assets/level2D/level2D_add.casl", [&](Level2DObjectData& objdata) { 
		if (objdata.EqualObjectName("burger_cheese")) {
			//�E���ɏo��i2P�j
			m_spritePositions[SHOW_BURGER_RIGHT] = objdata.position;
			m_slidePos[SHOW_BURGER_RIGHT] = m_spritePositions[SHOW_BURGER_RIGHT];
			m_level2DObjectDatas[enCheeseBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_tomato")) {
			//���Ԃɏo��
			m_spritePositions[SHOW_BURGER_MIDDLE] = objdata.position;
			m_slidePos[SHOW_BURGER_MIDDLE] = m_spritePositions[SHOW_BURGER_MIDDLE];
			m_level2DObjectDatas[enTomatoBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_egg")) {
			//�����ɏo��i1p�j
			m_spritePositions[SHOW_BURGER_LEFT] = objdata.position;
			m_slidePos[SHOW_BURGER_LEFT] = m_spritePositions[SHOW_BURGER_LEFT];
			m_level2DObjectDatas[enEggBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_basic")) {
			m_level2DObjectDatas[enBasicBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_double")) {
			m_level2DObjectDatas[enDoubleBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_vegetable")) {
			m_level2DObjectDatas[enVegetableBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_bacon")) {
			m_level2DObjectDatas[enBaconBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_blt")) {
			m_level2DObjectDatas[enBLTBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_onion")) {
			m_level2DObjectDatas[enOnionBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_high_cal")) {
			m_level2DObjectDatas[enHighcalBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_on_onion")) {
			m_level2DObjectDatas[enOnOnionBurger] = objdata;
			return true;
		}
		else{
			return true;
		}
	});

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

	ShowHamBurger(enCheeseBurger, m_showHamBurgers[SHOW_BURGER_RIGHT]);
	ShowHamBurger(enTomatoBurger, m_showHamBurgers[SHOW_BURGER_MIDDLE]);
	ShowHamBurger(enEggBurger, m_showHamBurgers[SHOW_BURGER_LEFT]);

	m_randNum[SHOW_BURGER_RIGHT] = enCheeseBurger;
	m_randNum[SHOW_BURGER_MIDDLE] = enTomatoBurger;
	m_randNum[SHOW_BURGER_LEFT] = enEggBurger;

	//�����Q�[�W
	m_menuTimer[MENU_TIMER_LEFT] = NewGO<MenuTimer>(0);
	Quaternion rot = Quaternion::Identity;
	//���E���]
	rot.SetRotationDegZ(180.0f);
	m_menuTimer[MENU_TIMER_LEFT]->SetRotation(rot);
	m_menuTimer[MENU_TIMER_LEFT]->SetPosition(MENU_TIMER_LEFT_POS);
	m_menuTimer[MENU_TIMER_LEFT]->SetNumber(MENU_TIMER_LEFT);
	//�E���Q�[�W
	m_menuTimer[MENU_TIMER_RIGHT] = NewGO<MenuTimer>(0);
	m_menuTimer[MENU_TIMER_RIGHT]->SetPosition(MENU_TIMER_RIGHT_POS);
	m_menuTimer[MENU_TIMER_RIGHT]->SetNumber(MENU_TIMER_RIGHT);


	m_missCounter = NewGO<MissCounter>(0);

	return true;
}

void CLevel2D::Update()
{
	//���x��2D�N���X��Sprite�̍X�V�����B

	for (int i = 0; i < SHOW_HAMBURGER_NUMBER; i++) {
		SpriteSet(i);
	}

	//�v���C���[1���̃��j���[�̎��Ԑ؂�
	if (m_slide[SHOW_BURGER_LEFT] == enStop) {
		if (m_menuTimer[0]->GetTimeUpState()) {
			//���Ԑ؂ꒆ�̃t���O�������Ă��Ȃ��Ƃ��c
			if (m_TimeUpSet[MENU_TIMEOVER_LEFT] == false) {
				//���̃��j���[�̍Ē��I
				Roulette(SHOW_BURGER_LEFT);
				//1P�̃~�X����1����
				m_missCounter->AddPl1MissCount();
				//�o�c��̉摜���o��
				m_missCounter->ChangeMarkState(true);
				//���Ԑ؂�̃t���O�𗧂Ă�
				m_TimeUpSet[MENU_TIMEUP_LEFT] = true;
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/blip01.wav", false);
				se->SetVolume(SE_VOLUME);
				se->Play(false);
			}

		}
	}
	//�v���C���[2�̎��Ԑ؂�
	if (m_slide[SHOW_BURGER_RIGHT] == enStop) {
		if (m_menuTimer[MENU_TIMEOVER_RIGHT]->GetTimeUpState()) {
			if (m_TimeUpSet[MENU_TIMEOVER_RIGHT] == false) {
				Roulette(SHOW_BURGER_RIGHT);
				m_missCounter->AddPl2MissCount();
				m_missCounter->ChangeMarkState(true);

				m_TimeUpSet[MENU_TIMEUP_RIGHT] = true;
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/blip01.wav", false);
				se->SetVolume(SE_VOLUME);
				se->Play(false);
			}
		}
	}
	
	m_level2D.Update();
}

void CLevel2D::Render(RenderContext& rc)
{
	if (GameObjectManager::GetInstance()->GetRenderTypes() == 0)
	{
		m_level2D.Draw(rc);
	}
}

//�����̃J�E���^�[�i���o�[�͂Por�Q�ł����B�����̎��_�Ńi���o�[�ɃC���N�������g����B
bool CLevel2D::GetIsMatchHamBurger(int* numbers, int size, int counterNo)
{
	if (counterNo == COUNTER_NUMBER_ONE) {
		//���j���[�̍��ƒ�����Ώۂɔ�r�J�n
		for (int i = SHOW_BURGER_LEFT; i >= counterNo; i--)
		{
			//�n���o�[�K�[�̃f�[�^�����Ă��邨�B
			HamBurger hamBurger = GetHamBurgerFactory().GetHamBurger(m_showHamBurgers[i]);
			//�����������B
			if (size != hamBurger.size()) 
				//�ȉ��̏������ȁ[���B
			continue;
			
			//���������B
			bool isSame = true;
			for (int j = 0; j < hamBurger.size(); j++)
			{
				int num = numbers[j];
				//��ނ�����Ă���B
				if (num != hamBurger[j])
				{
					//�Ⴄ���B
					isSame = false;
					break;
				}
			}
			//�������������B
			if (isSame == true)
			{
				//�����̃��j���[���o������c
				if (i == SHOW_BURGER_MIDDLE) {
					//�{�[�i�X�|�C���g�̃t���O�𗧂Ă�G
					m_counter00->SetBonusPoint(true);
				}
				//���ɕ\������n���o�[�K�[���߂邨�I
				Roulette(i);
				return true;
			}
			
		}
	}

	if (counterNo == COUNTER_NUMBER_TWO) {
		//���j���[�̉E�ƒ�����Ώۂɔ�r�J�n
		for (int i = 0; i < counterNo; i++)
		{
			//�n���o�[�K�[�̃f�[�^�����Ă��邨�B
			HamBurger hamBurger = GetHamBurgerFactory().GetHamBurger(m_showHamBurgers[i]);
			//�����������B
			if (size != hamBurger.size())
				//�ȉ��̏������ȁ[���B
				continue;

			//���������B
			bool isSame = true;
			for (int j = 0; j < hamBurger.size(); j++)
			{
				int num = numbers[j];
				//��ނ�����Ă���B
				if (num != hamBurger[j])
				{
					//�Ⴄ���B
					isSame = false;
					break;
				}
			}
			//�������������B
			if (isSame == true)
			{
				if (i == SHOW_BURGER_MIDDLE) {
					m_counter01->SetBonusPoint(true);
				}
				//���ɕ\������n���o�[�K�[���߂邨�I
				Roulette(i);

				return true;
			}
		}
	}
	//��������Ȃ�������Afalse�ȊO���肦�Ȃ��B
	return false;
}

void CLevel2D::Roulette(int number)
{
	//TODO �����̗����v�C���H
	int rn = rand() % enHamBurgerNum;
	
	//�����̃��j���[�Ɣ��Ȃ��悤�Ƀ��j���[�����߂�
	if(number == SHOW_BURGER_MIDDLE){
		while (rn == m_randNum[SHOW_BURGER_RIGHT] || rn == m_randNum[SHOW_BURGER_LEFT])
		{
			rn = rand() % enHamBurgerNum;
		}
	}
	else {
		while (rn == m_randNum[SHOW_BURGER_MIDDLE])
		{
			rn = rand() % enHamBurgerNum;
		}
	}
	m_showHamBurgers[number] = EnHamBurger(rn);

	//�J�E���^�[�ɕ\�����Ă���o�[�K�[��`����B
	m_randNum[number] = rn;
	
	//�摜�𓮂���
	m_slide[number] = enSlideDown;
	
	//����炷
	m_slideSe[number] = NewGO<CSoundSource>(0);
	m_slideSe[number]->Init(L"Assets/sound/machine_rotation1.wav", false);
	m_slideSe[number]->SetVolume(SE_VOLUME);
	m_slideSe[number]->Play(true);
}

void CLevel2D::SpriteSet(int number)
{
	//�ړ��t���O�ɂ���ď����𕪂���B
	switch (m_slide[number])
	{
	case enStop: {	//0�Ȃ瓮���Ȃ��B
		sprite[number]->SetPosition(m_spritePositions[number]);
		//Roulette(number);
	}break;
	case enSlideUp: {	//1�Ȃ��ɃX���C�h
		m_slidePos[number].y += SLIDE_RATE;
		m_slideAmount[number] += SLIDE_RATE;
		sprite[number]->SetPosition(m_slidePos[number]);

		//�摜�̈ʒu�����̈ʒu�ɖ߂�����c
		if (m_slidePos[number].y == m_spritePositions[number].y) {
			//2P���̃��j���[
			if (number == enStop) {
				//���j���[�^�C�}�[�����ɖ߂�
				m_menuTimer[MENU_TIMER_RIGHT]->ResetTimerParam(MENU_TIMER_RIGHT);
				m_menuTimer[MENU_TIMER_RIGHT]->SetTimeUpState(false);
				//���Ԑ؂�t���O�����ɖ߂��B
				m_TimeUpSet[MENU_TIMEUP_RIGHT] = false;
			}
			//1P���̃��j���[
			else if (number == enSlideDown) {
				m_menuTimer[MENU_TIMER_LEFT]->ResetTimerParam(MENU_TIMER_LEFT);
				//�o�c��t�����̂�FALSE�ɂ��ǂ��Ă��
				m_menuTimer[MENU_TIMER_LEFT]->SetTimeUpState(false);
				m_TimeUpSet[MENU_TIMEUP_LEFT] = false;
			}
			//�X���C�h�t���O0�ɕύX�B
			m_slide[number] = enStop;
			DeleteGO(m_slideSe[number]);
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/button03b.wav", false);
			se->SetVolume(SE_VOLUME);
			se->Play(false);
		}
	}break;
	case enSlideDown: {	//2�Ȃ牺�ɃX���C�h�B
		m_slidePos[number].y -= SLIDE_RATE;
		m_slideAmount[number] -= SLIDE_RATE;
		sprite[number]->SetPosition(m_slidePos[number]);
		//��o�ƃ^�C���A�b�v���d�Ȃ�Ȃ��悤�ɂ���B
		if (number == enSlideDown) {
			m_menuTimer[MENU_TIMER_LEFT]->SetTimeUpState(false);
		}
		if (number == enStop) {
			m_menuTimer[MENU_TIMER_RIGHT]->SetTimeUpState(false);
		}
		//�摜�̈ʒu�����܂ŉ���������B
		if (m_slidePos[number].y < m_spritePositions[number].y - MAKE_MENU_BOTTOM) {
			//�J�E���^�[�ɕ\�����Ă���o�[�K�[��`����B
			if (number == enSlideDown) {
				m_counter00->m_showHamBurgers[number] = EnHamBurger(m_randNum[number]);
			}
			else if (number == enStop) {
				m_counter01->m_showHamBurgers[number] = EnHamBurger(m_randNum[number]);
			}
			else if (number == enSlideUp) {
				m_counter00->m_showHamBurgers[number] = EnHamBurger(m_randNum[number]);
				m_counter01->m_showHamBurgers[number] = EnHamBurger(m_randNum[number]);
			}
			//�X���C�h�t���O��1�ɕύX�B
			m_slide[number] = enSlideUp;
			//���j���[�摜���X�V�B
			ShowHamBurger(number, m_showHamBurgers[number]);
		}
	}break;
	default:
		break;
	}
}

void CLevel2D::ShowHamBurger(int number, EnHamBurger enHamBurger)
{
	if (sprite[number] != nullptr)
	{
		DeleteGO(sprite[number]);
	}

	Level2DObjectData& objData = m_level2DObjectDatas[enHamBurger];
	sprite[number] = NewGO<SpriteRender>(2);
	sprite[number]->Init(objData.ddsFilePath, objData.width, objData.height);
	sprite[number]->SetScale(MENU_SCALE);
	//�n���o�[�K�[�̉摜��\�����܁[���B
	
	sprite[number]->SetPosition(m_slidePos[number]);
}