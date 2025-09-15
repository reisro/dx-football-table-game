#include "YEApplication.h"

using namespace YE;

YEngineConfig::DXConfig YEngineConfig::DXConfig::instance;
YEApplication* YEApplication::instance = 0;

YEApplication::YEApplication()
{
}

YEApplication::~YEApplication()
{
	DXLog("\nDestroyed Application....");
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
void YEApplication::Setup(const YEngineConfig::DXConfig& config)
{
	YEngineConfig::DXConfig::instance = config;
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
bool YEApplication::Init()
{

	return true;
}

bool YE::YEApplication::InitEngine()
{
	// Create singletons for this application
	instance = new YEApplication();

	// Create singletons for subsystems
	YEWindow::CreateInstance();
	DXRenderer::CreateInstance();
	DXTimer::CreateInstance();

	return true;
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
bool YE::YEApplication::InitWindow()
{
	YEWindow::GetInstance()->Create();

	return false;
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
void YEApplication::InitRenderer()
{
	DXRenderer::GetInstance()->Init();
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
void YE::YEApplication::Run(DXGame* gameApp)
{
	if (instance->_isInitialized)
	{
		instance->_window->Show(1366, 768);
		instance->_gameApp = gameApp;
		instance->_gameApp->update(DXTimer::GetInstance()->GetDeltaTime());
	}
	else
		DXLog("Application not initialized...");
}

DX_API YEApplication* createDXApplication()
{
	return new YEApplication();
}