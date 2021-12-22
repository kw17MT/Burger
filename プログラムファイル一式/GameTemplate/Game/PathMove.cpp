#include "stdafx.h"
#include "PathMove.h"
#include "PlayerGene.h"
#include "SoundSource.h"
#include "CycleDirection.h"
#include "DishManager.h"

namespace
{
	const float DISTANCE = 50.0f * 50.0f;
	const int LEFT_CYCLE_SPRITE = 0;
	const int RIGHT_CYCLE_SPRITE = 1;
	const int FIXED_CYCLE_SPRITE = 2;

	const float SE_VOLUME = 2.0f;
}

//����������Ă���Ƃ���T��
void PathMove::Init(const Vector3& pos, const float move, EnLane enLane)
{
	m_position = pos;
	m_moveSpeed = move;

	m_cycleDirection = enNormal;

	m_path = PathFactory::GetInstance().GetPath(enLane);

	m_point = m_path->GetNearPoint(m_position);
}

void PathMove::SwitchCycleDirection()
{
	//�ʏ�������t�]�����ɕς���
	if (m_cycleDirection == enNormal) {
		m_cycleDirection = enReverse;
		//m_point�͎��̖ړI�n�̃E�F�C�|�C���g�ԍ��ł��邩��A�����߂�ɂ�2�}�C�i�X����
		m_point = m_path->GetPoint(m_point->s_number - 2);
		//�E�F�C�|�C���g�ԍ���1~36��36��
		if (m_point->s_number <= 0) {
			m_point = m_path->GetPoint(m_wayPointNum - 1);
		}
		Vector3 nextDistance = m_point->s_vector - m_position;
		nextDistance.Normalize();
		m_moveVector = nextDistance;

		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/mechanical.wav", false);
		se->SetVolume(0.1f);
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

		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/mechanical.wav", false);
		se->SetVolume(SE_VOLUME);
		se->Play(false);
	}
}

//�������X�v���C�g�݂̂̕ύX�֐����쐬����B
void PathMove::SwitchCycleSpriteDirection()
{
	//�t�]�����ɕς���
	if (m_cycleDirection == enNormal) {
		m_cycleDirection = enReverse;
		//��]�����X�v���C�g(�t�])
		m_directSprite[LEFT_CYCLE_SPRITE] = FindGO<CycleDirection>("dirsp1");
		m_directSprite[LEFT_CYCLE_SPRITE]->ChangeSpriteForward();
		m_directSprite[LEFT_CYCLE_SPRITE]->SetDirection(Forward);					//�E��]
		m_directSprite[LEFT_CYCLE_SPRITE]->SetSide(Left);							//��

		m_directSprite[RIGHT_CYCLE_SPRITE] = FindGO<CycleDirection>("dirsp2");
		m_directSprite[RIGHT_CYCLE_SPRITE]->ChangeSpriteReverse();
		m_directSprite[RIGHT_CYCLE_SPRITE]->SetDirection(Reverse);					//����]
		m_directSprite[RIGHT_CYCLE_SPRITE]->SetSide(Right);							//�E

		m_directSprite[FIXED_CYCLE_SPRITE] = FindGO<CycleDirection>("dirspfixed");	//�Œ�\��
		m_directSprite[FIXED_CYCLE_SPRITE]->SetDirection(FixedReverse);
		m_directSprite[FIXED_CYCLE_SPRITE]->ChangeFixedSpriteForward();				//���]
	}
	else {
		m_cycleDirection = enNormal;
		//��]�����X�v���C�g(���])
		m_directSprite[LEFT_CYCLE_SPRITE] = FindGO<CycleDirection>("dirsp1");
		m_directSprite[LEFT_CYCLE_SPRITE]->ChangeSpriteReverse();
		m_directSprite[LEFT_CYCLE_SPRITE]->SetDirection(Reverse);					//����]
		m_directSprite[LEFT_CYCLE_SPRITE]->SetSide(Left);							//��

		m_directSprite[RIGHT_CYCLE_SPRITE] = FindGO<CycleDirection>("dirsp2");
		m_directSprite[RIGHT_CYCLE_SPRITE]->ChangeSpriteForward();
		m_directSprite[RIGHT_CYCLE_SPRITE]->SetDirection(Forward);					//�E��]
		m_directSprite[RIGHT_CYCLE_SPRITE]->SetSide(Right);							//�E

		m_directSprite[FIXED_CYCLE_SPRITE] = FindGO<CycleDirection>("dirspfixed");	//�Œ�\��
		m_directSprite[FIXED_CYCLE_SPRITE]->SetDirection(FixedForward);
		m_directSprite[FIXED_CYCLE_SPRITE]->ChangeFixedSpriteReverse();
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

	//�M�̗���������ς���ƌ���ꂽ��
	if (DishManager::GetInstance().GetIsOrderedDirection()) {
		//������ς���B
		SwitchCycleDirection();
		//������ς����񐔂��L�^����i�{�P����j
		DishManager::GetInstance().AddCompletedChangeDirectionNum();

		//������ς����񐔂��M�̑����ƈ�v�����Ȃ��
		if (DishManager::GetInstance().JudgeChangedAllDirection()) {
			//�摜�̌���������ς���B
			SwitchCycleSpriteDirection();
			//�S����v�����̂ŁA������ς��閽�߂��~�߂�
			DishManager::GetInstance().SetOrderChangeDirection(false);
			DishManager::GetInstance().ResetCompletedChangeDirectionNum();
		}
	}

	//���W�̔z��͂O�|�R�T
	//��Nuumber�͂P�|�R�U
	//getpoint�֐��̈����͂O�`�Ή�
	Vector3 distance = m_point->s_vector - m_position;
	if (distance.LengthSq() <= DISTANCE) {
		//���̃p�X�Ɍ����Ă̈ړ��x�N�g�������߂�
		if (m_cycleDirection == enNormal) {
			/*if (m_point->s_number <= 0) {
				m_point = m_path->GetPoint(1);
			}
			else
			{
				m_point = m_path->GetPoint(m_point->s_number);
			}*/
			m_point = m_path->GetPoint(m_point->s_number);
			if (m_point->s_number <= 0) {
				m_point = m_path->GetPoint(0);
			}
			Vector3 nextDistance = m_point->s_vector - m_position;
			nextDistance.Normalize();
			m_moveVector = nextDistance;
		}
		//�t�������̈ړ��������v�Z����
		else if (m_cycleDirection == enReverse) {
			/*if (m_point->s_number >= 2)
			{
				m_point = m_path->GetPoint(m_point->s_number - 2);
			}
			else if (m_point->s_number <= 1) {
				m_point = m_path->GetPoint(m_wayPointNum - 1);
			}*/
			m_point = m_path->GetPoint(m_point->s_number - 2);
			if (m_point->s_number <= 0) {
				m_point = m_path->GetPoint(m_wayPointNum - 1);
			}
			Vector3 nextDistance = m_point->s_vector - m_position;
			nextDistance.Normalize();
			m_moveVector = nextDistance;
		}
	}
	float gameTime = GameTime().GetFrameDeltaTime();

	m_position += m_moveVector * gameTime * m_moveSpeed;
	return m_position;
}
