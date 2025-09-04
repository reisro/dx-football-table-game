#include "DXGame.h"

yakiraentry::DXGame::DXGame(const char* _game_name):
	game_name(_game_name)
{
}

yakiraentry::DXGame::~DXGame()
{
	game_name = nullptr;
}

int yakiraentry::runGame(DXGame* _game, uint32_t _width, uint32_t _height)
{
	_game->init(_width, _height);
	
	// Game loop
	while (_game->update(0.0f))
	{

	}

	_game->shutdown();

    return 0;
}

void yakiraentry::SetWindowTitle(const char* _title)
{

}

uint32_t yakiraentry::GetWindowWidth()
{
	return 0;
}

void yakiraentry::SetWindowWidth(uint32_t _width)
{

}

uint32_t yakiraentry::GetWindowHeight()
{
	return 0;
}

void yakiraentry::SetWindowHeight(uint32_t _height)
{

}