#include "stdafx.h"
#include "PathMove.h"
#include "PlayerGene.h"
#include "SoundSource.h"
#include "CycleDirection.h"

namespace
{
	const float DISTANCE = 50.0f * 50.0f;
}

void PathMove::Init(const Vector3& pos, const float move, EnLane enLane)
{
	m_position = pos;
	m_moveSpeed = move;

	m_position = pos;
	m_moveSpeed = move;
	m_path = PathFactory::GetInstance().GetPath(enLane);
	//��ԍŏ��̃|�C���g���擾����
	//m_point = m_path->GetFirstPoint();
	m_point = m_path->GetNearPoint(m_position);
	m_playerGene = FindGO<PlayerGene>("playerGene");
}

void PathMove::SwitchCycleDirection()
{
	if (m_cycleDirection == enNormal) {
		m_cycleDirection = enReverse;
		m_point = m_path->GetPoint(m_point->s_number - 2);
		if (m_point->s_number <= 0) {
			m_point = m_path->GetPoint(m_wayPointNum - 1);
		}
		Vector3 nextDistance = m_point->s_vector - m_position;
		nextDistance.Normalize();
		m_moveVector = nextDistance;

		//��]�����X�v���C�g(�t�])
		m_directSprite[0] = FindGO<CycleDirection>("dirsp1");
		m_directSprite[0]->ChangeSpriteReverse();
		m_directSprite[0]->SetDirection(Reverse);					//����]
		m_directSprite[0]->SetSide(Left);							//��
		
		m_directSprite[1] = FindGO<CycleDirection>("dirsp2");
		m_directSprite[1]->ChangeSpriteForward();
		m_directSprite[1]->SetDirection(Forward);					//�E��]
		m_directSprite[1]->SetSide(Right);							//�E
		
		m_directSprite[2] = FindGO<CycleDirection>("dirspfixed");	//�Œ�\��
		m_directSprite[2]->ChangeFixedSpriteReverse();
		m_directSprite[2]->SetDirection(FixedReverse);

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
		m_directSprite[0] = FindGO<CycleDirection>("dirsp1");
		m_directSprite[0]->ChangeSpriteForward();
		m_directSprite[0]->SetDirection(Forward);					//�E��]
		m_directSprite[0]->SetSide(Left);							//��
		
		m_directSprite[1] = FindGO<CycleDirection>("dirsp2");
		m_directSprite[1]->ChangeSpriteReverse();
		m_directSprite[1]->SetDirection(Reverse);					//����]
		m_directSprite[1]->SetSide(Right);							//�E

		m_directSprite[2] = FindGO<CycleDirection>("dirspfixed");	//�Œ�\��
		m_directSprite[2]->ChangeFixedSpriteForward();				//���]
		m_directSprite[2]->SetDirection(FixedForward);

		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/mechanical.wav", false);
		se->SetVolume(2.0f);
		se->Play(false);
	}
}

const Vector3& PathMove::Move()
{
	////�ŏI�|�C���g�ɓ��B�����A�����X�e�[�g���ݒ肳��ĂȂ�������B
	//if (m_enMoveState == enFinal || m_enMoveState == enNone)
	//{
	//	//�������Ȃ��B
	//	return m_position;
	//}
	
	//if (!m_playerGene->isMoving) {

		if (m_enMoveState == enStart) {
			m_moveVector = m_point->s_vector - m_position;
			m_moveVector.Normalize();
			m_enMoveState = enMove;
			return m_position;
		}

		if (m_playerGene->GetSubmitBurgerNum() == Num2ChangeCycle) {
			SwitchCycleDirection();
		
		////��]�����X�v���C�g
		//if (m_directSprite[0] == nullptr) {
		//	m_directSprite[0] = NewGO<CycleDirection>(0);
		//	m_directSprite[0]->SetDirection(Forward);
		//	m_directSprite[0]->SetSide(Left);
		//}
		//if (m_directSprite[1] == nullptr) {
		//	m_directSprite[1] = NewGO<CycleDirection>(0);
		//	m_directSprite[1]->SetDirection(Reverse);
		//	m_directSprite[1]->SetSide(Right);
		//}


			m_playerGene->AddChangeCycleNum();
			if (m_playerGene->GetChangeCycleNum() == m_wayPointNum) {
				m_playerGene->ResetSubmitBurgerNum();
				m_playerGene->ResetChangeCycleNum();
			}
		}

		Vector3 distance = m_point->s_vector - m_position;
		if (distance.LengthSq() <= DISTANCE) {
			/*if (m_path->GetIsFinalPoint(m_point->s_number))
			{
				m_enMoveState = enFinal;
				return m_position;
			}*/

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
	//}
	//if(m_playerGene->isMoving){
//		m_moveVector = Vector3::Zero;
//	}

	//TODO GameTime�ɕς���B
	m_position += m_moveVector * 1.0f / 60.0f * m_moveSpeed;
	return m_position;
}
