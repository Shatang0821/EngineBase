/**
 * @file SceneComponent.h
 * @brief �V�[���R���|�[�l���g�̊��N���X�ƂȂ�
 *
 * ���̃t�@�C���́A�V�[���R���|�[�l���g�̊��N���X���`���Ă��܂��B
 *
 * @author �T�g�E
 * @date 2024/06/19
 */

#ifndef _SCENECOMPONENT_H_
#define _SCENECOMPONENT_H_

#include <set>
#include "Component.h"
#include "Transform.h"

 /**
  * @class SceneComponent
  * @brief �V�[�����̃R���|�[�l���g��\���N���X
  *
  * ���̃N���X�́A�V�[�����̃R���|�[�l���g��\���A�e�q�֌W�������Ƃ��ł��܂��B
  */
class SceneComponent : public Component
{
protected:
    //! �R���|�[�l���g�̕ϊ����
    Transform transform;
    //! �R���|�[�l���g�̎q�v�f���Ǘ����܂��B�p�ɂɍ폜��ǉ����s���邽�߁Aset���g�p���Ă��܂��B
    std::set<SceneComponent*>children;
    //! �R���|�[�l���g�̐e�v�f���w���܂��B
    SceneComponent* parent = nullptr;
public:
    /**
     * @brief �R���|�[�l���g�̍X�V����
     *
     * ���̊֐��́A�R���|�[�l���g�̏�Ԃ��X�V���܂��B
     *
     * @param DeltaTime �O�t���[������̌o�ߎ���
     */
    virtual void Update(float DeltaTime) override;

    /**
    * @brief �e�R���|�[�l���g�̐ݒ�
    *
    * ���̊֐��́A�R���|�[�l���g�̐e�v�f��ݒ肵�܂��B
    *
    * @param par �ݒ肷��e�R���|�[�l���g�ւ̃|�C���^
    */
    void SetAttachment(SceneComponent* par);

    /**
     * @brief �폜�������T�|�[�g����֐�
     *
     * ���̊֐��́A�R���|�[�l���g�̍폜�������T�|�[�g���܂��B
     */
    void process_Destruct();

    /**
     * @brief �R���|�[�l���g�̍폜����
     *
     * ���̊֐��́A�R���|�[�l���g�̍폜�������s���܂��B
     */
    virtual void Destruct() override;
};

#endif // !_SCENECOMPONENT_H_

