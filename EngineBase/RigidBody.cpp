#include "stdafx.h"
#include "RigidBody.h"
#include "Object.h"
#include "Collider.h"

void RigidBody::FixedUpdate(float fixedDeltaTime)
{
	if (pOwner) {
		//移動処理
		if (bMoveable) {

			if (bGravityEnabled) acceleration.y += gravity;

			acceleration += force;

			velocity += acceleration * fixedDeltaTime;

			for (auto& collider : colliders) {
				if (collider->collisionMode != CollisionMode::COLLISION) continue;
				for (auto& another : collider->collisions) {
					if (collider->collisionMode != CollisionMode::COLLISION) continue;
					RestrictVelocity(-collider->CollisionHit(another).ImpactNormal, another->rigidBodyAttached);
				}
			}

			for (auto& collider : colliders) {
				if (collider->collisionMode != CollisionMode::COLLISION) continue;
				for (auto& another : collider->collisions) {
					if (collider->collisionMode != CollisionMode::COLLISION || another->rigidBodyAttached) continue;
					RestrictVelocity(-collider->CollisionHit(another).ImpactNormal);
				}
			}

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

void RigidBody::RestrictVelocity(Vector2 impactNormal, RigidBody* another)
{
	//
	Vector2 tangentVector = { impactNormal.y, -impactNormal.x };

	Vector2 normalVelocity = Vector2::ProjectVector(velocity,impactNormal);
	Vector2 tangentVelocity = Vector2::ProjectVector(velocity, tangentVector);

	float friction = 0.1f; // 摩擦系数
	float restitution = 0.0f;	// 弾性衝突係数

	if (!another)
	{
		if (Vector2::Dot(velocity, impactNormal) < 0)
		{
			float multiplier = (tangentVelocity.Length() - normalVelocity.Length() * friction) / tangentVelocity.Length();
			multiplier = Math::clamp(multiplier, 0.0f, 1.0f);
			velocity = tangentVelocity * multiplier - normalVelocity * restitution;
		}
		return;
	}


	Vector2 anotherNormalVelocity = Vector2::ProjectVector(another->velocity, impactNormal);
	Vector2 anotherTangentVelocity = Vector2::ProjectVector(another->velocity, tangentVector);

    // 相対速度と衝突法線の内積が0以下の場合、衝突応答を行う
    if (Vector2::Dot(normalVelocity - anotherNormalVelocity, impactNormal) >= 0) return;



	Vector2 normalVelocity_ = normalVelocity;
	normalVelocity = (normalVelocity * (mass - restitution * another->mass) + anotherNormalVelocity * (1 + restitution) * another->mass) / (mass + another->mass);
	anotherNormalVelocity = (anotherNormalVelocity * (another->mass - restitution * mass) + normalVelocity_ * (1 + restitution) * mass) / (mass + another->mass);

	velocity = normalVelocity + tangentVelocity;
	another->velocity = anotherNormalVelocity + anotherTangentVelocity;
}
