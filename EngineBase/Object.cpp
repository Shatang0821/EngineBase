#include "Object.h"

void Object::RegisterComponent(Component* pCom)
{
	components.insert(pCom);
}

void Object::UnregisterComponent(Component* pCom)
{
	auto it = components.find(pCom);
	components_iter = components.erase(it);
}

void Object::Update(float DeltaTime)
{
	components_iter = components.begin();
	while (components_iter != components.end()) {
		(*components_iter)->Update(DeltaTime);
		//end�𒴂��Ȃ��悤�ɐ��䂷��
		if (components_iter == components.end()) break;
		components_iter++;
	}
}
