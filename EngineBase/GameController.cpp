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
	inputComponent->SetMapping("Shake", DIK_SPACE);
	inputComponent->BindAction("Shake", InputType::Released, this,&GameController::Shake);

	inputComponent->SetMapping("ZoomIn", DIK_Q);
	inputComponent->BindAction("ZoomIn", InputType::Holding, this, &GameController::ZoomIn);

	inputComponent->SetMapping("ZoomOut", DIK_E);
	inputComponent->BindAction("ZoomOut", InputType::Holding, this, &GameController::ZoomOut);


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

void GameController::Shake()
{
	//camera->ShakeCamera(5,60);
	AddPosition(Vector2(100.0f, 0));
}

void GameController::ZoomIn()
{
	std::cout << "ZoomIn" << std::endl;
	armLength = Math::clamp(armLength - 0.05f, 0.5f, 10000.f);
	camera->SetSpringArmLength(armLength);
}

void GameController::ZoomOut()
{
	std::cout << "ZoomOut" << std::endl;
	armLength = Math::clamp(armLength + 0.05f, 0.5f, 10000.f);
	camera->SetSpringArmLength(armLength);
}
