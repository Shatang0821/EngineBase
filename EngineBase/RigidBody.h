/**
 * @file RigidBody.h
 * @brief ���̃R���|�[�l���g
 *
 * ���̃t�@�C���́A���̃R���|�[�l���g���`���Ă��܂��B
 *
 * @author �T�g�E
 * @date 2024/07/20
 */

#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_
#include "Component.h"


class RigidBody : public Component
{
private:
    bool bMoveable;              //< �����ړ��\���ǂ���
    // �ʒu�Ɋւ��镨���p�����[�^
    float mass;                  //< ����
    Vector2 velocity;            //< ���x
    Vector2 acceleration;        //< �����x

    // �p�x�Ɋւ��镨���p�����[�^
    float angularVelocity;       //< �p���xZ
    float angularAcceleration;   //< �p�����xZ
    
    float torque;                //< �g���N
    bool bRotatable;             //< ��]�\���ǂ���

    // ���̑��̕����p�����[�^
    Vector2 force;               //< ��
    float gravity;               //< �d��
    bool bGravityEnabled;        //< �d�̗͂L��

public:
    RigidBody() 
        : bMoveable(true)
        , mass(1.0f)
        , velocity(Vector2::Zero())
        , acceleration(Vector2::Zero())
        , angularVelocity(0)
        , angularAcceleration(0)
        , torque(0)
        , bRotatable(true)
        , force(Vector2::One())
        , gravity(1) 
        , bGravityEnabled(true)
    {};
    virtual void FixedUpdate(float fixedDeltaTime) override;

    /**
     * @brief �����ړ��\���ǂ�����ݒ肷��B
     *
     * @param b �����ړ��\���ǂ���
     */
    void SetMoveable(bool b) { bMoveable = b; }

    /**
	 * @brief �d�͂�ݒ肷��B
     * 
     * @param g �d�͂̒l
	 */
    void SetGravity(float g) { gravity = g; }
    
    /**
     * @brief ���x��ݒ肷��B
     *
     * @param v ���x�̒l
     */
    void SetVelocity(Vector2 v) { velocity = v; }

    /**
	 * @brief �p���x��ݒ肷��B
	 *
	 * @param v �p���x�̒l
	 */
    void SetAngularVelocity(float v) { angularVelocity = v; }

    /**
	 * @brief �d�͂̌v�Z�����邩�ǂ�����ݒ肷��B
	 *
	 * @param b �v�Z���邩
	 */
    void SetGravityEnabled(bool b) { bGravityEnabled = b; }
    
    /**
	 * @brief ��]�̌v�Z�����邩�ǂ�����ݒ肷��B�B
	 *
	 * @param b �v�Z���邩
	 */
    void SetRotatable(bool b) { bRotatable = b; }

    /**
     * @brief �͂�������B
     *
     * @param f �͂̒l
     */
    void AddForce(const Vector2& f){force += f;}
};

#endif // !_RIGIDBODY_H_



