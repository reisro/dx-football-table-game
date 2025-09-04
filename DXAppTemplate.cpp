
#include "DXApplication.h"
#include <cstdlib>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC

// type alias for unique ptr
using DXWindow_ptr = std::unique_ptr<DXWindow>;

int main()
{
	// Enable debug heap
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DXLog("----------------------------------------------");
	DXLog("\tYakira Engine v0.2");
	DXLog("----------------------------------------------");

	DXEngineConfig::DXConfig appConfig;
	appConfig.graphicsAPI = { DXEngineConfig::GraphicsAPI::DirectX11 };

	// Init the application setup configuration
	RFE::DXApplication::Setup(appConfig);

	// Create a window game application
	DXWindow* appWindow = new DXWindow();

	// Run the app
	if (RFE::DXApplication::Init(appWindow))
		RFE::DXApplication::Run();

	DXLog("\nFinished Application...");

	_CrtDumpMemoryLeaks();

	return 0;
}