#pragma once

#include <windows.h>

/////////////////////////////////////////////////////////////
// タイマー管理クラス.

class CTimer
{
private:
	LARGE_INTEGER StartingTime;
	LARGE_INTEGER Frequency;

public:
	CTimer()
	{
		StartingTime.QuadPart = 0;
		Frequency.QuadPart = 0;
		InitTimer();
	}
	~CTimer() {};

	// タイマー初期化.
	void InitTimer() {
		QueryPerformanceFrequency(&Frequency);
	}
	// タイマー開始.
	void StartTimer() {
		QueryPerformanceCounter(&StartingTime);
	}
	void GetPassTime(float*);
	void GetFps(UINT*);
};

