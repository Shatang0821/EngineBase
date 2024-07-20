#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "StaticMesh.h"
#include "Animator.h"

/**
 * @class Player
 * @brief �Q�[�����̃v���C���[�L�����N�^�[��\���N���X�B
 *
 * Player �N���X�́A�Q�[�����̃v���C���[�L�����N�^�[��\���܂��B
 * StaticMesh����h�����Ă���A�A�j���[�V�����A�R���C�_�[�i�{�b�N�X�ƃT�[�N���j�������Ă��܂��B
 */
class Player : public StaticMesh
{
	Animation ani; ///< �v���C���[�̃A�j���[�V����
	Animator* animator; ///< �A�j���[�V�������Ǘ�����Animator
	BoxCollider* boxCollider; ///< �v���C���[�̃{�b�N�X�R���C�_�[
	CircleCollider* circleCollider; ///< �v���C���[�̃T�[�N���R���C�_�[
	class RigidBody* rigidBody; ///< �v���C���[�̍��̃R���|�[�l���g
public:
	Player(); ///< �R���X�g���N�^

	void Update(float DeltaTime) override; ///< �t���[�����Ƃ̍X�V����
};


#endif // !_PLAYER_H_
