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
#include "GameDirector.h"

namespace
{
	const float MOVE_SPEED = 70.0f;
	const float DROP_POS_PHASE1 = 800.0f;
	const float DROP_SPEED_PHASE1 = 4.0f;
	const float DROP_POS_PHASE2 = 10.0f;
	const float DROP_SPEED_PHASE2 = 20.0f;
	const float DROP_POS_TOP = 1000.0f;
	const float SE_FALLING_VOLUME = 0.3f;
	const float SE_VOLUME = 0.1f;
	const float SE_FIRST_POP_VOLUME = 0.02f;
	const int GUZAI_POP_DELAY = 60;
}

Dish::~Dish()
{
	//���̎M���o������ނ����ׂč폜�̂���
	for (Guzai* guzai : m_guzai)
	{
		if (guzai != nullptr) {
			DeleteGO(guzai);
		}
	}
	//�S�Ă̋�ނ̗v�f��S�폜
	m_guzai.clear();

	//�M�̃��f�����폜
	DeleteGO(m_skinModelRender);
}

bool Dish::Start()
{
	//�M�̃��f��������
	m_skinModelRender = NewGO<SkinModelRender>(0,"dish");
	//�V���h�E���V�[�o�[�̃I�u�W�F�N�g��������
	m_skinModelRender->InitForRecieveShadow("Assets/modelData/dish/dish2.tkm", nullptr, enModelUpAxisZ, m_position);
	//�V���h�E�L���X�^�[�̃I�u�W�F�N�g��������
	m_skinModelRender->InitForCastShadow("Assets/modelData/dish/dish2.tkm", nullptr, enModelUpAxisZ, m_position);
	//�v���C���[������̃I�u�W�F�N�g���擾
	m_playerGene = FindGO<PlayerGene>("playerGene");
	//�M������̃I�u�W�F�N�g���擾
	m_dishGene = FindGO<DishGene>("dishGene");

	m_pathMove = std::make_unique<PathMove>();
	m_pathMove.get()->Init(m_position, MOVE_SPEED, enNormalLane);

	//�g�嗦��ݒ�
	m_skinModelRender->SetScale(m_scale);

	return true;
}

void Dish::Move()
{
	//�M���E�F�C�|�C���g�ňړ�������B
	m_position = m_pathMove.get()->Move();
	//�ʒu���X�V
	m_skinModelRender->SetPosition(m_position);
	//�Ō�̃|�C���g�܂œ��B������B
	if (m_pathMove.get()->GetIsFinalPoint())
	{
	}
}

void Dish::PopGuzaiOnDish()
{
	//���̎M�͋�ނ������Ă���Ȃ�
	//��ނ̃|�b�v���ɌĂ΂��
	if (m_isHavingGuzai == true) {
		if (m_popedSound)
		{
			//����炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/thi-n.wav", false);
			se->SetVolume(SE_VOLUME);
			se->Play(false);
			//�|�b�v�����u�Ԃ�1�񂾂�����点�΂����̂ł�����FALSE��
			m_popedSound = false;
		}
		//��ނ̈ʒu���M�̏��
		m_guzaiPos = m_position;
		//Y���̈ʒu�����ɉ��Z
		m_guzaiPos.y += m_guzaiYPos;
		//�����̏�ɏo���������Ƃ̂����ނōŌ�ɏo�Ă�����̈ʒu���X�V
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
				se->SetVolume(SE_FALLING_VOLUME);
				se->Play(false);
				m_dishGene->SetFallingSound(true);
			}
		}
	}
	else {
		//���|�b�v���Ă����ނ̂��߂Ƀf�t�H���g�l�ŏ�����
		m_guzaiYPos = DROP_POS_TOP;
	}
}

void Dish::ShouldRefill()
{
	//��[����悤�ɖ��߂��ꂽ��
	if (GuzaiManager::GetInstance().IsOrderedRefill()) {
		if (!m_isHavingGuzai)
		{
			m_guzaiYPos = DROP_POS_TOP;
		}

		//��������܂ł̒x���𔭐�������
		m_guzaiTimer++;
		if (m_guzaiTimer > GUZAI_POP_DELAY) {
			//���̎M�͋�ނ������Ă��Ȃ�������
			if (m_isHavingGuzai == false) {
				//�ǉ��̋�ނ��o���B
				m_guzai.push_back(NewGO<Guzai>(0));
				m_isHavingGuzai = true;
				m_popedSound = true;
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
			}
			m_guzaiTimer = 0;
		}
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

			//�ŏ��ɉ����Ȃ炷
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init(L"Assets/sound/thi-n.wav", false);
			se->SetVolume(SE_FIRST_POP_VOLUME);
			se->Play(false);
		}
	}

	if (GetGameDirector().GetGameScene() == enResult)
	{
		return;
	}
	
	//�����̏�̋�ނ�������Ă���Ȃ��
	if (m_guzai.back()->GetisHadState() == true) {
		m_isHavingGuzai = false;
	}

	//��[�̖��߂����Ă����玩�g�̏�ɋ�ނ��[
	ShouldRefill();

	//�M�̈ړ����x�A�b�v�̖��߂����Ă�����
	if (DishManager::GetInstance().GetSpeedUpState() == true) {
		//�ړ����x��2�{�ɂ���B
		float moveSpeed = MOVE_SPEED * 2.0f;
		m_pathMove.get()->ChangeMoveSpeed(moveSpeed);
	}
	else{
		//���߂��I�������or���Ă��Ȃ���Βʏ푬�x�ɂ���B
		m_pathMove.get()->ChangeMoveSpeed(MOVE_SPEED);
	}

	//�ړ�����
	Move();

	//��ނ��M�̏�ɏo���B
	PopGuzaiOnDish();

	//�g�嗦�̍X�V
	m_skinModelRender->SetScale(m_scale);
}