#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Base.h"

//コンポーネンベース
class Component : public Base
{
    friend class Object;
protected:
    //所有者
    class Object* pOwner = nullptr;
    //所有者の設定
    void SetOwner(class Object* owner) { pOwner = owner; }
public:
    virtual void Update(float DeltaTime) override;
    //削除処理
    virtual void Destruct();
};

#endif // !_COMPONENT_H_
