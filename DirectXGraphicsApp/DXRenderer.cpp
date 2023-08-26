#include "DXRenderer.h"
#include "DXRenderingDirectX11.h"

DXRenderer* DXRenderer::Singleton = 0;
bool DXRenderer::initialized;

DXRenderer::DXRenderer()
{
}

DXRenderer::DXRenderer(const DXRenderer& rhs)
{
}

DXRenderer::~DXRenderer()
{
}

void DXRenderer::CreateInstance()
{
    if (DXEngineConfig::DXConfig::instance.graphicsAPI == DXEngineConfig::GraphicsAPI::DirectX11)
        Singleton = new DXRenderingDirectX11();
}

void DXRenderer::Setup()
{
}

bool DXRenderer::Init()
{
    return Singleton->initialized;
}

void DXRenderer::PostInit()
{
}

void DXRenderer::Clean()
{
}

void DXRenderer::Render()
{
    BeginFrame();
}

void DXRenderer::BeginFrame()
{
    EndFrame();
}

void DXRenderer::EndFrame()
{
}

DXRenderer* DXRenderer::GetInstance()
{
    return Singleton;
}
