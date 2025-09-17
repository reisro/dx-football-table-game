#include "YEGame.h"

YEGame::YEGame(const char* _game_name) : game_name(_game_name)
{
}

YEGame::~YEGame()
{
	game_name = nullptr;
}