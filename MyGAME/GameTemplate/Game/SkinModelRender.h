#pragma once
class AnimationClip;

class SkinModelRender :public IGameObject
{
private:
	Model m_model;
	ModelInitData m_modelInitData;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;

public:
	SkinModelRender();
	~SkinModelRender();

	bool Start();
	void Update();

	void SetPosition(Vector3 pos) { m_position = pos; }
	void SetScale(Vector3 scale) { m_scale = scale; }
	void SetRotation(Quaternion rot) { m_rot = rot; }
	void SetNewModel() { m_model.Init(m_modelInitData); }

	Vector3 GetPosition() { return m_position; }
	Vector3 GetScale() { return m_scale; }


	void Init(const char* modelFilePath, EnModelUpAxis UpAxis, Vector3 pos);
	//���f���̃t�@�C���p�X�Ə����ʒu��ݒ肷��B
	void Init(const char* filePath, const char* skeletonPath, EnModelUpAxis UpAxis, Vector3 pos);
	//���f���̃t�@�C���p�X�݂̂�ύX����Ƃ��Ɏg�p����B
	void ChangeModel(const char* newModelFilePath);
	//�V�F�[�_�[�̃t�@�C���p�X��
	void InitShader(const char* filePath, const char* entryPointPath, const char* skinEntryPointPath, DXGI_FORMAT colorBuffer);
	//��Ƀt�����g�J�����O�ɕς���Ƃ��Ɏg�p����
	void SetFrontCulling(const char* psEntryPoint) { m_modelInitData.m_psEntryPointFunc = psEntryPoint; }
	//�e�����󂯂郉�C�g�̎�ނ̕ύX�B
	void InitLight(Light light);
	//�e�𗎂Ƃ��w�i�p�̏������֐�
	void InitBackGroundLight(Texture texture, Matrix lightcamera, Matrix lightcamerasize);
	//�A�j���[�V������ݒ肷��B
	void InitAnimation(AnimationClip* animation, int animationNum);
	//�����Q�͕⊮����
	void PlayAnimation(int animNo, float interpolateTime = 0.0f);

	void Render(RenderContext& rc) { m_model.Draw(rc); }

	Animation m_animation;
	AnimationClip* m_animationClip;
};

