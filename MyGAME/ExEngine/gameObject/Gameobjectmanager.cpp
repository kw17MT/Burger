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

	rootSignature.Init(
		D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP
	);

	//���C���̃����_�[�^�[�Q�b�g�̏�����
	mainRenderTarget.Create(
		1280,
		720,
		1,
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);

	copyToBufferSpriteData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
	copyToBufferSpriteData.m_width = 1280;
	copyToBufferSpriteData.m_height = 720;
	copyToBufferSpriteData.m_fxFilePath = "Assets/shader/sample2D.fx";

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

	gaussianBlur.Init(&luminanceRenderTarget.GetRenderTargetTexture());

	//�ŏI�\���p�̉摜�̏�����
	finalSpriteData.m_textures[0] = &gaussianBlur.GetBokeTexture();
	finalSpriteData.m_width = 1280;
	finalSpriteData.m_height = 720;

	finalSpriteData.m_fxFilePath = "Assets/shader/sample2D.fx";
	finalSpriteData.m_alphaBlendMode = AlphaBlendMode_Add;
	finalSpriteData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	finalSprite.Init(finalSpriteData);


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
	/*rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	rc.SetRenderTargetAndViewport(mainRenderTarget);
	rc.ClearRenderTargetView(mainRenderTarget);*/

	//���f���̃h���[
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}
	////���f�����S���h���[�ł���܂ő҂B
	//rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

	////�u���[���p�̃����o�Ƃ������Ă���������


	////�P�x�p�̉摜���o�͂���
	//rc.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
	//rc.SetRenderTargetAndViewport(luminanceRenderTarget);
	//rc.ClearRenderTargetView(luminanceRenderTarget);
	//luminanceSprite.Draw(rc);
	//rc.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);

	////�K�E�V�A���u���[��������B
	//gaussianBlur.ExecuteOnGPU(rc, 40);
	////�ŏI���ʂƂȂ�摜�����C�������_�[�^�[�Q�b�g�ɐݒ肵�ĕ`��
	//rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	//rc.SetRenderTargetAndViewport(mainRenderTarget);
	//finalSprite.Draw(rc);
	//rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

	////�K�E�V�A���u���[��������B
	//gaussianBlur.ExecuteOnGPU(rc, 60);
	////�ŏI���ʂƂȂ�摜�����C�������_�[�^�[�Q�b�g�ɐݒ肵�ĕ`��
	//rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	//rc.SetRenderTargetAndViewport(mainRenderTarget);
	//finalSprite.Draw(rc);
	//rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

	////�K�E�V�A���u���[��������B
	//gaussianBlur.ExecuteOnGPU(rc, 80);
	////�ŏI���ʂƂȂ�摜�����C�������_�[�^�[�Q�b�g�ɐݒ肵�ĕ`��
	//rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	//rc.SetRenderTargetAndViewport(mainRenderTarget);
	//finalSprite.Draw(rc);
	//rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

	////�K�E�V�A���u���[��������B
	//gaussianBlur.ExecuteOnGPU(rc, 160);
	////�ŏI���ʂƂȂ�摜�����C�������_�[�^�[�Q�b�g�ɐݒ肵�ĕ`��
	//rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	//rc.SetRenderTargetAndViewport(mainRenderTarget);
	//finalSprite.Draw(rc);
	//rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

	////�A���C�������_�����O�^�[�Q�b�g�̓��e��
	////  �t���[���o�b�t�@�ɃR�s�[�B
	//rc.SetRenderTarget(
	//	g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
	//	g_graphicsEngine->GetCurrentFrameBuffuerDSV()
	//);

	//copyToBufferSprite.Draw(rc);
}