#include "YERenderer.h"
#include "YERenderingDirectX11.h"

YERenderer* YERenderer::Singleton = 0;
bool YERenderer::initialized;

YERenderer::YERenderer():
    _meshLoader{ new YEMeshLoader }
{
}

YERenderer::YERenderer(const YERenderer& rhs)
{
}

YERenderer::~YERenderer()
{
	DXLog("\nDestroyed Renderer....");
}

void YERenderer::CreateInstance()
{
    if (YEngineConfig::YEConfig::instance.graphicsAPI == YEngineConfig::GraphicsAPI::DirectX11)
        Singleton = new YERenderingDirectX11();
}

void YERenderer::Setup()
{
}

bool YERenderer::Init()
{
    return Singleton->initialized;
}

void YERenderer::PostInit()
{
}

void YERenderer::Clean()
{
}

void YERenderer::Render()
{
    BeginFrame();
}

void YERenderer::BeginFrame()
{
    EndFrame();
}

void YERenderer::EndFrame()
{
}

void YERenderer::Cleanup()
{
}

void YERenderer::CreateBasicGeometry()
{
}

void YERenderer::CreateDefaultCube()
{
}

void YERenderer::LoadMesh()
{
}

void YERenderer::InitPipeline()
{
}

void YERenderer::BuildFX()
{
}

void YERenderer::CreateVertexLayout()
{
}

void YERenderer::CreatePixelLayout()
{
}

IUnknown* YERenderer::GetDevice()
{
    return _device;
}

IUnknown* YERenderer::GetDeviceContext()
{
    return _deviceContext;
}

YERenderer* YERenderer::GetInstance()
{
    return Singleton;
}
