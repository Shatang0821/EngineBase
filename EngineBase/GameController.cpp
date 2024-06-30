#include "stdafx.h"
#include "GameController.h"

void GameController::Update(float DeltaTime)
{
	if (OverallTimeHandle.GetDelay() > 2.f && OverallTimeHandle.GetDelay() <= 5.f && GetWorldPosition().x < 600) {
		AddPosition(Vector2(3.f, 0));
	}
	if (OverallTimeHandle.GetDelay() > 7.f && GetWorldPosition().x >= 225.f)
	{
		AddPosition(Vector2(-3.f, 0));
	}
}
