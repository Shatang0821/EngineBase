#include "stdafx.h"
#include "RigidBody.h"
#include "Object.h"
#include "Collider.h"

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
			Vector2 v2friction = -velocity.normalized() * friction * mass * gravity;
			velocity += v2friction * fixedDeltaTime;

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

	// �d�Ȃ�̉��������@�������Ă��̕����������ړ�������
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

			//�����ړ�
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

	//�����ړ�
	pOwner->AddPosition(impactNormal * halfLength);
	another->pOwner->AddPosition(-impactNormal * halfLength);
}
