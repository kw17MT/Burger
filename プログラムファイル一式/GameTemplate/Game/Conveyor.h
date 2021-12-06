#pragma once
class SkinModelRender;

class Conveyor : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;									//�R���x�A�̈ʒu���W
	const Vector3 m_scale = { 0.8f,1.0f,1.0f };							//�R���x�A�̊g�嗦����
public:

	/**
	 * @brief �R���x�A�̏�����
	 * @return true
	*/
	bool Start();

	/**
	 * @brief �ʒu�̌Œ���s��
	*/
	void Update();

	/**
	 * @brief �R���x�A�̈ʒu��ݒ肷��
	 * @param pos �V�����ʒu���W
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }

private:
	SkinModelRender* m_skinModelRender = nullptr;		//�R���x�A�̃��f��
};	

