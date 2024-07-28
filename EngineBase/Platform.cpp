#include "stdafx.h"
#include "Platform.h"
#include "RigidBody.h"
Platform::Platform()
{
	// �{�b�N�X�R���C�_�[�̐ݒ�
	boxCollider = ConstructComponent<BoxCollider>();
	boxCollider->AttachTo(root);
	boxCollider->SetSize(Vector2(128, 32));

	// ���̃R���|�[�l���g�̐ݒ�
	rigidBody = ConstructComponent<RigidBody>();
	rigidBody->SetGravity(9.8f);
	rigidBody->SetGravityEnabled(false);
}
