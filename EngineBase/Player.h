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
	Animation animation[2]; ///< �v���C���[�̃A�j���[�V����
	Animator* animator; ///< �A�j���[�V�������Ǘ�����Animator
	BoxCollider* boxCollider; ///< �v���C���[�̃{�b�N�X�R���C�_�[
	class RigidBody* rigidBody; ///< �v���C���[�̍��̃R���|�[�l���g
	class StateMachine* stateMachine; ///< �v���C���[�̃X�e�[�g�}�V��
public:
	Player(); ///< �R���X�g���N�^


	void Update(float DeltaTime) override; ///< �t���[�����Ƃ̍X�V����
	void FixedUpdate(float fixedDeltaTime) override; ///< �����X�V����

	void DrawDebug() override; ///< �f�o�b�O�`�揈��
private:
	void BeginOverlap(Collider*, Collider*, Object* );
	void EndOverlap  (Collider*, Collider*, Object* );
	void OnHit(Collider* hitComp,Collider* otherComp,Object* otherActor,Vector2 hitNormal,const HitResult& hitResult);

	/// <summary>
	/// �A�j���[�V�����̏��������s���܂��B
	/// </summary>
	void InitAnimation();
	/// <summary>
	/// �������Z�̏��������s���܂��B
	/// </summary>
	void InitPhysics();
};


#endif // !_PLAYER_H_
