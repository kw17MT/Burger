#include "stdafx.h"
#include "GaussianBlur.h"
//#include "RenderContext_inline.h"

void GaussianBlur::Init(Texture* originalTexture, bool isDownSamle)
{
	m_originalTexture = originalTexture;

	//レンダリングターゲットを初期化。
	InitRenderTargets(isDownSamle);
	//スプライトを初期化。
	InitSprites();
}


void GaussianBlur::ExecuteOnGPU(RenderContext& rc, float blurPower)
{
	//重みテーブルを更新する。
	UpdateWeightsTable(blurPower);

	//横ブラーを実行。
	//レンダリングターゲットとして利用できるようになるまでwaitを入れる。
	rc.WaitUntilToPossibleSetRenderTarget(m_xBlurRenderTarget);
	//レンダリングターゲットを設定。
	rc.SetRenderTargetAndViewport(m_xBlurRenderTarget);
	//レンダリングターゲットをクリア。
	rc.ClearRenderTargetView(m_xBlurRenderTarget);
	//ドロー。
	m_xBlurSprite.Draw(rc);
	//レンダリングターゲットへの書き込み終了待ち。
	rc.WaitUntilFinishDrawingToRenderTarget(m_xBlurRenderTarget);

	//縦ブラーを実行。
	//レンダリングターゲットとして利用できるようになるまでwaitを入れる。
	rc.WaitUntilToPossibleSetRenderTarget(m_yBlurRenderTarget);
	//レンダリングターゲットを設定。
	rc.SetRenderTargetAndViewport(m_yBlurRenderTarget);
	//レンダリングターゲットをクリア。
	rc.ClearRenderTargetView(m_yBlurRenderTarget);
	//ドロー。
	m_yBlurSprite.Draw(rc);
	//レンダリングターゲットへの書き込み終了待ち。
	rc.WaitUntilFinishDrawingToRenderTarget(m_yBlurRenderTarget);
}

void GaussianBlur::InitRenderTargets(bool isDownSample)
{
	float w = m_originalTexture->GetWidth();
	float half_w = w / 2;
	float h = m_originalTexture->GetHeight();
	float half_h = h / 2;
	//Xブラー用のレンダリングターゲットを作成する。
	m_xBlurRenderTarget.Create(
		//ここが1280,720になればちゃんと映る。
		//1280,720,
		isDownSample ? half_w : w,			//640
		h,									//720
		1,
		1,
		m_originalTexture->GetFormat(),
		DXGI_FORMAT_D32_FLOAT
	);

	//Yブラー用のレンダリングターゲットを作成する。
 	m_yBlurRenderTarget.Create(
		//ここが1280,720になればちゃんと映る。
		//1280, 720,
		isDownSample ? half_w : w,			//640
		isDownSample ? half_h : h,			//640
		1,
		1,
		m_originalTexture->GetFormat(),
		DXGI_FORMAT_D32_FLOAT
	);
}

void GaussianBlur::InitSprites()
{
	//横ブラー用のスプライトを初期化する。
	{
		SpriteInitData xBlurSpriteInitData;
		xBlurSpriteInitData.m_fxFilePath = "Assets/shader/blur/gaussianBlur.fx";
		xBlurSpriteInitData.m_vsEntryPointFunc = "VSXBlur";
		xBlurSpriteInitData.m_psEntryPoinFunc = "PSBlur";
		//スプライトの解像度はm_xBlurRenderTargetと同じ。
		xBlurSpriteInitData.m_width = m_xBlurRenderTarget.GetWidth();
		xBlurSpriteInitData.m_height = m_xBlurRenderTarget.GetHeight();
		//テクスチャは輝度テクスチャ。
		xBlurSpriteInitData.m_textures[0] = m_originalTexture;
		//描き込むレンダリングターゲットのフォーマットを指定する。
		xBlurSpriteInitData.m_colorBufferFormat = m_xBlurRenderTarget.GetColorBufferFormat();
		//ユーザー拡張の定数バッファにブラー用のパラメーターを設定する。
		xBlurSpriteInitData.m_expandConstantBuffer = &m_weights;
		xBlurSpriteInitData.m_expandConstantBufferSize = sizeof(m_weights);

		//初期化情報をもとに横ブラー用のスプライトを初期化する。
		m_xBlurSprite.Init(xBlurSpriteInitData);
	}
	//縦ブラー用のスプライトを初期化する。
	{
		SpriteInitData yBlurSpriteInitData;
		yBlurSpriteInitData.m_fxFilePath = "Assets/shader/blur/gaussianBlur.fx";
		yBlurSpriteInitData.m_vsEntryPointFunc = "VSYBlur";
		yBlurSpriteInitData.m_psEntryPoinFunc = "PSBlur";
		//スプライトの解像度はm_yBlurRenderTargetと同じ。
		yBlurSpriteInitData.m_width = m_yBlurRenderTarget.GetWidth();
		yBlurSpriteInitData.m_height = m_yBlurRenderTarget.GetHeight();
		//テクスチャは横ブラーをかけたもの。
		yBlurSpriteInitData.m_textures[0] = &m_xBlurRenderTarget.GetRenderTargetTexture();
		//描き込むレンダリングターゲットのフォーマットを指定する。
		yBlurSpriteInitData.m_colorBufferFormat = m_yBlurRenderTarget.GetColorBufferFormat();
		//ユーザー拡張の定数バッファにブラー用のパラメーターを設定する。
		yBlurSpriteInitData.m_expandConstantBuffer = &m_weights;
		yBlurSpriteInitData.m_expandConstantBufferSize = sizeof(m_weights);

		//初期化情報をもとに縦ブラー用のスプライトを初期化する。
		m_yBlurSprite.Init(yBlurSpriteInitData);
	}
}
void GaussianBlur::UpdateWeightsTable(float blurPower)
{
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_weights[i] = expf(-0.5f * (float)(i * i) / blurPower);
		total += 2.0f * m_weights[i];

	}
	// 規格化
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_weights[i] /= total;
	}
}