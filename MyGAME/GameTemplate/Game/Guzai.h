#pragma once
#include <vector>

class Guzai : public IGameObject
{
private:
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;
	
	//�ǂ������ɗ���Ă����ނ��B
	int GuzaiNo = 0;
	//�O�D�`�[�Y�@�P�D�G�b�O�@�Q�D���^�X�@�R�D�p�e�@�S�D�g�}�g
	int TypeNo = 99;

public:	
	Guzai();
	bool Start();
	void Update();
	
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);

	//��ނ��L�b�`���ɒu�����Ƃ��ɃI�u�W�F�N�g���������߁A���߂ɐݒ肵�Ă�����TypeNo�������Ă��܂��B
	//�܂�A���[����ɏo�����I�u�W�F�N�g�ƐV�����L�b�`����ɏo���I�u�W�F�N�g���Ⴄ�B
	//�v���C���[���ɕۑ����Ă���TypeNo���L�b�`������NewGO����I�u�W�F�N�g�ɗ^���Ă��B
	//�����Ƀv���C���[�Ɋi�[����Ă����ރi���o�[��^����B
	void ChangeGuzai(int num);
	//�ǂ��瑤�ɗ���Ă����ނ��ݒ肷��B
	void SetGuzaiNo(int num) { GuzaiNo = num; }

	int GetTypeNo() { return TypeNo; }

	void Render(RenderContext& rc) { model.Draw(rc); }

	//Update()�ŃC���N�������g����B
	int timer = 0;
	//�P�Ȃ�Ύ�����Ă���B
	int state = 0;
	//�P�Ȃ�΂����L�b�`���ɒu����Ă���B
	int put = 0;
	//X�{�^���������Őςݏグ�Ă����ނ�S���폜����B���̂��߂̃^�C�}�[�B
	int DeleteTimer = 0;
	//��ނ̎�ޔԍ�
	//ToDo...�ύX�\�ɂ���B
	
};

