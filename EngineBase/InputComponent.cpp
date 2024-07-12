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
			// ���͂������ꂽ�u�Ԃ��A1�t���[���O�ɉ�����Ă��Ȃ��ꍇ
			if (info.type == InputType::Pressed && !info.isPressed) {
				info.func();
			}
			if (info.type == InputType::Holding) info.func();
			// �������g���K�[��true�ɂ���
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



