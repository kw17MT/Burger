#pragma once
class AnimationClip;

class SkinModelRender :public IGameObject
{
private:
	ModelInitData m_modelInitData;										//���f���̃t�@�C���p�X��V�F�[�_�[��ݒ肷��
	ModelInitData m_shadowData;											//�e�����̂��߂̃��f�����
	Model m_model;														//���f��
	Model m_shadow;														//�e���f��
	Skeleton m_skeleton;												//�X�P���g��
	CharacterController m_charaCon;										//���f���̏Փ˔����ړ��֌W

	Vector3 m_position = Vector3::Zero;									//���f���̈ʒu���W
	Vector3 m_scale = Vector3::One;										//���f���̊g�嗦
	Quaternion m_rot = Quaternion::Identity;							//���f���̉�]

	RenderTarget m_shadowMap = GameObjectManager::GetInstance()->GetShadowMap();	//�쐬�����V���h�E�̎擾
	Camera m_lightCamera = GameObjectManager::GetInstance()->GetLightCamera();		//���C�g�J�����̎擾

	bool m_isCastShadow = false;
public:
	SkinModelRender() {};
	//�C���X�^���X��j��
	~SkinModelRender();

	bool Start() { return true; }

	/**
	 * @brief �X�P���g���A�A�j���[�V�����A�ʒu���W�A��]��ݒ肷��B
	*/
	void Update();

	/**
	 * @brief �ʒu���W��ݒ肷��B
	 * @param pos �ʒu���W
	*/
	void SetPosition(Vector3 pos) { m_position = pos; }
	/**
	 * @brief �g�嗦��ݒ肷��B
	 * @param scale �g�嗦
	*/
	void SetScale(Vector3 scale) { m_scale = scale; }

	/**
	 * @brief ��]����ݒ肷��B
	 * @param rot ��]��
	*/
	void SetRotation(Quaternion rot) { m_rot = rot; }

	/**
	 * @brief ���f���̍��W��ݒ肷��B
	 * @return �V�������W
	*/
	Vector3 GetPosition() { return m_position; }

	/**
	 * @brief ���f���̊g�嗦��ݒ肷��B
	 * @return �V�����g�嗦
	*/
	Vector3 GetScale() { return m_scale; }

	/**
	 * @brief ���f���̏��������s���B���C�g��Ǝ��̂��̂ɂ������Ƃ��͂�����������
	 * @param filePath ���f���̃t�@�C���p�X
	 * @param skeletonPath �X�P���g���̃t�@�C���p�X
	 * @param UpAxis �ǂ̎�����ɂ��邩
	 * @param pos ���f�����o��������ŏ��̈ʒu
	 * @param pLig �ݒ肵���Ǝ��̃��C�g
	*/
	void Init(const char* filePath, const char* skeletonPath, EnModelUpAxis UpAxis, Vector3 pos, Light* pLig = nullptr);
	//���f���̃t�@�C���p�X�݂̂�ύX����Ƃ��Ɏg�p����B

	/**
	 * @brief �e�𐶐�����l�̃��f���������֐�
	 * @param filePath �@
	 * @param skeletonPath 
	 * @param UpAxis 
	 * @param pos 
	 * @param pLig 
	*/
	void InitForCastShadow(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis UpAxis, Vector3 pos, Light* pLig);

	/**
	 * @brief �e���f����̂̃��f���������֐�
	 * @param filePath 
	 * @param skeletonPath 
	 * @param UpAxis 
	 * @param pos 
	*/
	void InitForRecieveShadow(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis UpAxis, Vector3 pos, Light* lig);

	/**
	 * @brief ����p�V���h�E���V�[�o�\�Ƃ��Ă̏�����
	*/
	void InitAsFloor(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis UpAxis, Vector3 pos);

	/**
	 * @brief ���f���̃t�@�C���p�X��ς������Ƃ��Ɏg�p
	 * @param newModelFilePath �V�����t�@�C���p�X
	*/
	void ChangeModel(const char* newModelFilePath);

	/**
	 * @brief �V�����t�@�C���p�X��K������B
	*/
	void SetNewModel() {
		m_model.Init(m_modelInitData); 
		if (m_isCastShadow) {
			m_shadow.Init(m_shadowData);
		}
	}

	/**
	 * @brief �V�F�[�_�[�̃t�@�C���p�X�Ǝg���s�N�Z���V�F�[�_�\��ς������Ƃ��Ɏg�p����B
	 * @param filePath �V�����V�F�[�_�[�̃t�@�C���p�X
	 * @param entryPointPath ���_�V�F�[�_�[
	 * @param skinEntryPointPath �s�N�Z���V�F�[�_�\
	 * @param colorBuffer �J���[�̃t�H�[�}�b�g�@DXGI_FORMAT_R?G?B?A?_???��
	*/
	void InitShader(const char* filePath, const char* entryPointPath, const char* skinEntryPointPath, DXGI_FORMAT colorBuffer);

	/**
	 * @brief ��Ƀt�����g�J�����O�ɕς���Ƃ��Ɏg�p����
	 * @param psEntryPoint �s�N�Z���V�F�[�_�\
	*/
	void SetFrontCulling(const char* psEntryPoint) { m_modelInitData.m_psEntryPointFunc = psEntryPoint; }

	/**
	 * @brief �e�����󂯂郉�C�g�̕ύX�B
	 * @param light �K���������V�������C�g
	*/
	void InitLight(Light& light);

	/**
	 * @brief �A�j���[�V������ݒ肷��B
	 * @param animation �A�j���[�V����
	 * @param animationNum �A�j���[�V�����̐�
	*/
	//void InitAnimation(AnimationClip* animation, int animationNum);

	/**
	 * @brief �A�j���[�V�������Đ�����
	 * @param animNo �A�j���[�V�����̐�
	 * @param interpolateTime ����鎞��
	*/
	//void PlayAnimation(int animNo, float interpolateTime = 0.0f);

	/**
	 * @brief ���f����`��
	 * @param rc �����_�[�R���e�L�X�g
	*/
	void Render(RenderContext& rc) 
	{
		//���ʕ`��
		if (GameObjectManager::GetInstance()->GetRenderTypes() == 0) {				
			m_model.Draw(rc);
			return;
		}
		//�e���
		if (GameObjectManager::GetInstance()->GetRenderTypes() == 1) {
			m_shadow.Draw(rc, GameObjectManager::GetInstance()->GetLightCamera());
			return;
		}
	}

private:
	//�A�j���[�V������t����ۂɎg��
	//Animation m_animation;
	//AnimationClip* m_animationClip = nullptr;
};

