#pragma once

#ifndef _GAME_ENTRY_H_
#define _GAME_ENTRY_H_

#include <stdint.h>
#include "DXGame.h"

extern "C" int main();

#ifndef WINDOW_MAIN_IMPLEMENTED
#define WINDOW_MAIN_IMPLEMENTED 0
#endif // WINDOW_MAIN_IMPLEMENTED

#define WINDOW_MAIN_ENTRY(_gameApp)         \
	int main()                              \
	{                                       \
		_gameApp app;                       \
		return gamentry::runGame(&app);     \
	}

namespace gamentry
{
	void SetWindowAppTitle(const char* _title);
	
	uint32_t GetWindowWidth();
	
	void SetWindowAppWidth(uint32_t _width);
	
	uint32_t GetWindowHeight();
	
	void SetWindowAppHeight(uint32_t _height);
	
	int DX_API runGame(DXGame* _gameApp);

	extern "C" void* GetWindowsHandle();
}

#endif // _GAME_ENTRY_H_
