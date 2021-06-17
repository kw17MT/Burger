#pragma once
class SkinModelRender;

class MenuTimer : public IGameObject
{
private:
	Vector3 m_position;											//�^�C�}�[�̈ʒu
	Vector3 m_scale = { 2.8f,1.0f,1.0f };						//�^�C�}�[�̊g�嗦�BX���g�債�ĉ����ɂ��Ă���
	Quaternion m_rot = Quaternion::Identity;					//��]

	Light m_lig;												//�^�C�}�[�Ǝ��̃��C�g

	bool m_isTimeUp = false;									//�^�C�}�[���O�ɂȂ�����
public:
	/**
	 * @brief �^�C�}�[�̃C���X�^���X�̔j��
	*/
	~MenuTimer();

	/**
	 * @brief �^�C�}�[�̃��f���̏�����
	 * @return true
	*/
	bool Start();

	/**
	 * @brief �^�C�}�[�̏k���ƐF�̕ω�
	*/
	void Update();

	/**
	 * @brief �V�����ʒu�̐ݒ�
	 * @param pos �V�����ʒu
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }

	/**
	 * @brief �V�����g�嗦�̐ݒ�
	 * @param scale �V�����g�嗦
	*/
	void SetScale(Vector3 scale) { m_scale = scale; }

	/**
	 * @brief �V������]�̐ݒ�
	 * @param rot �V������]��
	*/
	void SetRotation(Quaternion rot) { m_rot = rot; }

	/**
	 * @brief �^�C���A�b�v�������Ԃ�
	 * @return TRUE���^�C���A�b�v����
	*/
	bool GetTimeUpState() { return m_isTimeUp; }

	/**
	 * @brief �^�C���A�b�v�������̐ݒ�
	 * @param state TRUE���^�C���A�b�v����
	*/
	void SetTimeUpState(bool state) { m_isTimeUp = state; }

	/**
	 * @brief �^�C�}�[�̊g�嗦�A�F�������l�ɐݒ肷��B
	*/
	void ResetTimerParam();

private:
	SkinModelRender* m_skinModelRender = nullptr;
};

