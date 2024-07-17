/**
 * @file MyApp.h
 * @brief ゲームアプリケーションの基盤となるクラス
 *
 * このファイルには、ゲーム全体の管理を行うMyAppクラスが定義されています。
 * MyAppクラスはシングルトンパターンを使用して実装されており、
 * ゲームの初期化、メインループ、リソースの解放などの基本的な機能を提供します。
 *
 * @date 2024/06/28
 * @author サトウ
 */

#ifndef _MYAPP_H_
#define _MYAPP_H_

#include "Singleton.h"
#include "Timer.h"
#include "GameStatics.h"
#include "World.h"

 /**
  * @enum GameState
  * @brief ゲーム全体の状態遷移を表す列挙型
  *
  * ゲームの各フェーズ（開始待ち、進行中、クリア）を定義します。
  */
enum GameState
{
	GAME_STATE_READY,    ///< ゲーム開始待ち
	GAME_STATE_PLAYING,  ///< ゲーム進行中
	GAME_STATE_CLEAR,    ///< ステージクリア

	GAME_STATE_COUNT,    ///< 状態の数を表す
	GAME_STATE_INVALID = -1, ///< 無効な状態
};

/**
 * @class MyApp
 * @brief ゲームアプリケーションの基盤クラス
 *
 * MyAppクラスは、シングルトンパターンを使用して、
 * ゲームアプリケーションの初期化、メインループ、リソースの解放などを管理します。
 */
class MyApp : public Singleton<MyApp>
{
	// SingletonクラスがMyAppのプライベートコンストラクタにアクセスできるようにする
	friend class Singleton<MyApp>;
protected:
	/**
	 * @brief コンストラクタ
	 *
	 * シングルトンパターンを維持するためにprotectedにしています。
	 */
	MyApp() 
	: pDevice(NULL)
	, pSprite(NULL)
	, pFont(NULL)
	{
	};
	/**
	 * @brief デストラクタ
	 *
	 * シングルトンパターンを維持するためにprotectedにしています。
	 */
	~MyApp() {};

public:
	/**
	 * @brief アプリケーションを初期化する
	 *
	 * ゲームの初期化処理を行います。
	 *
	 * @return 成功した場合はtrue、失敗した場合はfalseを返します。
	 */
	bool InitApp();
	

	/**
	 * @brief ウィンドウのリサイズ処理
	 *
	 * ウィンドウのリサイズ処理を行います。
	 *
	 * @param width ウィンドウの幅
	 * @param height ウィンドウの高さ
	 */
	void ResizeWindow(int, int);


	/**
	 * @brief 描画開始処理
	 *
	 * 描画処理を開始します。
	 *
	 * @return 成功した場合はtrue、失敗した場合はfalseを返します。
	 */
	bool DrawStart();

	/**
	 * @brief 描画終了処理
	 *
	 * 描画処理を終了します。
	 */
	void DrawEnd();
	/**
	 * @brief メインループを実行する
	 *
	 * ゲームのメインループを実行します。通常、この関数はゲームのメインループが終了するまで呼び出されます。
	 */
	void	MainLoop();
	/**
	 * @brief リソースを解放する
	 *
	 * ゲームで使用したリソースの解放処理を行います。
	 */
	void	ReleaseData();
	/**
	 * @brief D3Dスプライトを取得する
	 *
	 * D3Dスプライトを返します。
	 *
	 * @return D3Dスプライト
	 */

	ID3DXFont* GetFont() { return pFont; }
	ID3DXSprite* GetSprite() { return pSprite; }
	IDirect3DDevice9* GetDevice() { return pDevice; }
	HWND GetHWND() { return hWnd; }
	HINSTANCE GetHInstance() { return hInstance; }
private:
	HRESULT InitDirect3D();
	HRESULT InitFont();
private:
	HINSTANCE hInstance;		// インスタンスハンドル.
	HWND hWnd;					// 表示ウィンドウ.

	IDirect3D9* pD3D;		   // Direct3Dインスタンスオブジェクト.

	IDirect3DDevice9* pDevice; // Direct3Dデバイスオブジェクト.
	ID3DXSprite* pSprite;	   // スプライト.

	ID3DXFont* pFont;		   // フォント.
};


#endif // !_MYAPP_H_