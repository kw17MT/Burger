#include "stdafx.h"
#include "Kitchen.h"
//#include "ModelRender.h"
#include "Burger.h"
#include "Guzai.h"
#include "Counter.h"

#include "Player.h"
#include "SkinModelRender.h"

Kitchen::Kitchen()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/object/kitchen.tkm", nullptr, enModelUpAxisZ, m_position);
	Vector3 scale = { 0.2f,0.2f,0.2f };
	m_skinModelRender->SetScale(scale);

	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);

}

//��ނ̈ʒu���L�b�`���̏�ɐݒ肷��
void Kitchen::Stack(int num)
{
	if (KitchenNo == 1) {
		/*ModelRender*/Player* pl01 = FindGO<Player/*ModelRender*/>("player01");
		
		//����if���ŃX�^�b�N�������������̏�Ԃ�ύX��A���t���[���Ŏ��s�ł���悤�ɏ�ɒu���Ă���B
		if (isCompletedStack == true) {
			//����������ނ̃��f�����A�v���C���[�ɕۑ����ꂽ��ޔz��̔ԍ������Ɍ��肷��
			StackedGuzai[stack - 1]->ChangeGuzai(pl01->GuzaiNo[stack - 1]);
			//���f�����L�b�`���p�̃��f���ɍ����ւ���p
			StackedGuzai[stack - 1]->ChangeModel(pl01->GuzaiNo[stack - 1]);
			//��ނ𐶐�����ʒu�̊�����g�̈ʒu�Ƃ���
			//Vector3 GuzaiPos = m_charaCon.GetPosition();
			//(���݂̒i��) * ���� �̏ꏊ�ɋ�ނ𐶐�����
			/*GuzaiPos*/m_position.y = stack * 100.0f;
			StackedGuzai[nextStackNum - 1]->SetPosition(m_position/*GuzaiPos*/);
			//��ނ��u�����̂�҂�Ԃɂ���
			isCompletedStack = false;
		}

		if (nextStackNum < stack) {
			StackedGuzai[nextStackNum] = NewGO<Guzai>(0);
			//�����ŁA�L�b�`���Ɂu�u���ꂽ�v���Ƃ��L�^���A�L�b�`���ォ�瓮���Ȃ��悤�ɂ���B
			StackedGuzai[nextStackNum]->put = 1;

			isCompletedStack = true;
			nextStackNum++;
		}
	}

	if (KitchenNo == 2) {
		/*ModelRender*/Player* pl02 = FindGO<Player/*ModelRender*/>("player02");

		if (isCompletedStack == true) {
			StackedGuzai[stack - 1]->ChangeGuzai(pl02->GuzaiNo[stack - 1]);
			//���f�����L�b�`���p�̃��f���ɍ����ւ���p
			StackedGuzai[stack - 1]->ChangeModel(pl02->GuzaiNo[stack - 1]);
			//Vector3 GuzaiPos = m_charaCon.GetPosition();
			/*GuzaiPos*/m_position.y = stack * 100.0f;
			StackedGuzai[nextStackNum - 1]->SetPosition(m_position/*GuzaiPos*/);

			isCompletedStack = false;
		}

		if (nextStackNum < stack) {
			StackedGuzai[nextStackNum] = NewGO<Guzai>(0);
			StackedGuzai[nextStackNum]->put = 1;

			isCompletedStack = true;
			nextStackNum++;
		}
	}
}

//�ς�ł����ނ�S����������B
//�X�^�b�N�Ɏg�����ϐ���S���������B
void Kitchen::Delete()
{
	if (KitchenNo == 1) {
		for (int i = 0;i < nextStackNum; i++) {
			DeleteGO(StackedGuzai[i]);
			//���ɐςދ�ނ�Y���W���[���ɂ���B
			m_position.y = 0;
		}

		Counter* co01 = FindGO<Counter>("counter01");
		co01->SetStackNum(stack);

		stack = 0;
		nextStackNum = 0;
		DeleteTimer = 0;
		/*ModelRender*/Player* pl01 = FindGO<Player/*ModelRender*/>("player01");
		pl01->have = 0;
	}
	if (KitchenNo == 2) {
		for (int i = 0;i < nextStackNum; i++) {
			DeleteGO(StackedGuzai[i]);
		}
		Counter* co02 = FindGO<Counter>("counter02");
		co02->SetStackNum(stack);

		stack = 0;
		nextStackNum = 0;
		DeleteTimer = 0;
		/*ModelRender*/Player* pl02 = FindGO<Player/*ModelRender*/>("player02");
		pl02->have = 0;
	}
}

// Delay�͕K�v
// �Ȃ��ƃG���[
void Kitchen::BornBurger()
{
	if (KitchenNo == 1) {
		if (nextStackNum >= 1 && g_pad[0]->IsPress(enButtonY)) {
			Delay--;
			if (Delay == 0) {
				/*ModelRender*/Player* pl01 = FindGO</*ModelRender*/Player>("player01");

				//�����ŋ�ނ������Ă�����No.���v���C���[�������Ă���No.�i�[�p�z��ɂ���Ă����B
				//�����Ńn���o�[�K�[�̋�ނ��L�^���Ă�B
				for (int i = 0;i < nextStackNum; i++) {
					pl01->GuzaiNo[i] = StackedGuzai[i]->GetTypeNo();
				}
				//�L�b�`���ɂ��Ă����ނ�S������
				Delete();
				//�������P�ɂ��Ă��邱�ƂŁA�n���o�[�K�[���ł��Ă���Ƃ���ނ��Ƃ�Ȃ��悤�ɂ��Ă����B
				pl01->have = 1;
				bur = NewGO<Burger>(0, "burger01");
				bur->SetBurgerNo(1);
				//�Ԉ�����o�[�K�[�������AX�{�^���������ō폜������
				bur->burgerExist = 1;

				Delay = 60;
			}
		}
	}
	if (KitchenNo == 2) {
		if (nextStackNum >= 1 && g_pad[1]->IsPress(enButtonY)) {
			Delay--;
			if (Delay == 0) {
				/*ModelRender*/Player* pl02 = FindGO<Player/*ModelRender*/>("player02");

				//�����ŋ�ނ̎��No.���v���C���[�������Ă���No.�i�[�p�z��ɂ���Ă����B
				for (int i = 0;i < nextStackNum; i++) {
					pl02->GuzaiNo[i] = StackedGuzai[i]->GetTypeNo();
				}
				//�L�b�`���ɂ��Ă����ނ�S������
				Delete();
				//�������P�ɂ��Ă��邱�ƂŁA�n���o�[�K�[���ł��Ă���Ƃ���ނ��Ƃ�Ȃ��悤�ɂ��Ă����B
				pl02->have = 1;
				bur = NewGO<Burger>(0, "burger02");
				bur->SetBurgerNo(2);
				bur->burgerExist = 1;

				Delay = 60;
			}
		}
	}
}

void Kitchen::ClearNo()
{
	if (KitchenNo == 1) {
		/*ModelRender*/Player* pl01 = FindGO<Player/*ModelRender*/>("player01");

		for (int i = 0;i < nextStackNum; i++) {
			pl01->GuzaiNo[i] = 9;
		}
	}
	if (KitchenNo == 2) {
		/*ModelRender*/Player* pl02 = FindGO<Player/*ModelRender*/>("player02");

		for (int i = 0;i < nextStackNum; i++) {
			pl02->GuzaiNo[i] = 9;
		}
	}
}

void Kitchen::Update()
{
	Stack(stack);

	//X�{�^���������Ńv���C���[�Ɋi�[���Ă���ςݏグ����ނ̋L�^���������A�L�b�`����ɒu����Ă����ނ̍폜�B
	if (g_pad[0]->IsPress(enButtonX) && KitchenNo == 1) {
		DeleteTimer++;
		if (DeleteTimer > 50) {
			ClearNo();
			Delete();
		}
	}
	if (g_pad[1]->IsPress(enButtonX) && KitchenNo == 2) {
		DeleteTimer++;
		if (DeleteTimer > 50) {
			ClearNo();
			Delete();
		}
	}

	//�L�b�`����5�ȏ��ނ�����Ǝ��Ȃ��悤�ɂ���B
	//Guzaicpp�ŃL�b�`���̏ꏊ���オ���Ă������ߋ@�\���Ă��Ȃ��B

	if (nextStackNum >= MaxStack && KitchenNo == 1) {
		/*ModelRender*/Player* pl01 = FindGO<Player/*ModelRender*/>("player01");
		pl01->have = 1;
	}
	if (nextStackNum >= MaxStack && KitchenNo == 2) {
		/*ModelRender*/Player* pl02 = FindGO</*ModelRender*/Player>("player02");
		pl02->have = 1;
	}

	BornBurger();

	m_skinModelRender->SetPosition(m_kitchenPos);
	//model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);
}