#pragma once
class SpriteRender;
class FixedUI;

class Result : public IGameObject
{
private:
	//�e��p�����[�^
	Vector2 m_position = Vector2::Zero;
	Vector2 m_pivot = Vector2::Zero;
	Vector2 m_scale;
	Quaternion m_rotation = Quaternion::Identity;

	//�����A���A�E�̉摜�\���ʒu�p�ϐ���p��
	//�X�v���C�g�����_�[��SetPosition�̈�����Vector3�Ȃ̂�Vector3�^�Ƃ���
	Vector3 center = Vector3::Zero;
	Vector3 left = Vector3::Zero;
	Vector3 right = Vector3::Zero;
	
	//�摜�̏c���𑜓x��萔�Ō��߂Ă���
	const int wideth = 512;
	const int height = 512;

	//�^�C���A�b�v�t���O
	bool isTimeUp = false;
	//�ǂ̃X�v���C�g�ɂ��邩�����߂邽�߂̐����l
	int spriteNum;
	//�ǂ̈ʒu�ɕ\�����邩�����߂邽�߂̐����l
	int positionNum;
	
	//�ǂ��炩��MISS��3���܂�������TRUE�ɂ���
	bool isReach3Miss = false;

	//
	bool tf = false;

	//�A���t�@�p�ϐ�
	float m_alpha = 0.0f;
	//�g�嗦�p�ϐ�
	float m_scaleRate = 3.0f;

public:

	//UI
	FixedUI* m_ui = nullptr;
	//�X�v���C�g�����_�[
	SpriteRender* m_spriteRender = nullptr;

	//�R���X�g���N�^�Ȃ�
	~Result();
	bool Start();
	void Update();

	//�Q�b�^�[�e��
	Vector2 GetPos() { return m_position; }
	Vector2 GetPivot() { return m_pivot; }
	Vector2 GetScale() { return m_scale; }
	Quaternion GetRotation() { return m_rotation; }
	bool GetIsTimeUp() { return isTimeUp; }

	//�Z�b�^�[
	void SetPosition(const Vector2& pos) { m_position = pos; }
	void SetPivot(const Vector2& piv) { m_pivot = piv; }
	void SetScale(const Vector2& scl) { m_scale = scl; }
	void SetRotation(const Quaternion& rot) { m_rotation = rot; }
	void SetIsTimeUp() { isTimeUp = true; }
	void Reach3Miss(bool state) { isReach3Miss = state; }

	//�ǂ̃X�v���C�g�ɂ��邩�Ăяo�����Ō��߂Ă��炤���߂̊֐�
	void SetSprite(const int& No) { spriteNum = No; }
	//�ǂ̈ʒu�ɕ\�����邩�Ăяo�����Ō��߂Ă��炤���߂̊֐�
	void SetSpritePos(const int& posNo) { positionNum = posNo; }
	
	//dds�̐U�蕪���֐�
	void DecideDDS();
	//�X�v���C�g�̈ʒu�����߂�֐�
	void DecidePos();
};

