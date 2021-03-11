#pragma once

class Buff : public IGameObject
{
private:
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

	//�ǂ���ɗ���Ă���o�t�A�C�e����
	int BuffNo = 0;

public:
	Buff();

	bool Start();
	void Update();

	Vector3 GetPosition();
	void SetPosition(Vector3 pos);
	void SetBuffNo(int num) { BuffNo = num; }

	void Render(RenderContext& rc)
	{
		model.Draw(rc);
	}

	//Update()�ŃC���N�������g����B
	int time = 0;
	//���Ԗڂɍ쐬���ꂽ����
	int exist = 0;
	//Start()�ő҂��Ԃ����߂Ă���B
	int wait = 0;
	//�P�Ȃ�Ύ�����Ă���B
	int state = 0;
	//�P�Ȃ�΂����L�b�`���ɒu����Ă���B
	int put = 0;

};

