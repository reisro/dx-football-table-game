#pragma once

#ifndef _GAME_ENTRY_H_
#define _GAME_ENTRY_H_

#include <stdint.h>
#include "YEApplication.h"

extern "C" int main();

#ifndef WINDOW_MAIN_IMPLEMENTED
#define WINDOW_MAIN_IMPLEMENTED 0
#endif // WINDOW_MAIN_IMPLEMENTED

#define WINDOW_MAIN_ENTRY(_gameApp)         \
	int main()								\
	{										\
		_gameApp app;						\
		return gamentry::runGame(&app);     \
	}

namespace gamentry
{
	/// <summary>
	/// Game initialization structure
	/// </summary>
	struct GameInit
	{
		const char* _title;
		uint32_t	_width;
		uint32_t	_height;
		DXGame*     _game;

	};
	const GameInit DefaultGameInit = { "Yakira Engine v0.2", 1366, 768 };
	
	/// <summary>
	void SetWindowAppTitle(const char* _title);
	
	/// <summary>
	uint32_t GetWindowWidth();
	
	/// <summary>
	void SetWindowAppWidth(uint32_t _width);
	
	/// <summary>
	uint32_t GetWindowHeight();
	
	/// <summary>
	void SetWindowAppHeight(uint32_t _height);
	
	/// <summary>
	int DX_API runGame(DXGame* _gameapp);

	/// <summary>
	extern void* GetWindowsHandle();
}

#endif // _GAME_ENTRY_H_
