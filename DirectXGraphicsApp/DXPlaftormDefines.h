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

	template <typename T, typename U, typename V>
	class GameState;

	class PlatformOperatingSystem
	{
		PlatformOperatingSystem() {}
		virtual ~PlatformOperatingSystem() = default;

		template <typename T, typename U, typename V>
		explicit PlatformOperatingSystem(std::string name, std::unique_ptr<GameState<T,U,V>>& state):
			identifier_name{ name }, game_state{ std::move(state) } {}

		virtual bool hasInitiated() {};
		virtual bool hasShutDown() {};

		std::string identifier_name;
		std::unique_ptr<GameState<int,std::string,float>> game_state;
	};

	template <typename T, typename U, typename V>
	class GameState
	{
	public:

		enum class RunState
		{
			Idle,
			Running,
			Pause
		};

		enum class TriggerEvent
		{
			UI,
			Rendering,
			Network,
			Physics,
			AI,
			Sound,
			Cinematic
		};

		GameState() = default;
		virtual ~GameState() = default;

		explicit GameState(const GameState& state):
			run_state { state.run_state } {}

		template <typename T, typename U, typename V>
		explicit GameState(T t, U u, V v) noexcept :
			run_state{ default }, trigger_event{ default } {}
		
		template <typename T, typename U, typename V>
		explicit GameState(const GameState<T,U,V>& rhs) noexcept :
			run_state{ default }, trigger_event{ default } {}

		virtual void Start() {};
		virtual void Stop()  {};
		virtual void Pause() {};

	private:

		RunState run_state;
		TriggerEvent trigger_event;
	};
}

#endif _PLATFORM_DEFINES_H