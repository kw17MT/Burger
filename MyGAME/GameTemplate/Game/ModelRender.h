#pragma once
class Guzai;

class ModelRender : public IGameObject
{
private:
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

	int playerNo = 0;
	int setPos = 0;

	bool Buff = false;
	int BuffTime = 120;

public:
	ModelRender();
	void SetPlayerNo(int num) { playerNo = num; }

	bool Start();
	void Update();

	void SetBuffAffect(bool buff) { Buff = buff; }
	bool stateBuff() { return Buff; }
	void SetGuzaiNo9();

	Vector3 GetPosition();

	void Render(RenderContext& rc) { model.Draw(rc); }

	void GiveData(const char* ModelPath, const char* ShaderPath);
	//�v���C���[����ނ������Ă��邩�B�P�Ȃ��ނ������Ă���B�Q�Ȃ�n���o�[�K�[�������Ă���B
	int have = 0;
	//�ςݏグ�Ă����ނ̎�ނ��i�[���Ă����B
	int GuzaiNo[10];
};