#include "stdafx.h"
#include "CLevel2D.h"
#include "SpriteRender.h"
#include "MenuTimer.h"
#include "MissCounter.h"
#include "Counter.h"
#include "SoundSource.h"

//objdata.ddsFilePath�ɂ��łɗp�ӂ���Ă������ߕs�v

//�����ɂ�objdata.name
//�������@char��wchar_t�@�ɂ���B
//const char* CLevel2D::MakePathFromName(const char* name) 
//{
//	
//	
//	size_t iReturnValue;
//	size_t MAX = 20;
//	wchar_t result[20];
//	wchar_t filepath[256];
//
//	//wcstombs_s( size_t�ϊ����ꂽ�������Awchar_t*�ϊ����ʁAconst size_t�ϊ����ʂ̃T�C�Y�Aconst char*�ϊ����镶���A�Ȃ��B
//	errno_t ret = mbstowcs_s(&iReturnValue, result, MAX, name, _TRUNCATE);
//
//	//�^��wchar_t�ɒ�����objdata.name��p����dds�̃p�X�����B
//	swprintf_s(filepath, L"Assets/Image/%s.dds", result);
//
//	//������p�X��wchar_t�Ȃ̂ŁAchar�^�ɒ����B
//	size_t origsize = wcslen(filepath) + 1;
//	//�ϊ�����������
//	size_t convertedChars = 0;
//	//�}���`�o�C�g�i�[�p
//	char strCon[] = "";
//	//�T�C�Y
//	size_t strConSize = (strlen(strCon) + 1) * 2;
//	//�ϊ���̃T�C�Y�B
//	const size_t newsize = origsize * 2;
//	//�A����̃T�C�Y
//	char* nstring = new char[newsize + strConSize];
//	//�}���`�o�C�g�ɕϊ�����B���肫��Ȃ����̂͐؂肷��
//	wcstombs_s(&convertedChars, nstring, newsize, filepath, _TRUNCATE);
//	//������̘A��
//	_mbscat_s((unsigned char*)nstring, newsize + strConSize, (unsigned char*)strCon);
//
//	//�߂�l��const char* �����Ă���B
//	return nstring;
//}

bool CLevel2D::Start()
{
	m_counter01 = FindGO<Counter>("counter01");
	m_counter02 = FindGO<Counter>("counter02");
	//���x����ǂݍ��ށB
	//��ԍ����z���3�Ԗڂ̗v�f�A�E��1�Ԗڂ̗v�f
	
	m_level2D.Init("Assets/level2D/level2D_add.casl", [&](Level2DObjectData& objdata) { 
		if (objdata.EqualObjectName("burger_cheese")) {
			//SpriteInitData data;
			////DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
			//data.m_ddsFilePath[0] = objdata.ddsFilePath;
			////Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
			//data.m_fxFilePath = "Assets/shader/sprite.fx";
			////�X�v���C�g�̕��ƍ������擾����B
			//data.m_width = objdata.width;
			//data.m_height = objdata.height;
			////Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			//m_sprite.Init(data);
			////���W���擾����B
			//m_position = objdata.position;
			////�傫����ݒ肷��B
			//m_scale = objdata.scale;

			/*sprite[0] = NewGO<SpriteRender>(2);
			sprite[0]->Init(objdata.ddsFilePath, objdata.width /2 , objdata.height /2);
			sprite[0]->SetScale(objdata.scale);*/
			//sprite[0]->SetPosition(objdata.position);
			m_spritePositions[0] = objdata.position;
			m_slidePos[0] = m_spritePositions[0];
			m_level2DObjectDatas[enCheeseBurger] = objdata;
			return true;
		}
		if (objdata.EqualObjectName("burger_tomato")) {
			//���Ԃɏo��

			/*sprite[1] = NewGO<SpriteRender>(2);
			sprite[1]->Init(objdata.ddsFilePath, objdata.width / 2, objdata.height / 2);
			sprite[1]->SetScale(objdata.scale);*/
			//sprite[1]->SetPosition(objdata.position);
			m_spritePositions[1] = objdata.position;
			m_slidePos[1] = m_spritePositions[1];
			m_level2DObjectDatas[enTomatoBurger] = objdata;

			return true;
		}
		if (objdata.EqualObjectName("burger_egg")) {
			//�����ɏo��o1p�j

			/*sprite[2] = NewGO<SpriteRender>(2);
			sprite[2]->Init(objdata.ddsFilePath, objdata.width / 2, objdata.height / 2);
			sprite[2]->SetScale(objdata.scale);*/
			//sprite[2]->SetPosition(objdata.position);
			m_spritePositions[2] = objdata.position;
			m_slidePos[2] = m_spritePositions[2];
			m_level2DObjectDatas[enEggBurger] = objdata;

			return true;
		}
		if (objdata.EqualObjectName("burger_basic")) {
			/*sprite[2] = NewGO<SpriteRender>(2);
			sprite[2]->Init(objdata.ddsFilePath, objdata.width / 2, objdata.height / 2);
			sprite[2]->SetScale(objdata.scale);*/
			//sprite[2]->SetPosition(objdata.position);
			//m_spritePositions[2] = objdata.position;
			m_level2DObjectDatas[enBasicBurger] = objdata;

			return true;
		}
		if (objdata.EqualObjectName("burger_double")) {
			/*sprite[2] = NewGO<SpriteRender>(2);
			sprite[2]->Init(objdata.ddsFilePath, objdata.width / 2, objdata.height / 2);
			sprite[2]->SetScale(objdata.scale);*/
			//sprite[2]->SetPosition(objdata.position);
			//m_spritePositions[2] = objdata.position;
			m_level2DObjectDatas[enDoubleBurger] = objdata;

			return true;
		}
		if (objdata.EqualObjectName("burger_vegetable")) {
			/*sprite[2] = NewGO<SpriteRender>(2);
			sprite[2]->Init(objdata.ddsFilePath, objdata.width / 2, objdata.height / 2);
			sprite[2]->SetScale(objdata.scale);*/
			//sprite[2]->SetPosition(objdata.position);
			//m_spritePositions[2] = objdata.position;
			m_level2DObjectDatas[enVegetableBurger] = objdata;

			return true;
		}
		if (objdata.EqualObjectName("burger_bacon")) {
			/*sprite[2] = NewGO<SpriteRender>(2);
			sprite[2]->Init(objdata.ddsFilePath, objdata.width / 2, objdata.height / 2);
			sprite[2]->SetScale(objdata.scale);*/
			//sprite[2]->SetPosition(objdata.position);
			//m_spritePositions[2] = objdata.position;
			m_level2DObjectDatas[enBaconBurger] = objdata;

			return true;
		}
		if (objdata.EqualObjectName("burger_blt")) {
			/*sprite[2] = NewGO<SpriteRender>(2);
			sprite[2]->Init(objdata.ddsFilePath, objdata.width / 2, objdata.height / 2);
			sprite[2]->SetScale(objdata.scale);*/
			//sprite[2]->SetPosition(objdata.position);
			//m_spritePositions[2] = objdata.position;
			m_level2DObjectDatas[enBLTBurger] = objdata;

			return true;
		}
		if (objdata.EqualObjectName("burger_onion")) {
			/*sprite[2] = NewGO<SpriteRender>(2);
			sprite[2]->Init(objdata.ddsFilePath, objdata.width / 2, objdata.height / 2);
			sprite[2]->SetScale(objdata.scale);*/
			//sprite[2]->SetPosition(objdata.position);
			//m_spritePositions[2] = objdata.position;
			m_level2DObjectDatas[enOnionBurger] = objdata;

			return true;
		}
		if (objdata.EqualObjectName("burger_high_cal")) {
			/*sprite[2] = NewGO<SpriteRender>(2);
			sprite[2]->Init(objdata.ddsFilePath, objdata.width / 2, objdata.height / 2);
			sprite[2]->SetScale(objdata.scale);*/
			//sprite[2]->SetPosition(objdata.position);
			//m_spritePositions[2] = objdata.position;
			m_level2DObjectDatas[enHighcalBurger] = objdata;

			return true;
		}
		if (objdata.EqualObjectName("burger_on_onion")) {
			/*sprite[2] = NewGO<SpriteRender>(2);
			sprite[2]->Init(objdata.ddsFilePath, objdata.width / 2, objdata.height / 2);
			sprite[2]->SetScale(objdata.scale);*/
			//sprite[2]->SetPosition(objdata.position);
			//m_spritePositions[2] = objdata.position;
			m_level2DObjectDatas[enOnOnionBurger] = objdata;

			return true;
		}
		else{
			//return false�ɂ���ƁA
			//Level2D�N���X��Sprite�ŉ摜���ǂݍ��܂�܂��B
			return true;
		}
	});

	sprite[0] = nullptr;
	sprite[1] = nullptr;
	sprite[2] = nullptr;
	sprite[3] = nullptr;
	sprite[4] = nullptr;
	sprite[5] = nullptr;
	sprite[6] = nullptr;
	sprite[7] = nullptr;
	sprite[8] = nullptr;
	sprite[9] = nullptr;
	sprite[10] = nullptr;

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

	ShowHamBurger(0, m_showHamBurgers[0]);
	ShowHamBurger(1, m_showHamBurgers[1]);
	ShowHamBurger(2, m_showHamBurgers[2]);

	//�����Q�[�W
	m_menuTimer[0] = NewGO<MenuTimer>(0);
	Quaternion rot = Quaternion::Identity;
	rot.SetRotationDegY(180.0f);
	m_menuTimer[0]->SetRotation(rot);
	m_menuTimer[0]->SetPosition({ 480.0f,5.0f,770.0f });
	
	//�E���Q�[�W
	m_menuTimer[1] = NewGO<MenuTimer>(0);
	m_menuTimer[1]->SetPosition({ -480.0f,5.0f,750.0f });


	m_missCounter = NewGO<MissCounter>(0);

	return true;
}

void CLevel2D::Update()
{
	//m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//���x��2D�N���X��Sprite�̍X�V�����B

	for (int i = 0; i < SHOW_HAMBURGER_NUMBER; i++) {
		SpriteSet(i);
	}
	//�v���C���[1�̎��Ԑ؂�
	
	if (m_menuTimer[0]->GetTimeUpState()) {
		//���Ԑ؂ꒆ�̃t���O�������Ă��Ȃ��Ƃ��c
		if (m_TimeUpSet[0] == false) {
			//���̃��j���[�̍Ē��I
			Roulette(2);
			//1P�̃~�X����1����
			m_missCounter->AddPl1MissCount();
			//�o�c��̉摜���o��
			m_missCounter->ChangeMarkState(true);
			//���Ԑ؂�̃t���O�𗧂Ă�
			m_TimeUpSet[0] = true;
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/blip01.wav", false);
			se->SetVolume(2.0f);
			se->Play(false);
		}
		
	}

	//�v���C���[2�̎��Ԑ؂�
	
	if (m_menuTimer[1]->GetTimeUpState()) {
		if (m_TimeUpSet[1] == false) {
			Roulette(0);
			m_missCounter->AddPl2MissCount();
			m_missCounter->ChangeMarkState(true);
			
			m_TimeUpSet[1] = true;
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/blip01.wav", false);
			se->SetVolume(2.0f);
			se->Play(false);
		}
	}
	
	
	m_level2D.Update();
}

void CLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//���x��2D�N���X��Sprite�̕`�揈���B
	m_level2D.Draw(rc);
}

bool CLevel2D::GetIsMatchHamBurger(int* numbers, int size, int counterNo)
{
	if (counterNo == 1) {
		//���j���[�̍��ƒ�����Ώۂɔ�r�J�n
		for (int i = 2; i >= counterNo; i--)
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
				//���ɕ\������n���o�[�K�[���߂邨�I
				Roulette(i);
				//m_menuTimer[counterNo - 1]->ResetTimerParam();
				return true;
			}
			
		}
	}

	if (counterNo == 2) {
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
				//���ɕ\������n���o�[�K�[���߂邨�I
				Roulette(i);
				//m_menuTimer[counterNo - 1]->ResetTimerParam();

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

	m_showHamBurgers[number] = EnHamBurger(rn);

	//�J�E���^�[�ɕ\�����Ă���o�[�K�[��`����B
	if (number == 2) {
		m_counter01->m_showHamBurgers[number] = EnHamBurger(rn);
	}
	else if (number == 0) {
		m_counter02->m_showHamBurgers[number] = EnHamBurger(rn);
	}
	else if (number == 1) {
		m_counter01->m_showHamBurgers[number] = EnHamBurger(rn);
		m_counter02->m_showHamBurgers[number] = EnHamBurger(rn);
	}
	m_slide[number] = 2;
	//����炷
	m_slideSe[number] = NewGO<CSoundSource>(0);
	m_slideSe[number]->Init(L"Assets/sound/machine_rotation1.wav", false);
	m_slideSe[number]->SetVolume(1.0f);
	m_slideSe[number]->Play(true);
	//ShowHamBurger(number, m_showHamBurgers[number]);
}

void CLevel2D::SpriteSet(int number)
{
	//�ړ��t���O�ɂ���ď����𕪂���B
	switch (m_slide[number])
	{
	case 0: {	//0�Ȃ瓮���Ȃ��B
		sprite[number]->SetPosition(m_spritePositions[number]);
	}break;
	case 1: {	//1�Ȃ��ɃX���C�h
		m_slidePos[number].y += 10.0f;
		m_slideAmount[number] += 10.0f;
		sprite[number]->SetPosition(m_slidePos[number]);

		//�摜�̈ʒu�����̈ʒu�ɖ߂�����c
		if (m_slidePos[number].y == m_spritePositions[number].y) {
			//2P���̃��j���[
			if (number == 0) {
				//���j���[�^�C�}�[�����ɖ߂�
				m_menuTimer[1]->ResetTimerParam();
				m_menuTimer[1]->SetTimeUpState(false);
				//���Ԑ؂�t���O�����ɖ߂��B
				m_TimeUpSet[1] = false;
			}
			//1P���̃��j���[
			else if (number == 2) {
				m_menuTimer[0]->ResetTimerParam();
				//�o�c��t�����̂�FALSE�ɂ��ǂ��Ă��
				m_menuTimer[0]->SetTimeUpState(false);
				m_TimeUpSet[0] = false;
			}
			//�X���C�h�t���O0�ɕύX�B
			m_slide[number] = 0;
			DeleteGO(m_slideSe[number]);
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/button03b.wav", false);
			se->SetVolume(2.0f);
			se->Play(false);
		}
	}break;
	case 2: {	//2�Ȃ牺�ɃX���C�h�B
		m_slidePos[number].y -= 10.0f;
		m_slideAmount[number] -= 10.0f;
		sprite[number]->SetPosition(m_slidePos[number]);
		//�摜�̈ʒu�����܂ŉ���������B
		if (m_slidePos[number].y < m_spritePositions[number].y - 350.0f) {
			//�X���C�h�t���O��1�ɕύX�B
			m_slide[number] = 1;
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
	sprite[number]->SetScale({ 0.5f,0.5f,0.5f }/*objData.scale*/);
	//sprite[number]->SetScale(objData.scale);
	//�n���o�[�K�[�̉摜��\�����܁[���B
	
	sprite[number]->SetPosition(/*m_spritePositions[number]*/m_slidePos[number]);
}