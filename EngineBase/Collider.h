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
#include "CollisionManager.h"

//当たり判定の形状
enum class ColliderShape:uint8_t {
	COLLIDER_SHAPE_CIRCLE,
	COLLIDER_SHAPE_BOX,
};

//当たり判定のモード
enum class CollisionMode :uint8_t {
	NONE,
	TRIGGER,
	COLLISION,
};

//衝突結果
struct HitResult
{
	//! 衝突点
	Vector2 ImpactPoint;
	//! 衝突法線
	Vector2 ImpactNormal;
	Object* HitObject;
	Component* HitComponent;

	HitResult() 
		: ImpactPoint(Vector2::Zero())
		, ImpactNormal(Vector2::Zero())
		, HitObject(nullptr)
		, HitComponent(nullptr) 
	{}
	HitResult(const Vector2& impactPoint,const Vector2& impactNormal,Object* hitObject, Component* hitComponent)
		: ImpactPoint(impactPoint)
		, ImpactNormal(impactNormal)
		, HitObject(hitObject)
		, HitComponent(hitComponent) 
	{}
};

//前方宣言
class Collider;

//衝突デリゲート

/*Collider* overlapComp,Collider* otherComp, Object* otherActor */
DECLARE_MULTI_PARAM_MULTICAST_DELEGATE_CLASS(CollisionOverlapDelegate, Collider*, Collider*, Object*);

/* Collider* hitComp, Collider* otherComp, Object* otherActor, Vector2 normalImpulse, const HitResult& hitResult */
DECLARE_MULTI_PARAM_MULTICAST_DELEGATE_CLASS(CollisionHitDelegate, Collider*, Collider*, Object*, Vector2, const HitResult&)

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
	friend class RigidBody;
	friend void World::ProcessColliderZones();
private:
	//! コライダーのタイプ タイプを使って当たり判定の処理が必要な同士を判別する
	CollisionType type = CollisionType::Default;
	//! 当たり判定のモード
	CollisionMode collisionMode = CollisionMode::COLLISION;
	
	//! 衝突しているコライダー範囲を表す
	Pair point{-1,-1},point_1{-1,-1};

	//! レイヤ
	int layer = 0;
	//! 毎フレーム自身と衝突しているコライダー
	std::unordered_set<Collider*> collisions;
	//! 衝突しているオブジェクト
	std::vector<Object*>aims;
	//! コライダーを削除するためのコンテナ
	std::vector<Collider*>collisions_to_erase;

	class RigidBody* rigidBodyAttached = nullptr;
protected:
	ColliderShape shape = ColliderShape::COLLIDER_SHAPE_CIRCLE;

	/**
	 * @brief この関数は、マウスとの当たり判定を行います。
	 * 
	 * @return 衝突しているかどうか
	 */
	virtual bool IsMouseOver() = 0;
public:
	// 衝突時のデリゲート //
	CollisionOverlapDelegate OnComponentBeginOverlap;
	CollisionOverlapDelegate OnComponentEndOverlap;
	CollisionHitDelegate OnComponentHit;


	Collider(){mainWorld.GameColliders.insert(this);}
	virtual ~Collider(){
		//if(rigidBodyAttached) rigidBodyAttached->
		mainWorld.GameColliders.erase(this);
		Clear();
	}


	void BeginPlay() override;
	/**
	 * @brief この関数は、更新処理を行います。
	 *
	 * @param DeltaTime 前のフレームからの経過時間
	 */
	void Update(float DeltaTime) override;
	
	/**
	 * @brief この関数は、デバッグラインを描画します。
	 * 
	 */
	virtual void DrawDebugLine() = 0;

#pragma region  GetSet
	/**
	 * @brief この関数は、衝突しているコライダーを取得します。
	 *
	 * @param type コライダーのタイプ
	 *
	 * @return 衝突しているコライダー
	 */
	const std::vector<Object*>& GetCollisions(CollisionType type);

	/**
	 * @brief この関数は、レイヤーを取得します。
	 *
	 * @return レイヤー
	 */
	int GetLayer()const { return layer; }
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
	const CollisionType GetType() { return type; }
	/**
	 * @brief この関数は、コライダーのタイプを設定します。
	 *
	 * @param type コライダーのタイプ
	 */
	void SetType(CollisionType type) { this->type = type; }


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
#pragma endregion
private:

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
	void Insert(Collider* another);

	/**
	 * @brief この関数は、衝突してないコライダーを削除します。
	 *
	 */
	void Erase();

	bool CollisionJudge(Collider* another);

	//衝突判定
	static bool (*collisionJudgeMap[3])(Collider*, Collider*);
	static bool collisionJudgeCircleToCircle(Collider* c1, Collider* c2);
	static bool collisionJudgeCircleToBox(Collider* c1, Collider* c2);
	static bool collisionJudgeBoxToBox(Collider* c1, Collider* c2);

	//衝突結果
	HitResult CollisionHit(Collider* another);
	static HitResult(*collisionHitMap[3])(Collider*, Collider*);
	static HitResult collisionHitCircleToCircle(Collider* c1, Collider* c2);
	static HitResult collisionHitCircleToBox(Collider* c1, Collider* c2);
	static HitResult collisionHitBoxToBox(Collider* c1, Collider* c2);
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

public:
	CircleCollider(){shape = ColliderShape::COLLIDER_SHAPE_CIRCLE; }

	/**
	 * @brief この関数は、更新処理を行います。
	 *
	 * @param DeltaTime 前のフレームからの経過時間
	 */
	void Update(float DeltaTime) override;
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
public:
	struct Rect
	{
		float left = 0, top = 0, right = 0, bottom = 0;
	};
private:
	Vector2 size = Vector2::Zero();
	Vector2 size_init = Vector2::Zero();

	Rect rect;
public:
	

	BoxCollider(){shape = ColliderShape::COLLIDER_SHAPE_BOX; }

	/**
	 * @brief この関数は、更新処理を行います。
	 * 
	 * @param DeltaTime 前のフレームからの経過時間
	 */
	void Update(float DeltaTime) override;
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

	Rect GetRect()const { return rect; }
	static Vector2 GetOverlapRect(const Rect& r1, const Rect& r2);

	const Vector2& GetSize()const { return size; }
	void SetSize(const Vector2& s) { size = s; size_init = s / GetWorldScale(); }
};



#endif // !_COLLIDER_H_



