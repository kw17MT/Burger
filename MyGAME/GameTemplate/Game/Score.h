#pragma once
class FixedUI;
class FontRender;

class Score : public IGameObject
{
private:
	//タイムアップフラグ
	bool isTimeUp = false;

	//最終的に表示するスコア
	//具材の数 * 100
	int Score01 = 0;
	int Score02 = 0;
	//カウンター側で何層のハンバーガーを提供したか。
	//提供した具材を数えておく。
	int BasePoint01 = 0;
	int BasePoint02 = 0;

	Vector2 Score01Pos = { -400.0f,-300.0f };
	Vector2 Score02Pos = { 550.0f,-300.0f };

	RenderContext renderContext = g_graphicsEngine->GetRenderContext();
public:
	
	//ui
	FixedUI* m_ui = nullptr;

	//勝敗の状態
	//プレイヤー1
	enum EnResultP1 {
		enResultP1_draw,	//0
		enResultP1_win,		//1
		enResultP1_lose,	//2
		enResultP1Num		//ダミー(3)
	}ResultP1;

	//プレイヤー2
	enum EnResultP2 {
		enResultP2_draw,	//0
		enResultP2_win,		//1
		enResultP2_lose,	//2
		enResultP2Num		//ダミー(3)
	}ResultP2;


	bool Start();

	//カウンター側でnumをあてはめ、こちら側のBasePointに加算する。
	void SetBasePoint01(int num) { BasePoint01 += num; }
	void SetBasePoint02(int num) { BasePoint02 += num; }
	//タイムアップ時の結果を記録
	void SetResult();

	//ゲッター
	int GetPlayer01Score() { return Score01; }
	int GetPlayer02Score() { return Score02; }
	bool GetIsTimeUp() { return isTimeUp; }
	
	//タイムアップフラグをtrueにする
	void SetIsTimeUp() { isTimeUp = true; }

	void Update();

	FontRender* Score[2];
};

