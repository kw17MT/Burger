#include "stdafx.h"
#include "Dish.h"
#include "SkinModelRender.h"
#include "Level.h"
#include "Guzai.h"
#include "PlayerGene.h"
#include "PathMove.h"
#include "SoundSource.h"
#include "DishGene.h"
#include "GuzaiManager.h"
#include "DishManager.h"

namespace
{
	const float MOVE_SPEED = 70.0f;
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
	//�M�̃��f�����폜
	DeleteGO(m_skinModelRender);
	
	//���̎M���o������ނ����ׂč폜�̂���
	for (Guzai* guzai : m_guzai)
	{
		DeleteGO(guzai);
	}
	//�S�Ă̋�ނ̗v�f��S�폜
	m_guzai.clear();
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
	//m_skinModelRender->Init("Assets/modelData/object/dish.tkm", nullptr, enModelUpAxisZ, m_position, &m_lig);
	m_skinModelRender->InitForRecieveShadow("Assets/modelData/dish/dish.tkm", nullptr, enModelUpAxisZ, m_position, nullptr);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->InitForCastShadow("Assets/modelData/dish/dish.tkm", nullptr, enModelUpAxisZ, m_position);
	m_playerGene = FindGO<PlayerGene>("playerGene");
	m_dishGene = FindGO<DishGene>("dishGene");

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
		m_guzaiPos.y += m_guzaiYPos;
		m_guzai.back()->SetPosition(m_guzaiPos);
		//�ă|�b�v���s���āA��ނ��M�̂��Ȃ荂���ʒu�ɂ���Ƃ�
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
			//��ڂ̋�ނ��o���B
			m_guzai.push_back(NewGO<Guzai>(0));
			//���̎M�͋�ގ����Ă���B
			m_isHavingGuzai = true;
			//�ŏ��̃|�b�v�����������B
			m_isCompletedFirstPop = true;
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
	if (m_guzai.back()->GetisHadState() == true) {
		m_isHavingGuzai = false;
	}

	//��[����悤�ɖ��߂��ꂽ��
	if (GuzaiManager::GetInstance().IsOrderedRefill()) {
		//��������܂ł̒x���𔭐�������
		m_guzaiTimer++;
		if (m_guzaiTimer > GUZAI_POP_DELAY) {
			//���̎M�͋�ނ������Ă��Ȃ�������
			if (m_isHavingGuzai == false) {
				//�ǉ��̋�ނ��o���B
				m_guzai.push_back(NewGO<Guzai>(0));
				m_isHavingGuzai = true;
				//��[�����M�̖������P����
				GuzaiManager::GetInstance().AddRefilledGuzaiNum();
			}
			//��[�����M�̐����󂾂����M�̐��Ɠ����ɂȂ�����A�O�ŏ�����
			if (GuzaiManager::GetInstance().GetRefilledGuzaiNum() >= GuzaiManager::GetInstance().GetEmptyDishNum()) {
				//��̎M�A��[�����񐔂��O�Ƀ��Z�b�g����B
				GuzaiManager::GetInstance().ResetParamAboutDishAndRefill();
				//���߂��u�������Ȃ��v�ɂ��Ă���
				GuzaiManager::GetInstance().SetNothingOrder();
				m_dishGene->SetFallingSound(false);
				m_dishGene->SetSetSound(false);
			}
			m_guzaiTimer = 0;
		}
	}

	if (DishManager::GetInstance().GetSpeedUpState() == true/*m_speedManeger->GetSpeedUpState() == true*/) {
		float moveSpeed = MOVE_SPEED * 2.0f;
		m_pathMove.get()->ChangeMoveSpeed(moveSpeed);
	}
	else{
		m_pathMove.get()->ChangeMoveSpeed(MOVE_SPEED);
	}

	Move();

	m_skinModelRender->SetScale(m_scale);
}