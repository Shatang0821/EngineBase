#pragma once
#include "StaticMesh.h"
class Platform : public StaticMesh
{
private:
	BoxCollider* boxCollider; ///< �v���C���[�̃{�b�N�X�R���C�_�[
	BoxCollider* boxCollider2; ///< �v���C���[�̃{�b�N�X�R���C�_�[
	//CircleCollider* circleCollider; ///< �v���C���[�̃T�[�N���R���C�_�[
	//class RigidBody* rigidBody; ///< �v���C���[�̍��̃R���|�[�l���g
public:
	Platform(); ///< �R���X�g���N�^
};

