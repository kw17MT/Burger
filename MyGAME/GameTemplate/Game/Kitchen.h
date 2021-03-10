#pragma once
class Guzai;
class Burger;

class Kitchen : public IGameObject
{
private:
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;


	Vector3 KitchenPos = { 900.0f, 0.0f, 0.0f };

	//��ނ��L�b�`���ɒu�����Ƌ��CPP���ŃC���N�������g
	int stack = 0;
	//���A���Ԗڂ̗v�f�ɂȂ邩�̔ԍ�
	int nextStackNum = 0;
	//�Ƃ肠�����A10�܂ł����ςݏグ���Ȃ��B
	//�o�O�h�~�̂��߁A5�ςݏグ����R���x�A�����ނ������Ă����Ȃ��B
	Guzai* StackedGuzai[5];

public:
	//���f���f�[�^�̓ǂݍ���
	bool Start();
	void Update();
	//��ނ��L�b�`���̏�ɔ���������B
	void Stack(int num);
	//�L�b�`����̋�ނ�S����
	void Delete();
	int DeleteTimer = 0;
	//private�̕ϐ��X�^�b�N���C���N�������g
	void PlusStack() { stack++; }
	//�v���C���[���ɋ�ނ̎�ނ��i�[����ۂɎg�p����B
	int GetStackNum() { return stack; }
	//���5���n���o�[�K�[�ɕϊ�����B
	//�������x�����N�����Ă��Ȃ��ƃG���[��f�����߂���΍�
	void BornBurger();
	int Delay = 60;
	//��ނ��������ɁA�v���C���[�Ɋi�[����Ă�����No.���O�ŏ���������B
	//���̊֐��͋�ނ������O�Ɏg�����ƁB
	void ClearNo();

	void Render(RenderContext& rc) { model.Draw(rc); }

	Burger* bur;
};

