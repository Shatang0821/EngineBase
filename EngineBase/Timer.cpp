#include "stdafx.h"
#include "Timer.h"

void Timer::Execute()
{
	if (delay.count() > 0 && getDelay().count() >= delay.count()) {
		callback();
		if (bPersistent) lastTime = std::chrono::steady_clock::now();
		else delay = std::chrono::duration<double>(0);
	}
}

double Timer::GetDelay()
{
	return getDelay().count();
}

void Timer::SetDelay(double time)
{
	delay = std::chrono::duration<double>(time);
}

void Timer::Reset()
{
	lastTime = std::chrono::steady_clock::now();

}

void Timer::Stop()
{
	delay = std::chrono::duration<double>(0);
}

