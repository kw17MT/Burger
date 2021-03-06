#pragma once
class SpriteRender;
class Level2D;
class Result;
#include "Level2D.h"
class ToTitleSprite;

class MissCounter : public IGameObject
{
private:
	int m_pl1MissCount = 0;								//プレイヤー１のミス数				
	int m_pl2MissCount = 0;								//プレイヤー２のミス数

	bool m_pl1Win = false;								//プレイヤー1は勝ったか
	bool m_pl2Win = false;								//プレイヤー2は勝ったか
	bool m_shouldChangeFilePath = false;				//どれかの画像を変えるべきか
	bool m_isGameSet = false;							//ゲームが終了したか

	float m_missSpriteCounter1 = 0.0f;
	float m_missSpriteCounter2 = 0.0f;

	bool m_finishToTitleSprite = false;
public:
	~MissCounter();

	/**
	 * @brief レベルを用いた画像の配置
	 * @return true
	*/
	bool Start();

	/**
	 * @brief プレイヤーのミス数に応じて画像を変更する。WIN,LOSEの結果発表も
	*/
	void Update();

	/**
	 * @brief プレイヤー１のミス数を加算する
	*/
	void AddPl1MissCount() { m_pl1MissCount++; }
	
	/**
	 * @brief プレイヤー２のミス数を加算する
	*/
	void AddPl2MissCount() { m_pl2MissCount++; }

	/**
	 * @brief どれかの画像を変更するべきか
	 * @param state TRUE＝するべき
	*/
	void ChangeMarkState(bool state) { m_shouldChangeFilePath = state; }

	/**
	 * @brief 四角の画像をバツの画像に変える。
	*/
	void TurnSquareIntoCross();

	/**
	 * @brief 結果の画像を出現させる。
	*/
	void PopResultSprite();

	/**
	 * @brief ミスの画像を出現後、所定の位置に移動させる
	 * @param popPos 一番初めに出現させる位置
	 * @param targetPos 最終的な位置
	*/
	void PopMissSprite(int no);

private:
	Level2D m_level2D;											//レベル２Dの取得用
	std::array<Result*, 2> m_result = {nullptr};				//リザルト表示する画像取得用
	std::array<SpriteRender*, 6> m_spriteRender = { nullptr };	//ミスカウンター用の画像
	std::array<SpriteRender*, 6> m_missSprite = { nullptr };
	ToTitleSprite* m_toTitle = nullptr;
};

