#pragma once
#include "Engine/StaticMesh.h"
class Block : public StaticMesh
{
private:
	//BoxCollider* boxCollider; ///< ボックスコライダー
	CircleCollider* circleCollider; ///< サークルコライダー
	class RigidBody* rigidBody; ///< 剛体コンポーネント
public:
	Block();
};

