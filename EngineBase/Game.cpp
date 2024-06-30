#include "stdafx.h"
#include "myApp.h"
#include "StaticMesh.h"
#include "ResourceManager.h"
#include "GameLevel.h"
#include "GameController.h"

// イベント処理コールバック（ウィンドウプロシージャ）.
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// イベントの種類に応じて、switch文にて処理を切り分ける.
	switch (uMsg) {
	case WM_KEYDOWN: {
		// ESCキーが押下されたら終了.
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
		}
		break;
	}

	case WM_CLOSE: {// 終了通知(CLOSEボタンが押された場合など)が届いた場合.
		// プログラムを終了させるため、イベントループに0を通知する.
		// この結果、GetMessageの戻り値は0になる.
		PostQuitMessage(0);
		break;
	}

	default: {
		break;
	}
	}

	// デフォルトのウィンドウイベント処理.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
// エラー発生時のHRESULTを文字列に変換するための補助関数.
const TCHAR* D3DErrStr(HRESULT res)
{
	switch (res) {
	case D3D_OK: return _T("D3D_OK");
	case D3DERR_DEVICELOST: return _T("D3DERR_DEVICELOST");
	case D3DERR_DRIVERINTERNALERROR: return _T("D3DERR_DRIVERINTERNALERROR");
	case D3DERR_INVALIDCALL: return _T("D3DERR_INVALIDCALL");
	case D3DERR_OUTOFVIDEOMEMORY: return _T("D3DERR_OUTOFVIDEOMEMORY");
	case D3DERR_DEVICENOTRESET: return _T("D3DERR_DEVICENOTRESET");
	case D3DERR_NOTAVAILABLE: return _T("D3DERR_NOTAVAILABLE");
	case D3DXERR_INVALIDDATA: return _T("D3DXERR_INVALIDDATA");
	case MMSYSERR_NODRIVER: return _T("MMSYSERR_NODRIVER");
	case MMSYSERR_INVALPARAM: return _T("MMSYSERR_INVALPARAM");
	case MMSYSERR_BADDEVICEID: return _T("MMSYSERR_BADDEVICEID");
	case JOYERR_UNPLUGGED: return _T("JOYERR_UNPLUGGED");
	case JOYERR_PARMS: return _T("JOYERR_PARMS");
	case E_OUTOFMEMORY: return _T("E_OUTOFMEMORY");
	}
	return _T("unknown error");
}

class Engine
{
public:
	/**
	 * @brief エンジン初期化処理
	 */
	static void Init()
	{
		// ライブラリ初期化
		MyApp::Instance()->InitApp();
		//Engine初期化
		ResourceManager::Instance()->Initalize();
		//ワールド初期化
		mainWorld.currentLevel = new GameLevel;
		mainWorld.gameInstance = new GameInstance;

		//mainWorld.mainController = new Controller;
		mainWorld.mainController = GameStatics::CreateObject<GameController>();
	}

	/**
	 * @brief エンジン更新処理
	 */
	static void Tick()
	{

		// フレーム開始時のタイマーリセット
		mainWorld.Timer.StartTimer();

		// 入力処理
		mainWorld.Input();

		// 固定時間ステップでの物理更新
		mainWorld.fixedAccumulator += mainWorld.deltaTime;
		while (mainWorld.fixedAccumulator >= FIXED_DELTA_TIME)
		{
			mainWorld.FixedUpdate();
			mainWorld.fixedAccumulator -= FIXED_DELTA_TIME;
		}

		// ロジック更新
		mainWorld.Update(mainWorld.deltaTime);

		// 描画の準備
		MyApp::Instance()->DrawStart();

		// 描画処理
		mainWorld.Render();

		// 描画終了
		MyApp::Instance()->DrawEnd();

		// 更新処理後の時間計測
		float updateTime;
		mainWorld.Timer.GetPassTime(&updateTime);

		// フレームレート制御 (例えば、60FPSを目指す場合)
		if (updateTime < FRAME_TIME) {
			DWORD sleepTime = static_cast<DWORD>((FRAME_TIME - updateTime) * 1000);
			timeBeginPeriod(1);
			Sleep(sleepTime);
			timeEndPeriod(1);
		}

		// deltaTimeの計算
		mainWorld.Timer.GetPassTime(&mainWorld.deltaTime);
		// FPSの計算
		mainWorld.fps = 1.0f / mainWorld.deltaTime;
	}



	/**
	 * @brief エンジン終了処理
	 */
	static void Exit() {
		MyApp::Instance()->ReleaseData();
	}

};

class TestObject : public Object

{
private:
	Timer TimeHandle;
	Timer TimeHandle2;
public:
	TestObject() {
		TimeHandle.Bind(0.5,this,&TestObject::Func,true);
		TimeHandle2.Bind(2.0,this,&TestObject::Func2,true);
	}

private:
	void Func()
	{
		std::cout << "Hello World" << std::endl;
	}
	void Func2()
	{
		std::cout << "By World" << std::endl;
	}

};


int main() {
	setlocale(LC_ALL, "Japanese");		// 日本語にロケールを設定.

#ifdef MEMORY_LEAK
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif
	for (int i = 0; i < 10; i++) {
		std::cout << Math::RandReal(0,10) << std::endl;
	}
	
	Engine::Init();

	ShowWindow(MyApp::Instance()->GetHWND(), SW_SHOWNORMAL);	// 作成したウィンドウを表示する.

	// イベントループ.
	// ブロック型関数GetMessageではなくノンブロック型関数のPeekMessageを使う.
	MSG msg;
	bool flag = true;
	while (flag) {
		// メッセージがあるかどうか確認する.
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			// メッセージがあるので処理する.
			if (GetMessage(&msg, NULL, 0, 0) != 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				flag = 0;
			}
		}
		else {

			Engine::Tick();
		}
		// Sleepなど行っていないが、DrawData関数内のpDevice->Presentが.
		// 画面更新待ちを行うので、結果的にVSyncごとにイベントループが回る.
	}

	Engine::Exit();

#ifdef MEMORY_LEAK
	_CrtDumpMemoryLeaks();		// メモリリークを検出する.
#endif
	return 0;
}