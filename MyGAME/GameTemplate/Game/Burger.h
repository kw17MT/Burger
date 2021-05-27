
#pragma once

class SkinModelRender;
class TrashCan;
class Player;
class CSoundSourse;

class Effect;
#include "effect/Effect.h"

class CSoundSourse;


class Burger : public IGameObject
{
private:
	Vector3 m_position;
	Vector3 m_scale;
	//�ǂ���ɗ���Ă���o�[�K�[��
	int BurgerNo = 0;
	bool isSetOnTrashCan = false;

	int decrementTime = 20;
	
	Vector3 pos;
	Vector3 m_scale;


public:
	//���f���f�[�^�A�e�̐ݒ�B
	Burger();
	~Burger();
	//�o�[�K�[�̈ʒu���L�b�`���̏�ɂ��āA��ނ������铯���Ƀo�[�K�[���o��������B
	bool Start();
	//�o�[�K�[��DeleteGO�B
	void Delete();
	//�v���C���[���o�[�K�[�����������s���B
	void GrabBurger();
	//�o�[�K�[���������ہA�J�E���^�[�ɐς�ł�����ނ̎�ނ��������B
	//�v���C���[�ɕۑ����Ă����A�n���o�[�K�[���\�������ނ��X�ŏ������B	
	void ClearNo();
	//�J�E���^�[���Ńo�[�K�[�̃��f�����������߂Ɏg��
	void ClearModel() { DeleteGO(this); }

	void Update();
	
	void SetPosition(Vector3 pos) { m_position = pos; }
	//�o�[�K�[�͂ǂ��瑤�̂�...�P�A���@�Q�A�E
	void SetBurgerNo(int num) { BurgerNo = num; }
	//�S�~���ɃZ�b�g���ď���
	void SetOnTrashCan();

	//�{�^���������Ńo�[�K�[�������悤�ɂ��邽�߁B
	int DeleteTimer = 0;
	//�P�̎��ɏ��Delete(),ClearNo()��
	int burgerExist = 0;
	int putOnKitchen = 0;
	
	Vector3 CounterPos = { 900.0f, 100.0f, -400.0f };

	Effect m_effect;
	SkinModelRender* m_skinModelRender = nullptr;
	Player* m_player[2] = { nullptr };
	TrashCan* m_trashCan[2] = { nullptr };
};