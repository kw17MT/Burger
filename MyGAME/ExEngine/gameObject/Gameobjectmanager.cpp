/*!
 *@brief	CGameObject�̃}�l�[�W��
 */
#include "stdafx.h"
#include "ExEngine.h"
#include "GameObjectManager.h"


GameObjectManager* GameObjectManager::m_instance = nullptr;

GameObjectManager::GameObjectManager()
{
	if (m_instance != nullptr) {
		//�C���X�^���X�����łɍ���Ă���B
		std::abort();
	}
	m_instance = this;

	//���C���̃����_�[�^�[�Q�b�g�̏�����
	//�ŏI�̃����_�����O�^�[�Q�b�g�ɂ���
	mainRenderTarget.Create(
		1280,
		720,
		1,
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);

	//�ŏI�\���p�̉摜�f�[�^
	finalSpriteWithFXAAData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
	finalSpriteWithFXAAData.m_width = 1280;
	finalSpriteWithFXAAData.m_height = 720;
	finalSpriteWithFXAAData.m_fxFilePath = "Assets/shader/spriteHalfAlpha.fx";

	finalSpriteWithFXAA.Init(finalSpriteWithFXAAData);

	//�V���h�E�̃I�t�X�N���[�������_�����O�쐬
	shadowMap.Create(
		2048,
		2048,
		1,
		1,
		//DXGI_FORMAT_R8G8B8A8_UNORM,			//���e�V���h�E�Ŏg��
		DXGI_FORMAT_R32_FLOAT,					//�f�v�X�V���h�E�Ŏg��
		DXGI_FORMAT_D32_FLOAT,
		clearColor
	);
	//���C�g�J�����̍쐬
	lightCamera.SetPosition(0.0f, 1000.0f, -500.0f);
	lightCamera.SetTarget(0.0f, 0.0f, 0.0f);
	lightCamera.SetUp({ 1, 0, 0});							//�J�����̏��X���W�ɂ��Ă���
	lightCamera.SetViewAngle(Math::DegToRad(145.0f));
	//���s���e�ɂ���ꍇ
	/*
	lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	lightCamera.SetWidth(1280);
	lightCamera.SetHeight(720);
	*/
	lightCamera.Update();



	//��ʊE�[�x�p�����_�[�^�[�Q�b�g
	/*depthInViewMap.Create(
		1280,
		720,
		1,
		1,
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_UNKNOWN
	);

	depthGaussian.Init(&mainRenderTarget.GetRenderTargetTexture());*/

	//��ʊE�[�x���݂̍����摜
	//combineDepthSpriteData.m_textures[0] = &depthGaussian.GetBokeTexture();//&gaussianBlur[0].GetBokeTexture();
	//combineDepthSpriteData.m_textures[1] = &depthInViewMap.GetRenderTargetTexture();
	//combineDepthSpriteData.m_width = 1280;
	//combineDepthSpriteData.m_height = 720;
	//combineDepthSpriteData.m_fxFilePath = "Assets/shader/depthInView.fx";
	//combineDepthSpriteData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//combineDepthSpriteData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//depthInViewSprite.Init(combineDepthSpriteData);

	//depthTargets[] = { &mainRenderTarget, &depthInViewMap };


	albedoMap.Create(1280, 720, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	normalMap.Create(1280, 720, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_UNKNOWN);
	worldPosMap.Create(1280, 720, 1, 1, DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_UNKNOWN);

	defferedSpriteData.m_width = 1280;
	defferedSpriteData.m_height = 720;
	defferedSpriteData.m_textures[0] = &albedoMap.GetRenderTargetTexture();
	defferedSpriteData.m_textures[1] = &normalMap.GetRenderTargetTexture();
	defferedSpriteData.m_textures[2] = &worldPosMap.GetRenderTargetTexture();
	defferedSpriteData.m_textures[3] = &shadowMap.GetRenderTargetTexture();
	defferedSpriteData.m_fxFilePath = "Assets/shader/defferedSprite.fx";
	defferedSpriteData.m_alphaBlendMode = AlphaBlendMode_Add;
	defferedSpriteData.m_expandConstantBuffer = (void*)&LightManager::GetInstance().GetLightData();
	defferedSpriteData.m_expandConstantBufferSize = sizeof(LightManager::GetInstance().GetLightData());
	defferedSprite.Init(defferedSpriteData);

	m_postEffect.Init(mainRenderTarget);
}
GameObjectManager::~GameObjectManager()
{
	m_instance = nullptr;
}
void GameObjectManager::ExecuteUpdate()
{	
	//���S�t���O�����Ă���Q�[���I�u�W�F�N�g��j������B
	for (auto& goList : m_gameObjectListArray) {
		goList.remove_if([&](IGameObject* go) {	
			if (go->IsDead()) {
				delete go;
				return true;
			}
			return false;	 
		});
	}

	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->StartWrapper();
		}
	}


	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->UpdateWrapper();
		}
	}
}
void GameObjectManager::ExecuteRender(RenderContext& rc)
{
	//�����_���[��ύX����Ȃ炱�����������Ă����Ɨǂ��B
	//�@���C�������_�����O�^�[�Q�b�g�ɐ؂�ւ���
	//�@�����_�����O�^�[�Q�b�g�̓����o�ϐ��ɂ���
	//�@�R���X�g���N�^�ŏ������B				���t�H�[�}�b�g�̈Ⴂ��ERROR���ł邩������Ȃ��B���ꂼ��̃N���X�œ����t�H�[�}�b�g�ŏ���������B
	
	/*�V���h�E�}�b�v�쐬************************************************************************/
	//�V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g�ɐݒ肷��B
	rc.WaitUntilToPossibleSetRenderTarget(shadowMap);
	rc.SetRenderTargetAndViewport(shadowMap);
	rc.ClearRenderTargetView(shadowMap);
	m_renderTypes = enRenderShade;									//�e�����
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}
	rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);
	/********************************************************************************************/

	/*�f�B�t�@�[�h�쐬*****************************************************************************/
	rc.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(defferedTargets), defferedTargets);
	rc.SetRenderTargetsAndViewport(ARRAYSIZE(defferedTargets), defferedTargets);
	rc.ClearRenderTargetViews(ARRAYSIZE(defferedTargets), defferedTargets);
	m_renderTypes = enRenderNormal;
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}
	rc.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(defferedTargets), defferedTargets);
	/********************************************************************************************/

	/*��������ŏI�I�ɕ\�������ʁi�摜�j���쐬*************************************************/
	rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	rc.SetRenderTargetAndViewport(mainRenderTarget);
	rc.ClearRenderTargetView(mainRenderTarget);
	defferedSprite.Draw(rc);

	//UI��|�X�g�G�t�F�N�g�̊|�������Ȃ��摜���őO�ʂɃh���[
	/*m_renderTypes = enRenderUI;
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}*/

	rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	/********************************************************************************************/
	
	//�u���[����AA���s��
	m_postEffect.Render(rc, mainRenderTarget);

	/*���݂̃����_�[�^�[�Q�b�g���t���[���o�b�t�@�ɃR�s�[*****************************************/
	rc.SetRenderTarget(
		g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		g_graphicsEngine->GetCurrentFrameBuffuerDSV()
	);
	//�`�悷��T�C�Y��ݒ�
	rc.SetViewport(g_graphicsEngine->GetFrameBufferViewport());
	rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
	/********************************************************************************************/

	finalSpriteWithFXAA.Draw(rc);
	//�ŏI�̉�ʂ�\��
	//fxaaSprite.Draw(rc);
}