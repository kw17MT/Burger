#include "stdafx.h"
#include "Burger.h"
#include "Kitchen.h"
#include "Counter.h"
#include "Player.h"
#include "SkinModelRender.h"
#include "TrashCan.h"
#include "SoundSource.h"
#include "effect/Effect.h"
#include <string>

namespace {
	const Vector3 EFFECT_SCALE = { 10.0f,10.0f,10.0f };
	const int KITCHEN_NAME_SIZE = 10;
	const int PLAYER_NAME_SIZE = 9;
	const int TRASHCAN_NAME_SIZE = 11;
	const int COUNTER_NAME_SIZE = 10;
	const int NONE = 9;
	const int DEFAULT_DECREMENT_TIME = 20;
	const float SPACE_BETWEEN_KITCHEN_TO_BURGER = 100.0f;
	const float AJUST_HEIGHT = 50.0f;
	const float AJUST_SPEED_TO_FOLLOW_PLAYER = 90.0f;
	const float DISTANCE_BETWEEN_PLAYER_TO_BURGER = 150.0f;
	const float SE_VOLUME = 2.0f;
}

Burger::~Burger()
{
	DeleteGO(m_skinModelRender);
}

bool Burger::Start()
{
	//���f���̏�����
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//�ʏ�`��p���f���̏�����
	m_skinModelRender->Init("Assets/modelData/food/Burger.tkm", nullptr, enModelUpAxisZ, m_position);
	//�V���h�E�L���X�^�[�p�̏�����
	m_skinModelRender->InitForCastShadow("Assets/modelData/food/Burger.tkm", nullptr, enModelUpAxisZ, m_position);
	//���f���̊g��
	m_skinModelRender->SetScale(m_burgerScale);

	//�o�[�K�[�̔ԍ����擾
	int endNo = m_burgerNo;
	//string�^�ɕς���char�ɕϊ����邽�߂̏���������B
	std::string endNo_string = std::to_string(endNo);
	//�s�ωӏ����`
	char playerName[PLAYER_NAME_SIZE] = "player0";
	char trashcanName[TRASHCAN_NAME_SIZE] = "trashcan0";
	char counterName[COUNTER_NAME_SIZE] = "counter0";
	char kitchenName[KITCHEN_NAME_SIZE] = "kitchen0";
	//���[�ԍ�������ǉ�����
	strcat_s(kitchenName, endNo_string.c_str());
	strcat_s(playerName, endNo_string.c_str());
	strcat_s(trashcanName, endNo_string.c_str());
	strcat_s(counterName, endNo_string.c_str());
	//����̃L�b�`����ݒ��A���W���Ƃ��Ă��ăZ�b�g����B
	Kitchen* kitchen = FindGO<Kitchen>(kitchenName);
	Vector3 kitchenPos = kitchen->GetKitchenPos();
	kitchenPos.y += SPACE_BETWEEN_KITCHEN_TO_BURGER;
	SetPosition(kitchenPos);

	//���ꂽ���̃v���C���[�A�S�~���A�J�E���^�[��T���B
	m_player = FindGO<Player>(playerName);
	m_trashCan = FindGO<TrashCan>(trashcanName);
	m_counter = FindGO<Counter>(counterName);

	//�n���o�[�K�[���o�Ă����Ƃ��̃G�t�F�N�g
	Effect* m_effect = NewGO<Effect>(0);
	m_effect->Init(u"Assets/effect/kirakira.efk");
	m_effect->Play();
	m_effect->SetScale(EFFECT_SCALE);
	m_effect->SetPosition(m_position);

	m_skinModelRender->SetApplyBlur(true);

	return true;
}

//�v���C���[���o�[�K�[�����B
void Burger::GrabBurger()
{
	//�v���C���[�̈ʒu���W���擾
	Vector3 plPos = m_player->GetPosition();
	//�v���C���[�̒ʏ�ړ����x���擾
	Vector3 plSpeed = m_player->GetNormalMoveSpeed();
	//�v���C���[�̈ړ����x���グ��
	plSpeed *= AJUST_SPEED_TO_FOLLOW_PLAYER;

	//�v���C���[�ƃn���o�[�K�[�̋����𑪂�
	Vector3 playerToBurger_vec = plPos - m_position;
	float playerToBurger = playerToBurger_vec.Length();

	//A�{�^���������ăv���C���[�ƃo�[�K�[�̋��������ȉ��Ȃ�A�o�[�K�[��������������B
	if (g_pad[m_burgerNo]->IsTrigger(enButtonA) && playerToBurger < DISTANCE_BETWEEN_PLAYER_TO_BURGER && m_player->GetPlayerState() != enHaveBurger) {
		//�v���C���[�̏�Ԃ��A�n���o�[�K�[������Ԃɂ���
		m_player->SetPlayerState(enHaveBurger);
		//����炷
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/poka01.wav", false);
		se->SetVolume(SE_VOLUME);
		se->Play(false);
	}
	//�o�[�K�[�̈ʒu���v���C���[�̑O�Ɏ����Ă���B
	if (m_player->GetPlayerState() == enHaveBurger) {
		//�v���C���[�̈ړ������Ƀn���o�[�K�[�������Ă���B
		plPos += plSpeed;
		m_beHadPos = plPos;
		//�����𒲐��B
		m_beHadPos.y += AJUST_HEIGHT;
		//�J�E���^�\�ɒu����Ă��Ȃ��Ƃ��A�v���C���[�̎茳�ɗ���悤�Ɉʒu�����B
		if (m_putOnCounter == false) {
			m_position = m_beHadPos;
		}
	}
}

void Burger::ClearNo()
{
	//�J�E���^�[�ɕۑ�����Ă���ς񂾋�ނ́h���h���O�ɁB
	m_counter->SetStack0();
	//�v���C���[�ɕۑ����Ă���ς񂾋�ނ������Ȃ���ԁi�X�j�ŏ���������B
	for (int i = 0;i < m_player->GetMaxNumCanSaveGuzaiType(); i++) {
		m_player->ClearSpecificGuzaiNo(i);
	}
}

void Burger::SetOnTrashCan() 
{
	//�S�~���Ƃ̋��������ȉ���A�{�^���������ꂽ��
	if (g_pad[m_burgerNo]->IsTrigger(enButtonA)
		&& m_trashCan->GetCanTrash()) {
		//�n���o�[�K�[���S�~���ɃZ�b�g����Ă����Ԃɂ���B
		m_isSetOnTrashCan = true;
	}
	//�n���o�[�K�[���S�~���ɃZ�b�g����Ă�����
	if (m_isSetOnTrashCan == true) {
		m_decrementTime--;
		//�x�������������
		if (m_decrementTime <= 0) {
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/dumping.wav", false);
			se->SetVolume(SE_VOLUME);
			se->Play(false);
			//
			//m_burgerExist = false;
			m_player->SetPlayerState(enNothing);
			m_decrementTime = DEFAULT_DECREMENT_TIME;
			ClearNo();

			m_trashCan->ChangeMovingState(true);

			//�n���o�[�K�[������
			DeleteGO(this);
		}
		//�����܂ł̓S�~���̏�őҋ@������B
		m_position = m_trashCan->GetPosition();
		m_position.y += AJUST_HEIGHT;
	}
}

void Burger::Update()
{
	GrabBurger();
	
	SetOnTrashCan();

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_burgerScale);
}
