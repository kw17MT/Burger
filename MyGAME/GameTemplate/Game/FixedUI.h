#pragma once

class FixedUI : public IGameObject
{
private:
	//�\������c�莞��
	int LastTime = 120;
	//�t���[���J�E���g�p�A60�ɂȂ�����LastTime���P���炷�B
	int timer = 0;
	//�^�C���A�b�v�t���O
	bool isTimeUp = false;

	//���ꂼ��̃v���C���[�̃X�R�A
	int score01 = 0;
	int score02 = 0;

	//���ꂼ��̃p�����[�^�[�̍��W
	Vector2 posTime = { -100,350 };
	Vector2 posLastTime = { 50, 350 };

	Vector2 posItem01 = { -600,350 };
	Vector2 posItem02 = { 350, 350 };
	
	Vector2 posScore01 = { -600,-300 };
	Vector2 posScore02 = { 350, -300 };

	RenderContext renderContext = g_graphicsEngine->GetRenderContext();
public:
	//�����Ŗ��t���[��������\�����Ă���B
	void Update();

	int GetTime() { return LastTime; }
};


