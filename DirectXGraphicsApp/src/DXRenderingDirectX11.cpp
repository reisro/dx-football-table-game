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

	CreateRenderTargetView();

	if FAILED(hr)
	{
		MessageBox(0, L"Create Device Failed.", 0, 0);
		return false;
	}

	SetViewport();

	if (d3dDevice)
		DXRenderer::initialized = !DXRenderer::initialized;

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

	return DXRenderer::initialized;
}

void DXRenderingDirectX11::PostInit()
{
}

void DXRenderingDirectX11::Clean()
{
	::DestroyWindow(outputWindow->GetWindowsHandle());

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
	d3dDevice->CreateRenderTargetView(tBackBuffer, nullptr, &mainRenderTargetView);
	tBackBuffer->Release();

}

void DXRenderingDirectX11::SetViewport()
{
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 1368;
	viewport.Height = 720;

	d3dDeviceContext->RSSetViewports(1, &viewport);
}

void DXRenderingDirectX11::Render()
{
	BeginFrame();
}

void DXRenderingDirectX11::BeginFrame()
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
	d3dDeviceContext->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
	d3dDeviceContext->ClearRenderTargetView(mainRenderTargetView, clear_color_with_alpha);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	swapChain->Present(1, 0);
}

void DXRenderingDirectX11::EndFrame()
{
}

void DXRenderingDirectX11::Cleanup()
{
	// Cleanup imGui
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (swapChain) { swapChain->Release(); swapChain = nullptr; }

	if (d3dDeviceContext) { d3dDeviceContext->Release(); d3dDeviceContext = nullptr; }
	
	if (d3dDevice) { d3dDevice->Release(); d3dDevice = nullptr; }
}

DXRenderingDirectX11::~DXRenderingDirectX11()
{
	Clean();
}
