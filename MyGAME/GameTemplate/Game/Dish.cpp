#include "stdafx.h"
#include "Dish.h"
#include "SkinModelRender.h"
#include "Level.h"
#include "Guzai.h"
#include "PlayerGene.h"
#include "PathMove.h"
#include "DishSpeedManeger.h"
#include "SoundSource.h"
#include "DishGene.h"
#include "GuzaiGene.h"

namespace
{
	const float MOVE_SPEED = 130.0f;
	const float LIGHT_DIRECTION_PISITIVE = 1.0f;
	const Vector3 LIGHT_DIRECTION_RIGHTER = { 100.0f,100.0f,100.0f };
	const float DROP_POS_PHASE1 = 800.0f;
	const float DROP_SPEED_PHASE1 = 4.0f;
	const float DROP_POS_PHASE2 = 10.0f;
	const float DROP_SPEED_PHASE2 = 20.0f;
	const float DROP_POS_TOP = 1000.0f;
	const float SE_VOLUME = 0.5f;
	const Vector3 AJUST_AMBIENTLIGHT = { 0.98f,0.98f,0.98f };
	const int GUZAI_POP_DELAY = 60;
	const int MAX_GUZAI_POP_NUM = 99;
}

Dish::~Dish()
{
	DeleteGO(m_skinModelRender);
	

	if (m_guzai != nullptr) {
		DeleteGO(m_guzai);
	}
}

bool Dish::Start()
{
	//�M�A���L�̃��C�g��ݒ肷��B
	m_lig.ambientLight.Set(AJUST_AMBIENTLIGHT);
	m_lig.directionalLight.direction.x = LIGHT_DIRECTION_PISITIVE;
	m_lig.directionalLight.direction.y = LIGHT_DIRECTION_PISITIVE;
	m_lig.directionalLight.direction.z = LIGHT_DIRECTION_PISITIVE;
	m_lig.directionalLight.color.Set(LIGHT_DIRECTION_RIGHTER);
	m_lig.directionalLight.direction.Normalize();

	//�M�̃��f��������
	m_skinModelRender = NewGO<SkinModelRender>(0,"dish");
	m_skinModelRender->Init("Assets/modelData/object/dish.tkm", nullptr, enModelUpAxisZ, m_position, &m_lig);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);

	
	m_playerGene = FindGO<PlayerGene>("playerGene");
	m_speedManeger = FindGO<DishSpeedManeger>("speedManeger");
	m_dishGene = FindGO<DishGene>("dishGene");
	m_guzaiGene = FindGO<GuzaiGene>("GuzaiGene");

	m_pathMove = std::make_unique<PathMove>();
	m_pathMove.get()->Init(m_position, MOVE_SPEED, enNormalLane);

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
	if (m_isHavingGuzai == true) {
		m_guzaiPos = m_position;
		//m_guzaiPos.y += 10.0f;
		m_guzaiPos.y += m_guzaiYPos;
		m_guzaiGene->m_guzai[m_guzaiNo]->SetPosition(m_guzaiPos);
		//�ă|�b�v���s���āA�M�̂��Ȃ荂���ʒu�ɂ���Ƃ�
		if (m_guzaiYPos > DROP_POS_PHASE1) {
			//������藎���Ă���B
			m_guzaiYPos -= DROP_SPEED_PHASE1;
		}
		//���ȏ㗎���Ă�����
		else if (m_guzaiYPos > DROP_POS_PHASE2) {
			//�f���������Ă���
			m_guzaiYPos -= DROP_SPEED_PHASE2;
			if (m_dishGene->GetFallingSound() == false) {
				//��������炷
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init(L"Assets/sound/falling2.wav", false);
				se->SetVolume(SE_VOLUME);
				se->Play(false);
				m_dishGene->SetFallingSound(true);
			}
		}
	}
	else {
		m_guzaiYPos = DROP_POS_TOP;
	}
}

void Dish::Update()
{
	//�ŏ��������ׂĂ̎M�̏�ɏo���B
	if (m_isCompletedFirstPop == false) {
		//�v���C���[�͋�ނ���ɂ�������Əo�Ă��邩
		if (m_playerGene->GetPlayerGeneState() == false) {
			for (int i = 0; i < MAX_GUZAI_POP_NUM; i++) {
				//�󂢂Ă���ӏ���������
				if (m_guzaiGene->GetGuzaiFlag(i) == false) {
					m_guzaiGene->m_guzai[i] = NewGO<Guzai>(0);
					m_guzaiGene->m_guzai[i]->SetGuzaiNo(i);
					m_isHavingGuzai = true;
					m_guzaiNo = i;
					m_isCompletedFirstPop = true;
					m_guzaiGene->SetGuzaiFlag(i, true);
					//1�񂾂��o������
					break;
				}
			}
		}
	}
	else {
		if (m_dishGene->GetSetSound() == false) {
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/thi-n.wav", false);
			se->SetVolume(SE_VOLUME);
			se->Play(false);
			m_dishGene->SetSetSound(true);
		}
		
	}
	
	
	//�����̏�̋�ނ�������Ă���Ȃ��
	if (m_guzaiGene->m_guzai[m_guzaiNo]->GetisHadState() == true) {
		m_isHavingGuzai = false;
	}

	//��̎M���K�萔��葽���̂ŁA��̎M�����ɕ�[���J�n����B
	if (m_playerGene->GetNoHavingDishCounter() >= m_maxNum2Refill) {
		m_guzaiTimer++;
		if (m_guzaiTimer > GUZAI_POP_DELAY) {
			if (m_isHavingGuzai == false) {
				for (int i = 0; i < MAX_GUZAI_POP_NUM; i++) {
					if (m_guzaiGene->GetGuzaiFlag(i) == false) {
						m_guzaiGene->m_guzai[i] = NewGO<Guzai>(0);
						m_guzaiGene->m_guzai[i]->SetGuzaiNo(i);
						m_isHavingGuzai = true;
						m_guzaiNo = i;
						m_guzaiGene->SetGuzaiFlag(i, true);
						break;
					}
				}

				//��[�����M�̖������P����
				m_playerGene->AddRefilledNum();
			}
			//��[�����M�̐����󂾂����M�̐��Ɠ����ɂȂ�����A�O�ŏ�����
			if (m_playerGene->GetRefilledNum() >= m_maxNum2Refill) {
				//��̎M�͂O�̂͂�������A�J�E���g�����Z�b�g����B
				m_playerGene->ResetNohavingDishCounter();
				//���ɋ�ނ��[����Ƃ��ɁA�O����J�E���g���������߃J�E���g�����Z�b�g����B
				m_playerGene->ResetRefilledNum();
				m_dishGene->SetFallingSound(false);
				m_dishGene->SetSetSound(false);
			}
			m_guzaiTimer = 0;
		}
	}

	if (m_speedManeger->GetSpeedUpState() == true) {
		float moveSpeed = MOVE_SPEED * 2.0f;
		m_pathMove.get()->ChangeMoveSpeed(moveSpeed);
	}
	if (m_speedManeger->GetSpeedUpState() == false) {
		m_pathMove.get()->ChangeMoveSpeed(MOVE_SPEED);
	}


	Move();

	m_skinModelRender->SetScale(m_scale);
}