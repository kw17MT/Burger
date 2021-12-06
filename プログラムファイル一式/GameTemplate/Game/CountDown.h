#pragma once
class SpriteRender;

class CountDown : public IGameObject
{
private:
	Vector4 m_color = { 1.0f,1.0f,1.0f,0.0f };					//�摜�̃J���[
	Vector3 m_position = { 0.0f,100.0f,0.0f };					//�摜�̈ʒu
	Vector3 m_scale = { 2.0f,2.0f,2.0f };						//�摜�̏����g�嗦
	Vector2 m_pivot = { 0.5f,0.5f };							//�摜�̒��S
	bool m_soundFlag = false;									//���݂Ȃ�炩�̉��͂Ȃ��Ă��邩�i�J�E���g�_�E���֌W�j
	bool m_isFadeIn = true;										//�t�F�[�h�A�E�g���J�n���邩
	int m_changeCount = 1;										//�J�E���g�_�E����
	float m_alpha = 0.0f;										//
	float m_timer = 4.0f;										//�J�E���g�_�E���p�B
public:
	bool Start();
	void Update();
private:
	SpriteRender* m_spriteRender = nullptr;
};

