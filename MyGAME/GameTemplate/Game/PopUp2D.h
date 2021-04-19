#pragma once

class ModelRender; //�v���C���[

class PopUp2D : public IGameObject
{
public:
	PopUp2D() {};
	~PopUp2D() {};
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) { m_model.Draw(rc); }

private:
	Model m_model;
	
	//�v���C���[
	ModelRender* m_player01 = nullptr;
	ModelRender* m_player02 = nullptr;

	Vector3 m_position = Vector3::Zero;
	Quaternion m_rotation = Quaternion::Identity;
	Vector3 m_scale = Vector3::One;

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

	EnState m_state = enNone;
};

