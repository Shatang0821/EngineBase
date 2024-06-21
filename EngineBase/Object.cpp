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

void Object::AttachTo(Object* par)
{
	parent->children.insert(this);
	parent = par;
}

void Object::DetachFrom(Object* par)
{
	par->children.erase(this);
	parent = nullptr;
}

void Object::Update(float DeltaTime)
{
	components_iter = components.begin();
	while (components_iter != components.end()) {
		(*components_iter)->Update(DeltaTime);
		//endを超えないように制御する
		if (components_iter == components.end()) break;
		components_iter++;
	}
}

Vector2 Object::GetWorldPosition() const
{
	if (parent) return parent->GetWorldPosition() + GetLocalPosition();
	else return GetLocalPosition();
}

float Object::GetWorldRotation() const
{
	if (parent) return parent->GetWorldRotation() + GetLocalRotation();
	else return GetLocalRotation();
}

Vector2 Object::GetWorldScale() const
{
	if (parent) return parent->GetWorldScale() + GetWorldScale();
	else return GetLocalScale();
}
