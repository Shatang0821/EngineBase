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
    friend class Collider;
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

    std::unordered_set<Collider*> colliders;

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
        , force(Vector2::Zero())
        , gravity(98) 
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
     * @brief 重力を取得する
     *
     * @return  重力の値
    */
    float GetGravity() const { return gravity; }

    /**
	 * @brief 重力を設定する。
     * 
     * @param g 重力の値
	 */
    void SetGravity(float g) { gravity = g; }

    /**
	 * @brief 速度を取得する。
	 *
	 * @return 速度の値
	 */
    Vector2 GetVelocity() const { return velocity; }
    
    /**
     * @brief 速度を設定する。
     *
     * @param v 速度の値
     */
    void SetVelocity(Vector2 v) { velocity = v; }

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
     * @brief 角速度を取得する。
     *
     * @return 角速度の値
     */
    float GetAngularVelocity() const { return angularVelocity; }

    /**
	 * @brief 角速度を設定する。
	 *
	 * @param v 角速度の値
	 */
    void SetAngularVelocity(float v) { angularVelocity = v; }

    /**
     * @brief トルクを設定する。
     *
     * @param t トルクの値
     */
    void SetTorque(float t) { torque = t; }

    /**
     * @brief 力を加える。
     *
     * @param f 力の値
     */
    void AddForce(const Vector2& f){force += f;}

    void RestrictVelocity(class HitResult hitResult, RigidBody* another = nullptr);

};

#endif // !_RIGIDBODY_H_



