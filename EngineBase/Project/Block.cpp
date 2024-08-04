#include "stdafx.h"
#include "Block.h"
#include "../Engine/RigidBody.h"
#include "../Engine/Collider.h"

Block::Block()
{
	//boxCollider = ConstructComponent<BoxCollider>();
	//boxCollider->AttachTo(root);
	//boxCollider->SetSize(Vector2(32, 32));
	circleCollider = ConstructComponent<CircleCollider>();
	circleCollider->AttachTo(root);
	circleCollider->SetRadius(16);

	rigidBody = ConstructComponent<RigidBody>();
	rigidBody->SetGravity(100.0f);
	rigidBody->SetGravityEnabled(false);
}
