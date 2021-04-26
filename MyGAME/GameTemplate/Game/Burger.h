#pragma once
class SkinModelRender;

class Burger : public IGameObject
{
private:
	/*Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;*/

	Vector3 m_position;

	//�ǂ���ɗ���Ă���o�[�K�[��
	int BurgerNo = 0;
	
	Vector3 pos;

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
	
	void SetPosition(Vector3 pos) { m_position = pos;/*m_charaCon.SetPosition(pos);*/ }
	//�o�[�K�[�͂ǂ��瑤�̂�...�P�A���@�Q�A�E
	void SetBurgerNo(int num) { BurgerNo = num; }

	//void Render(RenderContext& rc) { model.Draw(rc); }

	//�{�^���������Ńo�[�K�[�������悤�ɂ��邽�߁B
	int DeleteTimer = 0;
	//�P�̎��ɏ��Delete(),ClearNo()��
	int burgerExist = 0;
	int putOnKitchen = 0;
	
	
	Vector3 CounterPos = { 900.0f, 100.0f, -400.0f };

	SkinModelRender* m_skinModelRender;
};

