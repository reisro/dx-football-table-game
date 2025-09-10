#include "DXGame.h"

DXGame::DXGame(const char* _game_name) : game_name(_game_name)
{
}

DXGame::~DXGame()
{
	game_name = nullptr;
}