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
	DXLog("----------------------------------------------");
	DXLog("\tYakira Engine v0.2");
	DXLog("----------------------------------------------");

	YEngineConfig::DXConfig gameConfig;
	gameConfig.graphicsAPI = { YEngineConfig::GraphicsAPI::DirectX11 };

	YE::DXApplication::Setup(gameConfig);

	GameInit gameInit;
	gameInit._width = 1368;
	gameInit._height = 720;
	gameInit._title = "Yakira Engine v0.2";

	// If game init is successful, run the game loop
	if (YE::DXApplication::Init())
	{
		DXLog("Initialized Game App...");

		YE::DXApplication::Run(_gameapp);
	}
	
	_gameapp->shutdown();

	return 0;
}