#pragma once
class SpriteRender;


enum EnDirection {
	Forward,		//��]�X�v���C�g���]
	Reverse,		//��]�X�v���C�g�t�]
	FixedForward,	//�Œ�\���X�v���C�g���]
	FixedReverse,	//�Œ�\���X�v���C�g�t�]
};

enum EnSide {
	Left,			//��
	Right,			//�E
	Up				//��ʏ㕔
};

class CycleDirection : public IGameObject
{
public:
	CycleDirection() {};
	~CycleDirection();

	/**
	 * @brief �摜�̏�����
	 * @return true
	*/
	bool Start();

	/**
	 * @brief �摜�̉�]���s��
	*/
	void Update();
	
	/**
	 * @brief ���]�摜�ɕύX����B
	*/
	void ChangeSpriteForward();

	/**
	 * @brief �t�]�摜�ɕύX����B
	*/
	void ChangeSpriteReverse();

	/**
	 * @brief �Œ肳�ꂽ��]�̌�����\���摜�𐳓]�p�ɂ���B
	*/
	void ChangeFixedSpriteForward();

	/**
	 * @brief �t�]�p�ɂ���B
	*/
	void ChangeFixedSpriteReverse();

	/**
	 * @brief ��]�����̌�����ݒ肷��
	 * @param enDirection �V������]�̌���
	*/
	void SetDirection(const EnDirection& enDirection) { m_direction = enDirection; }

	/**
	 * @brief �E�������ǂ���ɕ\�������邩
	 * @param enSide enSide�Q��
	*/
	void SetSide(const EnSide& enSide) { m_side = enSide; }
	
	/**
	 * @brief ��]�̕�����Ԃ�
	 * @return ��]�̕���
	*/
	EnDirection GetDirection() const { return m_direction; }

	/**
	 * @brief �ǂ���ɕ\������Ă��邩�Ԃ�
	 * @return �\���ʒu
	*/
	EnSide GetSide() const { return m_side; }

private:
	Vector4 m_finalColor = { 2.0f,2.0f,2.0f,m_alpha };	//��]�̉摜�̐F
	Vector4 m_fixedColor = { 1.0f,1.0f,1.0f,m_alpha };	//�Œ肷��摜�̐F
	Vector3 m_scale = { 0.5f,0.5f,1.0f };						//�g�嗦
	Vector3 m_position = Vector3::Zero;							//�摜�̈ʒu
	Quaternion m_rotation = Quaternion::Identity;				//��]
	float m_angle = 0.0f;										//��]�̗�
	float m_alpha = 0.0f;										//�摜�̓����x
	EnDirection m_direction = Forward;							//��]�̌���
	EnSide m_side = Left;										//��]�̏ꏊ

	SpriteRender* m_sprite = nullptr;							//�摜
};

