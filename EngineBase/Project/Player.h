#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../Engine/StaticMesh.h"
#include "../Engine/Animator.h"
#include "../Engine/Collider.h"
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
	//エンジンコンポーネント
	Animation animation[2]; ///< プレイヤーのアニメーション
	Animator* animator; ///< アニメーションを管理するAnimator
	BoxCollider* boxCollider; ///< プレイヤーのボックスコライダー
	class RigidBody* rigidBody; ///< プレイヤーの剛体コンポーネント
	
	//自作コンポーネント
	class StateMachine* stateMachine; ///< プレイヤーのステートマシン
public:
	Player(); ///< コンストラクタ

	~Player() override; ///< デストラクタ

	void Update(float DeltaTime) override; ///< フレームごとの更新処理
	void FixedUpdate(float fixedDeltaTime) override; ///< 物理更新処理

	void DrawDebug() override; ///< デバッグ描画処理
	
	void SetAnimation(const std::string& name); ///< アニメーションの設定

	void SetVelocity(const Vector2& velocity); ///< 速度の設定
	void SetVelocityX(float x); ///< X軸方向の速度の設定
	void SetVelocityY(float y); ///< Y軸方向の速度の設定
	Vector2 GetVelocity(); ///< 速度の取得
private:
	/// <summary>
	/// 状態マシンの初期化を行います。
	/// </summary>
	void InitStateMachine();

	/// <summary>
	/// アニメーションの初期化を行います。
	/// </summary>
	void InitAnimation();
	/// <summary>
	/// 物理演算の初期化を行います。
	/// </summary>
	void InitPhysics();

	void BeginOverlap(Collider*, Collider*, Object* );
	void EndOverlap  (Collider*, Collider*, Object* );
	void OnHit(Collider* hitComp,Collider* otherComp,Object* otherActor,Vector2 hitNormal,const HitResult& hitResult);

	
};


#endif // !_PLAYER_H_
