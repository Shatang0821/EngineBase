#pragma once
#include "Base.h"
#include "SceneComponent.h"

class Object : public Base
{
	friend void Component::Destruct();
protected:
	SceneComponent * root = nullptr;
	//コンポーネントのコンテナ
	std::set<Component*>components;
	//削除すべきコンポーネントのコンテナ
	std::set<Component*>components_to_destruct;
public:
	template<typename T>
	T* ConstructComponent(Vector2 pos) {
		T* pCom = new T();
		//派生クラスを基底クラスにキャストするだけからstatic_castを使う
		if (Component* pBuffer = static_cast<Component*>(pCom)) {
			//pBuffer->SetPosition(pos);
			pBuffer->SetOwner(this);
			components.insert(pBuffer);
			return pCom;
		}
		//失敗したらnullを返す
		return nullptr;
	}
	virtual void Update(float DeltaTime) override;
};

