#include "stdafx.h"
#include "PathMove.h"
#include "PlayerGene.h"
#include "SoundSource.h"
#include "CycleDirection.h"

namespace
{
	const float DISTANCE = 50.0f * 50.0f;
	const int LEFT_CYCLE_SPRITE = 0;
	const int RIGHT_CYCLE_SPRITE = 1;
	const int FIXED_CYCLE_SPRITE = 2;
}

void PathMove::Init(const Vector3& pos, const float move, EnLane enLane)
{
	m_position = pos;
	m_moveSpeed = move;

	m_path = PathFactory::GetInstance().GetPath(enLane);

	m_point = m_path->GetNearPoint(m_position);
	m_playerGene = FindGO<PlayerGene>("playerGene");
}

void PathMove::SwitchCycleDirection()
{
	//�����Ŋ����߂�o�O������Ǝv��
	//�t�]�����ɕς���
	if (m_cycleDirection == enNormal) {
		m_cycleDirection = enReverse;
		//m_point�͎��̖ړI�n�̃E�F�C�|�C���g�ԍ��ł��邩��A�����߂�ɂ�2�}�C�i�X����
		m_point = m_path->GetPoint(m_point->s_number - 2);
		//�E�F�C�|�C���g�ԍ���1~36��36��
		if (m_point->s_number <= 0) {
			m_point = m_path->GetPoint(m_wayPointNum-1);
		}
		Vector3 nextDistance = m_point->s_vector - m_position;
		nextDistance.Normalize();
		m_moveVector = nextDistance;

		//��]�����X�v���C�g(�t�])
		m_directSprite[LEFT_CYCLE_SPRITE] = FindGO<CycleDirection>("dirsp1");
		m_directSprite[LEFT_CYCLE_SPRITE]->ChangeSpriteReverse();
		m_directSprite[LEFT_CYCLE_SPRITE]->SetDirection(Reverse);					//����]
		m_directSprite[LEFT_CYCLE_SPRITE]->SetSide(Left);							//��
		
		m_directSprite[RIGHT_CYCLE_SPRITE] = FindGO<CycleDirection>("dirsp2");
		m_directSprite[RIGHT_CYCLE_SPRITE]->ChangeSpriteForward();
		m_directSprite[RIGHT_CYCLE_SPRITE]->SetDirection(Forward);					//�E��]
		m_directSprite[RIGHT_CYCLE_SPRITE]->SetSide(Right);							//�E
		
		m_directSprite[FIXED_CYCLE_SPRITE] = FindGO<CycleDirection>("dirspfixed");	//�Œ�\��
		m_directSprite[FIXED_CYCLE_SPRITE]->ChangeFixedSpriteReverse();
		m_directSprite[FIXED_CYCLE_SPRITE]->SetDirection(FixedReverse);

		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/mechanical.wav", false);
		se->SetVolume(2.0f);
		se->Play(false);
	}
	else {
		m_cycleDirection = enNormal;
		m_point = m_path->GetPoint(m_point->s_number);
		if (m_point->s_number <= 0) {
			m_point = m_path->GetPoint(1);
		}
		Vector3 nextDistance = m_point->s_vector - m_position;
		nextDistance.Normalize();
		m_moveVector = nextDistance;

		//��]�����X�v���C�g(���])
		m_directSprite[LEFT_CYCLE_SPRITE] = FindGO<CycleDirection>("dirsp1");
		m_directSprite[LEFT_CYCLE_SPRITE]->ChangeSpriteForward();
		m_directSprite[LEFT_CYCLE_SPRITE]->SetDirection(Forward);					//�E��]
		m_directSprite[LEFT_CYCLE_SPRITE]->SetSide(Left);							//��
		
		m_directSprite[RIGHT_CYCLE_SPRITE] = FindGO<CycleDirection>("dirsp2");
		m_directSprite[RIGHT_CYCLE_SPRITE]->ChangeSpriteReverse();
		m_directSprite[RIGHT_CYCLE_SPRITE]->SetDirection(Reverse);					//����]
		m_directSprite[RIGHT_CYCLE_SPRITE]->SetSide(Right);							//�E

		m_directSprite[FIXED_CYCLE_SPRITE] = FindGO<CycleDirection>("dirspfixed");	//�Œ�\��
		m_directSprite[FIXED_CYCLE_SPRITE]->ChangeFixedSpriteForward();				//���]
		m_directSprite[FIXED_CYCLE_SPRITE]->SetDirection(FixedForward);

		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/mechanical.wav", false);
		se->SetVolume(2.0f);
		se->Play(false);
	}
}

const Vector3& PathMove::Move()
{

		if (m_enMoveState == enStart) {
			m_moveVector = m_point->s_vector - m_position;
			m_moveVector.Normalize();
			m_enMoveState = enMove;
			return m_position;
		}

		//��o�����n���o�[�K�[�̐����A��ނ̗����ς���K�萔�ɒB������
		if (m_playerGene->GetSubmitBurgerNum() == Num2ChangeCycle) {
			SwitchCycleDirection();
			//�M��������ς���ɂ��������ăC���N�������g
			m_playerGene->AddChangeCycleNum();
			//�S���̎M�������ς�����
			if (m_playerGene->GetChangeCycleNum() == m_wayPointNum) {
				//���܂܂Œ�o�����n���o�[�K�[�̐������Z�b�g����
				m_playerGene->ResetSubmitBurgerNum();
				//�������C���N�������g�����M�������ς������������Z�b�g����B
				m_playerGene->ResetChangeCycleNum();
			}
		}

		Vector3 distance = m_point->s_vector - m_position;
		if (distance.LengthSq() <= DISTANCE) {
			//���̃p�X�Ɍ����Ă̈ړ��x�N�g�������߂�
			if (m_cycleDirection == enNormal) {
				m_point = m_path->GetPoint(m_point->s_number);
				if (m_point->s_number <= 0) {
					m_point = m_path->GetPoint(1);
				}
				Vector3 nextDistance = m_point->s_vector - m_position;
				nextDistance.Normalize();
				m_moveVector = nextDistance;
			}
			//�����ŋ�ނ̗���𔽓]������
			else if (m_cycleDirection == enReverse) {
				m_point = m_path->GetPoint(m_point->s_number - 2);
				if (m_point->s_number <= 0) {
					m_point = m_path->GetPoint(m_wayPointNum - 1);
				}
				Vector3 nextDistance = m_point->s_vector - m_position;
				nextDistance.Normalize();
				m_moveVector = nextDistance;
			}
		}

	//TODO GameTime�ɕς���B
	m_position += m_moveVector * 1.0f / 60.0f * m_moveSpeed;
	return m_position;
}
