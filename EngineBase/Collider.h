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
public:
	enum ColliderShape {
		COLLIDER_SHAPE_CIRCLE,
		COLLIDER_SHAPE_BOX,
	};
private:
	//! コライダーのタイプ タイプを使って当たり判定の処理が必要な同士を判別する
	std::string type = "Default";

	//! レイヤ
	int layer = 0;
	//! 毎フレーム自身と衝突しているコライダー
	std::unordered_set<Collider*> collisions;
	//! 衝突しているオブジェクト
	std::vector<Object*>aims;

protected:
	ColliderShape shape = COLLIDER_SHAPE_CIRCLE;

	virtual bool CollisionJudge(Collider* another) = 0;
public:
	Collider(){mainWorld.GameColliders.insert(this);}
	virtual ~Collider(){mainWorld.GameColliders.erase(this);}

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

	ColliderShape GetShape() { return shape; }

	/**
	 * @brief この関数は、コンテナの中身をクリアします。
	 * 
	 */
	void Clear(){collisions.clear(); }

	/**
	 * @brief この関数は、衝突しているコライダーを集めている
	 * 
	 * 引数との当たり判定を行い、衝突しているコライダーを
	 * collisionsに追加します。
	 * 
	 * @param another 衝突しているコライダー
	 */
	void Inser(Collider* another);

	virtual void DrawDebugLine() = 0;
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
	CircleCollider(){shape = COLLIDER_SHAPE_CIRCLE; }

	virtual void Update(float DeltaTime) override;
	virtual void DrawDebugLine() override;

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
	BoxCollider(){shape = COLLIDER_SHAPE_BOX; }

	virtual void Update(float DeltaTime) override;
	virtual void DrawDebugLine() override;

	const Vector2& GetSize()const { return size; }
	void SetSize(const Vector2& s) { size = s; size_init = s / GetWorldScale(); }
};



#endif // !_COLLIDER_H_



