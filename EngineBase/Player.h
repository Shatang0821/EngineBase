#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "StaticMesh.h"
#include "Animator.h"
#include "Collider.h"
/**
 * @class Player
 * @brief �Q�[�����̃v���C���[�L�����N�^�[��\���N���X�B
 *
 * Player �N���X�́A�Q�[�����̃v���C���[�L�����N�^�[��\���܂��B
 * StaticMesh����h�����Ă���A�A�j���[�V�����A�R���C�_�[�i�{�b�N�X�ƃT�[�N���j�������Ă��܂��B
 */
class Player : public StaticMesh
{
private:
	Animation ani; ///< �v���C���[�̃A�j���[�V����
	Animator* animator; ///< �A�j���[�V�������Ǘ�����Animator
	BoxCollider* boxCollider; ///< �v���C���[�̃{�b�N�X�R���C�_�[
	//CircleCollider* circleCollider; ///< �v���C���[�̃T�[�N���R���C�_�[
	class RigidBody* rigidBody; ///< �v���C���[�̍��̃R���|�[�l���g

private:
	Vector2 anchorPoint;		// �Œ�_
	float length;				// �U��q�̒���
	float angle;				// �U��q�̊p�x
	float angularVelocity;		// �p���x
	float angularAcceleration;	// �p�����x
public:
	Player(); ///< �R���X�g���N�^

	void Update(float DeltaTime) override; ///< �t���[�����Ƃ̍X�V����
	void FixedUpdate(float fixedDeltaTime) override; ///< �����X�V����

	void DrawDebug() override; ///< �f�o�b�O�`�揈��
private:
	void BeginOverlap(Collider* OverlapCpm, Object* OverlapActor);
	void EndOverlap(Collider* OverlapCpm, Object* OverlapActor);
};


#endif // !_PLAYER_H_
