#include "stdafx.h"
#include "InputManager.h"
#include "InputComponent.h"

void InputComponent::SetMapping(std::string mappingName, BYTE code)
{
	mappings.insert({mappingName,code });
}

void InputComponent::Update(float DeltaTime)
{
	InputManager::Instance()->GetMousePos(&lx, &ly);
	mousePos.x = static_cast<float>(lx);
	mousePos.y = static_cast<float>(ly);

	for (auto& mapping : mappings) {
		KeyBindInfo& info = callbacks[mapping.first];

		if(InputManager::Instance()->IsPushKey(mapping.second)) {
			// 入力が押された瞬間かつ、1フレーム前に押されていない場合
			if (info.type == InputType::Pressed && !info.isPressed) {
				info.func();
			}
			if (info.type == InputType::Holding) info.func();
			// 押されるトリガーをtrueにする
			info.isPressed = true;
		}
		else if(info.isPressed) {
			if(info.type == InputType::Pressed) info.isPressed = false;
			else if(info.type == Released) {
				info.func();
				info.isPressed = false;
			}

		}
	}
}



