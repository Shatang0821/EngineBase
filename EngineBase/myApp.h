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
	MyApp() {
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
	bool	InitApp();
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
};

#endif // !_MYAPP_H_



