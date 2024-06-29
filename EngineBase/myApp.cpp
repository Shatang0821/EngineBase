#include "stdafx.h"
#include "myApp.h"
#include "SpriteRenderer.h"

//#define FULLSCREEN

// ウィンドウタイトルバーに表示されるバージョン名.
#define WDATE(x, y) _T(x y)
static const TCHAR* version = WDATE(__DATE__, __TIME__);

#define APP_NAME _T("Game")

// 関数のプロトタイプ宣言.
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
const TCHAR* D3DErrStr(HRESULT res);

bool MyApp::InitApp()
{
	// このプログラムが実行されるときのインスタンスハンドルを取得.
	hInstance = GetModuleHandle(NULL);

	// まずウィンドウクラスを登録する.
	// これはウィンドウ生成後の処理の仕方をWindowsに教えるためである.
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));		// 変数wcをゼロクリアする.
	wc.cbSize = sizeof(WNDCLASSEX);				// この構造体の大きさを与える.
	wc.lpfnWndProc = (WNDPROC)WindowProc;		// ウィンドウプロシージャ登録.
	wc.hInstance = hInstance;					// インスタンスハンドルを設定.
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);	// マウスカーソルの登録.
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);// 背景をGRAYに.
	wc.lpszClassName = APP_NAME;				// クラス名、CreateWindowと一致させる.
	RegisterClassEx(&wc);						// 登録.

	RECT rc = { 0, 0, WIDTH, HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	_tprintf(_T("rc: %d, %d -- %d, %d\n"), rc.left, rc.top, rc.right, rc.bottom);

	// ウィンドウを作成する.
	hWnd = CreateWindow(APP_NAME, version, WS_OVERLAPPEDWINDOW, 0, 0, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
	assert(hWnd != NULL);

	// Direct3Dを初期化する.
	HRESULT hr = InitDirect3D();
	if (FAILED(hr)) {
		MessageBox(NULL, D3DErrStr(hr), _T("Direct3D初期化失敗"), MB_OK);
		return false;
	}
	
	// スプライトの作成.
	hr = D3DXCreateSprite(pDevice, &(pSprite));
	if (FAILED(hr)) {
		MessageBox(NULL, D3DErrStr(hr), _T("スプライト作成失敗"), MB_OK);
		return false;
	}

	// テクスチャを読み込む。エラー時にはLoadTextureは例外を発生させる.
	// LoadTextureごとにif判定をするのは面倒なので、try～throw～catchを使う.
	try {
		// テストテクスチャの読み込み.

	}
	// catch句はtryの直後に記述する.
	catch (HRESULT /*hr*/) {
		return false;
	}

	return true;
}

bool MyApp::DrawStart()
{
	auto myApp = MyApp::Instance();
	D3DCOLOR rgb = D3DCOLOR_XRGB(10, 10, 80);
	HRESULT hr = myApp->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, rgb, 1.0f, 0);
	if (FAILED(hr)) {
		_tprintf(D3DErrStr(hr));
		return false;
	}

	// 描画を開始（シーン描画の開始）.
	if (FAILED(myApp->GetDevice()->BeginScene())) {
		return false;
	}

	if (FAILED(myApp->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		return false;
	}
	return true;
}

void MyApp::DrawEnd()
{
	auto myApp = MyApp::Instance();
	myApp->GetSprite()->End();
	myApp->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	// 描画を終了（シーン描画の終了）.
	myApp->GetDevice()->EndScene();

	// 実際に画面に表示。バックバッファからフロントバッファへの転送.
	// デバイス生成時のフラグ指定により、ここでVSYNCを待つ.
	myApp->GetDevice()->Present(NULL, NULL, NULL, NULL);
}

void MyApp::MainLoop()
{
	
}

// マクロを複数行で書きたいときは\を行末に付けることで可能.
#define RELEASE(__xx__)    \
	if (__xx__)            \
	{                      \
		__xx__->Release(); \
		__xx__ = NULL;     \
	}


void MyApp::ReleaseData()
{

	// テクスチャの開放.
	MyTexture::ReleaseAll();
	
	// DirectXデバイスの開放.
	RELEASE(pSprite);
	RELEASE(pDevice);
	RELEASE(pD3D);
}

HRESULT MyApp::InitDirect3D()
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (pD3D == NULL) return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&(d3dpp), sizeof(d3dpp));

#ifdef FULLSCREEN
	d3dpp.Windowed = FALSE;
	//int fx = GetSystemMetrics(SM_CXSCREEN);
	//int fy = GetSystemMetrics(SM_CYSCREEN);
	int fx = WIDTH;
	int fy = HEIGHT;
	_tprintf(_T(" フルスクリーン%d x %d\n"), fx, fy);
	d3dpp.BackBufferHeight = fy;
	d3dpp.BackBufferWidth = fx;
#else
	d3dpp.Windowed = TRUE;
#endif

	d3dpp.BackBufferHeight = HEIGHT;
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	
	// Present時に垂直同期に合わせる.
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// デプスステンシルバッファを有効にする
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	// D3Dデバイスオブジェクトの作成。HAL&HARD.
	HRESULT hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &(d3dpp), &(pDevice));
	if (hr == D3D_OK)
	{
		_tprintf(_T("HAL & HARD\n"));
		return hr;
	}
	// D3Dデバイスオブジェクトの作成。HAL&SOFT.
	hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &(d3dpp), &(pDevice));
	if (hr == D3D_OK)
	{
		_tprintf(_T("HAL & SOFT\n"));
		return hr;
	}
	// D3Dデバイスオブジェクトの作成。REF&HARD.
	hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &(d3dpp), &(pDevice));
	if (hr == D3D_OK)
	{
		_tprintf(_T("REF & HARD\n"));
		return hr;
	}
	// D3Dデバイスオブジェクトの作成。REF&SOFT.
	hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &(d3dpp), &(pDevice));
	if (hr == D3D_OK)
	{
		_tprintf(_T("REF & SOFT\n"));
		return hr;
	}
	return hr;
}
