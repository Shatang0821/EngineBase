/**
 * @file World.h
 * @brief ゲーム全般を管理するクラス
 *
 * @author サトウ
 * @date 2024/06/21
 */
#ifndef _WORLD_H_
#define _WORLD_H_

#include <set>
#include "Object.h"
#include "Level.h"
#include "GameInstance.h"

 /**
  * @class World
  * @brief ゲームを管理するクラス
  *
  * @details このクラスは、
  * ゲーム内のタイマー、UI、シーンオブジェクトを管理するクラス
  * 
  */
class World final
{
	friend class Engine;
	friend class GameStatics;
	friend class Timer;

	friend void Object::Destroy();
private:
	/* シーンオブジェクト、UI、タイマーコンテナ*/

	//! オブジェクトコンテナ
	std::set<class Object*>GameObjects;
	//! 削除予定のオブジェクトコンテナ
	std::set<class Object*>GameObjects_to_delete;

	//! UIコンテナ
	std::set<class UserInterface*>GameUIs;
	//! 削除予定のUIコンテナ
	std::set<class UserInterface*>GameUIs_to_delete;

	//! タイマーコンテナ
	std::set<class Timer*>GameTimers;

	/* レンダラー、コライダーコンテナ*/

	//! レンダラーコンテナ
	std::set<class LayerInterface*>GameRenderers;
	//! コライダーコンテナ
	std::set<class BoxCollider*>GameColliders;	//まずボックスだけで
	//             Circle実装予定

	/*ゲームシングルトンオブジェクト*/

	//! シーンを指すインスタンス
	Level* currentLevel = nullptr;
	//! 入力と出力管理
	class Controller* mainController = nullptr;
	//! ゲームデータ管理
	GameInstance* gameInstance = nullptr;

	/* メインロジック */

	/**
	 * @brief ゲーム更新処理
	 *
	 * この関数は、ゲームの状態を更新します。
	 *
	 * @param DeltaTime 前フレームからの経過時間
	 */
	void Update(float DeltaTime);

	/**
	 * @brief ゲーム描画更新処理
	 *
	 * この関数は、ゲームの描画を更新します。
	 */
	void Render();

	/**
	 * @brief 入力更新処理
	 *
	 * この関数は、ゲームの入力を更新します。
	 */
	void Input();
};

extern World mainWorld;
#endif // !_WORLD_H_



