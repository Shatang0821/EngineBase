#ifndef _BASESTATE_H_
#define _BASESTATE_H_
#include "StateMachine.h"
class BaseState
{
protected:
    StateMachine* stateMachine; //< ��ԃ}�V��
public:
    BaseState(StateMachine* sm) : stateMachine(sm) {}
    virtual ~BaseState() = default;
    /// <summary>
    /// ��Ԃɓ���Ƃ��ɌĂ΂��֐�
    /// </summary>
    virtual void Enter() = 0;
    /// <summary>
    /// ��Ԃ̍X�V����
    /// </summary>
    /// <param name="deltaTime">�f���^�^�C��</param>
    virtual void LogicUpdate(float deltaTime) = 0;
    /// <summary>
    /// �����X�V�����Œ�Ԋu�ŌĂ΂��
    /// </summary>
    /// <param name="fixedDeltaTime">�����X�V�o�ߎ���</param>
    virtual void PhysicsUpdate(float fixedDeltaTime) = 0;
    /// <summary>
    /// ��Ԃ���o��Ƃ��ɌĂ΂��֐�
    /// </summary>
    virtual void Exit() = 0;
};

#endif


