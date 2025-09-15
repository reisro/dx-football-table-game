#include "DXApplication.h"

using namespace YE;

YEngineConfig::DXConfig YEngineConfig::DXConfig::instance;
DXApplication* DXApplication::instance = 0;

DXApplication::DXApplication()
{
}

DXApplication::~DXApplication()
{
	DXLog("\nDestroyed Application....");
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
void DXApplication::Setup(const YEngineConfig::DXConfig& config)
{
	YEngineConfig::DXConfig::instance = config;
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
bool DXApplication::Init()
{
	// Create singletons for this application
	instance = new DXApplication();

	// Create singletons for subsystems
	YEWindow::CreateInstance();
	DXRenderer::CreateInstance();
	DXTimer::CreateInstance();

	return true;
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
bool YE::DXApplication::InitWindow()
{
	return false;
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
void DXApplication::InitRenderer()
{
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
void YE::DXApplication::Run(DXGame* gameApp)
{
	instance->_gameApp = gameApp;
	instance->_gameApp->update(DXTimer::GetInstance()->GetDeltaTime());
}

DX_API DXApplication* createDXApplication()
{
	return new DXApplication();
}