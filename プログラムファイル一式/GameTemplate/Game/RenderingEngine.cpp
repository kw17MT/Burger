#include "stdafx.h"
#include "RenderingEngine.h"

RenderingEngine* RenderingEngine::instance = nullptr;

RenderingEngine::RenderingEngine()
{
	InitLightCamera();
}

void RenderingEngine::PrepareRender()
{
	InitRenderTarget();
	InitSprite();
	m_postEffect.Init(mainRenderTarget);
}

void RenderingEngine::InitRenderTarget()
{
	albedoMap.Create(1280, 720, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	normalMap.Create(1280, 720, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_UNKNOWN);
	specAndDepthMap.Create(1280, 720, 1, 1, DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_UNKNOWN);
	forwardBloomTarget.Create(1280, 720, 1, 1, DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_D32_FLOAT);
	//�V���h�E�̃I�t�X�N���[�������_�����O�쐬
	shadowMap.Create(4096, 2048, 1, 1, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_D32_FLOAT, clearColor);
	//���C���̃����_�[�^�[�Q�b�g�̏�����
	mainRenderTarget.Create(1280,720,1,1,DXGI_FORMAT_R32G32B32A32_FLOAT,DXGI_FORMAT_D32_FLOAT);
}

void RenderingEngine::InitSprite()
{
	shadowBlur.Init(&shadowMap.GetRenderTargetTexture());

	defferedSpriteData.m_width = 1280;
	defferedSpriteData.m_height = 720;
	defferedSpriteData.m_textures[0] = &albedoMap.GetRenderTargetTexture();
	defferedSpriteData.m_textures[1] = &normalMap.GetRenderTargetTexture();
	defferedSpriteData.m_textures[2] = &specAndDepthMap.GetRenderTargetTexture();
	defferedSpriteData.m_textures[3] = &shadowBlur.GetBokeTexture();
	defferedSpriteData.m_fxFilePath = "Assets/shader/deffered/defferedSprite.fx";
	defferedSpriteData.m_alphaBlendMode = AlphaBlendMode_None;
	defferedSpriteData.m_expandConstantBuffer = (void*)&LightManager::GetInstance().GetLightData();
	defferedSpriteData.m_expandConstantBufferSize = sizeof(LightManager::GetInstance().GetLightData());
	defferedSprite.Init(defferedSpriteData);

	//�ŏI�\���p�̉摜�f�[�^
	finalSpriteData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
	finalSpriteData.m_width = 1280;
	finalSpriteData.m_height = 720;
	finalSpriteData.m_fxFilePath = "Assets/shader/sprite.fx";

	finalSprite.Init(finalSpriteData);

	m_forwardBloom.Init(forwardBloomTarget);
}

void RenderingEngine::InitLightCamera()
{
	//���C�g�J�����̍쐬
	lightCamera.SetPosition(0.0f, 1000.0f, -500.0f);
	lightCamera.SetTarget(0.0f, 0.0f, 0.0f);
	lightCamera.SetUp({ 0, 0, 1 });							//�J�����̏��X���W�ɂ��Ă���
	lightCamera.SetViewAngle(Math::DegToRad(105.0f));
	//���s���e�ɂ���ꍇ
	/*
	lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	lightCamera.SetWidth(1280);
	lightCamera.SetHeight(720);
	*/
	lightCamera.Update();
}

void RenderingEngine::CreateShadowMap(RenderContext& rc)
{
	rc.WaitUntilToPossibleSetRenderTarget(shadowMap);
	rc.SetRenderTargetAndViewport(shadowMap);
	rc.ClearRenderTargetView(shadowMap);
	m_renderTypes = enRenderShade;									//�e�����
	//�V���h�E�̍쐬���s�����f���̃h���[
	GameObjectManager::GetInstance()->CallRenderWrapper(rc);
	rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);
	m_renderTypes = enRenderNormal;
}

void RenderingEngine::CreateDeffered(RenderContext& rc)
{
	rc.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(defferedTargets), defferedTargets);
	rc.SetRenderTargetsAndViewport(ARRAYSIZE(defferedTargets), defferedTargets);
	rc.ClearRenderTargetViews(ARRAYSIZE(defferedTargets), defferedTargets);
	m_renderTypes = enRenderNormal;
	GameObjectManager::GetInstance()->CallRenderWrapper(rc);

	//�Q�[���^�C����p���ăG�t�F�N�g�̍Đ��i�s�x�̍X�V
	EffectEngine::GetInstance()->Update(GameTime().GetFrameDeltaTime());
	//�G�t�F�N�g�̕`��
	EffectEngine::GetInstance()->Draw();

	rc.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(defferedTargets), defferedTargets);
}

void RenderingEngine::CreateMainRenderTarget(RenderContext& rc)
{
	rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	rc.SetRenderTargetAndViewport(mainRenderTarget);
	rc.ClearRenderTargetView(mainRenderTarget);
	//�f�B�t�@�[�h���C�e�B���O�������摜�̕`��
	defferedSprite.Draw(rc);
	rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
}

void RenderingEngine::CreateForwardBloom(RenderContext& rc)
{
	rc.WaitUntilToPossibleSetRenderTarget(forwardBloomTarget);
	rc.SetRenderTargetAndViewport(forwardBloomTarget);
	rc.ClearRenderTargetView(forwardBloomTarget);
	m_renderTypes = enRenderLuminance;								
	GameObjectManager::GetInstance()->CallRenderWrapper(rc);
	rc.WaitUntilFinishDrawingToRenderTarget(forwardBloomTarget);
}

void RenderingEngine::CreateUI(RenderContext& rc)
{
	rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	rc.SetRenderTargetAndViewport(mainRenderTarget);
	m_renderTypes = enRenderUI;
	GameObjectManager::GetInstance()->CallRenderWrapper(rc);
	rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
}

void RenderingEngine::Render(RenderContext& rc)
{
	//�V���h�E�}�b�v�̍쐬
	CreateShadowMap(rc);
	//�V���h�E�}�b�v�Ƀu���[���|����
	shadowBlur.ExecuteOnGPU(rc, 5);
	//�f�t�@�[�h���C�e�B���O���s��
	CreateDeffered(rc);
	//���C���^�[�Q�b�g�Ƀf�B�t�@�[�h���C�e�B���O�ς݂̊G��`��
	CreateMainRenderTarget(rc);
	//�n���o�[�K�ɓ��ʂȃu���[���t�B���^��������
	CreateForwardBloom(rc);
	m_forwardBloom.Render(rc, mainRenderTarget);
	//�G�S�̂Ƀ|�X�g�G�t�F�N�g���|����
	m_postEffect.Render(rc, mainRenderTarget);
	//�Ō��UI��`��
	CreateUI(rc);


	rc.SetRenderTarget(
		g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		g_graphicsEngine->GetCurrentFrameBuffuerDSV()
	);
	//�`�悷��T�C�Y��ݒ�
	rc.SetViewport(g_graphicsEngine->GetFrameBufferViewport());
	rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

	finalSprite.Draw(rc);
}