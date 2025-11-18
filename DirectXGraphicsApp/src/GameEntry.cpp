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

int gamentry::runGame(YEGame* _gameapp)
{
	YELog("----------------------------------------------");
	YELog("\tYakira Engine v0.2");
	YELog("----------------------------------------------");

	YEngineConfig::YEConfig gameConfig;

	gameConfig.graphicsAPI = { YEngineConfig::GraphicsAPI::DirectX11 };
	gameConfig.physicsAPI = { YEngineConfig::PhysicsAPI::PhysX };
	gameConfig.platform = { YEngineConfig::Platform::Windows };
	gameConfig.inputAPI = { YEngineConfig::InputAPI::XInput };
	gameConfig.resolution.width = 1368;
	gameConfig.resolution.height = 720;

	YE::YEApplication::Setup(gameConfig);

	// Initialize the game engine components
	if (!YE::YEApplication::InitEngine())
	{
		YELog("Failed to initialize game engine...");
		return -1;
	}

	// If engine init is successful
	if (YE::YEApplication::Init())
	{
		YELog("Initialized Game App...");

		// Run the game application
		YE::YEApplication::GetInstance()->Run(_gameapp);
	}

	return 0;
}