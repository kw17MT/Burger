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
	const float distance = 130.0f;									//�S�~�����v���C���[�����ʂ��鋗��
	int trashcanNo = 0;												//�S�~���̔ԍ��A�P�����A�Q���E
	bool canTrash = false;											//�v���C���[���߂���TRUE�ɂ��Ď̂Ă邱�Ƃ��ł���悤�ɂ���B

	bool targetUp = true;											//�^�[�Q�b�g�A�C�R���𕂗V������悤
	bool isMoving = false;											//�S�~���𓮂������邩
	int movingTime = 120;											//�S�~����ꂽ��ǂ̂��炢�̎��ԓ�����
public:
	bool Start();
	void Update();

	void SetScale(Vector3 scale) { m_targetScale = scale; }
	void SetPosition(Vector3 pos) { m_position = pos; }
	Vector3 GetPosition() { return m_position; }

	//�S�~���̔ԍ��̐ݒ�@�P�����@2���E
	void SetTrashCanNum(int num) { trashcanNo = num; }

	//���݂��̂Ă��邩�ǂ����̕ϐ��𓾂�
	bool GetCanTrash() { return canTrash; }

	//2�n�_�Ԃ̋��������߂�
	float CalcDistance(Vector3 v1, Vector3 v2);

	void ChangeMovingState(bool state) { isMoving = state; }
	//�S�~�������ē������ǂ�����ύX����@TRUE�ɂ���Ɠ����n�߂�
	void LetStartMoving();

	Player* player[2];
	SkinModelRender* m_skinModelRender;
	SkinModelRender* m_targeting;
	PlayerGene* m_playerGene;
};

