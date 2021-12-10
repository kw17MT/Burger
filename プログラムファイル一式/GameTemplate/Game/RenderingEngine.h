#pragma once
#include "postEffect.h"
#include "ForwardBloom.h"

enum EnRenderTypes
{
	enRenderNormal,							//通常描画
	enRenderShade,							//影の描画
	enRenderLuminance,						//輝度の描画
	enRenderUI								//UIの描画
};

class RenderingEngine
{
	static RenderingEngine* instance;
public:
	RenderingEngine();
	/**
	 * @brief インスタンスの取得
	 * @return 具材管理のインスタンス
	*/
	static RenderingEngine& GetInstance()
	{
		static RenderingEngine instance;
		return instance;
	}

	/**
	 * @brief インスタンスの作成
	*/
	static void CreateInstance()
	{
		instance = new RenderingEngine;
	}

	/**
	 * @brief インスタンスの削除
	*/
	static void DeleteInstance()
	{
		delete instance;
	}

	Camera& GetLightCamera()
	{
		return lightCamera;
	}

	const EnRenderTypes& GetRenderTypes() const
	{
		return m_renderTypes;
	}

	void SetRenderTypes(EnRenderTypes TypeNumber)
	{
		m_renderTypes = TypeNumber;
	}

	void PrepareRender();

	void InitRenderTarget();

	void InitSprite();

	void InitLightCamera();

	void CreateShadowMap(RenderContext& rc);
	void CreateDeffered(RenderContext& rc);
	void CreateMainRenderTarget(RenderContext& rc);
	void CreateForwardBloom(RenderContext& rc);
	void CreateUI(RenderContext& rc);

	void Render(RenderContext& rc);

private:
	//指定のものをレンダリングする。
	EnRenderTypes m_renderTypes = enRenderNormal;
	//メインレンダーターゲット
	RenderTarget mainRenderTarget;
	//フレームバッファにコピーしてきた画像の貼り付け
	SpriteInitData finalSpriteData;
	Sprite finalSprite;
	//シャドウ関連
	float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
	RenderTarget shadowMap;
	//ライト座標から見た影を作るためのもの
	Camera lightCamera;
	//ディファードレンダリング関連
	//アルベドマップ
	RenderTarget albedoMap;
	//法線マップ
	RenderTarget normalMap;
	//ワールド座標マップ
	RenderTarget specAndDepthMap;
	RenderTarget* defferedTargets[3] = { &albedoMap, &normalMap, &specAndDepthMap };
	//ディファードライティング作成の画像
	SpriteInitData defferedSpriteData;
	Sprite defferedSprite;
	//フォワードレンダリング用のブルーム作成ターゲット
	RenderTarget forwardBloomTarget;
	//特別にフォワードレンダリングでブルームをかけたいものがあるため
	ForwardBloom m_forwardBloom;
	//ポストエフェクトをまとめたもの
	PostEffect m_postEffect;

	GaussianBlur shadowBlur;
};

