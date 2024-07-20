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

			acceleration += force * fixedDeltaTime;

			velocity += acceleration * fixedDeltaTime;
			pOwner->AddPosition(velocity);
		}
		
		//回転処理
		if (bRotatable) {
			/*angularAcceleration = torque;
			angularVelocity += angularAcceleration * fixedDeltaTime;*/

			pOwner->AddRotation(angularVelocity);
		}

		force = Vector2::Zero();
		acceleration = Vector2::Zero();
		torque = 0;
	}
}
