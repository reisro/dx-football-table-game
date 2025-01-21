#pragma once

#ifndef _PLATFORM_DEFINES_H
#define _PLATFORM_DEFINES_H

#include <memory>
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

	class GameState;

	class PlatformOperatingSystem
	{
		PlatformOperatingSystem() {}
		virtual ~PlatformOperatingSystem() = default;

		explicit PlatformOperatingSystem(std::string name, std::unique_ptr<GameState>& state):
			identifier_name{ name }, game_state{ std::move(state) } {}

		virtual bool hasInitiated() {};
		virtual bool hasShutDown() {};

		std::string identifier_name;
		std::unique_ptr<GameState> game_state;
	};

	class GameState
	{
	public:
		enum class RunState
		{
			Idle,
			Running,
			Pause
		};

		GameState() = default;
		virtual ~GameState() {}

		explicit GameState(const GameState& state):
			run_state { state.run_state } {}

		virtual void Start() {};
		virtual void Stop()  {};
		virtual void Pause() {};

	private:

		RunState run_state;
	};
}

#endif _PLATFORM_DEFINES_H