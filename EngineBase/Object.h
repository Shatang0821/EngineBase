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
	//! �R���|�[�l���g�̃C�e���[�^ �ǉ��폜�\��̃R���|�[�l���g���Ǘ����܂��B
	std::set<Component*>::iterator components_iter;
public:
	/**
	 * @brief �R���|�[�l���g�̐���
	 *
	 * �w�肳�ꂽ�V�����R���|�[�l���g�𐶐����A�I�u�W�F�N�g�ɒǉ����܂��B
	 *
	 * @tparam T ��������R���|�[�l���g�̌^
	 * @return T* �������ꂽ�R���|�[�l���g�ւ̃|�C���^
	 */
	template<typename T>
	T* ConstructComponent() {
		T* pCom = new T();
		//�h���N���X�����N���X�ɃL���X�g���邾������static_cast���g��
		if (pCom && static_cast<Component*>(pCom)) {
			pCom->SetOwner(this);
			RegisterComponent(pCom);
			return pCom;
		}
		//���s������null��Ԃ�
		return nullptr;
	}

	/**
	 * @brief �R���|�[�l���g�̓o�^
	 *
	 * �w�肳�ꂽ�R���|�[�l���g���R���e�i�ɓo�^���܂��B
	 *
	 * @param pCom �o�^����R���|�[�l���g�̃|�C���^
	 */
	void RegisterComponent(Component* pCom);

	/**
	 * @brief �R���|�[�l���g�̓o�^����
	 *
	 * �w�肳�ꂽ�R���|�[�l���g���R���e�i����������܂��B
	 *
	 * @param pCom ��������R���|�[�l���g�̃|�C���^
	 */
	void UnregisterComponent(Component* pCom);
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



