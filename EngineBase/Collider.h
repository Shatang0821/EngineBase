/**
 * @file Collider.h
 * @brief コライダークラスの定義
 *
 * このファイルには、Colliderクラスが定義されています。
 * Colliderクラスは、当たり判定を行うためのクラスです。
 *
 * @date 2024/07/17
 * @autor サトウ
 */

#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "World.h"
#include "Delegate.h"

//当たり判定の形状
enum class ColliderShape:UINT8 {
	COLLIDER_SHAPE_CIRCLE,
	COLLIDER_SHAPE_BOX,
};

//当たり判定のモード
enum class CollisionMode :UINT8 {
	NONE,
	TRIGGER,
	COLLISION,
};

//前方宣言
class Collider;

//衝突デリゲート

/*Collider* overlapComp,Collider* otherComp, Object* otherActor */
DECLARE_MULTI_PARAM_MULTICAST_DELEGATE_CLASS(CollisionOverlapDelegate, Collider*, Collider*, Object*);


//
///**
// * @class CollisionDelegate
// * @brief 衝突時の処理を行うためのデリゲートクラス
// *
// * @details このクラスは、
// * 衝突時の処理を行うためのデリゲートクラスです。
// *
// */
//class CollisionDelegate 
//{
//private:
//	//! 衝突時の処理を行う関数
//	std::vector<std::function<void(Collider*,Object*)>> callbacks;
//public:
//	/**
//	 * @brief この関数は、コールバック関数を追加します。
//	 * 
//	 * @param obj コールバック関数を持つオブジェクト
//	 * @param func コールバック関数
//	 */
//	template<typename T>
//	void Add(T* obj,void(T::*func)(Collider*,Object*)) {
//		callbacks.push_back(std::bind(func,obj,std::placeholders::_1,std::placeholders::_2));
//	}
//
//	/**
//	 * @brief この関数は、コールバック関数を追加します。
//	 * 
//	 * @param func コールバック関数(ラムダ式)
//	 */
//	void Add(std::function<void(Collider*,Object*)>func)
//	{
//		callbacks.push_back(func);
//	}
//
//	/**
//	 * @brief この関数は、コールバックを削除します。
//	 * 
//	 * @param obje コールバック関数を持つオブジェクト
//	 * @param func コールバック関数
//	 */
//	template<typename T>
//	void Remove(T* obje, void(T::* func)(Collider*, Object*))
//	{
//		std::function<void(Collider*, Object*)>targetFunc = std::bind(func, obje, std::placeholders::_1, std::placeholders::_2);
//		for (auto it = callbacks.begin(); it != callbacks.end(); it++)
//		{
//			if (it->target<void(Collider*, Object*)>() == targetFunc.target<void(Collider*, Object*)>())
//			{
//				callbacks.erase(it);
//				break;
//			}
//		}
//	}
//
//	/**
//	 * @brief この関数は、コールバックを削除します。
//	 * 
//	 * @param func コールバック関数(ラムダ式)
//	 */
//	void Remove(std::function<void(Collider*, Object*)>func)
//	{
//		for (auto it = callbacks.begin(); it != callbacks.end(); it++)
//		{
//			if (it->target<void(Collider*, Object*)>() == func.target<void(Collider*, Object*)>())
//			{
//				callbacks.erase(it);
//				break;
//			}
//		}
//	}
//
//	/**
//	 * @brief この関数は、コールバックを実行します。
//	 * 
//	 * @param OverlapCollider 衝突しているコライダー
//	 * @param OverlapActor 衝突しているオブジェクト
//	 */
//	void BroadCast(Collider* OverlapCollider, Object* OverlapActor);
//
//#define AddDynamic Add
//#define RemoveDynamic Remove
//};

 /**
   * @class Collider
   * @brief コライダークラス
   *
   * @details このクラスは、
   * 当たり判定を行うためのクラスです。
   *
   */
class Collider : public SceneComponent
{
	friend class Controller;
private:
	//! コライダーのタイプ タイプを使って当たり判定の処理が必要な同士を判別する
	std::string type = "Default";
	//! 当たり判定のモード
	CollisionMode collisionMode = CollisionMode::TRIGGER;
	//! レイヤ
	int layer = 0;
	//! 毎フレーム自身と衝突しているコライダー
	std::unordered_set<Collider*> collisions;
	//! 衝突しているオブジェクト
	std::vector<Object*>aims;
	//! コライダーを削除するためのコンテナ
	std::vector<Collider*>collisions_to_erase;

protected:
	ColliderShape shape = ColliderShape::COLLIDER_SHAPE_CIRCLE;

	/**
	 * @brief この関数は、当たり判定を行います。
	 *
	 * @param another 衝突しているコライダー
	 * 
	 * @return 衝突しているかどうか
	 */
	virtual bool CollisionJudge(Collider* another) = 0;

	/**
	 * @brief この関数は、マウスとの当たり判定を行います。
	 * 
	 * @return 衝突しているかどうか
	 */
	virtual bool IsMouseOver() = 0;
public:
	Collider(){mainWorld.GameColliders.insert(this);}
	virtual ~Collider(){
		mainWorld.GameColliders.erase(this);
		Clear();
	}

	const std::vector<Object*>& GetCollisions(std::string type);


	/**
	 * @brief この関数は、レイヤーを取得します。
	 * 
	 * @return レイヤー
	 */
	int GetLayer()const{ return layer; }

	/**
	 * @brief この関数は、レイヤーを設定します。
	 * 
	 * @param l レイヤー
	 */
	void SetLayer(int l) { layer = l; }

	/**
	 * @brief この関数は、コライダーのタイプを取得します。
	 * 
	 * @return コライダーのタイプ
	 */
	const std::string& GetType() { return type; }

	/**
	 * @brief この関数は、コライダーのタイプを設定します。
	 * 
	 * @param type コライダーのタイプ
	 */
	void SetType(std::string type) { this->type = type; }

	/**
	 * @brief この関数は、コライダーの形状を取得します。
	 * 
	 * @return コライダーの形状
	 */
	ColliderShape GetShape() { return shape; }
	
	/**
	 * @brief この関数は、コライダーの当たり判定のモードを設定します。
	 * 
	 * @param mode 当たり判定のモード
	 */
	void SetCollisionMode(CollisionMode mode) { collisionMode = mode; }

	/**
	 * @brief この関数は、コライダーの当たり判定のモードを取得します。
	 * 
	 * @return 当たり判定のモード
	 */
	CollisionMode GetCollisionMode() { return collisionMode; }

	/**
	 * @brief この関数は、コンテナの中身をクリアします。
	 * 
	 */
	void Clear();

	/**
	 * @brief この関数は、衝突しているコライダーを集めている
	 * 
	 * 引数との当たり判定を行い、衝突しているコライダーを
	 * collisionsに追加します。
	 * 
	 * @param another 衝突しているコライダー
	 */
	void Inser(Collider* another);

	/**
	 * @brief この関数は、衝突してないコライダーを削除します。
	 * 
	 */
	void Erase();


	virtual void DrawDebugLine() = 0;

	CollisionOverlapDelegate OnComponentBeginOverlap;
	CollisionOverlapDelegate OnComponentEndOverlap;
};

/**
 * @class CircleCollider
 * @brief 円コライダークラス
 *
 * @details このクラスは、
 * 円コライダーを生成するためのクラスです。
 *
 */
class CircleCollider final : public Collider
{
private:
	//! 半径
	float radius = 0.0f;
	float radius_init = 0.0f;

	virtual bool CollisionJudge(Collider* another) override;

public:
	CircleCollider(){shape = ColliderShape::COLLIDER_SHAPE_CIRCLE; }

	/**
	 * @brief この関数は、更新処理を行います。
	 *
	 * @param DeltaTime 前のフレームからの経過時間
	 */
	virtual void Update(float DeltaTime) override;
	/**
	 * @brief この関数は、デバッグラインを描画します。
	 * 
	 */
	virtual void DrawDebugLine() override;
	/**
	 * @brief この関数は、マウスとの当たり判定を行います。
	 * 
	 * @return 衝突しているかどうか
	 */
	virtual bool IsMouseOver() override;

	float GetRadius()const { return radius; }
	void SetRadius(float r) { radius = r; radius_init = r / sqrtf(GetWorldScale().x * GetWorldScale().y); }

};

/**
 * @class BoxCollider
 * @brief ボックスコライダークラス
 *
 * @details このクラスは、
 * ボックスコライダーを生成するためのクラスです。
 *
 */
class BoxCollider final : public Collider
{
private:
	Vector2 size = Vector2::Zero();
	Vector2 size_init = Vector2::Zero();
	
	virtual bool CollisionJudge(Collider* another) override;
public:
	BoxCollider(){shape = ColliderShape::COLLIDER_SHAPE_BOX; }

	/**
	 * @brief この関数は、更新処理を行います。
	 * 
	 * @param DeltaTime 前のフレームからの経過時間
	 */
	virtual void Update(float DeltaTime) override;
	/**
	 * @brief この関数は、デバッグラインを描画します。
	 * 
	 */
	virtual void DrawDebugLine() override;
	/**
	 * @brief この関数は、マウスとの当たり判定を行います。
	 * 
	 * @return 衝突しているかどうか
	 */
	virtual bool IsMouseOver() override;

	const Vector2& GetSize()const { return size; }
	void SetSize(const Vector2& s) { size = s; size_init = s / GetWorldScale(); }
};



#endif // !_COLLIDER_H_



