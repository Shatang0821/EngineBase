#include "Component.h"
#include "Object.h"
void Component::Update(float DeltaTime)
{
}
void Component::Destruct()
{
	pOwner->UnregisterComponent(this);
	delete this;
}
