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
private:

    /**
     * @brief �폜�������T�|�[�g����֐�
     *
     * ���̊֐��́A�R���|�[�l���g�̍폜�������T�|�[�g���܂��B
     */
    void process_Destruct();

protected:
    //! �R���|�[�l���g�̕ϊ����
    Transform transform;

    //! �R���|�[�l���g�̎q�v�f���Ǘ����܂��B�p�ɂɍ폜��ǉ����s���邽�߁Aset���g�p���Ă��܂��B
    std::set<SceneComponent*>children;

    //! �R���|�[�l���g�̐e�v�f���w���܂��B�폜�ǉ����₷������
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
    * @brief �e�R���|�[�l���g�̐ݒ肷��֐�
    *
    * ���̊֐��́A�R���|�[�l���g�̐e�v�f��ݒ肵�܂��B
    *
    * @param par �ݒ肷��e�R���|�[�l���g�ւ̃|�C���^
    */
    void AttachTo(SceneComponent* par);
    /**
    * @brief �e�R���|�[�l���g�̐ݒ肷��֐�
    *
    * ���̊֐��́A�R���|�[�l���g�̐e�v�f���������܂��B
    *
    * @param par �ݒ肷��e�R���|�[�l���g�ւ̃|�C���^
    */
    void DetachFrom(SceneComponent* par);

    
    /**
     * @brief �R���|�[�l���g�̍폜��������֐�
     *
     * ���̊֐��́A�R���|�[�l���g�̍폜�������s���܂��B
     */
    virtual void Destruct() override;


    /**
     * @brief ���[�J���ʒu�����擾����֐�
     *
     * @return Vector2 ���[�J���ʒu
     */
    Vector2 GetLocalPosition() const { return transform.position; }
    /**
     * @brief ��]�����擾����֐�
     *
     * @return float ��](�x���@)
     */
    float GetLocalRotation() const { return transform.rotation; }
    /**
     * @brief �X�P�[�������擾����֐�
     *
     * @return Vector2 �X�P�[��
     */
    Vector2 GetLocalScale() const { return transform.scale; }
    /**
     * @brief ���[���h�ʒu�����擾����֐�
     *
     * @return Vector2 ���[���h�ʒu(��Έʒu)
     */
    Vector2 GetWorldPosition() const;
    /**
     * @brief ���[���h��]�����擾����֐�
     *
     * @return float ���[���h��](�x���@)
     */
    float GetWorldRotation() const;
    /**
     * @brief ���[���h�X�P�[�������擾����֐�
     *
     * @return Vector2 ���[���h�X�P�[��
     */
    Vector2 GetWorldScale() const;
	/**
     * @brief ���[�J���ʒu��ݒ肷��֐�
     * @param[in] pos �ʒu���
    */
    void SetLocalPosition(const Vector2& pos) { transform.position = pos; }
    /**
     * @brief ���[�J����]��ݒ肷��֐�
     * @param[in] rot ��]���
    */
    void SetLocalRotation(float rot) { transform.rotation = rot; }
    /**
     * @brief ���[�J���X�P�[����ݒ肷��֐�
     * @param[in] scale �X�P�[�����
    */
    void SetLocalScale(const Vector2& scale) { transform.scale = scale; }
    /**
     * @brief ���[�J���ʒu�����Z����֐�
     * @param[in] pos �ʒu���
    */
    void AddPosition(const Vector2& pos) { transform.position += pos; }
    /**
     * @brief ���[�J����]�����Z����֐�
     * @param[in] rot ��]���
    */
    void AddRotation(float rot) { transform.rotation += rot; }
};

#endif // !_SCENECOMPONENT_H_

