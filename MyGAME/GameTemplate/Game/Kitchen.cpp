#include "stdafx.h"
#include "Kitchen.h"
#include "Burger.h"
#include "Guzai.h"
#include "Counter.h"
#include "Player.h"
#include "SkinModelRender.h"
#include "SoundSource.h"
#include "Meter.h"

Kitchen::~Kitchen()
{
	DeleteGO(m_skinModelRender);
	
	//�o�[�K�[�̏���
	if (bur != nullptr) {
		DeleteGO(bur);
	}
	
	//�X�^�b�N������ނ��c���Ă��������
	for (int i = 0; i < 5; i++) {
		if (StackedGuzai[i] != nullptr) {
			DeleteGO(StackedGuzai[i]);
		}
	}
}

bool Kitchen::Start()
{
	m_player[0] = FindGO<Player>("player01");
	m_player[1] = FindGO<Player>("player02");

	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/object/kitchen.tkm", nullptr, enModelUpAxisZ, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);

	m_scale = { 0.3f,0.3f,0.3f };
	m_skinModelRender->SetScale(m_scale);

	return true;
}

void Kitchen::ChangeModel(const char* filePath)
{
	m_skinModelRender->Init(filePath, nullptr, enModelUpAxisZ, m_position);
}

//�ς�ł����ނ̑S�����A����Ɋւ���p�����[�^�̏�����
//BornBurger()�ł���
void Kitchen::Delete()
{
	//�ς�ł����ނ̏���
	if (KitchenNo == 1) {
		for (int i = 0;i < stack; i++) {
			DeleteGO(StackedGuzai[i]);
		}

		Counter* co01 = FindGO<Counter>("counter01");
		co01->SetStackNum(stack);

		//�ς�ł����ސ����O�ŏ�����
		stack = 0;
	}
	if (KitchenNo == 2) {
		for (int i = 0;i < stack; i++) {
			DeleteGO(StackedGuzai[i]);
		}
		Counter* co02 = FindGO<Counter>("counter02");
		co02->SetStackNum(stack);

		stack = 0;
	}
}

// Delay�͕K�v
// �Ȃ��ƃG���[
void Kitchen::BornBurger()
{
	Vector3 predistance1 = m_player[0]->GetPosition() - m_position;
	float distance1 = predistance1.Length();
	Vector3 predistance2 = m_player[1]->GetPosition() - m_position;
	float distance2 = predistance2.Length();
	if (KitchenNo == 1) {
		//��ނ���ȏ�ς�ł��āAB�{�^���𒷉���
		if (stack >= 1 && g_pad[0]->IsPress(enButtonB) && m_deleteFlag == false && distance1 < 100.0f) {
			Delay--;
			//�v���C���[�������Ȃ��悤�ɂ���B
			m_player[0]->StopMove02(true);
			m_player[0]->SetMoveSpeed({ 0.0f,0.0f,0.0f });
			if (m_soundFlag01 == false) {
				//�����̐i�݋�̃��[�^�[��\��
				m_meter = NewGO<Meter>(0);
				Vector3 pos = m_position;
				pos.x -= 200.0f;
				pos.y += 300.0f;
				pos.z += 100.0f;
				m_meter->SetPosition(pos);
				
				//����炷
				m_soundSource = NewGO<CSoundSource>(0);
				m_soundSource->Init(L"Assets/sound/cutting_a_onion_speedy.wav", false);
				m_soundSource->SetVolume(2.0f);
				m_soundSource->Play(true);
				m_soundFlag01 = true;
			}
			//���[�^�[�����������炷
			Vector3 scale = m_meter->GetScale();
			scale.x -= 1.4 / 60;
			m_meter->SetScale(scale);
			if (Delay == 0) {
				//�����o�Ă���Ώ����B
				if (m_soundFlag01 == true) {
					//���[�^�[������
					DeleteGO(m_meter);
					DeleteGO(m_soundSource);
					m_soundFlag01 = false;
				}
				//�������P�ɂ��Ă��邱�ƂŁA�n���o�[�K�[���ł��Ă���Ƃ���ނ��Ƃ�Ȃ��悤�ɂ��Ă����B
				m_player[0]->have = 1;
				//�폜�t���O�𗧂Ă�B
				m_deleteFlag = true;
				Delay = 40;
			}
		}
		else {
			if (m_deleteFlag == false) {
				Delay = 60;
				m_player[0]->StopMove02(false);
			}
			
			//�����o�Ă���Ώ����B
			if (m_soundFlag01 == true) {
				//���[�^�[�������B
				DeleteGO(m_meter);
				DeleteGO(m_soundSource);
				m_soundFlag01 = false;
			}
		}
		//�폜�t���O�������Ă���Ƃ��c
		if (m_deleteFlag == true) {
			m_player[0]->have = 1;
			Delay--;
			for (int i = 0; i < stack; i++) {
				m_slidePos = StackedGuzai[i]->GetPosition();
				//��ނ�y���W��(���x�~�ς�ł�i��)�ŉ�����B
				m_slidePos.y -= 1.2f * i;
				StackedGuzai[i]->SetPosition(m_slidePos);
			}
			if (Delay == 0) {
				//�L�b�`���ɂ��Ă����ނ�S������
				Delete();
				
				bur = NewGO<Burger>(0, "burger01");
				bur->SetBurgerNo(1);
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/thi-n.wav", false);
				se->SetVolume(2.0f);
				se->Play(false);
				
				m_player[0]->StopMove02(false);
				m_deleteFlag = false;
				Delay = 60;
			}
		}
	}

	if (KitchenNo == 2) {
		if (stack >= 1 && g_pad[1]->IsPress(enButtonB) && m_deleteFlag == false && distance2 < 100.0f) {
			Delay--;
			m_player[1]->StopMove02(true);
			m_player[1]->SetMoveSpeed({ 0.0f,0.0f,0.0f });
			if (m_soundFlag02 == false) {
				m_meter = NewGO<Meter>(0);
				Vector3 pos = m_position;
				pos.x += 100.0f;
				pos.y += 300.0f;
				pos.z += 100.0f;
				m_meter->SetPosition(pos);
				//����炷
				m_soundSource = NewGO<CSoundSource>(0);
				m_soundSource->Init(L"Assets/sound/cutting_a_onion_speedy.wav", false);
				m_soundSource->SetVolume(2.0f);
				m_soundSource->Play(true);
				m_soundFlag02 = true;
			}
			Vector3 scale = m_meter->GetScale();
			scale.x -= 1.4 / 60;
			m_meter->SetScale(scale);
			if (Delay == 0) {
				//�����o�Ă���Ώ����B
				if (m_soundFlag02 == true) {
					DeleteGO(m_meter);
					DeleteGO(m_soundSource);
					m_soundFlag02 = false;
				}
				//�������P�ɂ��Ă��邱�ƂŁA�n���o�[�K�[���ł��Ă���Ƃ���ނ��Ƃ�Ȃ��悤�ɂ��Ă����B
				m_player[1]->have = 1;
				m_deleteFlag = true;
				Delay = 40;
			}
		}
		else {
			if (m_deleteFlag == false) {
				Delay = 60;
				//m_player[1]->StopMove02(false);
			}
			//�����o�Ă���Ώ����B
			if (m_soundFlag02 == true) {
				DeleteGO(m_meter);
				DeleteGO(m_soundSource);
				m_soundFlag02 = false;
			}
		}
		if (m_deleteFlag == true) {
			m_player[1]->have = 1;
			Delay--;
			for (int i = 0; i < stack; i++) {
				m_slidePos = StackedGuzai[i]->GetPosition();
				//��ނ�y���W��(���x�~�ς�ł�i��)�ŉ�����B
				m_slidePos.y -= 1.2f * i;
				StackedGuzai[i]->SetPosition(m_slidePos);
			}
			if (Delay == 0) {
				//�L�b�`���ɂ��Ă����ނ�S������
				Delete();
			
				bur = NewGO<Burger>(0, "burger02");
				bur->SetBurgerNo(2);
				//����炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/thi-n.wav", false);
				se->SetVolume(2.0f);
				se->Play(false);

				m_player[1]->StopMove02(false);
				m_deleteFlag = false;
				Delay = 60;
				
			}
		}
	}
}

void Kitchen::ClearNo()
{
	if (KitchenNo == 1) {
		for (int i = 0;i < stack; i++) {
			m_player[0]->GuzaiNo[i] = 9;
		}
	}
	if (KitchenNo == 2) {
		for (int i = 0;i < stack; i++) {
			m_player[1]->GuzaiNo[i] = 9;
		}
	}
}

void Kitchen::Update()
{
	if (m_player[0] == nullptr) {
		m_player[0] = FindGO<Player>("player01");
	}
	if (m_player[1] == nullptr) {
		m_player[1] = FindGO<Player>("player02");
	}

	Vector3 predistance1 = m_player[0]->GetPosition() - m_position;
	float distance1 = predistance1.Length();
	Vector3 predistance2 = m_player[1]->GetPosition() - m_position;
	float distance2 = predistance2.Length();

	//��������
	//��鏈��
	//1�w�ȏ�ς܂�Ă�����Ƃ��悤�ɂ���B
	if (stack >= 1 && distance1 <= 150.0f) {
		if (g_pad[0]->IsTrigger(enButtonA) && KitchenNo == 1 && canGrab == true && m_player[0]->have <= 0) {
			//���̋�ނ͈��L�b�`������A���Ă�����
			StackedGuzai[stack - 1]->returned = true;
			//������Ă��邩
			StackedGuzai[stack - 1]->state = 1;
			//�ǂ���̃v���C���[�Ɏ�����Ă��邩
			StackedGuzai[stack - 1]->SetWhichPlayerGet(1);
			//��ԏゾ������ނ̔ԍ����X�ɂ��ĉ��������Ă��Ȃ���Ԃɂ���B
			m_player[0]->ClearLatestGuzaiNo(stack - 1);
			//���̋�ނ̓L�b�`���ɒu����Ă��邩
			StackedGuzai[stack - 1]->put = 0;
			//���݂̃X�^�b�N���A���̃X�^�b�N�ԍ���1���炷
			stack--;
			//�v���C���[�͋�ނ������Ă����Ԃɂ���B
			m_player[0]->have = 1;
		}
	}
	if (stack >= 1 && distance2 <= 150.0f) {
		if (g_pad[1]->IsTrigger(enButtonA) && KitchenNo == 2 && canGrab == true && m_player[1]->have <= 0) {
			//���̋�ނ͈��L�b�`������A���Ă�����
			StackedGuzai[stack - 1]->returned = true;
			//������Ă��邩
			StackedGuzai[stack - 1]->state = 1;
			//�ǂ���̃v���C���[�Ɏ�����Ă��邩
			StackedGuzai[stack - 1]->SetWhichPlayerGet(2);
			//��ԏゾ������ނ̔ԍ����X�ɂ��ĉ��������Ă��Ȃ���Ԃɂ���B
			m_player[1]->ClearLatestGuzaiNo(stack - 1);
			//���̋�ނ̓L�b�`���ɒu����Ă��邩
			StackedGuzai[stack - 1]->put = 0;
			//���݂̃X�^�b�N���A���̃X�^�b�N�ԍ���1���炷
			stack--;
			//�v���C���[�͋�ނ������Ă����Ԃɂ���B
			m_player[1]->have = 1;
		}
	}

	//�L�b�`����5�ȏ��ނ������"�R���x�A�����"���Ȃ��悤�ɂ���B
	if (stack >= MaxStack && KitchenNo == 1) {
		m_player[0]->have = -1;
	}
	if (stack >= MaxStack && KitchenNo == 2) {
		m_player[1]->have = -1;
	}

	BornBurger();

	m_skinModelRender->SetPosition(m_kitchenPos);
	m_skinModelRender->SetScale(m_scale);
}