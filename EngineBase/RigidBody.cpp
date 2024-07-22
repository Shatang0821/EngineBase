#include "stdafx.h"
#include "RigidBody.h"
#include "Object.h"

void RigidBody::FixedUpdate(float fixedDeltaTime)
{
	if (pOwner) {
		//�ړ�����
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
		
		//��]����
		if (bRotatable) {
			angularAcceleration = torque;
			angularVelocity += angularAcceleration * fixedDeltaTime;

			std::cout << angularVelocity << std::endl;
			pOwner->AddRotation(angularVelocity);

			torque = 0;
		}

		force = Vector2::Zero();
	}
}
