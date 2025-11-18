#include "DXTimer.h"

YETimer* YETimer::Singleton = 0;

YETimer::YETimer()
{
	QueryPerformanceCounter((LARGE_INTEGER*)& startTime);
	lastTime = startTime;
	elapsedTime = 0;
	performanceFrequency = QueryPerformanceFrequency((LARGE_INTEGER*)& performanceFrequency);
	currentTime = QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	secondsPerTick = 0.0000001;

	YELog("\nCreated Timer instance....");
}

YETimer::YETimer(const YETimer& rhs):
	startTime(rhs.startTime), lastTime(rhs.lastTime), elapsedTime(rhs.elapsedTime),
	performanceFrequency(rhs.performanceFrequency), currentTime(rhs.currentTime)
{
}

YETimer::~YETimer()
{
}

void YETimer::CreateInstance()
{
	if (Singleton == nullptr)
	{
		Singleton = new YETimer();
	}
}

YETimer* YETimer::GetInstance()
{
	return Singleton;
}

void YETimer::Tick()
{
}

dxInt64 YETimer::GetTicks()
{
	LARGE_INTEGER ticks;

	if (!QueryPerformanceCounter(&ticks))
	{
	}

	return ticks.QuadPart;
}

dxInt64 YETimer::GetElapsedTime()
{
	if (QueryPerformanceCounter((LARGE_INTEGER*)&lastTime))
	{
		elapsedTime = (dxDouble)(lastTime - startTime);
	}

	return (dxInt64)(elapsedTime * secondsPerTick);
}

dxDouble YETimer::GetDeltaTime()
{
	return deltaTime;
}

dxInt64 YETimer::GetPerformanceCounter()
{
	if (QueryPerformanceCounter((LARGE_INTEGER*)& startTime))
	{
	}

	return startTime;
}