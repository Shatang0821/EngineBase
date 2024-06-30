#pragma once
#include "Controller.h"
#include "Timer.h"

class GameController : public Controller
{
	Timer OverallTimeHandle;
public:
	void Update(float DeltaTime) override;
};