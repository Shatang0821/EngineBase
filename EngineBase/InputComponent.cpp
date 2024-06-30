#include "stdafx.h"
#include "InputComponent.h"

void InputComponent::SetMapping(std::string mappingName, int value)
{
	mappings.insert({mappingName,value});
}

void InputComponent::Update(float DeltaTime)
{
	for (auto& mapping : mappings) {
		KeyBindInfo& info = callbacks[mapping.first];
	}
}
