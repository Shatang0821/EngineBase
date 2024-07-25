/**
 * @file World.h
 * @brief ゲーム全般を管理するWorldクラスの定義を含むヘッダファイル。
 *
 * Worldクラスは、ゲーム内のオブジェクト、UI、タイマー、レンダラー、コライダーなどを管理します。
 * また、ゲームのメインループにおける更新、物理処理、描画処理を担当します。
 *
 * @author サトウ
 * @date 2024/06/21
 */
#ifndef _WORLD_H_
#define _WORLD_H_

#include "Object.h"
#include "GameInstance.h"
#include "VisualInterface.h"
#include "CTimer.h"
#include "Controller.h"
#include "Camera.h"


 /**
  * @struct LayerSort
  * @brief LayerInterfaceポインタをソートするための比較ファンクタ
  *
  * この構造体は、LayerInterfaceポインタを特定の基準でソートするための
  * 比較関数オブジェクトを定義します。主にstd::setのソートが必要なコンテナで使用されます。
  */
struct LayerSort
{
	/**
	 * @brief 比較演算子
	 *
	 * この関数は、2つのLayerInterfaceポインタを比較し、
	 * ソート順序を決定します。具体的には、まずLayerの値を比較し、
	 * 値が同じ場合にはポインタのアドレスを比較してソート順序を決定します。
	 *
	 * @param a 比較対象の最初のLayerInterfaceポインタ
	 * @param b 比較対象の2番目のLayerInterfaceポインタ
	 * @return aがbより前にある場合はtrue、そうでない場合はfalse
	 */
	bool operator()(const class LayerInterface* a, const class LayerInterface* b) const {
		if (a->GetLayer() == b->GetLayer())
			return a < b;
		else
			return a->GetLayer() < b->GetLayer();
	}
};

/**
 * @struct ColliderSort
 * @brief Colliderオブジェクトをソートするための比較ファンクタ。
 *
 * Colliderオブジェクトをレイヤーに基づいてソートするために使用されます。
 * 同じレイヤーの場合は、ポインタのアドレスで比較します。
 */
struct ColliderSort
{
	bool operator()(const class Collider* a, const class Collider* b) const;
};


/**
* @class World
* @brief ゲームのメインループとオブジェクト管理を担当するクラス。
*
* ゲーム内のオブジェクト、UI、タイマー、レンダラー、コライダーの管理を行います。
* Initで初期化を行い、Updateでゲームの状態を更新、FixedUpdateで物理処理を行い、
* Renderで描画処理を行います。Inputで入力処理を行い、Debugでデバッグ情報を表示します。
*/
class World final
{
	friend class MyApp;
	friend class Debug;
	friend class GameStatics;
	friend class Timer;
	friend class Controller;
	friend class LayerInterface;
	friend class Camera;
	friend class SpriteRenderer;
	friend class Collider;
	friend class CircleCollider;
	friend class BoxCollider;

	friend void Object::Destroy();
private:
	/* シーンオブジェクト、UI、タイマーコンテナ*/

	//! オブジェクトコンテナ
	std::unordered_set<class Object*>GameObjects;
	//! 削除予定のオブジェクトコンテナ
	std::unordered_set<class Object*>GameObjects_to_delete;

	//! UIコンテナ
	std::unordered_set<class UserInterface*>GameUIs;
	//! 削除予定のUIコンテナ
	std::unordered_set<class UserInterface*>GameUIs_to_delete;

	//! タイマーコンテナ
	std::unordered_set<class Timer*>GameTimers;

	/* レンダラー、コライダーコンテナ*/

	//! レンダラーコンテナ
	std::set<class LayerInterface*,LayerSort>GameRenderers;
	//! コライダーコンテナ
	std::unordered_set<class Collider*>GameColliders;
	std::set<class Collider*, ColliderSort>ColliderZones[8][6];

	/*ゲームシングルトンオブジェクト*/

	//! シーンを指すインスタンス
	class Level* currentLevel = nullptr;
	//! 入力と出力管理
	class Controller* mainController = nullptr;
	//! ゲームデータ管理
	GameInstance* gameInstance = nullptr;
	//! メインカメラ
	class Camera* mainCamera = nullptr;

	/*  FPS関連  */

	float deltaTime = 0.016f;			// 前フレームからの経過時間.
	float fixedDeltaTime = 0.02f;		// 固定間隔

	float fixedAccumulator = 0;		//経過時間

	UINT fps = 0;

	CTimer Timer;			// 時間管理オブジェクト(Update用).

private:
	/* メインロジック */


	/**
	 * @brief ゲーム初期化処理
	 * 
	 */
	bool Init();
	
	/**
	 * @brief ゲーム更新処理
	 *
	 * この関数は、ゲームの状態を更新します。
	 *
	 * @param DeltaTime 前フレームからの経過時間
	 */
	void Update(float DeltaTime);

	/**
	 * @brief ゲーム物理更新処理
	 *
	 * この関数は、ゲームの物理状態を更新します。
	 *
	 */
	void FixedUpdate(float fixedDeltaTime);

	/**
	 * @brief 物理計算処理
	 *
	 */
	void ProcessColliderZones();

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

	/**
	 * @brief デバッグ機能
	 *
	 * この関数は、デバッグ機能を提供します。
	 */
	void Debug();
	
	/**
	 * @brief リソース解放処理
	 *
	 * この関数は、ゲームで使用したリソースを解放します。
	 */
	void ReleaseData();

public:

	class Camera* GetMainCamera() { return mainCamera; }
};

extern World mainWorld;

/**
 * @brief 動的キャストを行うテンプレート関数
 *
 * この関数は、与えられたBaseクラスのポインタを指定された型に対して動的キャストを行います。
 * キャストが成功した場合、指定された型のポインタを返します。失敗した場合はnullptrを返します。
 *
 * @tparam T キャストする型
 * @param pBase キャスト対象のBaseクラスのポインタ
 * @return T* キャストされた型のポインタ。キャストが失敗した場合はnullptr。
 */
template<typename T>
T* Cast(Base* pBase)
{
	// pBaseが有効であれば動的キャストを行い、結果を返す
	if (pBase) {
		return dynamic_cast<T*>(pBase);
	}
	// pBaseがnullptrの場合はnullptrを返す
	std::cout << "Cast failed" << std::endl;
	return nullptr;
}
#endif // !_WORLD_H_



