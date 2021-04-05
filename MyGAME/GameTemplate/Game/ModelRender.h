#pragma once
class Guzai;
class FontRender;

class ModelRender : public IGameObject
{
private:
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

	//�v���C���[�̃p�����[�^
	//���W
	Vector3 m_position = Vector3::Zero;
	//��]
	Quaternion m_rotation = Quaternion::Identity;
	//�X�P�[��
	Vector3 m_scale = Vector3::One;
	//�p�x
	float angle = 0.0f;
	//�ړ����x
	Vector3 moveSpeed = Vector3::Zero;

	//�P�ō��A�Q�ŉE
	int playerNo = 0;
	//int setPos = 0;

	//�o�t�̌��ʂ��L�����ǂ����B
	bool Buff = false;
	//�o�t�̗L�����ԁB
	int BuffTime = 120;
	//���A��ނ��^�[�Q�b�g���Ă��邩�B1�ȏ�^�[�Q�e�B���O���Ȃ��悤�ɁB
	bool TargetingState = false;

public:
	ModelRender();
	~ModelRender();
	//���f���A�����蔻��A���No.���i�[����z����X�ŏ�����
	//���̏������R���X�g���N�^����Start�֐��ɕύX���܂����B
	bool Start();
	void SetPlayerNo(int num) { playerNo = num; }

	//�ړ������B
	void Update();

	void SetBuffAffect(bool buff) { Buff = buff; }
	bool stateBuff() { return Buff; }
	
	//��ފi�[�p�z����X�ŏ�����
	void SetGuzaiNo9();

	//void SetPosition(Vector3 pos) { m_charaCon.SetPosition(pos); }
	//���g�̎����W�����L�����R���ɓn���ď������Ă��炤���߂ɕύX���܂����B
	void SetPosition(Vector3 pos) { m_position.x = pos.x, m_position.y = pos.y, m_position.z = pos.z; }
	//�L�����R���̍��W �� �v���C���[���g�̍��W���擾����悤�ɕύX
	Vector3 GetPosition();

	void Render(RenderContext& rc) { model.Draw(rc); }

	void GiveData(const char* ModelPath, const char* ShaderPath);

	//���݃^�[�Q�e�B���O���Ă��邩�ǂ���
	void SetTarget(bool target) { TargetingState = target; }
	//���݂̃^�[�Q�e�B���O��Ԃ�Ԃ��B
	bool GetTargetState() { return TargetingState; }

	//�v���C���[����ނ������Ă��邩�B�P�Ȃ��ނ������Ă���B�Q�Ȃ�n���o�[�K�[�������Ă���B
	int have = 0;
	//�ςݏグ�Ă����ނ̎�ނ��i�[���Ă����B
	int GuzaiNo[10];

};