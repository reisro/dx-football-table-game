#include "GameEntry.h"

void gamentry::SetWindowAppTitle(const char* _title)
{

}

uint32_t gamentry::GetWindowWidth()
{
	return 0;
}

void gamentry::SetWindowAppWidth(uint32_t _width)
{

}

uint32_t gamentry::GetWindowHeight()
{
	return 0;
}

void gamentry::SetWindowAppHeight(uint32_t _height)
{

}

int gamentry::runGame(DXGame* _gameapp)
{
	_gameapp->init(gamentry::GetWindowWidth(), gamentry::GetWindowHeight());

	// Game loop
	while (_gameapp->update(0.0f))
	{
		DXLog("Game Loop.....");
	}

	_gameapp->shutdown();

	return 0;
}