#include "stdafx.h"
#include "TrashCan.h"
#include "SkinModelRender.h"
#include "Player.h"
#include "PlayerGene.h"

bool TrashCan::Start()
{
	player[0] = FindGO<Player>("player01");
	player[1] = FindGO<Player>("player02");
	m_playerGene = FindGO<PlayerGene>("playerGene");

	//�S�~�����f���̐ݒ�
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/trashcan/trashcan.tkm", nullptr, enModelUpAxisZ, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);

	m_skinModelRender->SetScale(m_trashcanScale);
	//�S�~���ɋ߂Â��Ɩ�󂪏o��悤��
	m_targeting = NewGO<SkinModelRender>(0);
	m_targeting->Init("Assets/modelData/Arrow/Arrow_Yellow.tkm", nullptr, enModelUpAxisZ, m_position);
	m_targeting->InitShader("Assets/shader/modelTomei.fx", "FrontCulling", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_targeting->SetScale(m_targetScale);

	if (trashcanNo == 1) {
	m_targetPos = m_position;
	m_targetPos.y += 300.0f;
	m_targeting->SetPosition(m_targetPos);

	m_rot.SetRotationDegY(45.0f);
	}
	if (trashcanNo == 2) {
		m_targetPos = m_position;
		m_targetPos.y += 300.0f;
		m_targeting->SetPosition(m_targetPos);

		m_rot.SetRotationDegY(-45.0f);
	}

	m_targeting->SetRotation(m_rot);

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
	movingTime--;
	if (movingTime > 20 && movingTime <= 30) {
		m_trashcanScale.y -= 0.03f;
	}
	if (movingTime <= 20) {
		m_trashcanScale.y += 0.015f;
	}
	if (movingTime < 0) {
		movingTime = 30;
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
	if (player[0] == nullptr) {
		player[0] = FindGO<Player>("player01");
	}
	if (player[1] == nullptr) {
		player[1] = FindGO<Player>("player02");
	}

	//���v���C���[�Ƃ̋����𑪂�B
	float player01Distance = CalcDistance(player[0]->GetPosition(), m_position);
	float player02Distance = CalcDistance(player[1]->GetPosition(), m_position);

	//���̑傫���ύX�p�B�߂Â��Ƒ傫���Ȃ�A�����Ə������Ȃ�B
	if (trashcanNo == 1) {
		if (player01Distance < distance) {
			m_targetScale.x += 0.1f;
			m_targetScale.y += 0.1f;
			m_targetScale.z += 0.1f;

			if (m_targetScale.x >= 1.0f) {
				m_targetScale.x = 1.0f;
				m_targetScale.y = 1.0f;
				m_targetScale.z = 1.0f;
			}
			canTrash = true;
		}
		else {
			m_targetScale.x -= 0.1f;
			m_targetScale.y -= 0.1f;
			m_targetScale.z -= 0.1f;

			if (m_targetScale.x <= 0.0f) {
				m_targetScale.x = 0.0f;
				m_targetScale.y = 0.0f;
				m_targetScale.z = 0.0f;
			}
			canTrash = false;
		}
		m_targeting->SetScale(m_targetScale);
	}

	if (trashcanNo == 2) {
		if (player02Distance < distance) {
			m_targetScale.x += 0.1f;
			m_targetScale.y += 0.1f;
			m_targetScale.z += 0.1f;

			if (m_targetScale.x >= 1.0f) {
				m_targetScale.x = 1.0f;
				m_targetScale.y = 1.0f;
				m_targetScale.z = 1.0f;
			}
			canTrash = true;
		}
		else {
			m_targetScale.x -= 0.1f;
			m_targetScale.y -= 0.1f;
			m_targetScale.z -= 0.1f;

			if (m_targetScale.x <= 0.0f) {
				m_targetScale.x = 0.0f;
				m_targetScale.y = 0.0f;
				m_targetScale.z = 0.0f;
			}
			canTrash = false;
		}
		m_targeting->SetScale(m_targetScale);
	}

	//���̕��V����
	if (targetUp == true) {
		m_targetPos.y += 1.0f;
		if (m_targetPos.y >= 175.0f) {
			targetUp = false;
		}
	}
	if (targetUp == false) {
		m_targetPos.y -= 1.0f;
		if (m_targetPos.y <= 150.0f) {
			targetUp = true;
		}
	}

	if (trashcanNo == 1) {
		if (isMoving) {
			LetStartMoving();
		}
	}
	if (trashcanNo == 2) {
		if (isMoving) {
			LetStartMoving();
		}
	}

	m_targeting->SetPosition(m_targetPos);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_trashcanScale);
}