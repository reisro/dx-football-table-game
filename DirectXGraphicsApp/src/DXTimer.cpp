#include "YETimer.h"
#include <thread>
#include <ctime>

YETimer* YETimer::Singleton = 0;

YETimer::YETimer()
{
	//QueryPerformanceCounter((LARGE_INTEGER*)& startTime);
	lastTime = clock_c::now();
	elapsedTime = 0;
	performanceFrequency = QueryPerformanceFrequency((LARGE_INTEGER*)& performanceFrequency);
	
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
	startTime = clock_c::now();

	seconds deltatime = startTime - lastTime;
		
	lastTime = startTime;

	return deltatime.count();
}

std::chrono::steady_clock::duration YETimer::GetCurrTime()
{
	return startTime.time_since_epoch();
}

bool YETimer::Countdown(int duration)
{
	bool returnValue = false;
	static bool getTime = false;

	static yeInt reachTime;

	auto start = startTime.time_since_epoch();

	auto now_s = std::chrono::duration_cast<std::chrono::seconds>(clock_c::now().time_since_epoch());

	if (!getTime)
	{
		reachTime = now_s.count() + duration;
		getTime = true;
	}

	if (now_s.count() > reachTime)
	{
		getTime = false;

		returnValue = true;
	}

	return returnValue;
}

void YETimer::ResetCountdown()
{
	//getTime = false;
}

void YETimer::NowTime()
{
	startTime = clock_c::now();
}

dxDouble YETimer::GetDeltaTime()
{
	seconds deltatime = startTime - lastTime;

	dxDouble millisecs = deltatime.count() / 1000.0;

	return millisecs;
}

dxInt64 YETimer::GetPerformanceCounter()
{
	if (QueryPerformanceCounter((LARGE_INTEGER*)& startTime))
	{
	}

	return 0.0;
}

void YETimer::UpdateLastTime()
{
	lastTime = startTime;
}
