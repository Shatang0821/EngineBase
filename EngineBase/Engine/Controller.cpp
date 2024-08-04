#include "stdafx.h"
#include "Controller.h"
#include "Camera.h"
#include "World.h"
#include "Collider.h"

Controller::Controller()
{
	camera = ConstructComponent<Camera>();
	camera->AttachTo(root);
	camera->SetMainCamera();

	inputComponent = ConstructComponent<InputComponent>();

}

void Controller::BeginPlay()
{
	SetUpInputComponent(inputComponent);
}

Vector2 Controller::GetMousePosition() const
{
	return inputComponent->GetMousePos();
}

Object* Controller::GetObjectUnderCursor()
{
	Vector2 pos = inputComponent->GetMousePos();
	int x = int(pos.x) / 100; x = Math::clamp(x, 0, 7);
	int y = int(pos.y) / 100; y = Math::clamp(y, 0, 5);

	if (!mainWorld.ColliderZones[x][y].empty()) {
		// レイヤーの高い順にソート
		for (auto it = mainWorld.ColliderZones[x][y].rbegin(); it != mainWorld.ColliderZones[x][y].rend(); it++)
		{
			if ((*it)->IsMouseOver())
			{
				return (*it)->pOwner;
			}
		}
		return nullptr;
	}
}
