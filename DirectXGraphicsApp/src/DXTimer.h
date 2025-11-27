#pragma once

#ifndef DX_TIMER_H
#define DX_TIMER_H

#include "pch.h"
#include <Windows.h>
#include <chrono> 
#include <timeapi.h>
#include <profileapi.h>

using clock_c = std::chrono::high_resolution_clock;
using seconds = std::chrono::duration<dxDouble>;

class YETimer
{
public:
					YETimer();
					YETimer(const YETimer& rhs);
	virtual        ~YETimer();

	//-------------------------------------------------------------------------
	// Public Static Functions
	//-------------------------------------------------------------------------
	static void     CreateInstance();
	static YETimer* GetInstance();

	//-------------------------------------------------------------------------
	// Public Methods
	//-------------------------------------------------------------------------
	void			Tick();
	dxInt64			GetTicks();
	dxInt64			GetElapsedTime();
	void			NowTime();
	dxDouble		GetDeltaTime();
	dxInt64			GetPerformanceCounter();
	void			UpdateLastTime();

	inline dxInt64	GetPerformanceFrequency() const { return performanceFrequency; }
	std::chrono::steady_clock::time_point GetStartTime() const { return startTime; }
protected:
	static YETimer* Singleton;

private:

	std::chrono::steady_clock::time_point		startTime;
	std::chrono::steady_clock::time_point		lastTime;

	seconds			currentTime;
	dxInt64			performanceFrequency;
	dxDouble		deltaTime;
	dxDouble		elapsedTime;
	dxDouble		secondsPerTick;
};

#endif DX_TIMER_H