#pragma once
class FontRender;
class SoundSource;

class FixedUI : public IGameObject
{
private:
	//�ω������Ȃ�����
	//Time,TimeUp,Score,Item�̌Œ蕶��
	FontRender* TextTime;
	//FontRender* TextTimeUp;
	FontRender* TextScore[2];
	FontRender* TextItem[2];
	//�ω����镶���B
	//�������ԁA�^�C���A�b�v��ONOFF
	FontRender* Time;
	//FontRender* isTimeUpState;
	//�~�X�p�̕���
	FontRender* TextMiss[2] = { nullptr };

	//�\������c�莞��
	int remainingTime = 999;
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
	////�^�C���A�b�v��Ԃ̕\��
	//Vector2 posTimeUpText = {-100,300};
	//Vector2 posTimeUpState = { 100,300 };

	Vector2 posItem01 = { -600,350 };
	Vector2 posItem02 = { 350, 350 };
	
	/*Vector2 posScore01 = { -600,-300 };
	Vector2 posScore02 = { 350, -300 };*/
	Vector2 posScore01 = { -600,-250 };
	Vector2 posScore02 = { 250, -250 };

	//�~�X�\���ʒu
	Vector2 posMiss01 = { -600.0f,-300.0f };
	Vector2 posMiss02 = { 250.0f,-300.0f };

	RenderContext renderContext = g_graphicsEngine->GetRenderContext();
public:
	//�f�X�g���N�^
	~FixedUI();
	bool Start();
	//�����Ŗ��t���[��������\�����Ă���B
	void Update();

	////�^�C���A�b�v�t���O�̏�Ԃŕ������ύX
	//const wchar_t* TurnTimeUpState();

	//�Q�b�^�[
	//�^�C���A�b�v��Ԃ��擾(true : ON , false : OFF)
	bool GetIsTimeUp() { return isTimeUp; }
	int GetTime() { return remainingTime; }
	//�c���Ԃ����Ȃ��Ƃ��̐F�̕ω�
	void RemainingTimeColor();
	CSoundSource* timeSound;
};


