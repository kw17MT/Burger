#include "stdafx.h"
#include "FXAA.h"

void FXAA::Init(RenderTarget& mainRenderTarget)
{
	SpriteInitData fxaaSpriteData;

	m_fxaaTarget.Create(1280, 720, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_UNKNOWN);

	fxaaSpriteData.m_width = 1280;
	fxaaSpriteData.m_height = 720;
	fxaaSpriteData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
	fxaaSpriteData.m_fxFilePath = "Assets/shader/fxaa.fx";
	fxaaSpriteData.m_vsEntryPointFunc = "VSMain";
	fxaaSpriteData.m_psEntryPoinFunc = "PSMain";

	fxaaSpriteData.m_expandConstantBuffer = (void*)&s_data;
	fxaaSpriteData.m_expandConstantBufferSize = sizeof(s_data) +
		(16 - (sizeof(s_data) % 16));

	fxaaSpriteData.m_alphaBlendMode = AlphaBlendMode_None;

	m_finalSprite.Init(fxaaSpriteData);
}

void FXAA::Render(RenderContext& rc, RenderTarget& TargetToApply)
{
	// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
	rc.WaitUntilToPossibleSetRenderTarget(TargetToApply);
	// �����_�����O�^�[�Q�b�g��ݒ�
	rc.SetRenderTargetAndViewport(TargetToApply);
	s_data.s_width = static_cast<float>(g_graphicsEngine->GetFrameBufferWidth());
	s_data.s_height = static_cast<float>(g_graphicsEngine->GetFrameBufferHeight());
	//�`��B
	m_finalSprite.Draw(rc);
	// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
	//���C�������_�\�^�[�Q�b�g��RENDERTARGET����PRESENT�ցB
	rc.WaitUntilFinishDrawingToRenderTarget(TargetToApply);
}