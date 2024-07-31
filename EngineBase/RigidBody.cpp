#include "stdafx.h"
#include "RigidBody.h"
#include "Object.h"
#include "Collider.h"

//void RigidBody::FixedUpdate(float fixedDeltaTime)
//{
//	if (pOwner) {
//		//�ړ�����
//		if (bMoveable) {
//
//			if (bGravityEnabled) force.y += gravity * mass;
//
//			acceleration += force / mass;
//
//			velocity += acceleration * fixedDeltaTime;
//
//			for (auto& collider : colliders) {
//				if (collider->collisionMode != CollisionMode::COLLISION) continue;
//				for (auto& another : collider->collisions) {
//					if (collider->collisionMode != CollisionMode::COLLISION) continue;
//					RestrictVelocity(-collider->CollisionHit(another).ImpactNormal, another->rigidBodyAttached);
//				}
//			}
//
//			for (auto& collider : colliders) {
//				if (collider->collisionMode != CollisionMode::COLLISION) continue;
//				for (auto& another : collider->collisions) {
//					if (collider->collisionMode != CollisionMode::COLLISION || another->rigidBodyAttached) continue;
//					RestrictVelocity(-collider->CollisionHit(another).ImpactNormal);
//				}
//			}
//
//			pOwner->AddPosition(velocity * fixedDeltaTime);
//
//			acceleration = Vector2::Zero();
//		}
//		
//		//��]����
//		if (bRotatable) {
//			angularAcceleration = torque;
//			angularVelocity += angularAcceleration * fixedDeltaTime;
//
//			pOwner->AddRotation(angularVelocity);
//
//			torque = 0;
//		}
//
//		force = Vector2::Zero();
//	}
//}
//
//void RigidBody::RestrictVelocity(Vector2 impactNormal, RigidBody* another)
//{
//	//
//	Vector2 tangentVector = { impactNormal.y, -impactNormal.x };
//
//	Vector2 normalVelocity = Vector2::ProjectVector(velocity,impactNormal);
//	Vector2 tangentVelocity = Vector2::ProjectVector(velocity, tangentVector);
//
//	float friction = 0.1f; // ���C�n��
//	float restitution = 0.0f;	// �e���ՓˌW��
//
//	if (!another)
//	{
//		if (Vector2::Dot(velocity, impactNormal) < 0)
//		{
//			float multiplier = (tangentVelocity.Length() - normalVelocity.Length() * friction) / tangentVelocity.Length();
//			multiplier = Math::clamp(multiplier, 0.0f, 1.0f);
//			velocity = tangentVelocity * multiplier - normalVelocity * restitution;
//		}
//		return;
//	}
//
//
//	Vector2 anotherNormalVelocity = Vector2::ProjectVector(another->velocity, impactNormal);
//	Vector2 anotherTangentVelocity = Vector2::ProjectVector(another->velocity, tangentVector);
//
//    // ���Α��x�ƏՓ˖@���̓��ς�0�ȉ��̏ꍇ�A�Փˉ������s��
//    if (Vector2::Dot(normalVelocity - anotherNormalVelocity, impactNormal) >= 0) return;
//
//
//
//	Vector2 normalVelocity_ = normalVelocity;
//	normalVelocity = (normalVelocity * (mass - restitution * another->mass) + anotherNormalVelocity * (1 + restitution) * another->mass) / (mass + another->mass);
//	anotherNormalVelocity = (anotherNormalVelocity * (another->mass - restitution * mass) + normalVelocity_ * (1 + restitution) * mass) / (mass + another->mass);
//
//	velocity = normalVelocity + tangentVelocity;
//	another->velocity = anotherNormalVelocity + anotherTangentVelocity;
//}

void RigidBody::FixedUpdate(float fixedDeltaTime)
{
	if (pOwner) {
		//�ړ�����
		if (bMoveable) {
			// �d�͂̉e��
			if (bGravityEnabled) force.y += gravity * mass;

			// �����x�̍X�V
			acceleration = force / mass;
			velocity += acceleration * fixedDeltaTime;

			// ���C�̓K�p
			Vector2 friction = -velocity.normalized() * 0.1f * mass * gravity;
			velocity += friction * fixedDeltaTime;

			// �Փ˂ɂ�鑬�x����
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


			// �ʒu�̍X�V
			pOwner->AddPosition(velocity * fixedDeltaTime);

			// �͂Ɖ����x�̃��Z�b�g
			acceleration = Vector2::Zero();
			force = Vector2::Zero();
		}

		//��]����
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

	Vector2 tangentVector = { impactNormal.y, -impactNormal.x };

	Vector2 normalVelocity = Vector2::ProjectVector(velocity, impactNormal);
	Vector2 tangentVelocity = Vector2::ProjectVector(velocity, tangentVector);

	float friction = 0.001f; // ���C�W��
	float restitution = 0.0f; // �e���ՓˌW��

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

	if (Vector2::Dot(normalVelocity - anotherNormalVelocity, impactNormal) >= 0) return;

	Vector2 normalVelocity_ = normalVelocity;
	normalVelocity = (normalVelocity * (mass - restitution * another->mass) + anotherNormalVelocity * (1 + restitution) * another->mass) / (mass + another->mass);
	anotherNormalVelocity = (anotherNormalVelocity * (another->mass - restitution * mass) + normalVelocity_ * (1 + restitution) * mass) / (mass + another->mass);

	velocity = normalVelocity + tangentVelocity;
	another->velocity = anotherNormalVelocity + anotherTangentVelocity;
}
