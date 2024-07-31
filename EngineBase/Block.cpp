#include "stdafx.h"
#include "Block.h"
#include "RigidBody.h"
#include "Collider.h"

Block::Block()
{
	boxCollider = ConstructComponent<BoxCollider>();
	boxCollider->AttachTo(root);
	boxCollider->SetSize(Vector2(32, 32));

	rigidBody = ConstructComponent<RigidBody>();
	rigidBody->SetGravity(100.0f);
	rigidBody->SetGravityEnabled(false);
}
