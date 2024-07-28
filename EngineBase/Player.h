#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "StaticMesh.h"
#include "Animator.h"
#include "Collider.h"
/**
 * @class Player
 * @brief ゲーム内のプレイヤーキャラクターを表すクラス。
 *
 * Player クラスは、ゲーム内のプレイヤーキャラクターを表します。
 * StaticMeshから派生しており、アニメーション、コライダー（ボックスとサークル）を持っています。
 */
class Player : public StaticMesh
{
private:
	Animation ani; ///< プレイヤーのアニメーション
	Animator* animator; ///< アニメーションを管理するAnimator
	BoxCollider* boxCollider; ///< プレイヤーのボックスコライダー
	//CircleCollider* circleCollider; ///< プレイヤーのサークルコライダー
	class RigidBody* rigidBody; ///< プレイヤーの剛体コンポーネント

private:
	Vector2 anchorPoint;		// 固定点
	float length;				// 振り子の長さ
	float angle;				// 振り子の角度
	float angularVelocity;		// 角速度
	float angularAcceleration;	// 角加速度
public:
	Player(); ///< コンストラクタ

	void Update(float DeltaTime) override; ///< フレームごとの更新処理
	void FixedUpdate(float fixedDeltaTime) override; ///< 物理更新処理

	void DrawDebug() override; ///< デバッグ描画処理
private:
	void BeginOverlap(Collider* OverlapCpm, Object* OverlapActor);
	void EndOverlap(Collider* OverlapCpm, Object* OverlapActor);
};


#endif // !_PLAYER_H_
