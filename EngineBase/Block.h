#pragma once
#include "Engine/StaticMesh.h"
class Block : public StaticMesh
{
private:
	//BoxCollider* boxCollider; ///< �{�b�N�X�R���C�_�[
	CircleCollider* circleCollider; ///< �T�[�N���R���C�_�[
	class RigidBody* rigidBody; ///< ���̃R���|�[�l���g
public:
	Block();
};

