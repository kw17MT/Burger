#include "stdafx.h"
#include "Counter.h"
#include "Burger.h"
#include "Kitchen.h"
#include "Score.h"
#include "CLevel2D.h";
#include "PlayerGene.h"
#include "Player.h"
#include "SkinModelRender.h"

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
			if (g_pad[0]->IsTrigger(enButtonB) && pl2Counter < 100.0f) {
				if (Judge() == true) {
					bu01->putOnKitchen = 1;
				}
			}

			//�u������30�t���[����ɏ���
			if (bu01->putOnKitchen == 1) {
				Delay++;
				CounterPos01.y += 100.0f;
				bu01->SetPosition(CounterPos01);

				if (Delay == 30) {
					//�����Őςݏグ�Ă���ނ̐���Score�ɓn���Ă�����B
					Score* sco = FindGO<Score>("score");
					sco->SetBasePoint01(StackNum);

					//���̋��No.��ۑ����邽�߁A�X�ŏ������B
					pl01->SetGuzaiNo9();
					
					bu01->ClearModel();
					DeleteGO(bu01);
					Delay = 0;
					pl01->have = 0;
					StackNum = 0;
					m_playerGene->AddSubmitBurgerNum();
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
			if (g_pad[1]->IsTrigger(enButtonB) && pl2Counter < 100.0f) {
				if (Judge() == true) {
					bu02->putOnKitchen = 1;
				}
			}

			//�u������30�t���[����ɏ���
			if (bu02->putOnKitchen == 1) {
				Delay++;
				CounterPos02.y += 100.0f;
				bu02->SetPosition(CounterPos02);

				if (Delay == 30) {
					//�����Őςݏグ�Ă���ނ̐���Score�ɓn���Ă�����B
					Score* sco = FindGO<Score>("score");
					sco->SetBasePoint02(StackNum);

					//���̋��No.��ۑ����邽�߁A�X�ŏ������B
					pl02->SetGuzaiNo9();

					DeleteGO(bu02);
					Delay = 0;
					pl02->have = 0;
					StackNum = 0;
					m_playerGene->AddSubmitBurgerNum();
				}
			}
		}
	}
}

void Counter::Update()
{
	Delete();
	m_skinModelRender->SetPosition(m_position);
}