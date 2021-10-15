#pragma once
class SpriteRender;
class FixedUI;

class Result : public IGameObject
{
private:
	Vector2 m_position = Vector2::Zero;						//�摜�̈ʒu
	Vector2 m_pivot = {0.5f,0.5f};							//�摜�̒��S
	Vector2 m_scale = { 1.0f,1.0f };										//�摜�̊g�嗦
	const Vector3 m_center = { 0.0f,0.0f,0.0f };			//�����\���p�̈ʒu
	const Vector3 m_left = { 450.0f, 0.0f, 0.0f };			//���\���p�̈ʒu
	const Vector3 m_right = { -450.0f, 0.0f, 0.0f };		//�E�\���p�̈ʒu
	Vector4 m_color = { 1.0f,1.0f,1.0f, 0.0f};				//�����J���[
	Quaternion m_rotation = Quaternion::Identity;			//�摜�̉�]

	const int m_wideth = 512;								//�摜�̏c
	const int m_height = 512;								//�摜�̏c
	int m_spriteNum = 0;										//�ǂ̃X�v���C�g�ɂ��邩�����߂邽�߂̐����l
	int m_positionNum = 0;										//�ǂ̈ʒu�ɕ\�����邩�����߂邽�߂̐����l
	
	float m_alpha = 0.0f;									//�A���t�@�p�ϐ�
	float m_scaleRate = 3.0f;								//�g�嗦�p�ϐ�
	bool m_isReach3Miss = false;							//�ǂ��炩��MISS��3���܂�������TRUE�ɂ���

public:
	~Result();
	
	/**
	 * @brief �摜�̏�����
	*/
	bool Start();

	/**
	 * @brief �k���Ɠ����x�̃A�b�v
	*/
	void Update();

	/**
	 * @brief �V�������W�̐ݒ�
	*/
	void SetPosition(const Vector2& pos) { m_position = pos; }

	/**
	 * @brief �V�������S�̐ݒ�
	*/
	void SetPivot(const Vector2& piv) { m_pivot = piv; }

	/**
	 * @brief �V�����g�嗦�̐ݒ�
	*/
	void SetScale(const Vector2& scl) { m_scale = scl; }

	/**
	 * @brief �V������]�̐ݒ�
	*/
	void SetRotation(const Quaternion& rot) { m_rotation = rot; }

	/**
	 * @brief �ǂ��炩�̃v���C���[��3�~�X�ɂȂ�����
	*/
	void Reach3Miss(bool state) { m_isReach3Miss = state; }

	/**
	 * @brief �Ăяo�����Ƃŉ摜�̎�ނ����肷��
	*/
	void SetSprite(int No) { m_spriteNum = No; }

	/**
	 * @brief �ʒu�ԍ����w�肵�č��W��ݒ肷��
	*/
	void SetSpritePos(int posNo) { m_positionNum = posNo; }

	/**
	 * @brief dds�̐U�蕪���֐�
	*/
	void DecideDDS();

	/**
	 * @brief �ʒu�����肷��
	*/
	void DecidePos();

private:
	FixedUI* m_ui = nullptr;								//�^�C���A�b�v���Ă��邩�m�F���邽�߂̃C���X�^���X
	SpriteRender* m_spriteRender = nullptr;					//�����A�����A���������̉摜
};

