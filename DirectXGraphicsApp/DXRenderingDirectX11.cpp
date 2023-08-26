#include "DXRenderingDirectX11.h"

DXRenderingDirectX11::DXRenderingDirectX11()
{
	Init();
}

DXRenderingDirectX11::DXRenderingDirectX11(const DXRenderingDirectX11& rhs)
{
}

void DXRenderingDirectX11::Setup()
{
}

bool DXRenderingDirectX11::Init()
{
	UINT createDeviceFlags = 0;

	#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	HRESULT hr = D3D11CreateDevice(0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		createDeviceFlags,
		0, 0,
		D3D11_SDK_VERSION,
		&d3dDevice,
		&featureLevel,
		&d3dDeviceContext);

	if FAILED(hr)
	{
		MessageBox(0, L"Create Device Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	//// create a device, device context and swap chain using the information in the scd struct
	//D3D11CreateDeviceAndSwapChain(NULL,
	//	D3D_DRIVER_TYPE_HARDWARE,
	//	NULL,
	//	NULL,
	//	NULL,
	//	NULL,
	//	D3D11_SDK_VERSION,
	//	&swapChainDesc,
	//	&swapChain,
	//	&d3dDevice,
	//	NULL,
	//	&d3dDeviceContext);

	if (d3dDevice)
		DXRenderer::initialized = !DXRenderer::initialized;

	return DXRenderer::initialized;
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

void DXRenderingDirectX11::FillSwapChainDescription()
{
	UINT m4xMsaaQuality;

	HRESULT hr = d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);

	// clear out the struct for use
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	swapChainDesc.BufferCount = 1;                                    // one back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	swapChainDesc.OutputWindow = renderWindow;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;
	swapChainDesc.SampleDesc.Count = 4;                               // how many multisamples
	swapChainDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
	swapChainDesc.Windowed = TRUE;
}

DXRenderingDirectX11::~DXRenderingDirectX11()
{
}