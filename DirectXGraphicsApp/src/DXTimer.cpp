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

yeInt YETimer::Countdown()
{
	auto start = startTime.time_since_epoch();

	auto now_s = std::chrono::duration_cast<std::chrono::seconds>(start).count();

	YELog("Countdown Start:"+std::to_string(std::chrono::duration_cast<std::chrono::seconds>(start).count()));

	return now_s;
}

void YETimer::NowTime()
{
	startTime = clock_c::now();
}

dxDouble YETimer::GetDeltaTime()
{
	seconds deltatime = startTime - lastTime;

	dxDouble millisecs = deltatime.count() / 1000.0;

	//YELog("Delta Time:" + std::to_string(millisecs));

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
