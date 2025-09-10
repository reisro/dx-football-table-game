#include "DXApplication.h"

DXEngineConfig::DXConfig DXEngineConfig::DXConfig::instance;

using namespace YE;

DXApplication::DXApplication()
{
}

DXApplication::~DXApplication()
{
	DXLog("\nDestroyed Application....");
}

void DXApplication::Setup(const DXEngineConfig::DXConfig& config)
{
	DXEngineConfig::DXConfig::instance = config;
}

bool DXApplication::Init(DXWindow* window)
{
	DXRenderer::CreateInstance();

	window->Create();

	return true;
}

bool YE::DXApplication::InitWindow()
{
	return false;
}

void DXApplication::InitRenderer()
{
}

void DXApplication::Run()
{
}

DX_API DXApplication* createDXApplication()
{
	return new DXApplication();
}