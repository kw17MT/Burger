#include "stdafx.h"
#include "TrashCan.h"
#include "SkinModelRender.h"
#include "Player.h"
#include "PlayerGene.h"

namespace
{
	const int PLAYER_NAME_SIZE = 9;
	const float AJUST_ARROW_POS_Y = 300.0f;
	const int TRASHCAN_SHRINK_TIME_MAX = 30;
	const int TRASHCAN_SHRINK_TIME_MIN = 20;
	const int TRASHCAN_EXPAND_TIME_MAX = 20;
	const int TRASHCAN_EXPAND_TIME_MIN = 0;
	const float TRASHCAN_SHRINK_RATE = 0.03f;
	const float TRASHCAN_EXPAND_RATE = 0.015f;
	const int DEFAULT_MOVING_TIME = 30;
	const float ARROW_CHANGE_SCALE_RATE = 0.1f;
	const float ARROW_MAX_SCALE = 1.0f;
	const float ARROW_MIN_SCLAE = 0.0f;
	const float ARROW_MAX_HEIGHT = 175.0f;
	const float ARROW_MIN_HEIGHT = 150.0f;
	const float ARROW_MOVE_RATE = 1.0f;
}

TrashCan::~TrashCan()
{
	//�S�~�����폜
	DeleteGO(m_skinModelRender);
	//�����폜
	DeleteGO(m_arrow);
}

bool TrashCan::Start()
{
	//string�^�ɕς���char�ɕϊ����邽�߂̏���������B
	std::string endNo_string = std::to_string(m_trashcanNo);
	//�s�ωӏ����`
	char playerName[PLAYER_NAME_SIZE] = "player0";
	//���[�ԍ�������ǉ�����
	strcat_s(playerName, endNo_string.c_str());
	//�K�v�ȃf�[�^�̒T���Ɗm��
	m_player = FindGO<Player>(playerName);
	m_playerGene = FindGO<PlayerGene>("playerGene");

	//�S�~�����f���̐ݒ�
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//�ʏ�`��p���f���̏�����
	m_skinModelRender->InitForRecieveShadow("Assets/modelData/trashcan/trashcan.tkm", nullptr, enModelUpAxisZ, m_position);
	//�e�����p�̏�����
	m_skinModelRender->InitForCastShadow("Assets/modelData/trashcan/trashcan.tkm", nullptr, enModelUpAxisZ, m_position);
	//�g�嗦�𒲐�
	m_skinModelRender->SetScale(m_trashcanScale);

	//�S�~���ɋ߂Â��Ɩ�󂪏o��悤��
	m_arrow = NewGO<SkinModelRender>(0);
	//�ʏ탂�f���̏�����
	m_arrow->InitForRecieveShadow("Assets/modelData/Arrow/Arrow_Yellow.tkm", nullptr, enModelUpAxisZ, m_position);
	//�V���h�E�L���X�g�p�̏�����
	m_arrow->InitForCastShadow("Assets/modelData/Arrow/Arrow_Yellow.tkm", nullptr, enModelUpAxisZ, m_position);
	//�g�嗦�𒲐�
	m_arrow->SetScale(m_targetScale);

	//���̈ʒu���S�~���̏�ɐݒ肵�Ă���
	m_arrowPos = m_position;
	//�S�~���̏�����ɒ���
	m_arrowPos.y +=AJUST_ARROW_POS_Y;
	//���̈ʒu���X�V
	m_arrow->SetPosition(m_arrowPos);
	m_arrow->SetRotation(m_rot);

	return true;
}

void TrashCan::LetStartMoving()
{
	//�S�~���������Ă���Ƃ�
	if (m_isMoving) {
		m_movingTime--;																					
		//Y���W�ɂ�����g�嗦�����������Ăւ��܂���														//�����l30
		if (m_movingTime > TRASHCAN_SHRINK_TIME_MIN && m_movingTime <= TRASHCAN_SHRINK_TIME_MAX) {		//30~21�@10�t���[��
			m_trashcanScale.y -= TRASHCAN_SHRINK_RATE;													//10 * -0.03f = -0.3f
		}
		if (m_movingTime > TRASHCAN_EXPAND_TIME_MIN && m_movingTime <= TRASHCAN_EXPAND_TIME_MAX) {		//20~1�@20�t���[��
			m_trashcanScale.y += TRASHCAN_EXPAND_RATE;													//20 * 0.015f = 0.3f
		}
		if (m_movingTime <= 0) {
			m_movingTime = DEFAULT_MOVING_TIME;
			m_isMoving = false;
		}
	}
}

void TrashCan::ChangeArrowScale()
{
	//�v���C���[�Ƃ̋����𑪂�B
	float playerDistance = CalcDistance(m_player->GetPosition(), m_position);

	//���̑傫���ύX�p�B�߂Â��Ƒ傫���Ȃ�A�����Ə������Ȃ�B
	if (playerDistance < m_distance) {
		m_targetScale.x += ARROW_CHANGE_SCALE_RATE;
		m_targetScale.y += ARROW_CHANGE_SCALE_RATE;
		m_targetScale.z += ARROW_CHANGE_SCALE_RATE;

		if (m_targetScale.x >= ARROW_MAX_SCALE) {
			m_targetScale.x = ARROW_MAX_SCALE;
			m_targetScale.y = ARROW_MAX_SCALE;
			m_targetScale.z = ARROW_MAX_SCALE;
		}
		m_canTrash = true;
	}
	else {
		m_targetScale.x -= ARROW_CHANGE_SCALE_RATE;
		m_targetScale.y -= ARROW_CHANGE_SCALE_RATE;
		m_targetScale.z -= ARROW_CHANGE_SCALE_RATE;

		if (m_targetScale.x <= ARROW_MIN_SCLAE) {
			m_targetScale.x = ARROW_MIN_SCLAE;
			m_targetScale.y = ARROW_MIN_SCLAE;
			m_targetScale.z = ARROW_MIN_SCLAE;
		}
		m_canTrash = false;
	}
}

void TrashCan::FloatArrow()
{
	//���̕��V����
	if (m_targetUp == true) {
		m_arrowPos.y += ARROW_MOVE_RATE;
		if (m_arrowPos.y >= ARROW_MAX_HEIGHT) {
			m_targetUp = false;
		}
	}

	if (m_targetUp == false) {
		m_arrowPos.y -= ARROW_MOVE_RATE;
		if (m_arrowPos.y <= ARROW_MIN_HEIGHT) {
			m_targetUp = true;
		}
	}
}

void TrashCan::Update()
{
	//�v���C���[�����S�ɏo��������IF���ȍ~�̏������s��
	if (m_playerGene->GetPlayerGeneState() == true) {
		return;
	}

	//�v���C���[�̏�񂪊m�肵�Ȃ��܂܂̎������邽�߁A�ŏI�m�F
	if (m_player == nullptr) {
		//string�^�ɕς���char�ɕϊ����邽�߂̏���������B
		std::string endNo_string = std::to_string(m_trashcanNo);
		//�s�ωӏ����`
		char playerName[PLAYER_NAME_SIZE] = "player0";
		//���[�ԍ�������ǉ�����
		strcat_s(playerName, endNo_string.c_str());
		//�K�v�ȃf�[�^�̒T���Ɗm��
		m_player = FindGO<Player>(playerName);
	}

	//�v���C���[�Ƃ̋����ɉ����Ė��̊g�嗦��ω�������B
	ChangeArrowScale();

	//���̕��V
	FloatArrow();

	//�S�~���ɉ��������ꂽ�Ƃ��Ƀ��A�N�V����������B
	LetStartMoving();

	m_arrow->SetPosition(m_arrowPos);
	m_arrow->SetScale(m_targetScale);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_trashcanScale);
}