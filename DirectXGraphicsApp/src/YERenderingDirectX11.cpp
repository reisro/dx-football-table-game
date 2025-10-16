#include "YERenderingDirectX11.h"
#include "d3dx11Effect.h"

YERenderingDirectX11::YERenderingDirectX11():
	depthStencilBuffer(0), m4xMsaaQuality(false)
{
	initialized = true;

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mWorld, I);
	XMStoreFloat4x4(&mView, I);
	XMStoreFloat4x4(&mProj, I);

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

	// Check for Direct3D Feature Level is supported
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
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	HRESULT hrDepthStencil = d3dDevice->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer);

	if (!FAILED(hrDepthStencil))
		HRESULT hrDepthStencilView = d3dDevice->CreateDepthStencilView(depthStencilBuffer, 0, &depthStencilView);

	d3dDeviceContext->OMSetRenderTargets(1, &mainRenderTargetView, depthStencilView);

	// Set the rasterizer states
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	d3dDevice->CreateRasterizerState(&rasterDesc, &rasterstate);
	d3dDeviceContext->RSSetState(rasterstate);

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

	PostInit();

	return YERenderer::initialized;
}

void YERenderingDirectX11::PostInit()
{
	if (createGeometryCmd)
		CreateDefaultCube();

	InitPipeline();

	//BuildFX();

	//CreateVertexLayout();

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	HRESULT hr = d3dDevice->CreateBuffer(&bd, nullptr, &pConstantBuffer);
	if (FAILED(hr))
		DXLog("Constant buffer couldn't be created");

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = d3dDevice->CreateSamplerState(&sampDesc, &texSamplerState);
	if (FAILED(hr))
		DXLog("Texture sampler state couldn't be created");
}

void YERenderingDirectX11::Clean()
{
	::DestroyWindow(outputWindow->GetWindowsHandle());

	swapChain->Release();
	backBuffer->Release();
	d3dDevice->Release();
	d3dDeviceContext->Release();
}

HRESULT YERenderingDirectX11::CompileShaderFromFile(LPCWSTR pFileName, const D3D_SHADER_MACRO* pDefines, LPCSTR pEntryPoint, LPCSTR pShaderModel, ID3DBlob** ppBytecodeBlob)
{
	UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;

#ifdef _DEBUG
	compileFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob = nullptr;

	HRESULT result = D3DCompileFromFile(pFileName, pDefines, D3D_COMPILE_STANDARD_FILE_INCLUDE, pEntryPoint, pShaderModel, compileFlags, 0, ppBytecodeBlob, &pErrorBlob);
	if (FAILED(result))
	{
		if (pErrorBlob != nullptr)
			OutputDebugStringA((LPCSTR)pErrorBlob->GetBufferPointer());
	}

	if (pErrorBlob != nullptr)
		pErrorBlob->Release();

	return result;
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
	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(4.2f, 3.53f, -3.53f, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, V);

	// Initialize the projection matrix
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*3.1415926535f, 1368 / (FLOAT)720, 0.01f, 100.0f);
	XMStoreFloat4x4(&mProj, P);

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
	d3dDeviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	d3dDeviceContext->IASetInputLayout(inputLayout);
	d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3dDeviceContext->IASetVertexBuffers(0, 1, &mCubeVB, &stride, &offset);
	d3dDeviceContext->IASetIndexBuffer(mCubeIB, DXGI_FORMAT_R32_UINT, 0);

	// Set constants
	XMMATRIX world = XMLoadFloat4x4(&mWorld);
	XMMATRIX view = XMLoadFloat4x4(&mView);
	XMMATRIX proj = XMLoadFloat4x4(&mProj);
	XMMATRIX worldViewProj = world * view * proj;

	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(world);
	cb.mView = XMMatrixTranspose(view);
	cb.mProjection = XMMatrixTranspose(proj);

	d3dDeviceContext->UpdateSubresource(pConstantBuffer, 0, nullptr, &cb, 0, 0);

	d3dDeviceContext->VSSetShader(pVS, 0, 0);
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	d3dDeviceContext->PSSetShader(pPS, 0, 0);
	d3dDeviceContext->PSSetSamplers(0, 1, &texSamplerState);
	_meshLoader->Draw(d3dDeviceContext);

	// if exists a default technique implemented
	if (defaultEffectTechnique)
	{
		fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

		D3DX11_TECHNIQUE_DESC techniqueDesc;
		defaultEffectTechnique->GetDesc(&techniqueDesc);
		for (UINT p = 0; p < techniqueDesc.Passes; ++p)
		{
			defaultEffectTechnique->GetPassByIndex(p)->Apply(0, d3dDeviceContext);

			// 36 indices for the box.
			//d3dDeviceContext->DrawIndexed(36, 0, 0);
			_meshLoader->Draw(d3dDeviceContext);
		}
	}

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

void YERenderingDirectX11::CreateDefaultCube()
{
	Vertex vertices[] =
	{
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(YEngineColors::WHITE.Value)	},
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(YEngineColors::WHITE.Value)   },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(YEngineColors::WHITE.Value)     },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(YEngineColors::WHITE.Value)   },
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(YEngineColors::WHITE.Value)    },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(YEngineColors::WHITE.Value)  },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(YEngineColors::WHITE.Value)    },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(YEngineColors::WHITE.Value) }
	};

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * 8;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	HRESULT result = d3dDevice->CreateBuffer(&vbd, &vinitData, &mCubeVB);

	// Create the index buffer

	UINT indices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * 36;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	HRESULT res = d3dDevice->CreateBuffer(&ibd, &iinitData, &mCubeIB);

	BuildFX();

	CreateVertexLayout();
}

void YERenderingDirectX11::LoadMesh()
{
	if (_meshLoader->Load(d3dDevice, d3dDeviceContext, "C:\\Game Assets\\football_player.fbx"))
		DXLog("Loaded 3D model successfully.");
	else
		DXLog("Could not load 3D model successfully.....");
}

void YERenderingDirectX11::InitPipeline()
{
	ID3DBlob* VS, * PS;
	if (FAILED(CompileShaderFromFile(L"C:\\DirectX\\graphicsapplication\\DirectXGraphicsApp\\shaders\\VertexShader.hlsl", 0, "main", "vs_5_0", &VS)))
		DXLog("Failed to compile shader from file");
	if (FAILED(CompileShaderFromFile(L"C:\\DirectX\\graphicsapplication\\DirectXGraphicsApp\\shaders\\PixelShader.hlsl", 0, "main", "ps_5_0", &PS)))
		DXLog("Failed to compile shader from file ");

	d3dDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), nullptr, &pVS);
	d3dDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), nullptr, &pPS);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	d3dDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &inputLayout);
	d3dDeviceContext->IASetInputLayout(inputLayout);
}

void YERenderingDirectX11::BuildFX()
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr = D3DX11CompileFromFile(L"C:\\DirectX\\graphicsapplication\\DirectXGraphicsApp\\src\\SimpleColor.fx", 0, 0, 0, "fx_5_0", shaderFlags,
		0, 0, &compiledShader, &compilationMsgs, 0);

	//// compilationMsgs can store errors or warnings.
	if (compilationMsgs != 0)
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		ReleaseCOM(compilationMsgs);
	}

	//// Even if there are no compilationMsgs, check to make sure there were no other errors.
	if (FAILED(hr))
	{
		DXLog("Shader Compilation errors.");
	}

	HRESULT hrEffect = (D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(),
		0, d3dDevice, &defaultColorFX));

	//// Done with compiled shader.
	ReleaseCOM(compiledShader);

	defaultEffectTechnique = defaultColorFX->GetTechniqueByName("SimpleColor");
	fxWorldViewProj = defaultColorFX->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void YERenderingDirectX11::CreateVertexLayout()
{
	// Create the vertex input layout.
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;

	defaultEffectTechnique->GetPassByIndex(0)->GetDesc(&passDesc);

	HRESULT hr = d3dDevice->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &inputLayout);
}

void YERenderingDirectX11::CreatePixelLayout()
{
}

IUnknown* YERenderingDirectX11::GetDevice()
{
	return d3dDevice;
}

IUnknown* YERenderingDirectX11::GetDeviceContext()
{
	return d3dDeviceContext;
}

YERenderingDirectX11::~YERenderingDirectX11()
{
	Clean();
}