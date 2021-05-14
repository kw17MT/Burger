#include "stdafx.h"
#include "CLevel2D.h"
#include "SpriteRender.h"
#include "MenuTimer.h"
#include "MissCounter.h"

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
			return false;
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

	//�v���C���[1�̎��Ԑ؂�
	if (m_menuTimer[0]->GetTimeUpState()) {
		//���̃��j���[�̍Ē��I
		Roulette(2);
		//1P�̃~�X����1����
		m_missCounter->AddPl1MissCount();
		//�o�c��̉摜���o��
		m_missCounter->ChangeMarkState(true);
		//�o�c��t�����̂�FALSE�ɂ��ǂ��Ă��
		m_menuTimer[0]->SetTimeUpState(false);
	}
	//�v���C���[2�̎��Ԑ؂�
	if (m_menuTimer[1]->GetTimeUpState()) {
		Roulette(0);
		m_missCounter->AddPl2MissCount();
		m_missCounter->ChangeMarkState(true);
		m_menuTimer[1]->SetTimeUpState(false);
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
				m_menuTimer[counterNo - 1]->ResetTimerParam();
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
				m_menuTimer[counterNo - 1]->ResetTimerParam();

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
	//�n���o�[�K�[�̉摜��\�����܁[���B
	ShowHamBurger(number, m_showHamBurgers[number]);
}

void CLevel2D::ShowHamBurger(int number, EnHamBurger enHamBurger)
{
	if (sprite[number] != nullptr)
	{
		DeleteGO(sprite[number]);
	}

	Level2DObjectData& objData = m_level2DObjectDatas[enHamBurger];
	sprite[number] = NewGO<SpriteRender>(2);
	sprite[number]->Init(objData.ddsFilePath, objData.width / 2, objData.height / 2);
	sprite[number]->SetScale(objData.scale);

	sprite[number]->SetPosition(m_spritePositions[number]);

}