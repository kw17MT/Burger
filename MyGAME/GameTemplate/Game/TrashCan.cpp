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
	const float TRASHCAN_EXPAND_RATE = 0.015;
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
	DeleteGO(m_skinModelRender);
	DeleteGO(m_arrow);
}

bool TrashCan::Start()
{
	//string�^�ɕς���char�ɕϊ����邽�߂̏���������B
	std::string endNo_string = std::to_string(trashcanNo);
	//�s�ωӏ����`
	char playerName[PLAYER_NAME_SIZE] = "player0";
	//���[�ԍ�������ǉ�����
	strcat_s(playerName, endNo_string.c_str());
	//�K�v�ȃf�[�^�̒T���Ɗm��
	m_player = FindGO<Player>(playerName);
	m_playerGene = FindGO<PlayerGene>("playerGene");

	//�S�~�����f���̐ݒ�
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/trashcan/trashcan.tkm", nullptr, enModelUpAxisZ, m_position);
	//m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_skinModelRender->InitForCastShadow("Assets/modelData/trashcan/trashcan.tkm", nullptr, enModelUpAxisZ, m_position, nullptr);
	m_skinModelRender->SetScale(m_trashcanScale);

	//�S�~���ɋ߂Â��Ɩ�󂪏o��悤��
	m_arrow = NewGO<SkinModelRender>(0);
	m_arrow->Init("Assets/modelData/Arrow/Arrow_Yellow.tkm", nullptr, enModelUpAxisZ, m_position);
	m_arrow->InitShader("Assets/shader/modelTomei.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_arrow->SetScale(m_targetScale);

	//���̈ʒu���S�~���̏�ɐݒ肵�Ă���
	m_arrowPos = m_position;
	m_arrowPos.y +=AJUST_ARROW_POS_Y;
	m_arrow->SetPosition(m_arrowPos);
	m_arrow->SetRotation(m_rot);

	return true;
}

float TrashCan::CalcDistance(Vector3 v1, Vector3 v2)
{
	Vector3 v3 = v1 - v2;
	float ans = v3.Length();

	return ans;
}

void TrashCan::LetStartMoving()
{
	movingTime--;																				//�����l30
	if (movingTime > TRASHCAN_SHRINK_TIME_MIN && movingTime <= TRASHCAN_SHRINK_TIME_MAX) {		//30~21�@10�t���[��
		m_trashcanScale.y -= TRASHCAN_SHRINK_RATE;												//10 * -0.03f = -0.3f
	}
	if (movingTime > TRASHCAN_EXPAND_TIME_MIN && movingTime <= TRASHCAN_EXPAND_TIME_MAX) {		//20~1�@20�t���[��
		m_trashcanScale.y += TRASHCAN_EXPAND_RATE;												//20 * 0.015f = 0.3f
	}
	if (movingTime <= 0) {
		movingTime = DEFAULT_MOVING_TIME;
		isMoving = false;
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
		std::string endNo_string = std::to_string(trashcanNo);
		//�s�ωӏ����`
		char playerName[PLAYER_NAME_SIZE] = "player0";
		//���[�ԍ�������ǉ�����
		strcat_s(playerName, endNo_string.c_str());
		//�K�v�ȃf�[�^�̒T���Ɗm��
		m_player = FindGO<Player>(playerName);
	}

	//���v���C���[�Ƃ̋����𑪂�B
	float playerDistance = CalcDistance(m_player->GetPosition(), m_position);

	//���̑傫���ύX�p�B�߂Â��Ƒ傫���Ȃ�A�����Ə������Ȃ�B
	if (playerDistance < distance) {
		m_targetScale.x += ARROW_CHANGE_SCALE_RATE;
		m_targetScale.y += ARROW_CHANGE_SCALE_RATE;
		m_targetScale.z += ARROW_CHANGE_SCALE_RATE;

		if (m_targetScale.x >= ARROW_MAX_SCALE) {
			m_targetScale.x = ARROW_MAX_SCALE;
			m_targetScale.y = ARROW_MAX_SCALE;
			m_targetScale.z = ARROW_MAX_SCALE;
		}
		canTrash = true;
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
		canTrash = false;
	}
	m_arrow->SetScale(m_targetScale);

	//���̕��V����
	if (targetUp == true) {
		m_arrowPos.y += ARROW_MOVE_RATE;
		if (m_arrowPos.y >= ARROW_MAX_HEIGHT) {
			targetUp = false;
		}
	}

	if (targetUp == false) {
		m_arrowPos.y -= ARROW_MOVE_RATE;
		if (m_arrowPos.y <= ARROW_MIN_HEIGHT) {
			targetUp = true;
		}
	}

	if (isMoving) {
		LetStartMoving();
	}

	m_arrow->SetPosition(m_arrowPos);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_trashcanScale);
}