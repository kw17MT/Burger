#pragma once
class FXAA
{
private:
	//fxaaを掛ける画面の縦横幅データ
	struct fxaa_data
	{
		float s_width;		//マップの幅
		float s_height;		//マップの高さ
	};
public:
	/**
	 * @brief AA作成の初期化を行う
	 * @param rt AAするレンダリングターゲット
	*/
	void Init(RenderTarget& rt);

	/**
	 * @brief アンチエイリアスする
	 * @param rc レンダーコンテキスト
	 * @param TargetToApply 適用したいターゲット
	*/
	void Render(RenderContext& rc, RenderTarget& TargetToApply);

private:
	Sprite m_finalSprite;			//適用した画像
	fxaa_data s_data;				//fxaaを掛ける画面の縦横幅データ
};

