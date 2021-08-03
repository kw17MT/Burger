#include "stdafx.h"
#include "PlayerGene.h"
#include "Player.h"

namespace
{
	const int PLAYER_NUMBER_ONE = 0;
	const int PLAYER_NUMBER_TWO = 1;
	const int PLAYER_MAX_NUM = 2;
}

PlayerGene::~PlayerGene()
{
	//�v���C���[�̍폜
	for (int i = 0; i < PLAYER_MAX_NUM; i++) {
		if (m_player[i] != nullptr) {
			DeleteGO(m_player[i]);
		}
	}
}

void PlayerGene::Update()
{
	//�v���C���[�̐����킪�����Ă���Ƃ�
	if (m_isWorking) {
		//�v���C���[�P�̐���
		m_player[PLAYER_NUMBER_ONE] = NewGO<Player>(0, "player00");
		//�v���C���[�P�̍��W�ݒ�
		m_player[PLAYER_NUMBER_ONE]->SetPosition(m_player01Pos);
		//��ԏ��߂̃v���C���[�̌���������
		m_player01Rot.SetRotationDegY(90.0f);
		m_player[PLAYER_NUMBER_ONE]->SetRotation(m_player01Rot);
		//�v���C���[�ԍ���ݒ肵�Ă��
		m_player[PLAYER_NUMBER_ONE]->SetPlayerNo(PLAYER_NUMBER_ONE);

		//�v���C���[�Q�̐���
		m_player[PLAYER_NUMBER_TWO] = NewGO<Player>(0, "player01");
		m_player[PLAYER_NUMBER_TWO]->SetPosition(m_player02Pos);
		m_player02Rot.SetRotationDegY(270.0f);
		m_player[PLAYER_NUMBER_TWO]->SetRotation(m_player02Rot);
		m_player[PLAYER_NUMBER_TWO]->SetPlayerNo(PLAYER_NUMBER_TWO);

		//���̐�����̓������~�߂�
		m_isWorking = false;
	}
}