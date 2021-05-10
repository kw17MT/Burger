#pragma once
class SkinModelRender;
class Player;
class PlayerGene;

class TrashCan : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_targetPos = Vector3::Zero;
	Vector3 m_trashcanScale = { 1.0f,1.0f,1.0f };
	Vector3 m_targetScale = Vector3::Zero;
	Quaternion m_rot = Quaternion::Identity;
	const float distance = 150.0f;									//�S�~�����v���C���[�����ʂ��鋗��
	int trashcanNo = 0;												//�S�~���̔ԍ��A�P�����A�Q���E
	bool canTrash = false;											//�v���C���[���߂���TRUE�ɂ��Ď̂Ă邱�Ƃ��ł���悤�ɂ���B

	bool targetUp = true;											//�^�[�Q�b�g�A�C�R���𕂗V������悤
public:
	bool Start();
	void Update();

	float CalcDistance(Vector3 v1, Vector3 v2);

	void SetPosition(Vector3 pos) { m_position = pos; }
	Vector3 GetPosition() { return m_position; }
	void SetScale(Vector3 scale) { m_targetScale = scale; }
	void SetTrashCanNum(int num) { trashcanNo = num; }
	bool GetCanTrash() { return canTrash; }

	Player* player[2];
	SkinModelRender* m_skinModelRender;
	SkinModelRender* m_targeting;
	PlayerGene* m_playerGene;
};

