#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::~SkinModelRender()
{
	DeleteGO(this);
}

//���f����ʏ�`�悷�邽�߂̏�����
void SkinModelRender::Init(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis UpAxis, Vector3 pos, Light* pLig)
{
	//���f���̃t�@�C���p�X�ݒ�
	m_modelInitData.m_tkmFilePath = modelFilePath;
	//���f�����g�p����V�F�[�_�[�i����PBR�̂݁j
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	//���_�V�F�[�_�[�ݒ�
	m_modelInitData.m_vsEntryPointFunc = "VSMain";
	m_modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
	//�g���F�͈̔͐ݒ�
	m_modelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//�ǂ̎�����ɂ��邩
	m_modelInitData.m_modelUpAxis = UpAxis;
	//�����A�C�ӂ̃��C�g������Ȃ��
	if (pLig) {
		m_modelInitData.m_expandConstantBuffer = pLig;
		m_modelInitData.m_expandConstantBufferSize = sizeof(pLig);
	}
	//�Ȃ������狤�ʂ̂���g��
	else {
		m_modelInitData.m_expandConstantBuffer = &g_lig;
		m_modelInitData.m_expandConstantBufferSize = sizeof(g_lig);
	}
	//���f���̃X�P���g��������Ȃ�
	if (skeletonPath != nullptr) {
		m_skeleton.Init(skeletonPath);
		m_modelInitData.m_skeleton = &m_skeleton;
	}

	m_model.Init(m_modelInitData);

	//�L�����R���̏�����
	m_charaCon.Init(0.0f, 0.0f, pos);
}

//�e���o�����߂̏�����
void SkinModelRender::InitForCastShadow(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis UpAxis, Vector3 pos, Light* pLig = nullptr)
{
	m_shadowData.m_tkmFilePath = modelFilePath;

	/****************************************************/
	/*	�f�v�X�V���h�E��K�p							*/
	/*	�V���h�E�}�b�v�̃J���[�o�b�t�@�[���ύX���邱�Ɓ@*/
	/****************************************************/
	m_shadowData.m_fxFilePath = "Assets/shader/shadow/drawDepthShadowMap.fx";
	m_shadowData.m_colorBufferFormat = DXGI_FORMAT_R32_FLOAT;


	/****************************************************/
	/*	���e�V���h�E��K�p								*/
	/*	�V���h�E�}�b�v�̃J���[�o�b�t�@�[���ύX���邱�Ɓ@*/
	/****************************************************/
	//m_shadowData.m_fxFilePath = "Assets/shader/shadow/drawProjectionShadowMap.fx";
	//m_shadowData.m_colorBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	m_shadowData.m_vsEntryPointFunc = "VSMain";
	m_shadowData.m_vsSkinEntryPointFunc = "VSMain";


	m_shadowData.m_modelUpAxis = UpAxis;

	if (pLig) {
		m_shadowData.m_expandConstantBuffer = pLig;
	}
	else {
		m_shadowData.m_expandConstantBuffer = &g_lig;
	}
	m_shadowData.m_expandConstantBufferSize = sizeof(g_lig);

	if (skeletonPath != nullptr) {
		m_skeleton.Init(skeletonPath);
		m_shadowData.m_skeleton = &m_skeleton;
	}

	m_shadow.Init(m_shadowData);
	//�������I���//

	//�L�����R���̏�����
	//m_charaCon.Init(0.0f, 0.0f, pos);

	m_isCastShadow = true;
}

void SkinModelRender::InitForRecieveShadow(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis UpAxis, Vector3 pos, Light* lig = nullptr)
{
	m_modelInitData.m_tkmFilePath = modelFilePath;

	/****************************************************/
	/*	���e�V���h�E��K�p								*/
	/****************************************************/
	//m_modelInitData.m_fxFilePath = "Assets/shader/shadowprojectionShadowReciever.fx";

	/****************************************************/
	/*	�f�v�X�V���h�E��K�p							*/
	/****************************************************/
	m_modelInitData.m_fxFilePath = "Assets/shader/shadow/depthShadowReciever.fx";

	//�J���[�o�b�t�@�[�̃t�H�[�}�b�g�͋���
	m_modelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;


	m_modelInitData.m_modelUpAxis = UpAxis;
	if (lig == nullptr) {
		m_modelInitData.m_expandShaderResoruceView = &m_shadowMap.GetRenderTargetTexture();
		m_modelInitData.m_expandConstantBuffer = (void*)&m_lightCamera.GetViewProjectionMatrix();
		m_modelInitData.m_expandConstantBufferSize = sizeof(m_lightCamera.GetViewProjectionMatrix());
	}
	else {
		m_modelInitData.m_expandShaderResoruceView = &m_shadowMap.GetRenderTargetTexture();
		m_modelInitData.m_expandConstantBuffer = &lig;
		m_modelInitData.m_expandConstantBufferSize = sizeof(lig);
	}

	if (skeletonPath != nullptr) {
		m_skeleton.Init(skeletonPath);
		m_modelInitData.m_skeleton = &m_skeleton;
	}

	m_model.Init(m_modelInitData);
	//�������I���//

	//�L�����R���̏�����
	m_charaCon.Init(0.0f, 0.0f, pos);
}

void SkinModelRender::InitAsFloor(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis UpAxis, Vector3 pos)
{
	m_modelInitData.m_tkmFilePath = modelFilePath;

	m_modelInitData.m_fxFilePath = "Assets/shader/shadow/shadowRecieverForFloor.fx";

	m_modelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	m_modelInitData.m_modelUpAxis = UpAxis;

	m_modelInitData.m_expandShaderResoruceView = &m_shadowMap.GetRenderTargetTexture();
	m_modelInitData.m_expandConstantBuffer = (void*)&m_lightCamera.GetViewProjectionMatrix();
	m_modelInitData.m_expandConstantBufferSize = sizeof(m_lightCamera.GetViewProjectionMatrix());


	if (skeletonPath != nullptr) {
		m_skeleton.Init(skeletonPath);
		m_modelInitData.m_skeleton = &m_skeleton;
	}

	m_model.Init(m_modelInitData);
}

void SkinModelRender::ChangeModel(const char* newModelFilePath)
{
	m_modelInitData.m_tkmFilePath = newModelFilePath;
	if (m_isCastShadow) {
		m_shadowData.m_tkmFilePath = newModelFilePath;
	}
}


void SkinModelRender::InitShader(const char* shaderFilePath, const char* entryPointPath, const char* skinEntryPointPath, DXGI_FORMAT colorBuffer)
{
	m_modelInitData.m_fxFilePath = shaderFilePath;
	m_modelInitData.m_vsEntryPointFunc = entryPointPath;
	m_modelInitData.m_vsSkinEntryPointFunc = skinEntryPointPath;
	m_modelInitData.m_colorBufferFormat = colorBuffer;
}

void SkinModelRender::InitLight(Light& light) {
	m_modelInitData.m_expandConstantBuffer = &light;
	m_modelInitData.m_expandConstantBufferSize = sizeof(light);
}

//void SkinModelRender::InitAnimation(AnimationClip* animationClip, int animationNum)
//{
//	m_animationClip = animationClip;
//
//	m_animation.Init(m_skeleton, m_animationClip, animationNum);
//}

//void SkinModelRender::PlayAnimation(int animNo, float interpolateTime)
//{
//	m_animation.Play(animNo, interpolateTime);
//}

void SkinModelRender::Update()
{
	//�X�P���g�����X�V�B
	m_skeleton.Update(m_model.GetWorldMatrix());

	//m_animation.Progress(GameTime().GetFrameDeltaTime());
	
	m_model.UpdateWorldMatrix(m_position, m_rot, m_scale);
	m_shadow.UpdateWorldMatrix(m_position, m_rot, m_scale);
}