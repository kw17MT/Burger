#pragma once
class SkinModelRender;
class Player;
class PlayerGene;

class TrashCan : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;								//�S�~���̈ʒu
	Vector3 m_arrowPos = Vector3::Zero;								//�S�~���̏�ɏo�Ă�����̈ʒu
	Vector3 m_trashcanScale = { 1.0f,1.0f,1.0f };					//�S�~���̊g�嗦
	Vector3 m_targetScale = Vector3::Zero;							//���̊g�嗦
	Quaternion m_rot = Quaternion::Identity;						//���̉�]
	
	int movingTime = 30;											//�S�~����ꂽ��ǂ̂��炢�̎��ԓ�����
	int trashcanNo = 0;												//�S�~���̔ԍ��A�P�����A�Q���E

	const float distance = 130.0f;									//�S�~�����v���C���[�����ʂ��鋗��

	bool canTrash = false;											//�v���C���[���߂���TRUE�ɂ��Ď̂Ă邱�Ƃ��ł���悤�ɂ���B
	bool targetUp = true;											//�^�[�Q�b�g�A�C�R���𕂗V������悤
	bool isMoving = false;											//�S�~���𓮂������邩

public:
	~TrashCan();

	/**
	 * @brief �S�~���̃��f���̏�����
	 * @return true
	*/
	bool Start();

	/**
	 * @brief �S�~���̃��A�N�V���������邩����A���̊g��A���V��\������B
	*/
	void Update();

	/**
	 * @brief ���̊g�嗦��ݒ肷��
	 * @param scale �V�����g�嗦
	*/
	void SetScale(Vector3 scale) { m_targetScale = scale; }

	/**
	 * @brief �S�~���̈ʒu��ݒ肷��
	 * @param pos �V�����ʒu���W
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }

	/**
	 * @brief �S�~���̍��W��Ԃ��B
	 * @return �S�~���̍��W
	*/
	Vector3 GetPosition() { return m_position; }

	/**
	 * @brief �S�~���̔ԍ��̐ݒ�@�O�����@�P���E
	 * @param num �S�~���̔ԍ�
	*/
	void SetTrashCanNum(int num) { trashcanNo = num; }

	/**
	 * @brief �S�~���͌��݉������̂Ă����Ԃ���Ԃ�
	 * @return �S�~���̏��
	*/
	bool GetCanTrash() { return canTrash; }

	/**
	 * @brief �Q�n�_�Ԃ̋��������߂�
	 * @param v1 �n�_�P
	 * @param v2 �n�_�Q
	 * @return �Q�n�_�Ԃ̋���
	*/
	float CalcDistance(Vector3 v1, Vector3 v2);

	/**
	 * @brief �S�~���͉������̂Ă��ă��A�N�V���������Ă��邩
	 * @param state TRUE�����Ă���
	*/
	void ChangeMovingState(bool state) { isMoving = state; }
	
	/**
	 * @brief �S�~������ꂽ�烊�A�N�V����������
	*/
	void LetStartMoving();

private:
	Player* m_player = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
	SkinModelRender* m_arrow = nullptr;
	PlayerGene* m_playerGene = nullptr;
};