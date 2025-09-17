#include "DXRenderingDirectX11.h"

DXRenderingDirectX11::DXRenderingDirectX11()
{
	initialized = true;

	DXLog("\nCreated Renderer instance....");
}

DXRenderingDirectX11::DXRenderingDirectX11(const DXRenderingDirectX11& rhs)
{
}

void DXRenderingDirectX11::Setup()
{
}

bool DXRenderingDirectX11::Init()
{
	// Create the window for rendering
	YEWindow::CreateInstance();

	outputWindow = dynamic_cast<YEWinAppWindow*>(YEWindow::GetInstance()); 
	outputWindow->Create();

	// clear out the struct for use
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	swapChainDesc.BufferCount = 1;                                    // one back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	swapChainDesc.OutputWindow = outputWindow->GetWindowsHandle();
	swapChainDesc.Flags = 0;
	swapChainDesc.SampleDesc.Count = 4;                               // how many multisamples
	swapChainDesc.Windowed = TRUE;

	UINT createDeviceFlags = 0;

	#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
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

	if FAILED(hr)
	{
		MessageBox(0, L"Create Device Failed.", 0, 0);
		return false;
	}

	CreateRenderTargetView();

	SetViewport();

	if (d3dDevice)
		DXRenderer::initialized = !DXRenderer::initialized;

	outputWindow->Show();

	return DXRenderer::initialized;
}

void DXRenderingDirectX11::PostInit()
{
}

void DXRenderingDirectX11::Clean()
{
	swapChain->Release();
	backBuffer->Release();
	d3dDevice->Release();
	d3dDeviceContext->Release();
}

void DXRenderingDirectX11::FillSwapChainDescription()
{
	// clear out the struct for use
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	swapChainDesc.BufferCount = 1;                                    // one back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	//swapChainDesc.OutputWindow = renderWindow;
	swapChainDesc.Flags = 0;
	swapChainDesc.SampleDesc.Count = 4;                               // how many multisamples
	swapChainDesc.Windowed = TRUE;
}

void DXRenderingDirectX11::CreateSwapChain()
{
}

void DXRenderingDirectX11::CreateRenderTargetView()
{
	// get the address of the back buffer
	swapChain->GetBuffer(0, IID_PPV_ARGS(&tBackBuffer));

	// use the back buffer address to create the render target
	d3dDevice->CreateRenderTargetView(tBackBuffer, NULL, &backBuffer);
	tBackBuffer->Release();

	// set the render target as the back buffer
	d3dDeviceContext->OMSetRenderTargets(1, &backBuffer, NULL);
}

void DXRenderingDirectX11::SetViewport()
{
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 1366;
	viewport.Height = 768;

	d3dDeviceContext->RSSetViewports(1, &viewport);
}

void DXRenderingDirectX11::Render()
{
	BeginFrame();
}

void DXRenderingDirectX11::BeginFrame()
{
	d3dDeviceContext->ClearRenderTargetView(backBuffer, RGBA{ 0.33f, 0.41f, 0.18f, 1.0f });

	swapChain->Present(1, 0);
}

void DXRenderingDirectX11::EndFrame()
{
}

DXRenderingDirectX11::~DXRenderingDirectX11()
{
	Clean();
}