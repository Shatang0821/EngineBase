#include "Component.h"
#include "Object.h"
void Component::Update(float DeltaTime)
{
}
void Component::Destruct()
{
	pOwner->components_to_destruct.insert(this);
}
