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
	mainRenderTarget.Create(
		1280,
		720,
		1,
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);

	//�ŏI�\���p�̉摜�f�[�^
	copyToBufferSpriteData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
	copyToBufferSpriteData.m_width = 1280;
	copyToBufferSpriteData.m_height = 720;
	copyToBufferSpriteData.m_fxFilePath = "Assets/shader/spriteHalfAlpha.fx";

	copyToBufferSprite.Init(copyToBufferSpriteData);

	//�P�x�p�̃����_�[�^�[�Q�b�g�̏�����
	luminanceRenderTarget.Create(
		1280,
		720,
		1,
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);
	//�P�x�p�̃X�v���C�g�f�[�^�ƃX�v���C�g�̏�����
	luminanceSpriteData.m_fxFilePath = "Assets/shader/postEffect.fx";
	luminanceSpriteData.m_vsEntryPointFunc = "VSMain";
	luminanceSpriteData.m_psEntryPoinFunc = "PSLuminance";
	luminanceSpriteData.m_width = 1280;
	luminanceSpriteData.m_height = 720;

	luminanceSpriteData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
	luminanceSpriteData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	luminanceSprite.Init(luminanceSpriteData);

	//�K�E�V�A���u���[�̏�����
	gaussianBlur[0].Init(&luminanceRenderTarget.GetRenderTargetTexture());
	gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
	gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
	gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());

	//�ŏI�\���p�̉摜�̏�����
	finalSpriteData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
	finalSpriteData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
	finalSpriteData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
	finalSpriteData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();
	finalSpriteData.m_width = 1280;
	finalSpriteData.m_height = 720;

	finalSpriteData.m_fxFilePath = "Assets/shader/spriteHalfAlpha.fx";
	finalSpriteData.m_alphaBlendMode = AlphaBlendMode_Add;
	finalSpriteData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	finalSprite.Init(finalSpriteData);

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
	depthInViewMap.Create(
		1280,
		720,
		1,
		1,
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_UNKNOWN
	);

	depthGaussian.Init(&mainRenderTarget.GetRenderTargetTexture());

	//��ʊE�[�x���݂̍����摜
	combineDepthSpriteData.m_textures[0] = &depthGaussian.GetBokeTexture();//&gaussianBlur[0].GetBokeTexture();
	combineDepthSpriteData.m_textures[1] = &depthInViewMap.GetRenderTargetTexture();
	combineDepthSpriteData.m_width = 1280;
	combineDepthSpriteData.m_height = 720;
	combineDepthSpriteData.m_fxFilePath = "Assets/shader/depthInView.fx";
	combineDepthSpriteData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
	combineDepthSpriteData.m_alphaBlendMode = AlphaBlendMode_Trans;
	depthInViewSprite.Init(combineDepthSpriteData);

	//depthTargets[] = { &mainRenderTarget, &depthInViewMap };
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
	m_renderTypes = 1;									//�e�����
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}
	rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);
	/********************************************************************************************/


	/*�ʏ�}�b�v�쐬*****************************************************************************/
	rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	rc.SetRenderTargetAndViewport(mainRenderTarget);
	rc.ClearRenderTargetView(mainRenderTarget);
	m_renderTypes = 0;
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}

	rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	/********************************************************************************************/

	/*��ʊE�[�x�}�b�v�쐬***********************************************************************/
	rc.WaitUntilToPossibleSetRenderTargets(2, depthTargets);
	rc.SetRenderTargetsAndViewport(2, depthTargets);
	rc.ClearRenderTargetViews(2, depthTargets);
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}

	rc.WaitUntilFinishDrawingToRenderTargets(2, depthTargets);
	depthGaussian.ExecuteOnGPU(rc, 120);
	/********************************************************************************************/


	/*�쐣���K�E�V�A���u���[*********************************************************************/
	rc.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
	rc.SetRenderTargetAndViewport(luminanceRenderTarget);
	rc.ClearRenderTargetView(luminanceRenderTarget);
	m_renderTypes = 2;
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}
	rc.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);

	gaussianBlur[0].ExecuteOnGPU(rc, 5);
	gaussianBlur[1].ExecuteOnGPU(rc, 5);
	gaussianBlur[2].ExecuteOnGPU(rc, 5);
	gaussianBlur[3].ExecuteOnGPU(rc, 5);
	/********************************************************************************************/

	/*��������ŏI�I�ɕ\�������ʁi�摜�j���쐬*************************************************/
	rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	rc.SetRenderTargetAndViewport(mainRenderTarget);
	finalSprite.Draw(rc);
	depthInViewSprite.Draw(rc);
	rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	/********************************************************************************************/
	
	/*���݂̃����_�[�^�[�Q�b�g���t���[���o�b�t�@�ɃR�s�[*****************************************/
	rc.SetRenderTarget(
		g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		g_graphicsEngine->GetCurrentFrameBuffuerDSV()
	);
	//�`�悷��T�C�Y��ݒ�
	rc.SetViewport(g_graphicsEngine->GetFrameBufferViewport());
	rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
	/********************************************************************************************/

	//�ŏI���ʕ\��
	copyToBufferSprite.Draw(rc);
}