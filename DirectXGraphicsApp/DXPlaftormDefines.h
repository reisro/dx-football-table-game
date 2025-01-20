#pragma once

#ifndef _PLATFORM_DEFINES_H
#define _PLATFORM_DEFINES_H

#include <string>

namespace YakiraEngine
{
	#define WINDOWSOS 1
	
	enum class OperatingSystem
	{
		Windows,
		Unix,
		Mac
	};

	enum class OSState
	{
		Initialized,
		Shutdown,
		Pause
	};

	typedef struct OperatingSystemParameters
	{
		OperatingSystemParameters(std::string uiid, OSState osstate) : 
			UIDID_instance { uiid }, state { osstate } {}

		std::string UIDID_instance;
		OSState state;

	} OperatingSystemParameters;
}

#endif _PLATFORM_DEFINES_H