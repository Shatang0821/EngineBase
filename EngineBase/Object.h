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

	//! �I�u�W�F�N�g�̎q�v�f���Ǘ����܂��B�p�ɂɍ폜��ǉ����s���邽�߁Aset���g�p���Ă��܂��B
	std::unordered_set<Object*>children;
	//! �I�u�W�F�N�g�̐e�v�f���w���܂��B�폜�ǉ����₷������
	Object* parent = nullptr;

	//! �I�u�W�F�N�g�̃��[�g�ƂȂ�Transform�������V�[���R���|�[�l���g���w���܂�
	SceneComponent * const root = new SceneComponent;
	//! �I�u�W�F�N�g�ɏ�������R���|�[�l���g���Ǘ����܂��B
	std::unordered_set<Component*>components;
	//! �R���|�[�l���g�̃C�e���[�^ �ǉ��폜�\��̃R���|�[�l���g���Ǘ����܂��B
	std::unordered_set<Component*>::iterator components_iter;
public:
	/**
	 * @brief �R���X�g���N�^
	 *
	 * ���[�g�R���|�[�l���g���L�Ґݒ�
	 */
	Object() { root->SetOwner(this); }
	/**
	 * @brief �f�X�g���N�^
	 *
	 * �R���|�[�l���g�����ׂč폜����
	 */
	virtual ~Object() {

		components_iter = components.begin();
		while (components_iter != components.end()) {
			(*components_iter)->Destruct();
			//end�𒴂��Ȃ��悤�ɐ��䂷��
			if (components_iter == components.end()) break;
		}

		components.clear();

		delete root;
	}

	/**
	 * @brief �R���|�[�l���g�̐���
	 *
	 * �w�肳�ꂽ�V�����R���|�[�l���g�𐶐����A�I�u�W�F�N�g�ɒǉ����܂��B
	 *
	 * @tparam T ��������R���|�[�l���g�̌^
	 * @return T* �������ꂽ�R���|�[�l���g�ւ̃|�C���^
	 */
	template<typename T>
	T* ConstructComponent();

	/**
	 * @brief �R���|�[�l���g�̎擾
	 *
	 * �w�肳�ꂽ�R���|�[�l���g���I�u�W�F�N�g����擾����B
	 *
	 * @tparam T �擾�������R���|�[�l���g�̌^
	 * @return T* �擾���ꂽ�R���|�[�l���g�ւ̃|�C���^
	 */
	template<typename T>
	T* GetComponentByClass();

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
	 * @brief �Q�[���v���C�̊J�n���ɌĂяo����鏃�����z�֐�
	 *
	 * ���̊֐��́A�Q�[���v���C���J�n�����Ƃ��ɏ������������s�����߂ɌĂяo����܂��B
	 * �e�h���N���X�́A���̊֐����I�[�o�[���C�h���ēƎ��̏�������������������K�v������܂��B
	 */
	virtual void BeginPlay() = 0;
	/**
	* @brief �e�I�u�W�F�N�g�̐ݒ�֐�
	*
	* ���̊֐��́A�I�u�W�F�N�g�̐e�v�f��ݒ肵�܂��B
	*
	* @param par �ݒ肷��e�I�u�W�F�N�g�ւ̃|�C���^
	*/
	void AttachTo(Object* par);
	/**
	* @brief �e�I�u�W�F�N�g�̐ݒ肷��֐�
	*
	* ���̊֐��́A�I�u�W�F�N�g�̐e�v�f���������܂��B
	*
	* @param par �ݒ肷��e�I�u�W�F�N�g�ւ̃|�C���^
	*/
	void DetachFrom(Object* par);


	/**
	 * @brief �I�u�W�F�N�g�̍X�V����
	 *
	 * ���̊֐��́A�I�u�W�F�N�g�̏�Ԃ��X�V���܂��B
	 *
	 * @param DeltaTime �O�t���[������̌o�ߎ���
	 */
	virtual void Update(float DeltaTime) override;

	/**
	 * @brief �������Z�X�V����
	 *
	 * ���̊֐��́A�I�u�W�F�N�g�̕������Z���X�V���܂��B
	 *
	 * @param fixedDeltaTime �Œ�t���[������
	 */
	virtual void FixedUpdate(float fixedDeltaTime) override;
public:

	/**
	 * @brief ���[���h���玩�g���폜����
	 *
	 */
	void Destroy();

	/**
	 * @brief ���[�J���ʒu�����擾����֐�
	 *
	 * @return Vector2 ���[�J���ʒu
	 */
	Vector2 GetLocalPosition() const { return root->GetLocalPosition(); }
	/**
	 * @brief ��]�����擾����֐�
	 *
	 * @return float ��](�x���@)
	 */
	float GetLocalRotation() const { return root->GetLocalRotation(); }
	/**
	 * @brief �X�P�[�������擾����֐�
	 *
	 * @return Vector2 �X�P�[��
	 */
	Vector2 GetLocalScale() const { return root->GetLocalScale(); }
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
	void SetLocalPosition(const Vector2& pos) { root->SetLocalPosition(pos); }
	/**
	 * @brief ���[�J����]��ݒ肷��֐�
	 * @param[in] rot ��]���
	*/
	void SetLocalRotation(float rot) { root->SetLocalRotation(rot); }
	/**
	 * @brief ���[�J���X�P�[����ݒ肷��֐�
	 * @param[in] scale �X�P�[�����
	*/
	void SetLocalScale(const Vector2& scale) { root->SetLocalScale(scale); }
	/**
	 * @brief ���[�J���ʒu�����Z����֐�
	 * @param[in] pos �ʒu���
	*/
	void AddPosition(const Vector2& pos) { root->AddPosition(pos); }
	/**
	 * @brief ���[�J����]�����Z����֐�
	 * @param[in] rot ��]���
	*/
	void AddRotation(float rot) { root->AddRotation(rot); }
};

template<typename T>
inline T* Object::ConstructComponent() {
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

template<typename T>
inline T* Object::GetComponentByClass()
{
	for (auto& com : components) {
		if (T* pCom = dynamic_cast<T*>(com)) return pCom;
	}
	return nullptr;
}

#endif // !_OBJECT_H_


