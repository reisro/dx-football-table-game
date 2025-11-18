#pragma once

#ifndef DX_TIMER_H
#define DX_TIMER_H

#include "pch.h"
#include <Windows.h>
#include <timeapi.h>
#include <profileapi.h>

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
	dxDouble		GetDeltaTime();
	dxInt64			GetPerformanceCounter();

	inline dxInt64	GetCurrentTime() const { return currentTime; }
	inline dxInt64	GetPerformanceFrequency() const { return performanceFrequency; }

protected:
	static YETimer* Singleton;

private:

	dxInt64			startTime;
	dxInt64			lastTime;
	dxInt64			currentTime;
	dxInt64			performanceFrequency;
	dxDouble		deltaTime;
	dxDouble		elapsedTime;
	dxDouble		secondsPerTick;
};

#endif DX_TIMER_H