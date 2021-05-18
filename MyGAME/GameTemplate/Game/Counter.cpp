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

Counter::Counter()
{
	//�n���o�[�K�[�̃f�[�^�����B
	/*HamBurger cheese;
	cheese.push_back(3);
	cheese.push_back(0);
	cheese.push_back(2);
	m_hamBurgers[enCheeseBurger] = cheese;

	HamBurger tomato;
	tomato.push_back(3);
	tomato.push_back(4);
	tomato.push_back(4);
	tomato.push_back(2);
	m_hamBurgers[enTomatoBurger] = tomato;

	HamBurger egg;
	egg.push_back(2);
	egg.push_back(4);
	egg.push_back(1);
	egg.push_back(3);
	m_hamBurgers[enEggBurger] = egg;*/
}

bool Counter::Start()
{
	m_playerGene = FindGO<PlayerGene>("playerGene");

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

	return true;
}

//////////////////////���ʂ���Ƃ���////////////////////////////////////////////////////////////////////////////////
bool Counter::Judge()
{
	CLevel2D* l2 = FindGO<CLevel2D>("clevel2d");

	if (CounterNo == 1) {
		Kitchen* ki01 = FindGO<Kitchen>("kitchen01");
		Player* pl01 = FindGO<Player>("player01");

		//�ŏI���ʂ��L�^������́B
		bool correct01 = true;
		//���ʂ��Ă����ߒ��Ő�����������C���N�������g����Ă����B���𐔂݂����Ȃ��́B
		int correctCount01 = 0;
		//���_�ƂȂ鐔�Bsizeof�̒��g��ς��邱�Ƃł����Ȏ�ނ̃o�[�K�[�ɑΉ��ł���Ǝv���B���ς��Ă������B
		//int correctGuzaiNum01 = sizeof(burger01) / sizeof(int);

		return l2->GetIsMatchHamBurger(pl01->GuzaiNo, StackNum, CounterNo);
		//������o�[�K�[�̑w�ɂ���ĉ�FOR���̉񐔂��ς��B
		//StackNum�̓o�[�K�[���ł���u�Ԃɂ����瑤�ɕۑ������B�iin Kitchen.cpp)
		//���ʉߒ��ň�x�ł��ԈႦ����FALSE
		/*for (int i = 0; i < enHamBurgerNum; i++)
		{
			//�n���o�[�K�[�̃f�[�^�����Ă��邨�B
			HamBurger hamBurger = m_hamBurgers[i];
			//�����������B
			if (StackNum != hamBurger.size())
				//�ȉ��̏������ȁ[���B
				continue;
			
			//���������B
			bool isSame = true;
			for (int j = 0; j < hamBurger.size(); j++)
			{
				//��ނ�����Ă���B
				if (pl01->GuzaiNo[j] != hamBurger[j])
				{
					//�Ⴄ���B
					isSame = false;
					break;
				}
			}
			//�������������B
			if (isSame == true)
			{
				return true;
			}
		}
		//��������Ȃ�������true�ȊO���肦�Ȃ��B
		return false;
		/*for (int i = 0; i < StackNum; i++) {
			
			if (burger01[i] == pl01->GuzaiNo[i]) {
				correctCount01++;
				continue;
			}
			else{
				correct01 = false;
				break;
			}
		}
		//�����܂ł̕��ł͓r���܂Ŋ����ɂł��Ă�����TRUE�ɂȂ�B
		//�����̕��ŁA�ŏI�I�ɑw�̐�������Ă�����FALSE�ɂ���B
		if (correctCount01 != correctGuzaiNum01) {
			correct01 = false;
		}

		return correct01;
		*/
	}

	if (CounterNo == 2) {
		Kitchen* ki02 = FindGO<Kitchen>("kitchen02");
		Player* pl02 = FindGO<Player>("player02");

		bool correct02 = true;
		int correctCount02 = 0;
		//int correctGuzaiNum02 = sizeof(burger01) / sizeof(int);

		return l2->GetIsMatchHamBurger(pl02->GuzaiNo, StackNum, CounterNo);
		/*
		for (int i = 0; i < enHamBurgerNum; i++)
		{
			//�n���o�[�K�[�̃f�[�^�����Ă��邨�B
			HamBurger hamBurger = m_hamBurgers[i];
			//�����������B
			if (StackNum != hamBurger.size())
				//�ȉ��̏������ȁ[���B
				continue;

			//���������B
			bool isSame = true;
			for (int j = 0; j < hamBurger.size(); j++)
			{
				//��ނ�����Ă���B
				if (pl02->GuzaiNo[j] != hamBurger[j])
				{
					//�Ⴄ���B
					isSame = false;
					break;
				}
			}
			//�������������B
			if (isSame == true)
			{
				return true;
			}
		}
		//��������Ȃ����I
		return false;*/
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//�o�[�K�[���ŏI�I�ɏ����ăX�R�A�𔭐�������B
//�J�E���^�[�ɋ߂��Ƃ����B�{�^���������Ƃ�������ڂ��ď����B
void Counter::Delete()
{
	if (CounterNo == 1) {
		Player* pl01 = FindGO<Player>("player01");
		Vector3 plPos = pl01->GetPosition();

		Vector3 CounterPos01 = m_position;

		//�J�E���^�[����v���C���[�̋���
		float pl2Counter = (plPos.x - CounterPos01.x) * (plPos.x - CounterPos01.x) + (plPos.y - CounterPos01.y) * (plPos.y - CounterPos01.y) + (plPos.z - CounterPos01.z) * (plPos.z - CounterPos01.z);
		pl2Counter = sqrt(pl2Counter);

		//�v���C���[���o�[�K�[�������Ă�����
		if (pl01->have == 2) {
			Burger* bu01 = FindGO<Burger>("burger01");

			//�L�b�`���ɒu������
			//�ł����n���o�[�K�[�̑g����Judge�֐��Œ��ׁA�����Ă�����J�E���^�[�ɒu����B
			if (g_pad[0]->IsTrigger(enButtonA) && pl2Counter < 100.0f) {
				bu01->putOnKitchen = 1;
				//�o�[�K�[�������Ă���ꍇ
				if (Judge() == true) {
					m_burgerCorrectFlag = true;
					//bu01->putOnKitchen = 1;
					if (m_spriteFlag01 == false) {
						m_spriteJudge01 = NewGO<SpriteRender>(0);
						m_spriteJudge01->Init("Assets/Image/win.dds", 100, 100);
						m_spriteJudge01->SetPosition(m_spritePos01);
						m_spriteFlag01 = true;
						//����炷
						CSoundSource* se = NewGO<CSoundSource>(0);
						se->Init(L"Assets/sound/crrect_answer2.wav", false);
						se->SetVolume(0.7f);
						se->Play(false);
						//���̋��No.��ۑ����邽�߁A�X�ŏ������B
						pl01->SetGuzaiNo9();
					}
				}
				//�o�[�K�[���Ԉ���Ă���ꍇ�B
				else {
					m_burgerMistakeFlag = true;
					if (m_spriteFlag01 == false) {
						m_spriteJudge01 = NewGO<SpriteRender>(0);
						m_spriteJudge01->Init("Assets/Image/lose.dds", 100, 100);
						m_spriteJudge01->SetPosition(m_spritePos01);
						m_spriteFlag01 = true;
						
						//����炷
						CSoundSource* se = NewGO<CSoundSource>(0);
						se->Init(L"Assets/sound/blip01.wav",false);
						se->SetVolume(0.7f);
						se->Play(false);
						pl01->SetGuzaiNo9();
					}
				}
			}

			if (bu01 != nullptr) {
				//�o�[�K�[�������Ă���ꍇ
				if (m_burgerCorrectFlag == true) {
					Delay++;
					//�o�[�K�[�𓮂����B
					CounterPos01.y += 100.0f;
					CounterPos01.z += m_burgerPos.z;
					m_burgerPos.z += 10.0f;
					bu01->SetPosition(CounterPos01);
					//�u������30�t���[����ɏ���
					if (Delay == 60) {
						//�����Őςݏグ�Ă���ނ̐���Score�ɓn���Ă�����B
						Score* sco = FindGO<Score>("score");
						sco->SetBasePoint01(StackNum);

						
						pl01->have = 0;

						bu01->ClearModel();
						DeleteGO(bu01);
						Delay = 0;
						
						StackNum = 0;
						m_playerGene->AddSubmitBurgerNum();
						m_burgerPos.z = 0.0f;
						m_burgerCorrectFlag = false;
					}
				}
				//�o�[�K�[���Ԉ���Ă���ꍇ�B
				if (m_burgerMistakeFlag == true) {
					Delay++;
					//�o�[�K�[�𓮂����B
					CounterPos01.y += 100.0f;
					CounterPos01.x += m_burgerPos.x;
					m_burgerPos.x += 10.0f;
					bu01->SetPosition(CounterPos01);

					if (Delay == 60) {
						Burger* bur01 = FindGO<Burger>("burger01");
						
						pl01->have = 0;
						bu01->ClearModel();
						DeleteGO(bu01);
						Delay = 0;
						
						StackNum = 0;
						m_burgerPos.x = 0.0f;
						m_burgerMistakeFlag = false;
					}
				}
			}
		}
	}

	if (CounterNo == 2) {
		Player* pl02 = FindGO<Player>("player02");
		Vector3 plPos = pl02->GetPosition();

		Vector3 CounterPos02 = m_position;

		float pl2Counter = (plPos.x - CounterPos02.x) * (plPos.x - CounterPos02.x) + (plPos.y - CounterPos02.y) * (plPos.y - CounterPos02.y) + (plPos.z - CounterPos02.z) * (plPos.z - CounterPos02.z);
		pl2Counter = sqrt(pl2Counter);

		//�v���C���[���o�[�K�[�������Ă�����
		if (pl02->have == 2) {
			Burger* bu02 = FindGO<Burger>("burger02");

			//�L�b�`���ɒu������
			//�ł����n���o�[�K�[�̑g����Judge�֐��ł���ׁA�����Ă�����J�E���^�[�ɒu����B
			if (g_pad[1]->IsTrigger(enButtonA) && pl2Counter < 100.0f) {
				bu02->putOnKitchen = 1;
				//�o�[�K�[�������Ă���ꍇ
				if (Judge() == true) {
					m_burgerCorrectFlag = true;
					//bu02->putOnKitchen = 1;
					if (m_spriteFlag02 == false) {
						m_spriteJudge02 = NewGO<SpriteRender>(0);
						m_spriteJudge02->Init("Assets/Image/win.dds", 100, 100);
						m_spriteJudge02->SetPosition(m_spritePos02);
						m_spriteFlag02 = true;
						//����炷
						CSoundSource* se = NewGO<CSoundSource>(0);
						se->Init(L"Assets/sound/crrect_answer2.wav", false);
						se->SetVolume(0.7f);
						se->Play(false);
						//���̋��No.��ۑ����邽�߁A�X�ŏ������B
						pl02->SetGuzaiNo9();
						
					}
				}
				//�o�[�K�[���Ԉ���Ă���ꍇ�B
				else {
					m_burgerMistakeFlag = true;
					if (m_spriteFlag02 == false) {
						m_spriteJudge02 = NewGO<SpriteRender>(0);
						m_spriteJudge02->Init("Assets/Image/lose.dds", 100, 100);
						m_spriteJudge02->SetPosition(m_spritePos02);
						m_spriteFlag02 = true;
						//����炷
						CSoundSource* se = NewGO<CSoundSource>(0);
						se->Init(L"Assets/sound/blip01.wav", false);
						se->SetVolume(0.7f);
						se->Play(false);
						pl02->SetGuzaiNo9();
						
					}
				}
			}

			if (bu02 != nullptr) {
				//���������Ƃ��B
				if (m_burgerCorrectFlag == true) {
					Delay++;
					CounterPos02.y += 100.0f;
					CounterPos02.z += m_burgerPos.z;
					m_burgerPos.z += 10.0f;
					bu02->SetPosition(CounterPos02);
					//�u������30�t���[����ɏ���
					if (Delay == 60) {
						//�����Őςݏグ�Ă���ނ̐���Score�ɓn���Ă�����B
						Score* sco = FindGO<Score>("score");
						sco->SetBasePoint02(StackNum);

						
						
						pl02->have = 0;
						DeleteGO(bu02);
						Delay = 0;
						
						StackNum = 0;
						m_playerGene->AddSubmitBurgerNum();
						m_burgerPos.z = 0.0f;
						m_burgerCorrectFlag = false;
					}
				}
				if (m_burgerMistakeFlag == true) {
					Delay++;
					CounterPos02.y += 100.0f;
					CounterPos02.x += m_burgerPos.x;
					m_burgerPos.x -= 10.0f;
					bu02->SetPosition(CounterPos02);

					if (Delay == 60) {
						Burger* bur02 = FindGO<Burger>("burger02");
						
						pl02->have = 0;
						bu02->ClearModel();
						DeleteGO(bu02);
						Delay = 0;
						
						StackNum = 0;
						m_burgerPos.x = 0.0f;
						m_burgerMistakeFlag = false;
					}
				}
			}
		}
	}
}

void Counter::HamBurgerCompare()
{
	//1P���̏���
	if (CounterNo == 1) {
		for (int i = 2; i >= CounterNo; i--) {
			Player* pl01 = FindGO<Player>("player01");
			HamBurger hamburger = GetHamBurgerFactory().GetHamBurger(m_showHamBurgers[i]);
			//��ނ��L�b�`���ɐς�ł��Ȃ��Ƃ��c
			for (int k = 0; k < 5; k++) {
				if (pl01->GuzaiNo[k] == 9) {
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
				if (pl01->GuzaiNo[j] == 9) {
					m_guzaiJudge[i + 1][j] = 2;
				}
				else {
					if (pl01->GuzaiNo[j] == hamburger[j]) {
						//���j���[�ƈ�v
						m_guzaiJudge[i + 1][j] = 1;
					}
					else {
						//���j���[�ƕs��v
						m_guzaiJudge[i + 1][j] = 0;
					}
				}

				Vector3 SetPos = { -95.0f,-255.0f,0.0f };
				SetPos.x += i * 120.0f;
				SetPos.y += j * 30.0f;
				//���j���[�ƈ�v���Ă��邩�Ō��߂�B
				switch (m_guzaiJudge[i+1][j])
				{
					
				case 0: {
					//��v�̉摜���o�Ă���Ώ����B
					if (m_spriteCompareFlagTrue[i + 1][j] == true) {
						DeleteGO(m_spriteCompare[i + 1][j]);
						m_spriteCompareFlagTrue[i + 1][j] = false;
					}
					//�s��v�̉摜���o�Ă��Ȃ���Ώo���B
					if (m_spriteCompareFlagFalse[i + 1][j] == false) {
						m_spriteCompare[i + 1][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i + 1][j]->Init("Assets/Image/JudgeMark/Batsu_White_Black512.dds", 40, 40);
						m_spriteCompare[i + 1][j]->SetPosition(SetPos);
						m_spriteCompareFlagFalse[i + 1][j] = true;
					}
				}break;
				case 1: {
					//�s��v�̉摜���o�Ă���Ώ����B
					if (m_spriteCompareFlagFalse[i + 1][j] == true) {
						DeleteGO(m_spriteCompare[i + 1][j]);
						m_spriteCompareFlagFalse[i + 1][j] = false;
					}
					//��v�̉摜���o�Ă��Ȃ���Ώo���B
					if (m_spriteCompareFlagTrue[i + 1][j] == false) {
						m_spriteCompare[i + 1][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i + 1][j]->Init("Assets/Image/JudgeMark/Check_White_Red512.dds", 30, 30);
						m_spriteCompare[i + 1][j]->SetPosition(SetPos);
						m_spriteCompareFlagTrue[i + 1][j] = true;
					}
				}break;
				default:
					break;
				}
			}
		}
	}
	//2P���̏���
	if (CounterNo == 2) {
		for (int i = 0; i < CounterNo; i++) {
			Player* pl02 = FindGO<Player>("player02");
			HamBurger hamburger = GetHamBurgerFactory().GetHamBurger(m_showHamBurgers[i]);
			for (int k = 0; k < 5; k++) {
				if (pl02->GuzaiNo[k] == 9) {
					if (m_spriteCompareFlagTrue[i][k] == true || m_spriteCompareFlagFalse[i][k] == true) {
						DeleteGO(m_spriteCompare[i][k]);
						m_spriteCompareFlagTrue[i][k] = false;
						m_spriteCompareFlagFalse[i][k] = false;
					}
				}
			}
			for (int j = 0; j < hamburger.size(); j++) {
				if (pl02->GuzaiNo[j] == 9) {
					m_guzaiJudge[i][j] = 2;
				}
				else {
					if (pl02->GuzaiNo[j] == hamburger[j]) {
						m_guzaiJudge[i][j] = 1;
					}
					else {
						m_guzaiJudge[i][j] = 0;
					}
				}
				Vector3 SetPos = { -155.0f,-255.0f,0.0f };
				SetPos.x += i * 120.0f;
				SetPos.y += j * 30.0f;
				switch (m_guzaiJudge[i][j])
				{
				case 0: {
					if (m_spriteCompareFlagTrue[i][j] == true) {
						DeleteGO(m_spriteCompare[i][j]);
						m_spriteCompareFlagTrue[i][j] = false;
					}
					if (m_spriteCompareFlagFalse[i][j] == false) {
						m_spriteCompare[i][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i][j]->Init("Assets/Image/JudgeMark/Batsu_White_Black512.dds", 40, 40);
						m_spriteCompare[i][j]->SetPosition(SetPos);
						m_spriteCompareFlagFalse[i][j] = true;
					}
				}break;
				case 1: {
					if (m_spriteCompareFlagFalse[i][j] == true) {
						DeleteGO(m_spriteCompare[i][j]);
						m_spriteCompareFlagFalse[i][j] = false;
					}
					if (m_spriteCompareFlagTrue[i][j] == false) {
						m_spriteCompare[i][j] = NewGO<SpriteRender>(10);
						m_spriteCompare[i][j]->Init("Assets/Image/JudgeMark/Check_White_Blue512.dds", 30, 30);
						m_spriteCompare[i][j]->SetPosition(SetPos);
						m_spriteCompareFlagTrue[i][j] = true;
					}
				}break;
				default:
					break;
				}
			}
		}
	}
}

void Counter::Update()
{
	Delete();
	HamBurgerCompare();
	
	if (m_spriteFlag01 == true) {
		m_spriteTime01++;
		if (m_spriteTime01 > 60) {
			DeleteGO(m_spriteJudge01);
			m_spriteFlag01 = false;
			m_spriteTime01 = 0;
		}
	}
	if (m_spriteFlag02 == true) {
		m_spriteTime02++;
		if (m_spriteTime02 > 60) {
			DeleteGO(m_spriteJudge02);
			m_spriteFlag02 = false;
			m_spriteTime02 = 0;
		}
	}
	m_skinModelRender->SetPosition(m_position);
}