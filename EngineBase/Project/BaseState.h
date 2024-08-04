#ifndef _BASESTATE_H_
#define _BASESTATE_H_
#include "StateMachine.h"
class BaseState
{
protected:
    StateMachine* stateMachine; //< 状態マシン
public:
    BaseState(StateMachine* sm) : stateMachine(sm) {}
    virtual ~BaseState() = default;
    /// <summary>
    /// 状態に入るときに呼ばれる関数
    /// </summary>
    virtual void Enter() = 0;
    /// <summary>
    /// 状態の更新処理
    /// </summary>
    /// <param name="deltaTime">デルタタイム</param>
    virtual void LogicUpdate(float deltaTime) = 0;
    /// <summary>
    /// 物理更新処理固定間隔で呼ばれる
    /// </summary>
    /// <param name="fixedDeltaTime">物理更新経過時間</param>
    virtual void PhysicsUpdate(float fixedDeltaTime) = 0;
    /// <summary>
    /// 状態から出るときに呼ばれる関数
    /// </summary>
    virtual void Exit() = 0;
};

#endif


