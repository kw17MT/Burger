#include "stdafx.h"
#include "Counter.h"
#include "ModelRender.h"
#include "Burger.h"
#include "Kitchen.h"
#include "Score.h"

Counter::Counter()
{
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/ches.tkm";
	modeldata.m_fxFilePath = "Assets/shader/model.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_modelUpAxis = enModelUpAxisY;

	modeldata.m_expandConstantBuffer = &g_lig;
	modeldata.m_expandConstantBufferSize = sizeof(g_lig);

	m_skeleton.Init("Assets/modelData/unityChan.tks");
	modeldata.m_skeleton = &m_skeleton;

	model.Init(modeldata);

	m_charaCon.Init(0.0f, 0.0f, g_vec3One);
}

//////////////////////���ʂ���Ƃ���////////////////////////////////////////////////////////////////////////////////
bool Counter::Judge()
{
	if (CounterNo == 1) {
		Kitchen* ki01 = FindGO<Kitchen>("kitchen01");
		ModelRender* pl01 = FindGO<ModelRender>("player01");

		//�ŏI���ʂ��L�^������́B
		bool correct01 = true;
		//���ʂ��Ă����ߒ��Ő�����������C���N�������g����Ă����B���𐔂݂����Ȃ��́B
		int correctCount01 = 0;
		//���_�ƂȂ鐔�Bsizeof�̒��g��ς��邱�Ƃł����Ȏ�ނ̃o�[�K�[�ɑΉ��ł���Ǝv���B���ς��Ă������B
		int correctGuzaiNum01 = sizeof(burger01) / sizeof(int);

		//������o�[�K�[�̑w�ɂ���ĉ�FOR���̉񐔂��ς��B
		//StackNum�̓o�[�K�[���ł���u�Ԃɂ����瑤�ɕۑ������B�iin Kitchen.cpp)
		//���ʉߒ��ň�x�ł��ԈႦ����FALSE
		for (int i = 0; i < StackNum; i++) {
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
	}

	if (CounterNo == 2) {
		Kitchen* ki02 = FindGO<Kitchen>("kitchen02");
		ModelRender* pl02 = FindGO<ModelRender>("player02");

		bool correct02 = true;
		int correctCount02 = 0;
		int correctGuzaiNum02 = sizeof(burger01) / sizeof(int);

		for (int i = 0; i < StackNum; i++) {
			if (burger01[i] == pl02->GuzaiNo[i]) {
				++correctCount02;
				continue;
			}
			else {
				correct02 = false;
				break;
			}
		}

		if (correctCount02 != correctGuzaiNum02) {
			correct02 = false;
		}
		return correct02;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//�o�[�K�[���ŏI�I�ɏ����ăX�R�A�𔭐�������B
//�J�E���^�[�ɋ߂��Ƃ����B�{�^���������Ƃ�������ڂ��ď����B
void Counter::Delete()
{
	if (CounterNo == 1) {
		ModelRender* pl01 = FindGO<ModelRender>("player01");
		Vector3 plPos = pl01->GetPosition();

		Vector3 CounterPos01 = m_charaCon.GetPosition();

		//�J�E���^�[����v���C���[�̋���
		float pl2Counter = (plPos.x - CounterPos01.x) * (plPos.x - CounterPos01.x) + (plPos.y - CounterPos01.y) * (plPos.y - CounterPos01.y) + (plPos.z - CounterPos01.z) * (plPos.z - CounterPos01.z);
		pl2Counter = sqrt(pl2Counter);

		//�v���C���[���o�[�K�[�������Ă�����
		if (pl01->have == 2) {
			Burger* bu01 = FindGO<Burger>("burger01");

			//�L�b�`���ɒu������
			//�ł����n���o�[�K�[�̑g����Judge�֐��Œ��ׁA�����Ă�����J�E���^�[�ɒu����B
			if (g_pad[0]->IsPress(enButtonB) && pl2Counter < 100.0f) {
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
					
					DeleteGO(bu01);
					Delay = 0;
					pl01->have = 0;
					StackNum = 0;
				}
			}
		}
	}

	if (CounterNo == 2) {
		ModelRender* pl02 = FindGO<ModelRender>("player02");
		Vector3 plPos = pl02->GetPosition();

		Vector3 CounterPos02 = m_charaCon.GetPosition();

		float pl2Counter = (plPos.x - CounterPos02.x) * (plPos.x - CounterPos02.x) + (plPos.y - CounterPos02.y) * (plPos.y - CounterPos02.y) + (plPos.z - CounterPos02.z) * (plPos.z - CounterPos02.z);
		pl2Counter = sqrt(pl2Counter);

		//�v���C���[���o�[�K�[�������Ă�����
		if (pl02->have == 2) {
			Burger* bu02 = FindGO<Burger>("burger02");

			//�L�b�`���ɒu������
			//�ł����n���o�[�K�[�̑g����Judge�֐��ł���ׁA�����Ă�����J�E���^�[�ɒu����B
			if (g_pad[1]->IsPress(enButtonB) && pl2Counter < 100.0f) {
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
				}

			}
		}
	}
}

void Counter::Update()
{
	Delete();
	model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);
}