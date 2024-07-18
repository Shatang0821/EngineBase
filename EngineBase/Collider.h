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
public:
	enum ColliderShape {
		COLLIDER_SHAPE_CIRCLE,
		COLLIDER_SHAPE_BOX,
	};
private:
	//! �R���C�_�[�̃^�C�v �^�C�v���g���ē����蔻��̏������K�v�ȓ��m�𔻕ʂ���
	std::string type = "Default";

	//! ���C��
	int layer = 0;
	//! ���t���[�����g�ƏՓ˂��Ă���R���C�_�[
	std::unordered_set<Collider*> collisions;
	//! �Փ˂��Ă���I�u�W�F�N�g
	std::vector<Object*>aims;

protected:
	ColliderShape shape = COLLIDER_SHAPE_CIRCLE;

	virtual bool CollisionJudge(Collider* another) = 0;
public:
	Collider(){mainWorld.GameColliders.insert(this);}
	virtual ~Collider(){mainWorld.GameColliders.erase(this);}

	const std::vector<Object*>& GetCollisions(std::string type);


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
	const std::string& GetType() { return type; }

	/**
	 * @brief ���̊֐��́A�R���C�_�[�̃^�C�v��ݒ肵�܂��B
	 * 
	 * @param type �R���C�_�[�̃^�C�v
	 */
	void SetType(std::string type) { this->type = type; }

	ColliderShape GetShape() { return shape; }

	/**
	 * @brief ���̊֐��́A�R���e�i�̒��g���N���A���܂��B
	 * 
	 */
	void Clear(){collisions.clear(); }

	/**
	 * @brief ���̊֐��́A�Փ˂��Ă���R���C�_�[���W�߂Ă���
	 * 
	 * �����Ƃ̓����蔻����s���A�Փ˂��Ă���R���C�_�[��
	 * collisions�ɒǉ����܂��B
	 * 
	 * @param another �Փ˂��Ă���R���C�_�[
	 */
	void Inser(Collider* another);

	virtual void DrawDebugLine() = 0;
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
	CircleCollider(){shape = COLLIDER_SHAPE_CIRCLE; }

	virtual void Update(float DeltaTime) override;
	virtual void DrawDebugLine() override;

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
	BoxCollider(){shape = COLLIDER_SHAPE_BOX; }

	virtual void Update(float DeltaTime) override;
	virtual void DrawDebugLine() override;

	const Vector2& GetSize()const { return size; }
	void SetSize(const Vector2& s) { size = s; size_init = s / GetWorldScale(); }
};



#endif // !_COLLIDER_H_



