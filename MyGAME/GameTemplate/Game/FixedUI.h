#pragma once
class FontRender;

class FixedUI : public IGameObject
{
private:
	//�\������c�莞��
	int remainingTime =10;
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
	//�^�C���A�b�v��Ԃ̕\��
	Vector2 posTimeUpText = {-100,300};
	Vector2 posTimeUpState = { 100,300 };

	Vector2 posItem01 = { -600,350 };
	Vector2 posItem02 = { 350, 350 };
	
	Vector2 posScore01 = { -600,-300 };
	Vector2 posScore02 = { 350, -300 };

	RenderContext renderContext = g_graphicsEngine->GetRenderContext();
public:
	
	bool Start();
	//�����Ŗ��t���[��������\�����Ă���B
	void Update();

	//�^�C���A�b�v�t���O�̏�Ԃŕ������ύX
	const wchar_t* TurnTimeUpState();

	//�Q�b�^�[
	//�^�C���A�b�v��Ԃ��擾(true : ON , false : OFF)
	bool GetIsTimeUp() { return isTimeUp; }
	int GetTime() { return remainingTime; }

	void RemainingTimeColor();

	//�ω������Ȃ�����
	//Time,TimeUp,Score,Item�̌Œ蕶��
	FontRender* TextTime;
	FontRender* TextTimeUp;
	FontRender* TextScore[2];
	FontRender* TextItem[2];
	//�ω����镶���B
	//�������ԁA�^�C���A�b�v��ONOFF
	FontRender* Time;
	FontRender* isTimeUpState;
	
};


