#ifndef _BASESTATE_H_
#define _BASESTATE_H_

class BaseState
{
public:
    virtual ~BaseState() = default;
    virtual void Enter() = 0;
    virtual void LogicUpdate(float) = 0;
    virtual void PhysicsUpdate(float) = 0;
    virtual void Exit() = 0;
};

#endif


