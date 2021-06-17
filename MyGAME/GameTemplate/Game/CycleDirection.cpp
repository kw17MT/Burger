#include "stdafx.h"
#include "CycleDirection.h"
#include "SpriteRender.h"
#include "GameDirector.h"
#include "system/system.h"

namespace{
	const Vector3 SPRITE_RIGHT = { -220.0f, 80.0f,0.0f };
	const Vector3 SPRITE_LEFT = { 220.0f, 80.0f,0.0f };
	const Vector3 SPRITE_UP = { 0.0f, 250.0f,0.0f };
	const Vector4 SPRITE_INVISIBLE = { 1.0f,1.0f,1.0f,0.0f };
	
	const Vector3 FIXEDSPRITE_SCALE = { 0.25f, 0.25f, 1.0f };
	const Vector2 SPRITE_PIVOT = { 0.5f,0.5f };

	const int WIDTH = 512;
	const int HEIGHT = 512;
	const float SPRITE_CYCLE_SPEED = 1.0f / 60.0f;
	const float SPRITE_ANGLE_CHANGE_RATE = 2.0f;
}

CycleDirection::~CycleDirection()
{
	DeleteGO(m_sprite);
}

bool CycleDirection::Start()
{
	m_sprite = NewGO<SpriteRender>(0);

	//�X�v���C�g������
	switch (m_direction) {
	case Forward:
		m_sprite->Init("Assets/Image/forward_dir.dds", WIDTH, HEIGHT);
		break;
	case Reverse:
		m_sprite->Init("Assets/Image/reverse_dir.dds", WIDTH, HEIGHT);
		break;
	case FixedForward:
		m_sprite->Init("Assets/Image/forward.dds", WIDTH, HEIGHT);
		break;
	case FixedReverse:
		m_sprite->Init("Assets/Image/reverse.dds", WIDTH, HEIGHT);
		break;
	defalt:
		break;
	}

	//�\���ꏊ������
	switch (m_side) {
	case Left:
		m_sprite->SetPosition(SPRITE_RIGHT);
		break;
	case Right:
		m_sprite->SetPosition(SPRITE_LEFT);
		break;
	case Up:
		m_sprite->SetPosition(SPRITE_UP);
		break;
	default:
		break;
	}

	//�����ɂ��Ă���
	m_sprite->SetColor(SPRITE_INVISIBLE);
	//�s�{�b�g��ݒ�
	m_sprite->SetPivot(SPRITE_PIVOT);
	m_sprite->SetScale(m_scale);

	return true;
}

void CycleDirection::ChangeSpriteForward()
{
	//��]�������t�]�̂Ƃ��A���]�̃^�C�~���O�Ő��]�X�v���C�g�ɕύX
	if (m_direction == Reverse) {
		m_sprite->Init("Assets/Image/forward_dir.dds", WIDTH, HEIGHT);
	}
}

void CycleDirection::ChangeSpriteReverse()
{
	//��]���������]�̂Ƃ��A�t�]�̃^�C�~���O�ŋt�]�X�v���C�g�ɕύX
	if (m_direction == Forward) {
		m_sprite->Init("Assets/Image/reverse_dir.dds", WIDTH, HEIGHT);
	}
}

void CycleDirection::ChangeFixedSpriteForward()
{
	if (m_direction == FixedReverse) {
		m_sprite->Init("Assets/Image/forward.dds", WIDTH, HEIGHT);
	}
}

void CycleDirection::ChangeFixedSpriteReverse()
{
	if (m_direction == FixedForward) {
		m_sprite->Init("Assets/Image/reverse.dds", WIDTH, HEIGHT);
	}
}

void CycleDirection::Update()
{
	/////////////////////////////////////////////////////
	//���ʕ���
	//�Q�[���v���C���łȂ����Update���������Ȃ�
	if (!GetGameDirector().GetIsGamePlay()) {
		return;
	}

	//�J�n���Ƀt�F�[�h�C������
	m_alpha += SPRITE_CYCLE_SPEED;
	if (m_alpha > 1.0f) {
		m_alpha = 1.0f;
	}
	/////////////////////////////////////////////////////

	/////////////////////////////////////////////////////
	//��]����X�v���C�g�̂Ƃ�
	if (m_direction == Forward || m_direction == Reverse) {
		//��]�p�x�C��
		if (m_direction == Forward) {
			m_angle += SPRITE_ANGLE_CHANGE_RATE;
			if (m_angle > 360.0f) {
				m_angle = 0.0f;
			}
		}
		else if (m_direction == Reverse) {
			m_angle -= SPRITE_ANGLE_CHANGE_RATE;
			if (m_angle < 0.0f) {
				m_angle = 360.0f;
			}
		}

		m_sprite->SetColor(m_finalColor);
	}
	/////////////////////////////////////////////////////

	/////////////////////////////////////////////////////
	//�Œ�\���X�v���C�g�̂Ƃ�
	if (m_direction == FixedForward || m_direction == FixedReverse) {
		m_sprite->SetColor(m_fixedColor);
		m_sprite->SetScale(FIXEDSPRITE_SCALE);
	}
	/////////////////////////////////////////////////////

	m_rotation.SetRotationDeg(Vector3::AxisZ, m_angle);

	m_sprite->SetRotation(m_rotation);
}

