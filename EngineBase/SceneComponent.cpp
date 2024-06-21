#include "SceneComponent.h"
#include "Object.h"

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

Vector2 SceneComponent::GetWorldPosition() const
{
	//�e�R���|�[�l���g��z������
	if (parent)
		return parent->GetWorldPosition() + GetLocalPosition();
	else {
		//���L�҂�z������
		if (pOwner) return pOwner->GetWorldPosition();
		else return GetLocalPosition();
	}
}

float SceneComponent::GetWorldRotation() const
{
	//�e�R���|�[�l���g��z������
	if (parent)
		return parent->GetWorldRotation() + GetLocalRotation();
	else{
		//���L�҂�z������
		if (pOwner) return pOwner->GetWorldRotation();
		else return GetLocalRotation();
	}
}

Vector2 SceneComponent::GetWorldScale() const
{
	//�e�R���|�[�l���g��z������
	if (parent)
		return parent->GetWorldScale() + GetLocalScale();
	else {
		//���L�҂�z������
		if (pOwner) return pOwner->GetWorldScale();
		else return GetLocalScale();
	}
}
