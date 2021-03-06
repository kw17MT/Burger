#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "Title.h"
#include "effect/Effect.h"
#include "RenderingEngine.h"

// ウィンドウプログラムのメイン関数。
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	//ゲームオブジェクトマネージャーのインスタンスを作成する。
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();
	//サウンドを鳴らす用のインスタンス
	CSoundEngine::CreateInstance();
	CSoundEngine::GetInstance()->Init();
	//レンダリングエンジン作成
	RenderingEngine::CreateInstance();
	RenderingEngine::GetInstance().PrepareRender();

	//エフェクトを出すインスタンス
	EffectEngine::CreateInstance();

	//ゲームタイムを測るもの
	CStopwatch stopWatch;
	
	//プレイヤー、文字、オブジェクトなどの生成
	NewGO<Title>(0, "title");


		
	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();
		
		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////
		//オブジェクトのアップデート関数を一気に行う
		GameObjectManager::GetInstance()->ExecuteUpdate();
		//オブジェクトのドローを行う
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		RenderingEngine::GetInstance().Render(renderContext);

		//スピンロックを行う。
		int restTime = 0;
		do {
			stopWatch.Stop();
			restTime = 16 - (int)stopWatch.GetElapsedMillisecond();
		} while (restTime > 0);
		//ストップウォッチの計測終了
		stopWatch.Stop();
		//デルタタイムをストップウォッチの計測時間から、計算する
		GameTime().PushFrameDeltaTime((float)stopWatch.GetElapsed());

		////ゲームタイムを用いてエフェクトの再生進行度の更新
		//EffectEngine::GetInstance()->Update(GameTime().GetFrameDeltaTime());
		////エフェクトの描画
		//EffectEngine::GetInstance()->Draw();


		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	//サウンドエンジンの消去
	CSoundEngine::DeleteInstance();
	return 0;
}