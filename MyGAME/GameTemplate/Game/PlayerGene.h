#pragma once
class Player;

//�J�n��"������"�v���C���[2�̂�"�����Ƃ���"�ɏo���ƃG���[�������B
//�����������邽�߂̐�����
//���ƃ|�W�V�����̒�����
class PlayerGene : public IGameObject
{
private:
	Vector3 player01Pos = { 1000.0f,0.0f,0.0f };
	Vector3 player02Pos = { -1000.0f, 0.0f, 0.0f };
	Quaternion player01Rot;
	Quaternion player02Rot;

	int playerNum = 0;
	bool isWorking = true;
public:
	~PlayerGene() {};

	bool Start();
	void Update();

	void SetPlayer01Pos(Vector3 pos) {	player01Pos = pos; }
	void SetPlayer02Pos(Vector3 pos) {	player02Pos = pos; }

	//�v���C���[������d�����,true = �����Ă�, false = �~�܂��Ă�B
	bool GetPlayerGeneState() { return isWorking; }

	Player* player[2];
};

