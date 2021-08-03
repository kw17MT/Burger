#pragma once
class SkinModelRender;
class Meter : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;				//�Q�[�W�̈ʒu
	Vector3 m_scale = { 1.4f,1.0f,1.0f };			//�Q�[�W�̊g�嗦
	Quaternion m_rot = Quaternion::Identity;		//�Q�[�W�̉�]
public:
	Meter() {};
	
	/**
	 * @brief���[�^�[�̃C���X�^���X�̔j��
	*/
	~Meter();

	/**
	 * @brief �Q�[�W�̃��f���̏�����
	 * @return true
	*/
	bool Start();

	/**
	 * @brief �ύX���ꂽ�A�ʒu�A�g�嗦�A��]�̐ݒ�
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
	 * @brief ���݂̊g�嗦�̊l��
	 * @return ���݂̊g�嗦
	*/
	Vector3 GetScale() const{ return m_scale; }

private:
	SkinModelRender* m_skinModelRender = nullptr;				//���f��
};

