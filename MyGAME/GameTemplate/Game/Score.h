#pragma once
class Score : public IGameObject
{
private:
	//�ŏI�I�ɕ\������X�R�A
	//��ނ̐� * 100
	int Score01 = 0;
	int Score02 = 0;
	//�J�E���^�[���ŉ��w�̃n���o�[�K�[��񋟂������B
	//�񋟂�����ނ𐔂��Ă����B
	int BasePoint01 = 0;
	int BasePoint02 = 0;

	RenderContext renderContext = g_graphicsEngine->GetRenderContext();
public:
	Score();
	//�J�E���^�[����num�����Ă͂߁A�����瑤��BasePoint�ɉ��Z����B
	void SetBasePoint01(int num) { BasePoint01 += num; }
	void SetBasePoint02(int num) { BasePoint02 += num; }

	void Update();
};

