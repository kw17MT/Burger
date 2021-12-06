#pragma once
#include "Bloom.h"
#include "FXAA.h"

class PostEffect
{
public:
	void Init(RenderTarget& mainRenderTarget);

	void Init(RenderTarget& mainRenderTarget, RenderTarget& depthRenderTarget,
		RenderTarget& normalRenderTarget,
		RenderTarget& metallicSmoothRenderTarget,
		RenderTarget& albedoRenderTarget );

	void Render(RenderContext& rc, RenderTarget& TargetToApply);
private:
	Bloom m_bloom;
	FXAA m_fxaa;
};