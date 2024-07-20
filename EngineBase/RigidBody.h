/**
 * @file RigidBody.h
 * @brief 剛体コンポーネント
 *
 * このファイルは、剛体コンポーネントを定義しています。
 *
 * @author サトウ
 * @date 2024/07/20
 */

#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_
#include "Component.h"


class RigidBody : public Component
{
private:
    bool bMoveable;              //< 物理移動可能かどうか
    // 位置に関する物理パラメータ
    float mass;                  //< 質量
    Vector2 velocity;            //< 速度
    Vector2 acceleration;        //< 加速度

    // 角度に関する物理パラメータ
    float angularVelocity;       //< 角速度Z
    float angularAcceleration;   //< 角加速度Z
    
    float torque;                //< トルク
    bool bRotatable;             //< 回転可能かどうか

    // その他の物理パラメータ
    Vector2 force;               //< 力
    float gravity;               //< 重力
    bool bGravityEnabled;        //< 重力の有無

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
     * @brief 物理移動可能かどうかを設定する。
     *
     * @param b 物理移動可能かどうか
     */
    void SetMoveable(bool b) { bMoveable = b; }

    /**
	 * @brief 重力を設定する。
     * 
     * @param g 重力の値
	 */
    void SetGravity(float g) { gravity = g; }
    
    /**
     * @brief 速度を設定する。
     *
     * @param v 速度の値
     */
    void SetVelocity(Vector2 v) { velocity = v; }

    /**
	 * @brief 角速度を設定する。
	 *
	 * @param v 角速度の値
	 */
    void SetAngularVelocity(float v) { angularVelocity = v; }

    /**
	 * @brief 重力の計算をするかどうかを設定する。
	 *
	 * @param b 計算するか
	 */
    void SetGravityEnabled(bool b) { bGravityEnabled = b; }
    
    /**
	 * @brief 回転の計算をするかどうかを設定する。。
	 *
	 * @param b 計算するか
	 */
    void SetRotatable(bool b) { bRotatable = b; }

    /**
     * @brief 力を加える。
     *
     * @param f 力の値
     */
    void AddForce(const Vector2& f){force += f;}
};

#endif // !_RIGIDBODY_H_



