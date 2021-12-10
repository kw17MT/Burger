#include "stdafx.h"
#include "RenderingEngine.h"

RenderingEngine* RenderingEngine::instance = nullptr;

RenderingEngine::RenderingEngine()
{
	InitLightCamera();
}

void RenderingEngine::PrepareRender()
{
	InitRenderTarget();
	InitSprite();
	m_postEffect.Init(mainRenderTarget);
}

void RenderingEngine::InitRenderTarget()
{
	albedoMap.Create(1280, 720, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	normalMap.Create(1280, 720, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_UNKNOWN);
	specAndDepthMap.Create(1280, 720, 1, 1, DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_UNKNOWN);
	forwardBloomTarget.Create(1280, 720, 1, 1, DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_D32_FLOAT);
	//シャドウのオフスクリーンレンダリング作成
	shadowMap.Create(4096, 2048, 1, 1, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_D32_FLOAT, clearColor);
	//メインのレンダーターゲットの初期化
	mainRenderTarget.Create(1280,720,1,1,DXGI_FORMAT_R32G32B32A32_FLOAT,DXGI_FORMAT_D32_FLOAT);
}

void RenderingEngine::InitSprite()
{
	shadowBlur.Init(&shadowMap.GetRenderTargetTexture());

	defferedSpriteData.m_width = 1280;
	defferedSpriteData.m_height = 720;
	defferedSpriteData.m_textures[0] = &albedoMap.GetRenderTargetTexture();
	defferedSpriteData.m_textures[1] = &normalMap.GetRenderTargetTexture();
	defferedSpriteData.m_textures[2] = &specAndDepthMap.GetRenderTargetTexture();
	defferedSpriteData.m_textures[3] = &shadowBlur.GetBokeTexture();
	defferedSpriteData.m_fxFilePath = "Assets/shader/deffered/defferedSprite.fx";
	defferedSpriteData.m_alphaBlendMode = AlphaBlendMode_None;
	defferedSpriteData.m_expandConstantBuffer = (void*)&LightManager::GetInstance().GetLightData();
	defferedSpriteData.m_expandConstantBufferSize = sizeof(LightManager::GetInstance().GetLightData());
	defferedSprite.Init(defferedSpriteData);

	//最終表示用の画像データ
	finalSpriteData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
	finalSpriteData.m_width = 1280;
	finalSpriteData.m_height = 720;
	finalSpriteData.m_fxFilePath = "Assets/shader/sprite.fx";

	finalSprite.Init(finalSpriteData);

	m_forwardBloom.Init(forwardBloomTarget);
}

void RenderingEngine::InitLightCamera()
{
	//ライトカメラの作成
	lightCamera.SetPosition(0.0f, 1000.0f, -500.0f);
	lightCamera.SetTarget(0.0f, 0.0f, 0.0f);
	lightCamera.SetUp({ 0, 0, 1 });							//カメラの上をX座標にしておく
	lightCamera.SetViewAngle(Math::DegToRad(105.0f));
	//平行投影にする場合
	/*
	lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	lightCamera.SetWidth(1280);
	lightCamera.SetHeight(720);
	*/
	lightCamera.Update();
}

void RenderingEngine::CreateShadowMap(RenderContext& rc)
{
	rc.WaitUntilToPossibleSetRenderTarget(shadowMap);
	rc.SetRenderTargetAndViewport(shadowMap);
	rc.ClearRenderTargetView(shadowMap);
	m_renderTypes = enRenderShade;									//影するよ
	//シャドウの作成を行うモデルのドロー
	GameObjectManager::GetInstance()->CallRenderWrapper(rc);
	rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);
	m_renderTypes = enRenderNormal;
}

void RenderingEngine::CreateDeffered(RenderContext& rc)
{
	rc.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(defferedTargets), defferedTargets);
	rc.SetRenderTargetsAndViewport(ARRAYSIZE(defferedTargets), defferedTargets);
	rc.ClearRenderTargetViews(ARRAYSIZE(defferedTargets), defferedTargets);
	m_renderTypes = enRenderNormal;
	GameObjectManager::GetInstance()->CallRenderWrapper(rc);
	rc.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(defferedTargets), defferedTargets);
}

void RenderingEngine::CreateMainRenderTarget(RenderContext& rc)
{
	rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	rc.SetRenderTargetAndViewport(mainRenderTarget);
	rc.ClearRenderTargetView(mainRenderTarget);
	//ディファードライティングをした画像の描画
	defferedSprite.Draw(rc);
	rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
}

void RenderingEngine::CreateForwardBloom(RenderContext& rc)
{
	rc.WaitUntilToPossibleSetRenderTarget(forwardBloomTarget);
	rc.SetRenderTargetAndViewport(forwardBloomTarget);
	rc.ClearRenderTargetView(forwardBloomTarget);
	m_renderTypes = enRenderLuminance;								
	GameObjectManager::GetInstance()->CallRenderWrapper(rc);
	rc.WaitUntilFinishDrawingToRenderTarget(forwardBloomTarget);
}

void RenderingEngine::CreateUI(RenderContext& rc)
{
	rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
	rc.SetRenderTargetAndViewport(mainRenderTarget);
	m_renderTypes = enRenderUI;
	GameObjectManager::GetInstance()->CallRenderWrapper(rc);
	rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
}

void RenderingEngine::Render(RenderContext& rc)
{
	//シャドウマップの作成
	CreateShadowMap(rc);
	//シャドウマップにブラーを掛ける
	shadowBlur.ExecuteOnGPU(rc, 5);
	//デファードライティングを行う
	CreateDeffered(rc);
	//メインターゲットにディファードライティング済みの絵を描く
	CreateMainRenderTarget(rc);
	//ハンバーガに特別なブルームフィルタをかける
	CreateForwardBloom(rc);
	m_forwardBloom.Render(rc, mainRenderTarget);
	//絵全体にポストエフェクトを掛ける
	m_postEffect.Render(rc, mainRenderTarget);
	//最後にUIを描く
	CreateUI(rc);


	rc.SetRenderTarget(
		g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		g_graphicsEngine->GetCurrentFrameBuffuerDSV()
	);
	//描画するサイズを設定
	rc.SetViewport(g_graphicsEngine->GetFrameBufferViewport());
	rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

	finalSprite.Draw(rc);
}