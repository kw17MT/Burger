#include "stdafx.h"
#include "Dish.h"
#include "SkinModelRender.h"
#include "Level.h"
#include "Guzai.h"
#include "PlayerGene.h"
#include "PathMove.h"

namespace
{
	const float MOVESPEED = 130.0f;
}

bool Dish::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	/*m_skinModelRender->Init("Assets/modelData/gu/egg.tkm", nullptr, enModelUpAxisZ, m_position);*/
	m_skinModelRender->Init("Assets/modelData/object/conveyor.tkm", nullptr, enModelUpAxisZ, m_position);
	Vector3 scale = { 0.2f,0.2f,0.2f };
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);

	SetScale({ 1.0f,0.2f,1.0f });

	playerGene = FindGO<PlayerGene>("playerGene");
	
	m_pathMove = std::make_unique<PathMove>();
	m_pathMove.get()->Init(m_position, MOVESPEED, enNormalLane);

	m_skinModelRender->SetNewModel();

	return true;
}

void Dish::Move()
{
	//�M���E�F�C�|�C���g�ňړ�������B
	m_position = m_pathMove.get()->Move();
	m_skinModelRender->SetPosition(m_position);
	//�Ō�̃|�C���g�܂œ��B������B
	if (m_pathMove.get()->GetIsFinalPoint())
	{
	}

	//��ނ��M�̏�Ɉړ�������
	if (isHavingGuzai == true) {
		m_guzaiPos = m_position;
		m_guzaiPos.y += 10.0f;
		m_guzai->SetPosition(m_guzaiPos);
	}
}

void Dish::Update()
{
	//�ŏ��������ׂĂ̎M�̏�ɏo���B
	if (isCompletedFirstPop == false) {
		if (playerGene->GetPlayerGeneState() == false) {
				m_guzai = NewGO<Guzai>(0);
				isHavingGuzai = true;

				isCompletedFirstPop = true;
		}
	}

	

		//���̂܂܂��ƁA�Ƃ����u�Ԃɂ܂��o���Ă��܂�
		//��ނ�������Ă�����A�M�ɋ�ނ��Ȃ����Ƃ�m�点��B
		//��ނ��Ƃ��Ă���Ԃ����ƃC���N�������g���Ă��܂����ߕϐ����傫���Ȃ肷���Ă����ɕ�[���Ă��܂�

		//��ރf�X�g���N�^��noHavingDish�̕ϐ���1�x�C���N�������g���Ă���B
		if (m_guzai->state == 1) {
			isHavingGuzai = false;
			//playerGene->AddNoHavingDishCounter();
		}

		//��̎M���K�萔��葽���̂ŁA��̎M�����ɕ�[���J�n����B
		if (playerGene->GetNoHavingDishCounter() >= maxNum2Refill) {
			if (isHavingGuzai == false) {
				m_guzai = NewGO<Guzai>(0);
				isHavingGuzai = true;
				
				//��[�����M�̖������P����
				playerGene->AddRefilledNum();
			}
			//��[�����M�̐����󂾂����M�̐��Ɠ����ɂȂ�����A�O�ŏ�����
			if (playerGene->GetRefilledNum() >= maxNum2Refill) {
				playerGene->ResetNohavingDishCounter();
				playerGene->ResetRefilledNum();
			}
		}

		Move();

	//m_skinModelRender->SetScale(m_scale);
}