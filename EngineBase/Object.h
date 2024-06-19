/**
 * @file Object.h
 * @brief �I�u�W�F�N�g�̊��N���X�ƂȂ�
 *
 * ���̃t�@�C���ɂ́A�Q�[�������ׂẴI�u�W�F�N�g�̊��N���X����`����Ă��܂��B
 *
 * @author �T�g�E
 * @date 2024/06/19
 */
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Base.h"
#include "SceneComponent.h"

/**
 * @class Object
 * @brief �Q�[���I�u�W�F�N�g�̊��N���X
 *
 * ���̃N���X�́A�Q�[�����̃I�u�W�F�N�g��\���A�����̃R���|�[�l���g��ێ����܂��B
 */
class Object : public Base
{
	friend void Component::Destruct();
protected:
	//! �I�u�W�F�N�g�̃��[�g�ƂȂ�V�[���R���|�[�l���g���w���܂�
	SceneComponent* root = nullptr;
	//! �I�u�W�F�N�g�ɏ�������R���|�[�l���g���Ǘ����܂��B
	std::set<Component*>components;
	//! �폜�\��̃R���|�[�l���g���Ǘ����܂��B
	std::set<Component*>components_to_destruct;
public:
	/**
	 * @brief �R���|�[�l���g�̐���
	 *
	 * �w�肳�ꂽ�ʒu�ɐV�����R���|�[�l���g�𐶐����A�I�u�W�F�N�g�ɒǉ����܂��B
	 *
	 * @tparam T ��������R���|�[�l���g�̌^
	 * @param pos �R���|�[�l���g�̈ʒu
	 * @return T* �������ꂽ�R���|�[�l���g�ւ̃|�C���^
	 */
	template<typename T>
	T* ConstructComponent(Vector2 pos) {
		T* pCom = new T();
		//�h���N���X�����N���X�ɃL���X�g���邾������static_cast���g��
		if (Component* pBuffer = static_cast<Component*>(pCom)) {
			//pBuffer->SetPosition(pos);
			pBuffer->SetOwner(this);
			components.insert(pBuffer);
			return pCom;
		}
		//���s������null��Ԃ�
		return nullptr;
	}
	/**
	 * @brief �I�u�W�F�N�g�̍X�V����
	 *
	 * ���̊֐��́A�I�u�W�F�N�g�̏�Ԃ��X�V���܂��B
	 *
	 * @param DeltaTime �O�t���[������̌o�ߎ���
	 */
	virtual void Update(float DeltaTime) override;
};

#endif // !_OBJECT_H_



