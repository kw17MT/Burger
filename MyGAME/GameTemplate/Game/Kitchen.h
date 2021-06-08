#pragma once
class Guzai;
class Burger;
class SkinModelRender;
class Player;
class CSoundSource;
class Meter;
class GuzaiGene;

class Kitchen : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;						//�L�b�`���̍��W
	Vector3 m_kitchenPos;									
	Vector3 m_scale = { 0.3f,0.3f,0.3f };							//�L�b�`���̊g�嗦

	const int MaxStack = 5;									//�L�b�`���ɂ�����ő吔
	int m_kitchenNo = 0;										//�ǂ������̃L�b�`�����B�O�����A�P���E
	int stack = 0;											//���܉���ނ�ς�ł��邩		
	bool canGrab = true;									//���݂��߂邩�i�t���[���̂�����N�����p�j
	Guzai* StackedGuzai[5] = { nullptr };					//�L�b�`���̏�ɂ�����

	bool m_soundFlag01 = false;								//1P�̉����o�Ă��邩�H
	bool m_soundFlag02 = false;								//2P�̉����o�Ă��邩�H

	bool m_deleteFlag = false;
	Vector3 m_slidePos = Vector3::Zero;

public:

	~Kitchen();

	//�L�b�`���̃��f���Ȃǂ̐ݒ�B
	bool Start();

	void Update();

	//�L�b�`���ԍ���ݒ肷��B
	void SetKitchenNo(int num) { m_kitchenNo = num; }

	//�L�b�`���̍��W��ݒ肷��B
	void SetKitchenPos(Vector3 pos) { m_kitchenPos = pos; m_position = pos; }

	//�L�b�`���̍��W���擾
	Vector3 GetKitchenPos() { return m_kitchenPos; }

	//�L�b�`����̋�ނ�S����
	void Delete();

	//�X�^�b�N�����w�����C���N�������g
	void PlusStack() { stack++; }

	//�X�^�b�N�����w�����f�N�������g
	void MinusStack() { stack--; }

	//�����Ă���Stack�ϐ����O�ɏ������B
	void SetStack0() { stack = 0; }

	//�v���C���[���ɋ�ނ̎�ނ��i�[����ۂɎg�p����B
	int GetStackNum() { return stack; }

	//��ނ��n���o�[�K�[�ɕϊ�����B
	//�������x�����N�����Ă��Ȃ��ƃG���[��f�����߂���΍�
	void BornBurger();
	int Delay = 60;

	//��ނ��������ɁA�v���C���[�Ɋi�[����Ă�����No.���X�ŏ���������B
	//���̊֐��͋�ނ������O�Ɏg�����ƁB
	void ClearNo();
	//�L�b�`���̃��f����ύX����
	void ChangeModel(const char* modelPath);
	//�g�嗦��ύX����
	void SetScale(Vector3 scale) { m_scale = scale; }

	void ChangeGrabState(bool state) { canGrab = state; }

	//�X�^�b�N���Ă����ނ�ۑ����Ă����B
	void RegistStackedGuzai(Guzai* m_guzai) { StackedGuzai[stack - 1] = m_guzai; }

	//�o�[�K�[�̒����󋵂��擾
	bool GetKitchenCooking() { return m_deleteFlag; }


private:
	Player* m_player = nullptr;
	Burger* bur = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
	CSoundSource* m_soundSource = nullptr;
	Meter* m_meter = nullptr;
	GuzaiGene* m_guzaiGene = nullptr;
};

