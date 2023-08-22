#include "DXApplication.h"

DXEngineConfig::DXConfig DXEngineConfig::DXConfig::instance;

using namespace RFE;

DXApplication::DXApplication()
{
}

DXApplication::~DXApplication()
{
}

void DXApplication::Setup(const DXEngineConfig::DXConfig& config)
{
	DXEngineConfig::DXConfig::instance = config;
}

bool DXApplication::Init()
{
	return false;
}

void DXApplication::Run(std::unique_ptr<DXWindow> window)
{
	DXLog("\nApplication running...");

	window->Create();
}

DX_API DXApplication* createDXApplication()
{
	return new DXApplication();
}