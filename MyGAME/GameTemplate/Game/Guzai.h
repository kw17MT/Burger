#pragma once

class Kitchen;
class SkinModelRender;
class Player;
class PlayerGene;
class GuzaiGene;
class GuzaiOkiba;
class TrashCan;

class Guzai : public IGameObject
{
private:
	Vector3 m_position = { 0.0f,0.0f,-1000.0f };
	Vector3 m_scale = Vector3::One; //{ 0.8f, 0.8f, 0.8f };
	const Vector3 m_dummyScale = { 1.3f,1.3f,1.3f };
	Quaternion m_rotation = Quaternion::Identity;
	float angle = 0.0f;
	
	//Update()�ŃC���N�������g����B
	int timer = 0;
	//X�{�^���������Őςݏグ�Ă����ނ�S���폜����B���̂��߂̃^�C�}�[�B
	int DeleteTimer = 0;
	//�O�D�`�[�Y�@�P�D�G�b�O�@�Q�D���^�X�@�R�D�p�e�@�S�D�g�}�g
	//�T�D�I�j�I���@�U�D�x�[�R���@���ǉ����
	int TypeNo = 9;
	//��ނ���v���C���[�ւ̋���
	float guzai2Pl01 = 0.0f;
	float guzai2Pl02 = 0.0f;
	//�L�b�`������v���C���[�ւ̋���
	float kit2Pl01 = 0.0f;
	float kit2Pl02 = 0.0f;
	
	//�^�[�Q�e�B���O�֘A
	//�^�[�Q�e�B���O���ꂽ��ނ�ݒ肷��悤�B
	bool targeted = false;
	//1�x�����_�~�[��ނ��o���Ȃ��悤�ɂ��邽�߂̕ϐ��B1�Ȃ�_�~�[�����łɏo�����B
	bool isSetTargetDummy = false;
	//��x�^�[�Q�b�e�B���O�������̂�������x���߂邽�߂̎��ԁB
	//HOLDTIME���҂����ԁBDECREMENTTIME�����X�Ɍ��炵�Ă�������������B
	const int holdTime = 10;
	int decrementTime = holdTime;
	//�^�[�Q�b�g����ŒZ�����B
	const int TargetRangeNear = 100;
	//�^�[�Q�b�e�B���O��؂�n�߂鋗���B�i���ۂ̓f�B���C�����邽�ߏ�����̂͂���������Ɛ�ɂȂ�j
	const int TargetRangeFar = 110;
	//�g�������̂��߂Ɏg�p
	Vector3 GuzaiScale = { 1.0f,1.0f,1.0f };
	//���̋�ނ͉��ł��邩�̃����p�A�^�[�Q�e�B���O�̃I�u�W�F�N�g���쐬���Ɏg�p�B
	const char* NowModelPath;

	//���̋�ނ͂ǂ���̃v���C���[�ɂ��܂ꂽ��
	int whichPlayerGet = 0;
	//�ǂ���̃v���C���[�Ƀ^�[�Q�b�g���ꂽ��
	int whichPlayerTargetMe = 0;
	//1~36
	int dishNumber = 0;
	//���g����ޒu����ɃZ�b�g����Ă��邩�H
	bool m_guzaiOkibaSet = false;
	//���g���Z�b�g���ꂽ��ޒu����̔ԍ�
	int m_setKitchenNum = 9;
	//���g����������Ă��邩�H
	bool m_cooking = false;
	//1P�̒������̎��ԁB
	int m_hold01 = 0;
	//2P�̒������̎��ԁB
	int m_hold02 = 0;
	//�����ɂ����鎞�ԁB
	int m_cookingTime = 60;

	//�S�~���ɒu�����̂��ǂ���
	bool isSetOnTrashCan = false;

	bool canPutOnGuzaiOkiba = true;
public:	
	//������p���ċ�ނ����܂��Ɠ����ɂǂ̋�ނ𗬂����ݒ肷��B
	Guzai();
	~Guzai();
	bool Start();
	void Update();
	
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);
	void SetScale(Vector3 scale) { GuzaiScale = scale; }

	//��ނ��L�b�`���ɒu�����Ƃ��ɃI�u�W�F�N�g���������߁A���߂ɐݒ肵�Ă�����TypeNo�������Ă��܂��B
	//�܂�A���[����ɏo�����I�u�W�F�N�g�ƐV�����L�b�`����ɏo���I�u�W�F�N�g���Ⴄ�B
	//�v���C���[���ɕۑ����Ă���TypeNo���L�b�`������NewGO����I�u�W�F�N�g�ɗ^���Ă��B
	//�����Ƀv���C���[�Ɋi�[����Ă����ރi���o�[��^����B
	void ChangeGuzai(int num);
	//�L�b�`���ɒu�����Ƃ��ɈႤ���f���ɍ����ւ���p
	void ChangeModel(int& num);

	int GetTypeNo() { return TypeNo; }

	//��ނ̔���
	void GrabNPut();
	//�^�[�Q�e�B���O�̑ΏۑI��ƃ^�[�Q�b�g�_�~�[���o���B
	//�����ƕʂ̃^�[�Q�b�g��T���B
	void TargetingNPopDummy();
	//�u���ꂽ�M�ԍ����L�^����B
	void SetDishNumber(int num) { dishNumber = num; }

	//��ޒu����ɒu�������B
	void SetGuzaiOkiba();

	//��ޒu���ꂩ����o�������B
	void GetGuzaiOkiba();

	//��ޒu����Œ������鏈���B
	void Cooking();

	//�S�~���̏�ɋ�ނ��Z�b�g�A��ɏ����B
	void SetOnTrashCan();

	//��ނ̉�]�����B
	void Rotation();

	//�P�Ȃ�Ύ�����Ă���B
	int state = 0;
	//�P�Ȃ�΂����L�b�`���ɒu����Ă���B
	int put = 0;

	Player* pl01 = nullptr;
	Player* pl02 = nullptr;
	Kitchen* ki01 = nullptr;
	Kitchen* ki02 = nullptr;
	SkinModelRender* m_skinModelRender;
	PlayerGene* playerGene;
	GuzaiGene* m_guzaiGene;
	GuzaiOkiba* m_guzaiOkiba;
	TrashCan* m_trashCan[2];
};

