#include "stdafx.h"
#include "CountDown.h"
#include "GameDirector.h"
#include "SoundSource.h"
#include "SpriteRender.h"

namespace
{
	const Vector3 DEFAULT_SCALE = { 2.0f,2.0f,1.0f };
	const Vector4 COUNTDOWN_START_COLOR = { 1.0f,1.0f,1.0f,0.0f };
	const int AJUST_TIMER_SPEED = 2;
	const int COUNTDOWN_SPRITE_WIDTH = 512;
	const int COUNTDOWN_SPRITE_HEIGHT = 512;
	const int COUNTDOWN_PHASE_ONE = 1;
	const int COUNTDOWN_PHASE_TWO = 2;
	const int COUNTDOWN_PHASE_THREE = 3;
	const int COUNTDOWN_PHASE_END = 4;
	const float COUNTDOWN_PHASE1_START = 4.0f;
	const float COUNTDOWN_PHASE1_END = 3.0f;
	const float COUNTDOWN_PHASE2_START = 3.0f;
	const float COUNTDOWN_PHASE2_END = 2.0f;
	const float COUNTDOWN_PHASE3_START = 2.0f;
	const float COUNTDOWN_PHASE3_END = 1.0f;
	const float COUNTDOWN_PHASE_FINAL_START = 1.0f;
	const float COUNTDOWN_PHASE_FINAL_END = 0.0f;
	const float COUNTDOWN_SHRINK_SPEED = 2.0f / 60.0f;
	const float COUNTDOWN_START_SCALE = 2.0f;
	const float SE_VOLUME = 1.0f;
	const float COLOR_ALPHA_RUN_OUT = 0.0f;
}

bool CountDown::Start()
{
	m_spriteRender = NewGO<SpriteRender>(10, "count");
	//�F��ݒ�
	m_spriteRender->SetColor(m_color);
	//���S��ݒ�
	m_spriteRender->SetPivot(m_pivot);
	//�ʒu��ݒ�
	m_spriteRender->SetPosition(m_position);

	//�J�E���g�_�E�����J�n����Ƃ������Ƃ�ݒ肷��B
	GetGameDirector().SetGameScene(enGameCountDown);

	return true;
}

void CountDown::Update()
{
	//1�t���[���ɂ����鎞�Ԃ��擾�i�b�j
	float gameTime = GameTime().GetFrameDeltaTime();

	m_timer -= gameTime / AJUST_TIMER_SPEED;

	//�X�v���C�g�̕s�����x�ƃJ�E���g�_�E���̂��ׂẴt�F�[�Y���I�������Q�[���X�^�[�g
	if (m_timer <= COUNTDOWN_PHASE_FINAL_END && m_alpha <= COLOR_ALPHA_RUN_OUT) {
		//�Q�[�����J�n�������Ƃ�ݒ肷��B
		GetGameDirector().SetGameScene(enGamePlay);
		//�폜
		DeleteGO(this);
	}

	//�X�v���C�g�ύX����
	if (m_spriteRender != nullptr) {
		//�R���o���i�K�B
		if (m_timer <= COUNTDOWN_PHASE1_START && m_timer > COUNTDOWN_PHASE1_END && m_changeCount == COUNTDOWN_PHASE_ONE) {
			//�t�@�C���p�X���R�ŏ�����
			m_spriteRender->Init("Assets/Image/3.dds", COUNTDOWN_SPRITE_WIDTH, COUNTDOWN_SPRITE_HEIGHT);
			//�����ɂ���
			m_alpha = 0.0f;
			//�ŏ��̊g�嗦�ɖ߂�
			m_scale = DEFAULT_SCALE;
			//�摜��ς����񐔂��C���N�������g
			m_changeCount++;
			//����炷����
			m_soundFlag = true;
		}
		//�Q���o���i�K�B
		else if (m_timer <= COUNTDOWN_PHASE2_START && m_timer > COUNTDOWN_PHASE2_END && m_changeCount == COUNTDOWN_PHASE_TWO) {
			m_spriteRender->Init("Assets/Image/2.dds", COUNTDOWN_SPRITE_WIDTH, COUNTDOWN_SPRITE_HEIGHT);
			m_alpha = 0.0f;
			m_scale = DEFAULT_SCALE;
			m_isFadeIn = true;
			m_changeCount++;
			m_soundFlag = true;
		}
		//�P���o���i�K�B
		else if (m_timer <= COUNTDOWN_PHASE3_START && m_timer > COUNTDOWN_PHASE3_END && m_changeCount == COUNTDOWN_PHASE_THREE) {
			m_spriteRender->Init("Assets/Image/1.dds", COUNTDOWN_SPRITE_WIDTH, COUNTDOWN_SPRITE_HEIGHT);
			m_alpha = 0.0f;
			m_scale = DEFAULT_SCALE;
			m_isFadeIn = true;
			m_changeCount++;
			m_soundFlag = true;
		}
		//START���o���i�K
		else if (m_timer <= COUNTDOWN_PHASE_FINAL_START && m_timer > COUNTDOWN_PHASE_FINAL_END && m_changeCount == COUNTDOWN_PHASE_END) {
			m_spriteRender->Init("Assets/Image/start.dds", COUNTDOWN_SPRITE_WIDTH, COUNTDOWN_SPRITE_HEIGHT);
			m_alpha = 0.0f;
			m_scale = DEFAULT_SCALE;
			m_isFadeIn = true;
			m_changeCount++;
			m_soundFlag = true;		
		}
	}

	//�t�F�[�h�C��
	if (m_isFadeIn == true) {
		m_alpha += gameTime;
	}
	//�t�F�[�h�A�E�g
	else {
		m_alpha -= gameTime;
	}

	//�t�F�[�h�C������
	if (m_alpha > 1.0f) {
		m_alpha = 1.0f;
		m_isFadeIn = false;
	}
	else if (m_alpha < 0.0f) {
		m_alpha = 0.0f;
	}

	//�X�P�[���k������
	m_scale.x -= COUNTDOWN_SHRINK_SPEED;
	m_scale.y -= COUNTDOWN_SHRINK_SPEED;
	//�ʏ�̑傫�������ɂȂ�Ȃ��悤�ɂ���B
	if (m_scale.x < 1.0f || m_scale.y < 1.0f) {
		m_scale.x = 1.0f;
		m_scale.y = 1.0f;
	}

	//�J�n���̃J�E���g�_�E���ɉ����ĉ���炷�B
	if (m_timer < COUNTDOWN_PHASE_FINAL_START && m_soundFlag == true) {
		//����炷
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/basketball_buzzer1.wav", false);
		se->SetVolume(SE_VOLUME);
		se->Play(false);
		m_soundFlag = false;
	}
	else if (m_timer < COUNTDOWN_PHASE1_START && m_timer > COUNTDOWN_PHASE_FINAL_START && m_soundFlag == true) {
		//����炷
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init(L"Assets/sound/Time.wav", false);
		se->SetVolume(SE_VOLUME);
		se->Play(false);
		m_soundFlag = false;
	}

	m_color.w = m_alpha;
	m_spriteRender->SetColor(m_color);
	m_spriteRender->SetScale(m_scale);
}