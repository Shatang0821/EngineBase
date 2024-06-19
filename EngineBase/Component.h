/**
 * @file Component.h
 * @brief �R���|�[�l���g�̊��N���X�ƂȂ�
 *
 * ���̃t�@�C���́A���ׂẴR���|�[�l���g�̊��N���X���`���Ă��܂��B
 *
 * @author �T�g�E
 * @date 2024/06/19
 */
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Base.h"

 /**
  * @class Component
  * @brief �R���|�[�l���g�̊��N���X
  *
  * ���̃N���X�́A���ׂẴR���|�[�l���g�̊��N���X�ƂȂ�܂��B
  */
class Component : public Base
{
    friend class Object;
protected:
    //! �R���|�[�l���g�̏��L�ҁi�e�I�u�W�F�N�g�j���w���܂��B
    class Object* pOwner = nullptr;
    /**
     * @brief ���L�҂̐ݒ�
     *
     * ���̊֐��́A�R���|�[�l���g�̏��L�ҁi�e�I�u�W�F�N�g�j��ݒ肵�܂��B
     *
     * @param owner �ݒ肷�鏊�L�҂ւ̃|�C���^
     */
    void SetOwner(class Object* owner) { pOwner = owner; }
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
     * @brief �폜����
     *
     * ���̊֐��́A�R���|�[�l���g�̍폜�������s���܂��B
     */
    virtual void Destruct();
};

#endif // !_COMPONENT_H_
