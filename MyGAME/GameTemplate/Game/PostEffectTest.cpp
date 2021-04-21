#include "stdafx.h"
#include "PostEffectTest.h"

//void PostEffectTest::InitRootSig(RootSignature& rs)
//{
//	rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
//		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
//		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
//		D3D12_TEXTURE_ADDRESS_MODE_WRAP);
//}
//
//void PostEffectTest::InitMainRenderTarget()
//{
//	mainRenderTarget.Create(
//		1280,
//		720,
//		1,
//		1,
//		DXGI_FORMAT_R32G32B32A32_FLOAT,
//		DXGI_FORMAT_D32_FLOAT
//	);
//}
//
//void PostEffectTest::InitLuminanceRenderTarget()
//{
//	luminanceRenderTarget.Create(
//		1280,
//		720,
//		1,
//		1,
//		DXGI_FORMAT_R32G32B32A32_FLOAT,
//		DXGI_FORMAT_D32_FLOAT
//	);
//}
//
//void PostEffectTest::InitLuminaceSprite()
//{
//	luminanceSpriteData.m_fxFilePath = "Assets/shader/postEffect.fx";
//	luminanceSpriteData.m_vsEntryPointFunc = "VSMain";
//	luminanceSpriteData.m_psEntryPoinFunc = "PSLuminance";
//	luminanceSpriteData.m_width = 1280;
//	luminanceSpriteData.m_height = 720;
//
//	luminanceSpriteData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
//
//	luminanceSpriteData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
//
//
//	luminanceSprite.Init(luminanceSpriteData);
//
//	//�K�E�V�A���u���[��������
//	gaussianBlur.Init(&luminanceRenderTarget.GetRenderTargetTexture());
//}
//
//void PostEffectTest::InitFinalSprite()
//{
//	finalSpriteData.m_textures[0] = &gaussianBlur.GetBokeTexture();
//	finalSpriteData.m_width = 1280;
//	finalSpriteData.m_height = 720;
//
//	finalSpriteData.m_fxFilePath = "Assets/shader/sample2D.fx";
//	finalSpriteData.m_alphaBlendMode = AlphaBlendMode_Add;
//	finalSpriteData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
//
//	finalSprite.Init(finalSpriteData);
//}
//
//void PostEffectTest::InitFrameBufferSprite()
//{
//	copyToFrameBufferSpriteData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
//	copyToFrameBufferSpriteData.m_width = 1280;
//	copyToFrameBufferSpriteData.m_height = 720;
//
//	copyToFrameBufferSpriteData.m_fxFilePath = "Assets/shader/sample2D.fx";
//
//	copyToFrameBufferSprite.Init(copyToFrameBufferSpriteData);
//}


bool PostEffectTest::Start()
{
	modelData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	modelData.m_fxFilePath = "Assets/shader/sample3D.fx";

	modelData.m_vsEntryPointFunc = "VSMain";
	modelData.m_vsSkinEntryPointFunc = "VSSkinMain";

	modelData.m_modelUpAxis = enModelUpAxisZ;

	modelData.m_expandConstantBuffer = &g_postLig;
	modelData.m_expandConstantBufferSize = sizeof(g_postLig);

	m_skeleton.Init("Assets/modelData/unityChan.tks");
	modelData.m_skeleton = &m_skeleton;

	// �����_�����O����J���[�o�b�t�@�[�̃t�H�[�}�b�g���w�肷��
	modelData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	model.Init(modelData);
	m_charaCon.Init(0.0f, 0.0f, m_pos);

	
	return true;
}

void PostEffectTest::Update()
{
	m_skeleton.Update(model.GetWorldMatrix());

	{
		////�����_�����O�^�[�Q�b�g��mainRenderTarget�ɕύX����
		//renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		//renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		//renderContext.ClearRenderTargetView(mainRenderTarget);

		////mainRenderTarget�Ɋe�탂�f����`�悷��
		//model.Draw(renderContext);
		//renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

		////�P�x���o
		//renderContext.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
		//renderContext.SetRenderTargetAndViewport(luminanceRenderTarget);
		//renderContext.ClearRenderTargetView(luminanceRenderTarget);
		//luminanceSprite.Draw(renderContext);
		//renderContext.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);

		////�K�E�V�A���u���[�����s����
		//gaussianBlur.ExecuteOnGPU(renderContext, 20);

		////�{�P�摜�����C�������_�����O�^�[�Q�b�g�ɉ��Z����
		//renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		//renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		//finalSprite.Draw(renderContext);
		//renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

		////���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
		//renderContext.SetRenderTarget(
		//	g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		//	g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		//);
		//copyToFrameBufferSprite.Draw(renderContext);
	}


	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);
	}

	model.UpdateWorldMatrix(m_pos, g_quatIdentity, g_vec3One);
}