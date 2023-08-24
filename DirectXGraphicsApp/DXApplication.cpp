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
	return InitRenderer();
}

bool RFE::DXApplication::InitWindow()
{
	return false;
}

bool DXApplication::InitRenderer()
{
	DXRenderer::CreateInstance();

	return DXRenderer::initialized;
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