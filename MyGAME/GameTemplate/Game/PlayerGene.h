#pragma once
class Player;

class PlayerGene : public IGameObject
{
private:
	Vector3 player01Pos = { 1000.0f,0.0f,0.0f };
	Vector3 player02Pos = { -1000.0f, 0.0f, 0.0f };
	Quaternion player01Rot;
	Quaternion player02Rot;

	int playerNum = 0;																//���l�v���C���[�𐶐��������̐�
	bool isWorking = true;															//�v���C���[�����킪�ғ������@�ғ����Ȃ�v���C���[�������I����Ă��Ȃ�

	int noHavingDishCounter = 0;													//��̎M�̐�
	int refilledNum = 0;				
	
	int SubmitBurgerNum = 0;														//��o�����o�[�K�[�̐�
	int ChangeCycleNum = 0;															//����[�������BDish�Ŏg�p�B���ꂪmaxNum2Refill�Ɠ��l�ɂȂ�ƕ�[�������Ӗ����AnoHavingDish�ArefilledNum���O�ŏ���������B
public:
	~PlayerGene() {};

	bool Start();
	void Update();

	//�e�v���C���[�̍��W�Z�b�^�[
	void SetPlayer01Pos(Vector3 pos) { player01Pos = pos; }
	void SetPlayer02Pos(Vector3 pos) { player02Pos = pos; }

	//��̎M�̌v���֌W
	int GetNoHavingDishCounter() { return noHavingDishCounter; }					//��̎M�̃Q�b�^�\
	void AddNoHavingDishCounter() { noHavingDishCounter++; }						//��̎M�̐���1����
	void ResetNohavingDishCounter() { noHavingDishCounter = 0; }					//��[�������ɋ�̎M���O�ɖ߂�
	//��[�����M�֌W	
	int GetRefilledNum() { return refilledNum; }									//��[���������M�̐�
	void AddRefilledNum() { refilledNum++; }										//��[���������M�̐��������
	void ResetRefilledNum() { refilledNum = 0; }									//��[�������ɕ�[�����M���O�ɖ߂�

	//��o�����o�[�K�[�֌W
	void AddSubmitBurgerNum() { SubmitBurgerNum++; }								//��o�����o�[�K�[�̐���1����
	int GetSubmitBurgerNum() { return SubmitBurgerNum; }							//��o�����o�[�K�[�̐���Ԃ�
	void ResetSubmitBurgerNum() { SubmitBurgerNum = 0; }							//
	//�����ς����񐔊֌W
	void AddChangeCycleNum() { ChangeCycleNum++; }									//�����ς�����
	int GetChangeCycleNum() { return ChangeCycleNum; }								//�����ς����񐔂̃Q�b�^�\
	void ResetChangeCycleNum() { ChangeCycleNum = 0; }								//

	//�v���C���[������d�����,true = �����Ă�, false = �~�܂��Ă�B
	bool GetPlayerGeneState() { return isWorking; }

	bool isMoving = true;
	void isMovingDish() {

		if (isMoving == false) {
			isMoving = true;
		}
		else if (isMoving == true) {
			isMoving = false;
		}
	}

	Player* player[2];
};

