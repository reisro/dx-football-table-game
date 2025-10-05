#include "YERenderingDirectX11.h"

YERenderingDirectX11::YERenderingDirectX11()
{
	initialized = true;

	DXLog("\nCreated Renderer instance....");
}

YERenderingDirectX11::YERenderingDirectX11(const YERenderingDirectX11& rhs)
{
}

void YERenderingDirectX11::Setup()
{
}

bool YERenderingDirectX11::Init()
{
	// Create the window for rendering
	YEWindow::CreateInstance();

	outputWindow = dynamic_cast<YEWinAppWindow*>(YEWindow::GetInstance()); 
	outputWindow->Create();

	// clear out the struct for use
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// fill the swap chain description struct
	swapChainDesc.BufferCount = 1;                                    // one back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	swapChainDesc.BufferDesc.Width = 1368;
	swapChainDesc.BufferDesc.Height = 720;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	swapChainDesc.OutputWindow = outputWindow->GetWindowsHandle();
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.SampleDesc.Count = 1;         
	swapChainDesc.SampleDesc.Quality = 0;								// how many multisamples
	swapChainDesc.Windowed = TRUE;

	UINT createDeviceFlags = 0;

	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

	#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	// Create the device, context and swap chain
	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		featureLevelArray,
		2,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&d3dDevice,
		&featureLevel,
		&d3dDeviceContext);

	if (FAILED(hr))
	{
		DXLog("D3D11CreateDeviceAndSwapChain Failed.");

		return false;
	}

	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.

	HRESULT hrMultiSample = d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);

	// Create the render target view to the swap chain back buffer
	CreateRenderTargetView();

	if FAILED(hr)
	{
		MessageBox(0, L"Create Device Failed.", 0, 0);
		return false;
	}

	// Fill out Depth Stencil structure
	depthStencilDesc.Width = 1368;
	depthStencilDesc.Height = 720;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	if (enable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
	}

	HRESULT hrDpethStencil = d3dDevice->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer);
	HRESULT hrDpethStencilView = d3dDevice->CreateDepthStencilView(depthStencilBuffer, 0, &depthStencilView);

	d3dDeviceContext->OMSetRenderTargets(1, &mainRenderTargetView, depthStencilView);

	// Set the viewport
	SetViewport();

	if (d3dDevice)
		YERenderer::initialized = !YERenderer::initialized;

	outputWindow->Show();

	// Make process DPI aware and obtain main monitor scale
	ImGui_ImplWin32_EnableDpiAwareness();
	float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
	style.FontScaleDpi = main_scale;

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(outputWindow->GetWindowsHandle());
	ImGui_ImplDX11_Init(d3dDevice, d3dDeviceContext);

	return YERenderer::initialized;
}

void YERenderingDirectX11::PostInit()
{
}

void YERenderingDirectX11::Clean()
{
	::DestroyWindow(outputWindow->GetWindowsHandle());

	swapChain->Release();
	backBuffer->Release();
	d3dDevice->Release();
	d3dDeviceContext->Release();
}

void YERenderingDirectX11::CreateRenderTargetView()
{
	// get the address of the back buffer
	swapChain->GetBuffer(0, IID_PPV_ARGS(&tBackBuffer));

	// use the back buffer address to create the render target
	d3dDevice->CreateRenderTargetView(tBackBuffer, nullptr, &mainRenderTargetView);
	tBackBuffer->Release();

}

void YERenderingDirectX11::SetViewport()
{
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 1368;
	viewport.Height = 720;

	d3dDeviceContext->RSSetViewports(1, &viewport);
}

void YERenderingDirectX11::Render()
{
	BeginFrame();
}

void YERenderingDirectX11::BeginFrame()
{
	bool show_demo_window = true;

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");
		ImGui::Text("Hello World.");
		ImGui::End();
	}

	ImGui::Render();
	DXLog("imgui rendering...");

	// Rendering
	const float clear_color_with_alpha[4] = { 0.33f, 0.41f, 0.18f, 1.0f };
	
	// set the render target as the back buffer
	d3dDeviceContext->ClearRenderTargetView(mainRenderTargetView, clear_color_with_alpha);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	swapChain->Present(1, 0);
}

void YERenderingDirectX11::EndFrame()
{
}

void YERenderingDirectX11::Cleanup()
{
	// Cleanup imGui
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (swapChain) { swapChain->Release(); swapChain = nullptr; }

	if (d3dDeviceContext) { d3dDeviceContext->Release(); d3dDeviceContext = nullptr; }
	
	if (d3dDevice) { d3dDevice->Release(); d3dDevice = nullptr; }
}

YERenderingDirectX11::~YERenderingDirectX11()
{
	Clean();
}
