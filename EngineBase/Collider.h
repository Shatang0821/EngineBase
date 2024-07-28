/**
 * @file Collider.h
 * @brief �R���C�_�[�N���X�̒�`
 *
 * ���̃t�@�C���ɂ́ACollider�N���X����`����Ă��܂��B
 * Collider�N���X�́A�����蔻����s�����߂̃N���X�ł��B
 *
 * @date 2024/07/17
 * @autor �T�g�E
 */

#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "World.h"
#include "Delegate.h"
#include "CollisionManager.h"

//�����蔻��̌`��
enum class ColliderShape:uint8_t {
	COLLIDER_SHAPE_CIRCLE,
	COLLIDER_SHAPE_BOX,
};

//�����蔻��̃��[�h
enum class CollisionMode :uint8_t {
	NONE,
	TRIGGER,
	COLLISION,
};

//�O���錾
class Collider;

//�Փ˃f���Q�[�g

/*Collider* overlapComp,Collider* otherComp, Object* otherActor */
DECLARE_MULTI_PARAM_MULTICAST_DELEGATE_CLASS(CollisionOverlapDelegate, Collider*, Collider*, Object*);


 /**
   * @class Collider
   * @brief �R���C�_�[�N���X
   *
   * @details ���̃N���X�́A
   * �����蔻����s�����߂̃N���X�ł��B
   *
   */
class Collider : public SceneComponent
{
	friend class Controller;
private:
	//! �R���C�_�[�̃^�C�v �^�C�v���g���ē����蔻��̏������K�v�ȓ��m�𔻕ʂ���
	CollisionType type = CollisionType::Default;
	//! �����蔻��̃��[�h
	CollisionMode collisionMode = CollisionMode::TRIGGER;
	
	//! �Փ˂��Ă���R���C�_�[�͈͂�\��
	Pair point{-1,-1},point_1{-1,-1};

	//! ���C��
	int layer = 0;
	//! ���t���[�����g�ƏՓ˂��Ă���R���C�_�[
	std::unordered_set<Collider*> collisions;
	//! �Փ˂��Ă���I�u�W�F�N�g
	std::vector<Object*>aims;
	//! �R���C�_�[���폜���邽�߂̃R���e�i
	std::vector<Collider*>collisions_to_erase;

protected:
	ColliderShape shape = ColliderShape::COLLIDER_SHAPE_CIRCLE;

	/**
	 * @brief ���̊֐��́A�����蔻����s���܂��B
	 *
	 * @param another �Փ˂��Ă���R���C�_�[
	 * 
	 * @return �Փ˂��Ă��邩�ǂ���
	 */
	virtual bool CollisionJudge(Collider* another) = 0;

	/**
	 * @brief ���̊֐��́A�}�E�X�Ƃ̓����蔻����s���܂��B
	 * 
	 * @return �Փ˂��Ă��邩�ǂ���
	 */
	virtual bool IsMouseOver() = 0;
public:
	Collider(){mainWorld.GameColliders.insert(this);}
	virtual ~Collider(){
		mainWorld.GameColliders.erase(this);
		Clear();
	}

	/**
	 * @brief ���̊֐��́A�X�V�������s���܂��B
	 *
	 * @param DeltaTime �O�̃t���[������̌o�ߎ���
	 */
	void Update(float DeltaTime) override;
	
	

	const std::vector<Object*>& GetCollisions(CollisionType type);


	/**
	 * @brief ���̊֐��́A���C���[���擾���܂��B
	 * 
	 * @return ���C���[
	 */
	int GetLayer()const{ return layer; }

	/**
	 * @brief ���̊֐��́A���C���[��ݒ肵�܂��B
	 * 
	 * @param l ���C���[
	 */
	void SetLayer(int l) { layer = l; }

	/**
	 * @brief ���̊֐��́A�R���C�_�[�̃^�C�v���擾���܂��B
	 * 
	 * @return �R���C�_�[�̃^�C�v
	 */
	const CollisionType GetType() { return type; }

	/**
	 * @brief ���̊֐��́A�R���C�_�[�̃^�C�v��ݒ肵�܂��B
	 * 
	 * @param type �R���C�_�[�̃^�C�v
	 */
	void SetType(CollisionType type) { this->type = type; }

	/**
	 * @brief ���̊֐��́A�R���C�_�[�̌`����擾���܂��B
	 * 
	 * @return �R���C�_�[�̌`��
	 */
	ColliderShape GetShape() { return shape; }
	
	/**
	 * @brief ���̊֐��́A�R���C�_�[�̓����蔻��̃��[�h��ݒ肵�܂��B
	 * 
	 * @param mode �����蔻��̃��[�h
	 */
	void SetCollisionMode(CollisionMode mode) { collisionMode = mode; }

	/**
	 * @brief ���̊֐��́A�R���C�_�[�̓����蔻��̃��[�h���擾���܂��B
	 * 
	 * @return �����蔻��̃��[�h
	 */
	CollisionMode GetCollisionMode() { return collisionMode; }

	/**
	 * @brief ���̊֐��́A�R���e�i�̒��g���N���A���܂��B
	 * 
	 */
	void Clear();

	/**
	 * @brief ���̊֐��́A�Փ˂��Ă���R���C�_�[���W�߂Ă���
	 * 
	 * �����Ƃ̓����蔻����s���A�Փ˂��Ă���R���C�_�[��
	 * collisions�ɒǉ����܂��B
	 * 
	 * @param another �Փ˂��Ă���R���C�_�[
	 */
	void Insert(Collider* another);

	/**
	 * @brief ���̊֐��́A�Փ˂��ĂȂ��R���C�_�[���폜���܂��B
	 * 
	 */
	void Erase();


	virtual void DrawDebugLine() = 0;

	CollisionOverlapDelegate OnComponentBeginOverlap;
	CollisionOverlapDelegate OnComponentEndOverlap;
};

/**
 * @class CircleCollider
 * @brief �~�R���C�_�[�N���X
 *
 * @details ���̃N���X�́A
 * �~�R���C�_�[�𐶐����邽�߂̃N���X�ł��B
 *
 */
class CircleCollider final : public Collider
{
private:
	//! ���a
	float radius = 0.0f;
	float radius_init = 0.0f;

	virtual bool CollisionJudge(Collider* another) override;

public:
	CircleCollider(){shape = ColliderShape::COLLIDER_SHAPE_CIRCLE; }

	/**
	 * @brief ���̊֐��́A�X�V�������s���܂��B
	 *
	 * @param DeltaTime �O�̃t���[������̌o�ߎ���
	 */
	void Update(float DeltaTime) override;
	/**
	 * @brief ���̊֐��́A�f�o�b�O���C����`�悵�܂��B
	 * 
	 */
	virtual void DrawDebugLine() override;
	/**
	 * @brief ���̊֐��́A�}�E�X�Ƃ̓����蔻����s���܂��B
	 * 
	 * @return �Փ˂��Ă��邩�ǂ���
	 */
	virtual bool IsMouseOver() override;

	float GetRadius()const { return radius; }
	void SetRadius(float r) { radius = r; radius_init = r / sqrtf(GetWorldScale().x * GetWorldScale().y); }

};

/**
 * @class BoxCollider
 * @brief �{�b�N�X�R���C�_�[�N���X
 *
 * @details ���̃N���X�́A
 * �{�b�N�X�R���C�_�[�𐶐����邽�߂̃N���X�ł��B
 *
 */
class BoxCollider final : public Collider
{
private:
	Vector2 size = Vector2::Zero();
	Vector2 size_init = Vector2::Zero();
	
	virtual bool CollisionJudge(Collider* another) override;
public:
	BoxCollider(){shape = ColliderShape::COLLIDER_SHAPE_BOX; }

	/**
	 * @brief ���̊֐��́A�X�V�������s���܂��B
	 * 
	 * @param DeltaTime �O�̃t���[������̌o�ߎ���
	 */
	void Update(float DeltaTime) override;
	/**
	 * @brief ���̊֐��́A�f�o�b�O���C����`�悵�܂��B
	 * 
	 */
	virtual void DrawDebugLine() override;
	/**
	 * @brief ���̊֐��́A�}�E�X�Ƃ̓����蔻����s���܂��B
	 * 
	 * @return �Փ˂��Ă��邩�ǂ���
	 */
	virtual bool IsMouseOver() override;

	const Vector2& GetSize()const { return size; }
	void SetSize(const Vector2& s) { size = s; size_init = s / GetWorldScale(); }
};



#endif // !_COLLIDER_H_



