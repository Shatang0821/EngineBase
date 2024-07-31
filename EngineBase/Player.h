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
	Animation animation[2]; ///< プレイヤーのアニメーション
	Animator* animator; ///< アニメーションを管理するAnimator
	BoxCollider* boxCollider; ///< プレイヤーのボックスコライダー
	class RigidBody* rigidBody; ///< プレイヤーの剛体コンポーネント
	class StateMachine* stateMachine; ///< プレイヤーのステートマシン
public:
	Player(); ///< コンストラクタ


	void Update(float DeltaTime) override; ///< フレームごとの更新処理
	void FixedUpdate(float fixedDeltaTime) override; ///< 物理更新処理

	void DrawDebug() override; ///< デバッグ描画処理
private:
	void BeginOverlap(Collider*, Collider*, Object* );
	void EndOverlap  (Collider*, Collider*, Object* );
	void OnHit(Collider* hitComp,Collider* otherComp,Object* otherActor,Vector2 hitNormal,const HitResult& hitResult);

	/// <summary>
	/// アニメーションの初期化を行います。
	/// </summary>
	void InitAnimation();
	/// <summary>
	/// 物理演算の初期化を行います。
	/// </summary>
	void InitPhysics();
};


#endif // !_PLAYER_H_
