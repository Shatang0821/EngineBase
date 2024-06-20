#include "SceneComponent.h"


void SceneComponent::Update(float DeltaTime)
{
}

void SceneComponent::AttachTo(SceneComponent* par)
{
	parent->children.insert(this);
	parent = par;
}

void SceneComponent::DetachFrom(SceneComponent* par)
{
	par->children.erase(this);
	parent = nullptr;
}

void SceneComponent::process_Destruct()
{
	if (!children.empty()) 
		for (auto& child : children) child->process_Destruct();
	
	Component::Destruct();
}

void SceneComponent::Destruct()
{
	if (parent) parent->children.erase(this);

	process_Destruct();
}
