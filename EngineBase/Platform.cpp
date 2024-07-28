#include "stdafx.h"
#include "Platform.h"
#include "RigidBody.h"
Platform::Platform()
{
	// ボックスコライダーの設定
	boxCollider = ConstructComponent<BoxCollider>();
	boxCollider->AttachTo(root);
	boxCollider->SetSize(Vector2(128, 32));

	// 剛体コンポーネントの設定
	rigidBody = ConstructComponent<RigidBody>();
	rigidBody->SetGravity(9.8f);
	rigidBody->SetGravityEnabled(false);
}
