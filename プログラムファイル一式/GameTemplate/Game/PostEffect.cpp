#include "stdafx.h"
#include "PostEffect.h"

void PostEffect::Init(RenderTarget& mainRenderTarget)
{
	//���C����ʂ���u���[�����쐬����
	m_bloom.Init(mainRenderTarget);
	//���C����ʂɃA���`�G�C���A�X���|����
	m_fxaa.Init(mainRenderTarget);
}

void PostEffect::Render(RenderContext& rc, RenderTarget& TargetToApply)
{
	//�u���[���쐬
	m_bloom.Render(rc, TargetToApply);
	//�A���`�G�C���A�X�쐬
	m_fxaa.Render(rc, TargetToApply);
}