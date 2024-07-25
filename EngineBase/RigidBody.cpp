#include "stdafx.h"
#include "RigidBody.h"
#include "Object.h"

void RigidBody::FixedUpdate(float fixedDeltaTime)
{
	if (pOwner) {
		//移動処理
		if (bMoveable) {

			if (bGravityEnabled)
			{
				acceleration.y += gravity;
			}

			acceleration += force;
			
			velocity += acceleration * fixedDeltaTime;
			pOwner->AddPosition(velocity * fixedDeltaTime);

			acceleration = Vector2::Zero();
		}
		
		//回転処理
		if (bRotatable) {
			angularAcceleration = torque;
			angularVelocity += angularAcceleration * fixedDeltaTime;

			pOwner->AddRotation(angularVelocity);

			torque = 0;
		}

		force = Vector2::Zero();
	}
}
