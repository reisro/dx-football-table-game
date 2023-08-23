#include "DXRenderingDirectX11.h"

DXRenderingDirectX11::DXRenderingDirectX11()
{
	Setup();
}

DXRenderingDirectX11::DXRenderingDirectX11(const DXRenderingDirectX11& rhs)
{
}

void DXRenderingDirectX11::Setup()
{
	// clear out the struct for use
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	swapChainDesc.BufferCount = 1;                                    // one back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	swapChainDesc.OutputWindow = renderWindow;
	swapChainDesc.SampleDesc.Count = 4;                               // how many multisamples
	swapChainDesc.Windowed = TRUE;                                    // windowed/full-screen mode

	Init();
}

bool DXRenderingDirectX11::Init()
{
	// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&d3dDevice,
		NULL,
		&d3dDeviceContext);

	return d3dDevice? !DXRenderer::initialized: DXRenderer::initialized;
}

void DXRenderingDirectX11::PostInit()
{
}

void DXRenderingDirectX11::Clean()
{
	swapChain->Release();
	d3dDevice->Release();
	d3dDeviceContext->Release();
}

DXRenderingDirectX11::~DXRenderingDirectX11()
{
}
