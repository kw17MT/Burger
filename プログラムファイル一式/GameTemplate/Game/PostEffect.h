#pragma once
#include "Bloom.h"
#include "FXAA.h"

/**
 * @brief ポストエフェクトを一括で行うクラス
*/
class PostEffect
{
public:
	/**
	 * @brief ポストエフェクトで使用するゲーム画面レンダーターゲットを設定する
	 * @param mainRenderTarget ゲーム画面
	*/
	void Init(RenderTarget& mainRenderTarget);

	/**
	 * @brief ポストエフェクトを作成、描画する
	 * @param rc レンダーコンテキスト
	 * @param TargetToApply 適用したいゲーム画面
	*/
	void Render(RenderContext& rc, RenderTarget& TargetToApply);
private:
	Bloom m_bloom;	//ブルーム作成インスタンス
	FXAA m_fxaa;	//FXAA作成インスタンス
};