#pragma once
#include "StaticMesh.h"
class Platform : public StaticMesh
{
private:
	BoxCollider* boxCollider; ///< プレイヤーのボックスコライダー
	BoxCollider* boxCollider2; ///< プレイヤーのボックスコライダー
	//CircleCollider* circleCollider; ///< プレイヤーのサークルコライダー
	//class RigidBody* rigidBody; ///< プレイヤーの剛体コンポーネント
public:
	Platform(); ///< コンストラクタ
};

