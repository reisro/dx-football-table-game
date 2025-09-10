#pragma once

#ifndef _DX_GAME_H_
#define _DX_GAME_H_

#include "DXAPI.h"

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
	
#endif _DX_GAME_H_