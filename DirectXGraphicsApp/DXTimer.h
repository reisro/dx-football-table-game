#pragma once

#ifndef DX_TIMER_H
#define DX_TIMER_H

#include <Windows.h>
#include <timeapi.h>
#include <profileapi.h>
#include "DXTypes.h"

class DXTimer
{
public:
	                DXTimer();
	                DXTimer(const DXTimer& rhs);
	virtual        ~DXTimer();

	void           Tick();
	dxInt64        GetTicks();
	dxInt64        GetElapsedTime();
	dxInt64        GetPerformanceCounter();

	inline dxInt64 GetCurrentTime() const { return currentTime; }
	inline dxInt64 GetPerformanceFrequency() const { return performanceFrequency; }

private:

	dxInt64		  startTime;
	dxInt64       lastTime;
	dxInt64       currentTime;
	dxInt64       performanceFrequency;
	dxDouble      elapsedTime;
	dxDouble      secondsPerTick;
};

#endif DX_TIMER_H