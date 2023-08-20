#include "DXApplication.h"

DXEngineConfig::DXConfig DXEngineConfig::DXConfig::instance;

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
	DXLog("\n Application running...");
}

DX_API DXApplication* createDXApplication()
{
	return new DXApplication();
}