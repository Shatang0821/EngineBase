#include "stdafx.h"
#include "Controller.h"
#include "Camera.h"

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
