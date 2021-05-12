#include "stdafx.h"
#include "Burger.h"
#include "Kitchen.h"
#include "Counter.h"

#include "Player.h"
#include "SkinModelRender.h"
#include "TrashCan.h"

Burger::Burger()
{

}

Burger::~Burger()
{
	DeleteGO(m_skinModelRender);
}

bool Burger::Start()
{
	m_player[0] = FindGO<Player>("player01");
	m_player[1] = FindGO<Player>("player02");
	m_trashCan[0] = FindGO<TrashCan>("trashcan01");
	m_trashCan[1] = FindGO<TrashCan>("trashcan02");

	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/food/Burger.tkm", nullptr, enModelUpAxisZ, m_position);
	Vector3 scale = { 10.0f,10.0f,10.0f };
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);

	if (BurgerNo == 1) {
		Kitchen* ki01 = FindGO<Kitchen>("kitchen01");
		Vector3 KiPos01 = ki01->GetKitchenPos();
		KiPos01.y += 100.0f;
		SetPosition(KiPos01);
	}
	if (BurgerNo == 2) {
		Kitchen* ki02 = FindGO<Kitchen>("kitchen02");
		Vector3 KiPos02 = ki02->GetKitchenPos();
		KiPos02.y += 100.0f;
		SetPosition(KiPos02);
	}

	return true;
}

void Burger::Delete()
{
	if (BurgerNo == 1) {
		Burger* bur01 = FindGO<Burger>("burger01");
		DeleteGO(bur01);
		DeleteGO(this);
	}
	if (BurgerNo == 2) {
		Burger* bur02 = FindGO<Burger>("burger02");
		DeleteGO(bur02);
		DeleteGO(this);
	}
}

//�v���C���[���o�[�K�[�����B
void Burger::GrabBurger()
{
	if (BurgerNo == 1) {
		Vector3 plPos = m_player[0]->GetPosition();
		Vector3 burPos = m_position;

		float pl2Burger = (plPos.x - burPos.x) * (plPos.x - burPos.x) + (plPos.y - burPos.y) * (plPos.y - burPos.y) + (plPos.z - burPos.z) * (plPos.z - burPos.z);
		pl2Burger = sqrt(pl2Burger);

		//A�{�^���������ăv���C���[�ƃo�[�K�[�̋�����150�ȉ��Ȃ�A�o�[�K�[��������������B
		if (g_pad[0]->IsPress(enButtonA) && pl2Burger < 150.0f) {
			m_player[0]->have = 2;
		}
		//�o�[�K�[�̈ʒu���v���C���[�̓���Ɏ����Ă���B
		if (m_player[0]->have == 2) {
			pos = plPos;
			pos.y += 100.0f;
			if (putOnKitchen != 1) {
				m_position = pos;
			}
		}
	}

	if (BurgerNo == 2) {
		Vector3 plPos = m_player[1]->GetPosition();
		Vector3 burPos = m_position;

		float pl2Burger = (plPos.x - burPos.x) * (plPos.x - burPos.x) + (plPos.y - burPos.y) * (plPos.y - burPos.y) + (plPos.z - burPos.z) * (plPos.z - burPos.z);
		pl2Burger = sqrt(pl2Burger);

		//A�{�^���������ăv���C���[�ƃo�[�K�[�̋�����150�ȉ��Ȃ�A�o�[�K�[��������������B
		if (g_pad[1]->IsPress(enButtonA) && pl2Burger < 200.0f) {
			m_player[1]->have = 2;
		}
		//�o�[�K�[�̈ʒu���v���C���[�̓���Ɏ����Ă���B
		if (m_player[1]->have == 2) {
			pos = plPos;
			pos.y += 100.0f;
			if (putOnKitchen != 1) {
				m_position = pos;
			}
		}
	}
}

void Burger::ClearNo()
{
	if (BurgerNo == 1) {
		//Player* pl01 = FindGO<Player>("player01");
		Counter* co01 = FindGO<Counter>("counter01");

		//�J�E���^�[�ɕۑ����Ă����A���܂Őς�ł�����ނ̐����O�ŏ���������B
		co01->SetStack0();

		//�v���C���[�ɕۑ����Ă����A�n���o�[�K�[���\�������ނ��X�ŏ������B	
		for (int i = 0;i < 10; i++) {
			m_player[0]->GuzaiNo[i] = 9;
		}
	}
	if (BurgerNo == 2) {
		//Player* pl02 = FindGO<Player>("player02");
		Counter* co02 = FindGO<Counter>("counter02");

		//�J�E���^�[�ɕۑ����Ă����A���܂Őς�ł�����ނ̎�ނ�S���O�ŏ���������B
		co02->SetStack0();

		//�v���C���[�ɕۑ����Ă����A�n���o�[�K�[���\�������ނ��X�ŏ������B	
		for (int i = 0;i < 10; i++) {
			m_player[1]->GuzaiNo[i] = 9;
		}
	}
}

void Burger::SetOnTrashCan() {
	if (BurgerNo == 1 && burgerExist == 1) {
		if (g_pad[0]->IsTrigger(enButtonA)
			&& m_trashCan[0]->GetCanTrash()) {
			isSetOnTrashCan = true;
		}

		if (isSetOnTrashCan == true) {
			decrementTime--;
			if (decrementTime <= 0) {

				burgerExist = 0;
				m_player[0]->have = 0;
				decrementTime = 10;
				ClearNo();
				Delete();
			}
			m_position = m_trashCan[0]->GetPosition();
			m_position.y += 60.0f;
		}
	}

	if (BurgerNo == 2 && burgerExist == 1) {
		if (g_pad[1]->IsTrigger(enButtonA)
			&& m_trashCan[1]->GetCanTrash()) {
			isSetOnTrashCan = true;
		}

		if (isSetOnTrashCan == true) {
			decrementTime--;
			if (decrementTime <= 0) {

				burgerExist = 0;
				m_player[1]->have = 0;
				decrementTime = 10;
				ClearNo();
				Delete();
			}
			m_position = m_trashCan[1]->GetPosition();
			m_position.y += 60.0f;
		}
	}
}

void Burger::Update()
{
	GrabBurger();
	
	SetOnTrashCan();

	m_skinModelRender->SetPosition(m_position);
}
