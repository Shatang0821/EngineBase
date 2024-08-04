#pragma once

#include <windows.h>

/////////////////////////////////////////////////////////////
// �^�C�}�[�Ǘ��N���X.

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

	// �^�C�}�[������.
	void InitTimer() {
		QueryPerformanceFrequency(&Frequency);
	}
	// �^�C�}�[�J�n.
	void StartTimer() {
		QueryPerformanceCounter(&StartingTime);
	}
	void GetPassTime(float*);
	void GetFps(UINT*);
};

