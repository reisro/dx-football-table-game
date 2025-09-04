#pragma once

#ifndef _DX_GAME_H_
#define _DX_GAME_H_

#include <stdint.h>
#include "DXAPI.h"

extern "C" int main();

#define WINDOW_ENTRYPOINT 0 UINT32_C(0x0)

#ifndef WINDOW_MAIN_IMPLEMENTED
#define WINDOW_MAIN_IMPLEMENTED 0
#endif // WINDOW_MAIN_IMPLEMENTED

#if WINDOW_MAIN_IMPLEMENTED
#define WINDOW_MAIN_ENTRY(_gameapp)
	int main()
	{
		_gameapp app;
		return yakiraentry::runGame(app);
	}

#endif // WINDOW_MAIN_IMPLEMENTED

namespace yakiraentry
{
	class DX_API DXGame
	{
	public:
		DXGame(const char* _game_name);

		virtual ~DXGame();

		virtual void init(uint32_t _width, uint32_t _height) = 0;

		virtual void shutdown() = 0;

		virtual bool update(float _deltaTime) = 0;

	private:
		const char* game_name;
	};
		
	void SetWindowTitle(const char* _title);

	uint32_t GetWindowWidth();

	void SetWindowWidth(uint32_t _width);

	uint32_t GetWindowHeight();

	void SetWindowHeight(uint32_t _height);

	int runGame(DXGame* _game, uint32_t _width, uint32_t _height);
}

#endif _DX_GAME_H_