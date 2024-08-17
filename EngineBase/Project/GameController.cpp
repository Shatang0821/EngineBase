#include "stdafx.h"
#include "GameController.h"

GameController::GameController()
{
	//ShakeTimeHandle.Bind(2.0f, this, &GameController::Shake, false);
}

void GameController::SetUpInputComponent(InputComponent* inputComponent)
{
	Controller::SetUpInputComponent(inputComponent);

	//キーバインドと設定
	inputComponent->SetMapping("Shake", DIK_X);
	inputComponent->BindAction("Shake", InputType::Pressed, this, &GameController::Shake);

	inputComponent->SetMapping("CameraMoveLeft", DIK_C);
	inputComponent->BindAction("CameraMoveLeft", InputType::Pressed, this, &GameController::CameraMove);
	inputComponent->SetMapping("CameraMoveRight", DIK_Z);
	inputComponent->BindAction("CameraMoveRight", InputType::Pressed, this, &GameController::CameraMove);


	inputComponent->SetMapping("ZoomIn", DIK_Q);
	inputComponent->BindAction("ZoomIn", InputType::Holding, this, &GameController::ZoomIn);

	inputComponent->SetMapping("ZoomOut", DIK_E);
	inputComponent->BindAction("ZoomOut", InputType::Holding, this, &GameController::ZoomOut);

	inputComponent->SetMapping("SetAxisUp", DIK_W);
	inputComponent->BindAction("SetAxisUp", InputType::Holding, this, &GameController::SetAxis);
	inputComponent->SetMapping("ResetAxisUp", DIK_W);
	inputComponent->BindAction("ResetAxisUp", InputType::Released, this, &GameController::ResetAxis);

	inputComponent->SetMapping("SetAxisDown", DIK_S);
	inputComponent->BindAction("SetAxisDown", InputType::Holding, this, &GameController::SetAxis);
	inputComponent->SetMapping("ResetAxisDown", DIK_S);
	inputComponent->BindAction("ResetAxisDown", InputType::Released, this, &GameController::ResetAxis);

	inputComponent->SetMapping("SetAxisLeft", DIK_A);
	inputComponent->BindAction("SetAxisLeft", InputType::Holding, this, &GameController::SetAxis);
	inputComponent->SetMapping("ResetAxisLeft", DIK_A);
	inputComponent->BindAction("ResetAxisLeft", InputType::Released, this, &GameController::ResetAxis);

	inputComponent->SetMapping("SetAxisRight", DIK_D);
	inputComponent->BindAction("SetAxisRight", InputType::Holding, this, &GameController::SetAxis);
	inputComponent->SetMapping("ResetAxisRight", DIK_D);
	inputComponent->BindAction("ResetAxisRight", InputType::Released, this, &GameController::ResetAxis);

	inputComponent->SetMapping("Jump", DIK_SPACE);
	inputComponent->BindAction("Jump", InputType::Pressed, this, &GameController::SetJump);
	inputComponent->SetMapping("ResetJump", DIK_SPACE);
	inputComponent->BindAction("ResetJump", InputType::Released, this, &GameController::ResetJump);
	
}

void GameController::Update(float DeltaTime)
{
	Controller::Update(DeltaTime);

	/*if (OverallTimeHandle.GetDelay() > 2.f && OverallTimeHandle.GetDelay() <= 5.f && GetWorldPosition().x < 600) {
		AddPosition(Vector2(3.f, 0));
	}
	if (OverallTimeHandle.GetDelay() > 7.f && GetWorldPosition().x >= 225.f)
	{
		AddPosition(Vector2(-3.f, 0));
	}*/
}

void GameController::Shake(BYTE key)
{
	camera->ShakeCamera(5,60);
	//AddPosition(Vector2(100.0f, 0));
}

void GameController::ZoomIn(BYTE key)
{

	armLength = Math::clamp(armLength - 0.05f, 0.5f, 10000.f);
	camera->SetSpringArmLength(armLength);
}

void GameController::ZoomOut(BYTE key)
{
	armLength = Math::clamp(armLength + 0.05f, 0.5f, 10000.f);
	camera->SetSpringArmLength(armLength);
}

void GameController::CameraMove(BYTE key)
{
	switch (key)
	{
	case DIK_C:
		camera->AddPosition(Vector2(100.0f, 0));
		break;
	case DIK_Z:
		camera->AddPosition(Vector2(-100.0f, 0));
		break;
	default:
		break;
	}
}

void GameController::SetAxis(BYTE key)
{
	switch (key) {
	case DIK_W:
		isWPressed = true;
		break;
	case DIK_S:
		isSPressed = true;
		break;
	case DIK_A:
		isAPressed = true;
		break;
	case DIK_D:
		isDPressed = true;
		break;
	default:
		break;
	}
	UpdateAxis();
	//std::cout << axis << std::endl;
}

void GameController::ResetAxis(BYTE key)
{
	switch (key) {
	case DIK_W:
		isWPressed = false;
		break;
	case DIK_S:
		isSPressed = false;
		break;
	case DIK_A:
		isAPressed = false;
		break;
	case DIK_D:
		isDPressed = false;
		break;
	default:
		break;
	}
	UpdateAxis();
}

void GameController::SetJump(BYTE)
{
	jump = true;
}

void GameController::ResetJump(BYTE)
{
	jump = false;
}

void GameController::UpdateAxis()
{
	if (isWPressed && !isSPressed) {
		axis.y = 1.0f;
	}
	else if (!isWPressed && isSPressed) {
		axis.y = -1.0f;
	}
	else {
		axis.y = 0.0f;
	}

	if (isAPressed && !isDPressed) {
		axis.x = -1.0f;
	}
	else if (!isAPressed && isDPressed) {
		axis.x = 1.0f;
	}
	else {
		axis.x = 0.0f;
	}
}
