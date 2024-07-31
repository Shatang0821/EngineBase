#pragma once
#include "StaticMesh.h"
class Block : public StaticMesh
{
private:
	BoxCollider* boxCollider; ///< ボックスコライダー
	class RigidBody* rigidBody; ///< 剛体コンポーネント
public:
	Block();
};

