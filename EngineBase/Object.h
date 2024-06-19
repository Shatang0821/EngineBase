#pragma once
#include "Base.h"
#include "SceneComponent.h"

class Object : public Base
{
	friend void Component::Destruct();
protected:
	SceneComponent * root = nullptr;
	//�R���|�[�l���g�̃R���e�i
	std::set<Component*>components;
	//�폜���ׂ��R���|�[�l���g�̃R���e�i
	std::set<Component*>components_to_destruct;
public:
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
	virtual void Update(float DeltaTime) override;
};

