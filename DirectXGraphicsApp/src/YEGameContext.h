#pragma once
#include "YESceneObject.h"

#ifndef _YE_GAMECONTEXT_H_
#define _YE_GAMECONTEXT_H_

enum class GameStatus
{
	MainMenu,
	GameInstructions,
	Match,
	GameOver
};


struct GameState
{
	GameState()
	{
	}

	void SetGameStatusVariables()
	{
		switch (_status)
		{
			case GameStatus::MainMenu:
			{
				// Set variables for Main Menu
				_statusString = "Press SPACE to begin";
				_statusString2 = "";

				break;
			}
			case GameStatus::GameInstructions:
			{
				// Set variables for Game Instructions
				_statusString = "AS key to move player handle, W to shoot";
				_statusString2 = "LEFT/RIGHT key to move keeper handle, UP to shoot";

				break;
			}
			case GameStatus::Match:
			{
				// Set variables for Match
				break;
			}
			case GameStatus::GameOver:
			{
				// Set variables for Game Over
				break;
			}
		}
	}

	void SetGameStatus(GameStatus status)
	{
		_status = status;

		SetGameStatusVariables();
	}

	GameStatus _status;
	const char* _statusString;
	const char* _statusString2;

};

struct YEGameContext
{
	UINT meshCount=0;
	YESceneObject* sceneObject;
	GameState gameState;
};

#endif