#include "stdafx.h"
#include "Kitchen.h"
#include "Burger.h"
#include "Guzai.h"
#include "Counter.h"
#include "Player.h"
#include "SkinModelRender.h"
#include "SoundSource.h"
#include "Meter.h"
#include "MenuTimer.h"

namespace
{
	const Vector3 MOVE_SPEED_ZERO = Vector3::Zero;

	const int PLAYER_NAME_SIZE = 9;
	const int COUNTER_NAME_SIZE = 10;
	const int BURGER_NAME_SIZE = 9;
	const int AJUST_METER_POS_X_No0 = 200;
	const int AJUST_METER_POS_X_No1 = 100;
	const int AJUST_METER_POS_Y = 300;
	const int AJUST_METER_POS_Z = 100;
	const int HAVE_GUZAI = 1;
	const int NOTHING = 0;
	const int FULL_KITCHEN = -1;
	const int MAX_STACK_NUM = 5;
	const int KITCHEN_NUMBER_0 = 0;
	const int KITCHEN_NUMBER_1 = 1;
	const int DEFAULT_DELAY_NUMBER = 60;

	const float SCALE_DECREASE_SPEED = 1.4f / 60.0f;
	const float GUZAI_DOWN_SPEED = 0.7f;
	const float SE_VOLUME = 1.5f;
	const float DISTANCE_BETWEEN_PLAYER_TO_KITCHEN = 100.0f;
}

Kitchen::~Kitchen()
{
	DeleteGO(m_skinModelRender);
	
	//�o�[�K�[�̏���
	if (bur != nullptr) {
		DeleteGO(bur);
	}

	//�X�^�b�N������ނ��c���Ă��������
	for (int i = 0; i < MAX_STACK_NUM; i++) {
		if (m_stackedGuzai[i] != nullptr) {
			DeleteGO(m_stackedGuzai[i]);
		}
	}

	if (m_soundFlag) {
		DeleteGO(m_soundSource);
		DeleteGO(m_meter);
	}
}

bool Kitchen::Start()
{
	//string�^�ɕς���char�ɕϊ����邽�߂̏���������B
	std::string endNo_string = std::to_string(m_kitchenNo);
	//�s�ωӏ����`
	char playerName[PLAYER_NAME_SIZE] = "player0";
	char counterName[COUNTER_NAME_SIZE] = "counter0";
	//���[�ԍ�������ǉ�����
	strcat_s(playerName, endNo_string.c_str());
	strcat_s(counterName, endNo_string.c_str());
	//�K�v�ȃf�[�^�̒T���Ɗm��
	m_player = FindGO<Player>(playerName);
	m_counter = FindGO<Counter>(counterName);

	//���f���f�[�^�̏�����
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/object/kitchen.tkm", nullptr, enModelUpAxisZ, m_position);
	//m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_skinModelRender->InitForCastShadow("Assets/modelData/object/kitchen.tkm", nullptr, enModelUpAxisZ, m_position, nullptr);
	m_skinModelRender->SetScale(m_scale);

	return true;
}

//�ς�ł����ނ̑S�����A����Ɋւ���p�����[�^�̏�����
//BornBurger()�ł���
void Kitchen::Delete()
{
	//�ς�ł����ނ̏���
	for (int i = 0;i < m_stack; i++) {
		//�ς�ł����ނ̏���
		DeleteGO(m_stackedGuzai[i]);
		//�ۑ����Ă�����ނ�����FALSE���Ȃ��@�ɐݒ�
		//m_guzaiGene->SetGuzaiFlag(m_stackedGuzai[i]->GetGuziNo(), false);
	}

	//�L�b�`���ɐς�ł�����ނ̐����J�E���^�[�̕��Ɉڂ�
	m_counter->SetStackNum(m_stack);
	//�L�b�`���ɐς�ł����ސ����O�ŏ�����
	m_stack = 0;
}

// Delay�͕K�v
// �Ȃ��ƃG���[
void Kitchen::BornBurger()
{
	Vector3 preDistance = m_player->GetPosition() - m_position;
	float distance = preDistance.Length();

	//��ނ���ȏ�ς�ł��āAB�{�^���𒷉���
	if (m_stack > 0 && g_pad[m_kitchenNo]->IsPress(enButtonB) && m_isPlayerCookingOnKitchen == false && distance < DISTANCE_BETWEEN_PLAYER_TO_KITCHEN && m_player->GetPlayerState() <= NOTHING) {
		m_delay--;
		//�v���C���[�������Ȃ��悤�ɂ���B
		m_player->StopMove(true);
		m_player->SetMoveSpeed(MOVE_SPEED_ZERO);
		if (m_soundFlag == false) {
			//�����̐i�݋�̃��[�^�[��\��
			m_meter = NewGO<Meter>(0);
			if (m_kitchenNo == KITCHEN_NUMBER_0) {
				Vector3 pos = m_position;
				pos.x -= AJUST_METER_POS_X_No0;
				pos.y += AJUST_METER_POS_Y;
				pos.z += AJUST_METER_POS_Z;

				m_meter->SetPosition(pos);
			}
			if (m_kitchenNo == KITCHEN_NUMBER_1) {
				Vector3 pos = m_position;
				pos.x += AJUST_METER_POS_X_No1;
				pos.y += AJUST_METER_POS_Y;
				pos.z += AJUST_METER_POS_Z;

				m_meter->SetPosition(pos);
			}
			
			//����炷
			m_soundSource = NewGO<CSoundSource>(0);
			m_soundSource->Init(L"Assets/sound/cutting_a_onion_speedy.wav", false);
			m_soundSource->SetVolume(SE_VOLUME);
			m_soundSource->Play(true);
			m_soundFlag = true;
		}
		//���[�^�[�����������炷
		Vector3 scale = m_meter->GetScale();
		scale.x -= SCALE_DECREASE_SPEED;
		m_meter->SetScale(scale);
		if (m_delay == 0) {
			//�����o�Ă���Ώ����B
			if (m_soundFlag == true) {
				//���[�^�[������
				DeleteGO(m_meter);
				DeleteGO(m_soundSource);
				m_soundFlag = false;
			}
			//�����ŋ�ނ������Ă��邱�Ƃɂ��āA�n���o�[�K�[���ł��Ă���Ƃ���ނ��Ƃ�Ȃ��悤�ɂ��Ă����B
			m_player->SetPlayerState(HAVE_GUZAI);
			//�폜�t���O�𗧂Ă�B
			m_isPlayerCookingOnKitchen = true;
			m_delay = DEFAULT_DELAY_NUMBER;
		}
	}
	else {
		if (m_isPlayerCookingOnKitchen == false) {
			m_delay = DEFAULT_DELAY_NUMBER;
			m_player -> StopMove(false);
		}

		//�����o�Ă���Ώ����B
		if (m_soundFlag == true) {
			//���[�^�[�������B
			DeleteGO(m_meter);
			DeleteGO(m_soundSource);
			m_soundFlag = false;
		}
	}
	//�폜�t���O�������Ă���Ƃ��c
	if (m_isPlayerCookingOnKitchen == true) {
		m_player->SetPlayerState(HAVE_GUZAI);
		m_delay--;
		for (int i = 0; i < m_stack; i++) {
			m_slidePos = m_stackedGuzai[i]->GetPosition();
			//��ނ�y���W��(���x�~�ς�ł�i��)�ŉ�����B
			m_slidePos.y -= GUZAI_DOWN_SPEED * i;
			m_stackedGuzai[i]->SetPosition(m_slidePos);
		}
		if (m_delay == 0) {
			//�L�b�`���ɂ��Ă����ނ�S������
			Delete();

			if (m_kitchenNo == 0) {
				bur = NewGO<Burger>(0, "burger00");
			}
			if (m_kitchenNo == 1) {
				bur = NewGO<Burger>(0, "burger01");
			}

			bur->SetBurgerNo(m_kitchenNo);
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/thi-n.wav", false);
			se->SetVolume(SE_VOLUME);
			se->Play(false);

			m_player->StopMove(false);
			m_isPlayerCookingOnKitchen = false;
			m_delay = DEFAULT_DELAY_NUMBER;
		}
	}
}

void Kitchen::ClearNo()
{
	for (int i = 0;i < m_stack; i++) {
		m_player->ClearSpecificGuzaiNo(i);
	}
}

void Kitchen::Update()
{
	if (m_player == nullptr) {
		//string�^�ɕς���char�ɕϊ����邽�߂̏���������B
		std::string endNo_string = std::to_string(m_kitchenNo);
		//�s�ωӏ����`
		char playerName[PLAYER_NAME_SIZE] = "player0";
		//���[�ԍ�������ǉ�����
		strcat_s(playerName, endNo_string.c_str());

		//�K�v�ȃf�[�^�̒T���Ɗm��
		m_player = FindGO<Player>(playerName);
	}
	
	Vector3 predistance = m_player->GetPosition() - m_position;
	float distance = predistance.Length();

	//��鏈��
	//1�w�ȏ�ς܂�Ă�����Ƃ��悤�ɂ���B
	if (m_stack >= 1 && distance <= DISTANCE_BETWEEN_PLAYER_TO_KITCHEN) {
		if (g_pad[m_kitchenNo]->IsTrigger(enButtonA) && /*m_kitchenNo == 1 &&*/ m_canGrab == true && m_player->GetPlayerState() <= NOTHING) {
			//���̋�ނ͈��L�b�`������A���Ă�����
			m_stackedGuzai[m_stack - 1]->SetReturnedState(true);
			//������Ă��邩
			m_stackedGuzai[m_stack - 1]->SetisHadState(true);
			//�ǂ���̃v���C���[�Ɏ�����Ă��邩
			m_stackedGuzai[m_stack - 1]->SetWhichPlayerGet(m_kitchenNo);
			//��ԏゾ������ނ̔ԍ����X�ɂ��ĉ��������Ă��Ȃ���Ԃɂ���B
			m_player->ClearSpecificGuzaiNo(m_stack - 1);
			//���̋�ނ̓L�b�`���ɒu����Ă��邩
			m_stackedGuzai[m_stack - 1]->SetPutState(false);
			//���݂̃X�^�b�N���A���̃X�^�b�N�ԍ���1���炷
			m_stack--;
			//�v���C���[�͋�ނ������Ă����Ԃɂ���B
			m_player->SetPlayerState(HAVE_GUZAI);
		}
	}
	
	//�L�b�`����5�ȏ��ނ������"�R���x�A�����"���Ȃ��悤�ɂ���B
	if (m_stack >= m_maxStack) {
		m_player->SetPlayerState(FULL_KITCHEN);
	}

	BornBurger();

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
}