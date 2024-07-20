#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "StaticMesh.h"
#include "Animator.h"

/**
 * @class Player
 * @brief ゲーム内のプレイヤーキャラクターを表すクラス。
 *
 * Player クラスは、ゲーム内のプレイヤーキャラクターを表します。
 * StaticMeshから派生しており、アニメーション、コライダー（ボックスとサークル）を持っています。
 */
class Player : public StaticMesh
{
	Animation ani; ///< プレイヤーのアニメーション
	Animator* animator; ///< アニメーションを管理するAnimator
	BoxCollider* boxCollider; ///< プレイヤーのボックスコライダー
	CircleCollider* circleCollider; ///< プレイヤーのサークルコライダー
	class RigidBody* rigidBody; ///< プレイヤーの剛体コンポーネント
public:
	Player(); ///< コンストラクタ

	void Update(float DeltaTime) override; ///< フレームごとの更新処理
};


#endif // !_PLAYER_H_
