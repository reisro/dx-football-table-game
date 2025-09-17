#include "GameEntry.h"
#include "YEApplication.h"

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

	YEngineConfig::YEConfig gameConfig;

	gameConfig.graphicsAPI = { YEngineConfig::GraphicsAPI::DirectX11 };
	gameConfig.platform = { YEngineConfig::Platform::Windows };
	gameConfig.inputAPI = { YEngineConfig::InputAPI::XInput };
	gameConfig.resolution.width = 1368;
	gameConfig.resolution.height = 720;

	YE::YEApplication::Setup(gameConfig);

	// Initialize the game engine
	if (!YE::YEApplication::InitEngine())
	{
		DXLog("Failed to initialize game engine...");
		return -1;
	}

	// If engine init is successful, run the application loop
	if (YE::YEApplication::Init())
	{
		DXLog("Initialized Game App...");

		YE::YEApplication::GetInstance()->Start(_gameapp);
	}

	return 0;
}