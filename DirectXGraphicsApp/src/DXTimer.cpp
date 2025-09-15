#include "DXTimer.h"

DXTimer* DXTimer::Singleton = 0;

DXTimer::DXTimer()
{
	QueryPerformanceCounter((LARGE_INTEGER*)& startTime);
	lastTime = startTime;
	elapsedTime = 0;
	performanceFrequency = QueryPerformanceFrequency((LARGE_INTEGER*)& performanceFrequency);
	currentTime = QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	secondsPerTick = 0.0000001;
}

DXTimer::DXTimer(const DXTimer& rhs):
	startTime(rhs.startTime), lastTime(rhs.lastTime), elapsedTime(rhs.elapsedTime),
	performanceFrequency(rhs.performanceFrequency), currentTime(rhs.currentTime)
{
}

DXTimer::~DXTimer()
{
}

void DXTimer::CreateInstance()
{
	if (Singleton == nullptr)
	{
		Singleton = new DXTimer();
	}
}

DXTimer* DXTimer::GetInstance()
{
	return Singleton;
}

void DXTimer::Tick()
{
}

dxInt64 DXTimer::GetTicks()
{
	LARGE_INTEGER ticks;

	if (!QueryPerformanceCounter(&ticks))
	{
	}

	return ticks.QuadPart;
}

dxInt64 DXTimer::GetElapsedTime()
{
	if (QueryPerformanceCounter((LARGE_INTEGER*)&lastTime))
	{
		elapsedTime = (dxDouble)(lastTime - startTime);
	}

	return (dxInt64)(elapsedTime * secondsPerTick);
}

dxDouble DXTimer::GetDeltaTime()
{
	return deltaTime;
}

dxInt64 DXTimer::GetPerformanceCounter()
{
	if (QueryPerformanceCounter((LARGE_INTEGER*)& startTime))
	{
	}

	return startTime;
}