#include "stdafx.h"
#include "Platform.h"
#include "../Engine/RigidBody.h"

Platform::Platform()
{
	// ボックスコライダーの設定
	boxCollider = ConstructComponent<BoxCollider>();
	boxCollider->AttachTo(root);
	boxCollider->SetSize(Vector2(1280, 32));
	
	boxCollider2 = ConstructComponent<BoxCollider>();
	boxCollider2->AttachTo(root);
	boxCollider2->SetSize(Vector2(64, 32));
	boxCollider2->SetLocalPosition(Vector2(0, -32));


	//rigidBody = ConstructComponent<RigidBody>();

	//rigidBody->SetGravityEnabled(false);
}
