#include "stdafx.h"
#include "RigidBody.h"
#include "Object.h"
#include "Collider.h"

void RigidBody::FixedUpdate(float fixedDeltaTime)
{
	if (pOwner) {
		//移動処理
		if (bMoveable) {
			// 重力の影響
			if (bGravityEnabled) force.y += gravity * mass;

			// 加速度の更新
			acceleration = force / mass;
			velocity += acceleration * fixedDeltaTime;

			// 摩擦の適用
			Vector2 v2friction = -velocity.normalized() * friction * mass * gravity;
			velocity += v2friction * fixedDeltaTime;

			// 衝突による速度制限
			for (auto& collider : colliders) {
				if (collider->collisionMode != CollisionMode::COLLISION) continue;
				for (auto& another : collider->collisions) {
					if (collider->collisionMode != CollisionMode::COLLISION) continue;
					RestrictVelocity(collider->CollisionHit(another), another->rigidBodyAttached);
				}
			}

			for (auto& collider : colliders) {
				if (collider->collisionMode != CollisionMode::COLLISION) continue;
				for (auto& another : collider->collisions) {
					if (collider->collisionMode != CollisionMode::COLLISION || another->rigidBodyAttached) continue;
					RestrictVelocity(collider->CollisionHit(another));
				}
			}


			// 位置の更新
			pOwner->AddPosition(velocity * fixedDeltaTime);

			// 力と加速度のリセット
			acceleration = Vector2::Zero();
			force = Vector2::Zero();
		}

		//回転処理
		if (bRotatable) {
			angularAcceleration = torque / mass;
			angularVelocity += angularAcceleration * fixedDeltaTime;

			pOwner->AddRotation(angularVelocity);

			torque = 0;
		}
	}
}



void RigidBody::RestrictVelocity(HitResult hitresult, RigidBody* another)
{
	auto impactNormal = -hitresult.ImpactNormal;

	// 重なりの解決距離　分割してその分だけ強制移動させる
	float halfLength = hitresult.Length / 4.0f;

	Vector2 tangentVector = { impactNormal.y, -impactNormal.x };

	Vector2 normalVelocity = Vector2::ProjectVector(velocity, impactNormal);
	Vector2 tangentVelocity = Vector2::ProjectVector(velocity, tangentVector);

	if (!another)
	{
		if (Vector2::Dot(velocity, impactNormal) < 0)
		{
			float multiplier = (tangentVelocity.Length() - normalVelocity.Length() * friction) / tangentVelocity.Length();
			multiplier = Math::clamp(multiplier, 0.0f, 1.0f);

			//強制移動
			pOwner->AddPosition(impactNormal * halfLength);

			velocity = tangentVelocity * multiplier - normalVelocity * restitution;
		}
		return;
	}

	Vector2 anotherNormalVelocity = Vector2::ProjectVector(another->velocity, impactNormal);
	Vector2 anotherTangentVelocity = Vector2::ProjectVector(another->velocity, tangentVector);

	if (Vector2::Dot(normalVelocity - anotherNormalVelocity, impactNormal) >= 0) return;

	Vector2 normalVelocity_ = normalVelocity;
	normalVelocity = (normalVelocity * (mass - restitution * another->mass) + anotherNormalVelocity * (1 + restitution) * another->mass) / (mass + another->mass);
	anotherNormalVelocity = (anotherNormalVelocity * (another->mass - restitution * mass) + normalVelocity_ * (1 + restitution) * mass) / (mass + another->mass);

	velocity = normalVelocity + tangentVelocity;
	another->velocity = anotherNormalVelocity + anotherTangentVelocity;

	//強制移動
	pOwner->AddPosition(impactNormal * halfLength);
	another->pOwner->AddPosition(-impactNormal * halfLength);
}
