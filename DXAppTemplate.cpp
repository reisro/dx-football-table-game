
#include "DXApplication.h"

// type alias for unique ptr
using DXWindow_ptr = std::unique_ptr<DXWindow>;

int main()
{
	DXLog("----------------------------------------------");
	DXLog("\tYakira Engine v0.2");
	DXLog("----------------------------------------------");

	DXEngineConfig::DXConfig appConfig;
	appConfig.graphicsAPI = { DXEngineConfig::GraphicsAPI::DirectX11 };

	// Init the application setup configuration
	RFE::DXApplication::Setup(appConfig);

	// Create a window game application
	DXWindow_ptr appWindow = { std::make_unique<DXWindow>() };

	// Run the app
	if (RFE::DXApplication::Init(std::move(appWindow)))
		RFE::DXApplication::Run();

	DXLog("\nFinished Application...");

	return 0;
}