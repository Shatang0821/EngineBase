#include "stdafx.h"
#include "Timer.h"

void Timer::Execute()
{
	if (delay.count() > 0 && getDelay().count() >= delay.count() && bRunning) {
		callback();
		if (bPersistent) lastTime = std::chrono::steady_clock::now();
		else delay = std::chrono::duration<double>(0);
	}
}

