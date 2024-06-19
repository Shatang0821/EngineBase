#include "SceneComponent.h"


void SceneComponent::Update(float DeltaTime)
{
}

void SceneComponent::SetAttachment(SceneComponent* par)
{
	parent = par;
	parent->children.insert(this);
}

void SceneComponent::process_Destruct()
{
	if (!children.empty()) {
		for (auto& child : children) child->process_Destruct();
	}
	
}

void SceneComponent::Destruct()
{
	Component::Destruct();
	if (parent) parent->children.erase(this);

	process_Destruct();
}
