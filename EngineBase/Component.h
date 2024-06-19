#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Base.h"

//�R���|�[�l���x�[�X
class Component : public Base
{
    friend class Object;
protected:
    //���L��
    class Object* pOwner = nullptr;
    //���L�҂̐ݒ�
    void SetOwner(class Object* owner) { pOwner = owner; }
public:
    virtual void Update(float DeltaTime) override;
    //�폜����
    virtual void Destruct();
};

#endif // !_COMPONENT_H_
