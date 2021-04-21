#pragma once

//class ModelRender;		//�v���C���[
class Guzai;			//���
class Kitchen;			//�L�b�`��
class Counter;			//�J�E���^�[

//���g�͂ǂ̃v���C���[�̂��̂�
enum EnSelf {
	enPlayer01,			//�v���C���[1
	enPlayer02,			//�v���C���[2
	enPlayerNum			//�v�f��
};

//�v���C���[�̃V�`���G�[�V����(�ǉ��\��)
enum EnState {
	enNone,				//���͂ɉ����Ȃ�
	enNearFood,			//��ނ��߂��ɂ���
	enNearBuffer,		//�o�t�A�C�e�����߂��ɂ���
	enNearDebuffer,		//�f�o�t�A�C�e�����߂��ɂ���
	enNearKitchen,		//�L�b�`�����߂��ɂ���
	enNearBurger,		//�쐬�����o�[�K�[���߂��ɂ���
	enNearCounter,		//�J�E���^�[���߂��ɂ���
	enDisposable,		//��肩���̃o�[�K�[��������o�[�K�[������
	enDerivable,		//�o�[�K�[��񋟉\�ł���
	enStateNum			//�V�`���G�[�V��������
};

class PopUp2D : public IGameObject
{
public:
	PopUp2D() {};
	~PopUp2D() {};
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) { m_model.Draw(rc); }
	
	//�Z�b�^�[�A�Q�b�^�[
	void SetPosition(const Vector3& pos) { m_position = pos; }
	Vector3 GetPosition() { return m_position; };
	void SetRotation(const Quaternion& rot) { m_rotation = rot; }
	Quaternion GetRotation() { return m_rotation; }
	void SetScale(const Vector3& scale) { m_scale = scale; }
	Vector3 GetScale() { return m_scale; }
	
	EnSelf GetEnSelf() { return m_self; }
	void SetEnSelf(const EnSelf& self) { m_self = self; }
	EnState GetEnState() { return m_state; }
	void SetEnState(const EnState& state) { m_state = state; }

	void Move();
	void Rotation();
	void ChangeState();
	void ChangeModel();
	
private:
	//�v���C���[
	//ModelRender* m_player = nullptr;
	Guzai* m_guzai = nullptr;
	std::vector<Guzai*> vecGuzai;
	std::size_t vecGuzaiSize = 0;
	const int MAXSIZE = 10;

	Kitchen* m_kitchen = nullptr;
	Counter* m_counter = nullptr;

	//���f��
	Model m_model;
	Vector3 m_position = Vector3::Zero;
	Quaternion m_rotation = Quaternion::Identity;
	Vector3 m_scale = Vector3::One;
	EnSelf m_self = enPlayer01;
	EnState m_state = enNone;

	//�p�x����p�Ɏg������
	const float PI = 3.1415f;

};

