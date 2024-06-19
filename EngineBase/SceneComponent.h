#ifndef _SCENECOMPONENT_H_
#define _SCENECOMPONENT_H_

#include <set>
#include "Component.h"
#include "Transform.h"

class SceneComponent : public Component
{
protected:
    Transform transform;
    //子
    //頻繁に削除追加など行うため木構造のsetを使う
    std::set<SceneComponent*>children;
    //親
    SceneComponent* parent = nullptr;
public:
    virtual void Update(float DeltaTime) override;
    //親の設定
    void SetAttachment(SceneComponent* par);

    //削除をサポートする関数
    void process_Destruct();

    //削除関数
    virtual void Destruct() override;
};

#endif // !_SCENECOMPONENT_H_

