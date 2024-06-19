#ifndef _SCENECOMPONENT_H_
#define _SCENECOMPONENT_H_

#include <set>
#include "Component.h"
#include "Transform.h"

class SceneComponent : public Component
{
protected:
    Transform transform;
    //�q
    //�p�ɂɍ폜�ǉ��ȂǍs�����ߖ؍\����set���g��
    std::set<SceneComponent*>children;
    //�e
    SceneComponent* parent = nullptr;
public:
    virtual void Update(float DeltaTime) override;
    //�e�̐ݒ�
    void SetAttachment(SceneComponent* par);

    //�폜���T�|�[�g����֐�
    void process_Destruct();

    //�폜�֐�
    virtual void Destruct() override;
};

#endif // !_SCENECOMPONENT_H_

