#pragma once
#include "Controller.h"
#include "Timer.h"

class GameController : public Controller
{
	Timer OverallTimeHandle;
	Timer ShakeTimeHandle;
public:
	GameController();

	void Update(float DeltaTime) override;

	void Shake();
};