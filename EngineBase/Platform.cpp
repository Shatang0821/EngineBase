#include "stdafx.h"
#include "Platform.h"
#include "RigidBody.h"

Platform::Platform()
{
	// �{�b�N�X�R���C�_�[�̐ݒ�
	/*boxCollider = ConstructComponent<BoxCollider>();
	boxCollider->AttachTo(root);
	boxCollider->SetSize(Vector2(128, 32));*/

	circleCollider = ConstructComponent<CircleCollider>();
	circleCollider->AttachTo(root);
	circleCollider->SetRadius(32);


}
