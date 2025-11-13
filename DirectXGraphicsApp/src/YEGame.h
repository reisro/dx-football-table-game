#pragma once
#pragma warning(disable : 4838) 

#ifndef _DX_GAME_H_
#define _DX_GAME_H_

#include "DXAPI.h"
#include "YEWindow.h"
#include "YEGameObject.h"
#include "YEGameContext.h"

class DX_API YEGame
{
	public:

	YEGame(const char* _game_name);

	virtual ~YEGame();

	virtual void init() = 0;

	virtual void shutdown() = 0;

	virtual bool update(dxDouble _deltaTime) = 0;

	YEGameContext GetGameContext() { return _gameContext; }

	void SetGameContext(const YEGameContext& _context) { _gameContext = _context; }

	private:
	const char*			  game_name;
	YEGameContext		 _gameContext;

};
	
#endif _DX_GAME_H_