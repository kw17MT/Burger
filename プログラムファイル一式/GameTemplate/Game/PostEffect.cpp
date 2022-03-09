#include "stdafx.h"
#include "PostEffect.h"

void PostEffect::Init(RenderTarget& mainRenderTarget)
{
	//メイン画面からブルームを作成する
	m_bloom.Init(mainRenderTarget);
	//メイン画面にアンチエイリアスを掛ける
	m_fxaa.Init(mainRenderTarget);
}

void PostEffect::Render(RenderContext& rc, RenderTarget& TargetToApply)
{
	//ブルーム作成
	m_bloom.Render(rc, TargetToApply);
	//アンチエイリアス作成
	m_fxaa.Render(rc, TargetToApply);
}