#include "stdafx.h"
#include "RigidBody.h"
#include "Object.h"

void RigidBody::FixedUpdate(float fixedDeltaTime)
{
	if (pOwner) {
		//ˆÚ“®ˆ—
		if (bMoveable) {

			if (bGravityEnabled)
			{
				acceleration.y += gravity;
			}

			acceleration += force * fixedDeltaTime;

			velocity += acceleration * fixedDeltaTime;
			pOwner->AddPosition(velocity);
		}
		
		//‰ñ“]ˆ—
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
