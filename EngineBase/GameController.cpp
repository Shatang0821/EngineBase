#include "stdafx.h"
#include "GameController.h"

GameController::GameController()
{
	ShakeTimeHandle.Bind(2.0f, this, &GameController::Shake, false);
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
	camera->ShakeCamera(5,1);
}
