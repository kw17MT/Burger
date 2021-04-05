#pragma once
class FixedUI;
class FontRender;
class CSoundSource;

class Score : public IGameObject
{
private:
	//�^�C���A�b�v�t���O
	bool isTimeUp = false;

	//�ŏI�I�ɕ\������X�R�A
	//��ނ̐� * 100
	int Score01 = 0;
	int Score02 = 0;
	//�J�E���^�[���ŉ��w�̃n���o�[�K�[��񋟂������B
	//�񋟂�����ނ𐔂��Ă����B
	int BasePoint01 = 0;
	int BasePoint02 = 0;

	

	Vector2 Score01Pos = { -400.0f,-300.0f };
	Vector2 Score02Pos = { 550.0f,-300.0f };

	//�X�R�A�̕\���ƁA�X�R�A�̉��Z���̐F�̕ω��Ɏg�p����B
	std::wstring nowScore01 = L"0";
	std::wstring prevScore01 = L"0";
	std::wstring nowScore02 = L"0";
	std::wstring prevScore02 = L"0";

	//�����̐F��ς���ׂ��������łȂ���
	bool isChangeColor01 = false;
	bool isChangeColor02 = false;

	

	RenderContext renderContext = g_graphicsEngine->GetRenderContext();
public:
	
	//ui
	FixedUI* m_ui = nullptr;

	//���s�̏��
	//�v���C���[1
	enum EnResultP1 {
		enResultP1_draw,	//0
		enResultP1_win,		//1
		enResultP1_lose,	//2
		enResultP1Num		//�_�~�[(3)
	}ResultP1;

	//�v���C���[2
	enum EnResultP2 {
		enResultP2_draw,	//0
		enResultP2_win,		//1
		enResultP2_lose,	//2
		enResultP2Num		//�_�~�[(3)
	}ResultP2;


	bool Start();

	//�J�E���^�[����num�����Ă͂߁A�����瑤��BasePoint�ɉ��Z����B
	void SetBasePoint01(int num) { BasePoint01 += num; }
	void SetBasePoint02(int num) { BasePoint02 += num; }
	//�^�C���A�b�v���̌��ʂ��L�^
	void SetResult();

	//�Q�b�^�[
	int GetPlayer01Score() { return Score01; }
	int GetPlayer02Score() { return Score02; }
	bool GetIsTimeUp() { return isTimeUp; }
	
	//�^�C���A�b�v�t���O��true�ɂ���
	void SetIsTimeUp() { isTimeUp = true; }

	void AddScoreNChangeColor();

	void Update();

	FontRender* Score[2];
	CSoundSource* moneySound;
};

