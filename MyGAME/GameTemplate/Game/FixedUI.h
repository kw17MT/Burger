#pragma once
class FontRender;
class SpriteRender;
class SoundSource;
class PlayerGene;
class PathMove;

class FixedUI : public IGameObject
{
private:
	int m_remainingTime = 30;							//�\������c�莞��
	int m_timer = 0;									//�t���[���J�E���g�p�A60�ɂȂ�����LastTime���P���炷�B
	bool m_isTimeUp = false;							//�^�C���A�b�v�t���O
public:
	~FixedUI();

	/**
	 * @brief �\������摜�̏�����
	 * @return true
	*/
	bool Start();
	
	/**
	 * @brief �c�莞�Ԃ╶���̕\��
	*/
	void Update();

	/**
	 * @brief �^�C���A�b�v��Ԃ��擾
	 * @return TRUE���^�C���A�b�v���Ă���@FALSE�����ĂȂ�
	*/
	bool GetIsTimeUp() { return m_isTimeUp; }

	/**
	 * @brief �c�莞�Ԃ�ς���
	 * @return �c�莞��
	*/
	int GetTime() { return m_remainingTime; }

	/**
	 * @brief �c���Ԃ����Ȃ��Ƃ��̐F�̕ω�
	*/
	void RemainingTimeColor();

private:
	FontRender* m_textTime = nullptr;								//���Ԃ̕�������
	FontRender* m_textScore[2] = { nullptr, nullptr };				//�X�R�A�̕�������
	FontRender* m_textMiss[2] = { nullptr, nullptr };				//�~�X�̕�������
	FontRender* m_time = nullptr;									//���Ԃ̐�������
	CSoundSource* m_timeSound = nullptr;							//�c�莞�Ԃ킸���̎��ɏo�����p
};


