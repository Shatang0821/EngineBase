#include "stdafx.h"
#include "CTimer.h"

void CTimer::GetPassTime(float* pTime)
{
	LARGE_INTEGER EndingTime;
	LARGE_INTEGER ElapsedMS;

	QueryPerformanceCounter(&EndingTime);
	ElapsedMS.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	// �o�ߎ��Ԃ�b�P�ʂŕԂ�
	*pTime = static_cast<float>(ElapsedMS.QuadPart) / Frequency.QuadPart;
}

void CTimer::GetFps(UINT* pFps)
{
	float elapsedTime;
	GetPassTime(&elapsedTime);
	*pFps = static_cast<UINT>(1.0f / elapsedTime);
}
