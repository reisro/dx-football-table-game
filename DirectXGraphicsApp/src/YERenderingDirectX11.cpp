#include "YERenderingDirectX11.h"
#include "d3dx11Effect.h"
#include "MatrixFunctions.inl"

YERenderingDirectX11::YERenderingDirectX11() :
	depthStencilBuffer(0), m4xMsaaQuality(true)
{
	initialized = true;

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mWorld, I);
	XMStoreFloat4x4(&mView, I);
	XMStoreFloat4x4(&mProj, I);

	_cameraAngles.push_back(new YEVector3(0.28f, 13.86f, 18.27f));
	_cameraAngles.push_back(new YEVector3(7.119f, 7.619f, 15.750f));
	_cameraAngles.push_back(new YEVector3(10.72f, 13.860f, 15.750f));
	_cameraAngles.push_back(new YEVector3(-7.999f, 11.460f, 18.510f));
	_cameraAngles.push_back(new YEVector3(-8.2399f, 7.499f, 15.750f));
	_cameraAngles.push_back(new YEVector3(-0.1399f, 4.8599f, 15.090f));
	_cameraAngles.push_back(new YEVector3(-5.1399f, 4.8599f, 15.090f));

	YELog("\nCreated Renderer instance....");
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

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Check for Direct3D Feature Level is supported
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

	#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	HRESULT hr_createDevice = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2,
			D3D11_SDK_VERSION, &d3dDevice, &featureLevel, &d3dDeviceContext);

	if(FAILED(hr_createDevice))
	{
		YELog("D3D11CreateDevice Failed.");
		return false;
	}	

	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.

	HRESULT hrMultiSample = d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);

	HRESULT hr;

	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	IDXGIFactory1* dxgiFactory = nullptr;
	{
		IDXGIDevice* dxgiDevice = nullptr;
		hr = d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

		if (SUCCEEDED(hr))
		{
			IDXGIAdapter* adapter = nullptr;
			hr = dxgiDevice->GetAdapter(&adapter);
			if (SUCCEEDED(hr))
			{
				hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
				adapter->Release();
			}
			dxgiDevice->Release();
		}

		if (FAILED(hr))
			YELog("Failed to get IDXGIFactory1");
	}

	IDXGIFactory2* dxgiFactory2 = nullptr;
	hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));

	if (dxgiFactory2)
	{
		hr = d3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&d3dDevice2));

		if (SUCCEEDED(hr))
		{
			(void)d3dDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&d3dDeviceContext2));
		}

		//// clear out the struct for use
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		// fill the swap chain description struct
		swapChainDesc.BufferCount = 2;                                    // one back buffer
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
		swapChainDesc.Width = 1368;
		swapChainDesc.Height = 720;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
		swapChainDesc.Flags = 0;
		swapChainDesc.SampleDesc.Quality = m4xMsaaQuality - 1;								// how many multisamples
		swapChainDesc.SampleDesc.Count = 4;

		hr = dxgiFactory2->CreateSwapChainForHwnd(d3dDevice, outputWindow->GetWindowsHandle(), &swapChainDesc, nullptr, nullptr, &swapChain1);
		if (SUCCEEDED(hr))
		{
			hr = swapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&swapChain));
		}

		dxgiFactory2->Release();
	}
	else
	{
		// DirectX 11.0 systems
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = 1368;
		sd.BufferDesc.Height = 720;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = outputWindow->GetWindowsHandle();
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = m4xMsaaQuality - 1;
		sd.Windowed = TRUE;

		hr = dxgiFactory->CreateSwapChain(d3dDevice, &sd, &swapChain);
	}

	dxgiFactory->Release();

	if(FAILED(hr))
	{
		YELog("CreateSwapChain Failed.");
		return false;
	}

	// Create the render target view to the swap chain back buffer
	CreateRenderTargetView();

	//// Fill out Depth Stencil structure
	depthStencilDesc.Width = 1368;
	depthStencilDesc.Height = 720;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	depthStencilDesc.SampleDesc.Count = 4;
	depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;

	HRESULT hrDepthStencil = d3dDevice->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer);

	if (FAILED(hrDepthStencil))
	{
		YELog("CreateTexture2D for Depth Stencil Failed.");
		return false;
	}

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = depthStencilDesc.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = d3dDevice->CreateDepthStencilView(depthStencilBuffer, 0, &depthStencilView);

	if (FAILED(hr))
	{
		YELog("Depth Stencil View couldn't be created!");
	}

	d3dDeviceContext->OMSetRenderTargets(1, &mainRenderTargetView, depthStencilView);

	// Set the rasterizer states
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = TRUE;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.ScissorEnable = false;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	
	d3dDevice->CreateRasterizerState(&rasterDesc, &rasterstate);
	d3dDeviceContext->RSSetState(rasterstate);

	// Set the viewport
	SetViewport();

	if (d3dDevice)
		YERenderer::initialized = !YERenderer::initialized;

	outputWindow->Show();

	m_SpriteShader = std::make_unique<YESpriteShader>(this);
	m_SpriteShader->Load();

	m_Sprite = std::make_unique<YESprite>(this);
	m_Sprite->Create();

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
	//if (createGeometryCmd)
		//CreateDefaultCube();

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
		YELog("Constant buffer couldn't be created");

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = 1000.0f;

	hr = d3dDevice->CreateSamplerState(&sampDesc, &texSamplerState);
	if (FAILED(hr))
		YELog("Texture sampler state couldn't be created");

	/*D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampDesc.MipLODBias = 0;
	sampDesc.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = 1000.0f;

	hr = d3dDevice->CreateSamplerState(&sampDesc, m_SamplerState.GetAddressOf());
	if (FAILED(hr))
		YELog("Texture sampler state couldn't be created");*/
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
	swapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), (LPVOID*)&tBackBuffer);

	// use the back buffer address to create the render target
	d3dDevice->CreateRenderTargetView(tBackBuffer, nullptr, &mainRenderTargetView);
	tBackBuffer->Release();
}

void YERenderingDirectX11::SetViewport()
{
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.Width = 1368;
	viewport.Height = 720;

	d3dDeviceContext->RSSetViewports(1, &viewport);
}

void YERenderingDirectX11::UpdateSpriteConstantBuffer(float pitch_radians, float yaw_radians, float roll_radians)
{
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();

	m_PitchRadians += pitch_radians;
	m_YawRadians += yaw_radians;
	m_PitchRadians = std::clamp<float>(m_PitchRadians, -(DirectX::XM_PIDIV2 - 0.1f), DirectX::XM_PIDIV2 - 0.1f);

	// Convert Spherical to Cartesian coordinates.
	DirectX::XMMATRIX rotation_matrix = DirectX::XMMatrixRotationRollPitchYaw(m_PitchRadians, m_YawRadians, 0);
	DirectX::XMVECTOR position = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	position = XMVector3TransformCoord(position, rotation_matrix);

	SpriteBuffer world_buffer = {};
	world_buffer.world = DirectX::XMMatrixTranspose(world);
	world_buffer.view = DirectX::XMMatrixTranspose(_cameraView);
	world_buffer.projection = DirectX::XMMatrixTranspose(_cameraProjection);

	DirectX::XMStoreFloat4(&mPosition, position);

	world_buffer.cameraPosition = mPosition;

	m_SpriteShader->UpdateWorldConstantBuffer(world_buffer);
}

void YERenderingDirectX11::UpdateWorldConstantBuffer(const SpriteBuffer& worldBuffer)
{
	ID3D11DeviceContext* context = (ID3D11DeviceContext*)this->GetDeviceContext();
	context->UpdateSubresource(m_WorldConstantBuffer.Get(), 0, nullptr, &worldBuffer, 0, 0);
}

void YERenderingDirectX11::Render()
{
	BeginFrame();
}

void YERenderingDirectX11::BeginFrame()
{
	static float y = 13.86f;
	static float x = 0.28f;
	static float z = 18.27f;
	static int id = 0;

	if (GetAsyncKeyState('1') & 0x8000)
	{
		x = _cameraAngles[0]->_x;
		y = _cameraAngles[0]->_y;
		z = _cameraAngles[0]->_z;
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		x = _cameraAngles[1]->_x;
		y = _cameraAngles[1]->_y;
		z = _cameraAngles[1]->_z;
	}
	if (GetAsyncKeyState('3') & 0x8000)
	{
		x = _cameraAngles[2]->_x;
		y = _cameraAngles[2]->_y;
		z = _cameraAngles[2]->_z;
	}
	if (GetAsyncKeyState('4') & 0x8000)
	{
		x = _cameraAngles[3]->_x;
		y = _cameraAngles[3]->_y;
		z = _cameraAngles[3]->_z;
	}	if (GetAsyncKeyState('5') & 0x8000)
	{
		x = _cameraAngles[4]->_x;
		y = _cameraAngles[4]->_y;
		z = _cameraAngles[4]->_z;
	}	if (GetAsyncKeyState('6') & 0x8000)
	{
		x = _cameraAngles[5]->_x;
		y = _cameraAngles[5]->_y;
		z = _cameraAngles[5]->_z;
	}	if (GetAsyncKeyState('7') & 0x8000)
	{
		x = _cameraAngles[6]->_x;
		y = _cameraAngles[6]->_y;
		z = _cameraAngles[6]->_z;
	}
	
	/*x -= 0.05f;
	if (x <= 0.28f)
		x = 0.28f;
	y += 0.02f;
	if (y >= 13.86f)
		y = 13.86f;
	z += 0.09f;
	if (z >= 18.27f)
		z = 18.27f;*/

	//0.28 13.86 18.27 gameplay
	YELog("Camera Position X: %.2f Y: %.2f Z: %.2f" + std::to_string(x) + "," + std::to_string(y) + "," +
		std::to_string(z));

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	_cameraView = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, _cameraView);

	// Initialize the projection matrix
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*3.1415926535f, 1368 / (FLOAT)720, .2f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);

	bool show_demo_window = true;

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//ImGui::SetNextWindowBgAlpha(0.0);
	//ImGui::SetNextWindowSize(ImVec2(540, 309));
	static bool show_another_window = false;

	if (_sceneObject->_sceneUI.showUI)
		OnRenderUI(&_sceneObject->_sceneUI.showUI, _sceneObject->_sceneUI.spriteID, _sceneObject->_sceneUI.textMsg, _sceneObject->_sceneUI.textMsg2);

	ImGui::Render();

	// Rendering
	const float clear_color_with_alpha[4] = { 0.161f, 0.161f, 0.157f, 1.0f };
	
	// set the render target as the back buffer
	d3dDeviceContext->ClearRenderTargetView(mainRenderTargetView, clear_color_with_alpha);
	d3dDeviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 1.0);

	d3dDeviceContext->IASetInputLayout(inputLayout);
	d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// Check if there are meshes loaded
	if (_sceneObject->_meshesToRender.size() == 0)
		YELog("No meshes loaded to render.");

	if (_sceneObject->_spritesToRender.size() == 0)
		YELog("No sprites to render.");

	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX proj;
	XMMATRIX worldViewProj;

	for (size_t i = 0; i < _sceneObject->_meshesToRender.size(); i++)
	{
		XMFLOAT4X4 _world = _sceneObject->LoadWorldPosition(_sceneObject->_meshesToRender[i]._idMWorld);

		world = XMLoadFloat4x4(&_world);
		view = XMLoadFloat4x4(&mView);
		proj = XMLoadFloat4x4(&mProj);
		worldViewProj = world * view * proj;

		ConstantBuffer cb;
		cb.mWorld = XMMatrixTranspose(world);
		cb.mView = XMMatrixTranspose(view);
		cb.mProjection = XMMatrixTranspose(proj);

		d3dDeviceContext->UpdateSubresource(pConstantBuffer, 0, nullptr, &cb, 0, 0);

		d3dDeviceContext->VSSetShader(pVS, 0, 0);
		d3dDeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		d3dDeviceContext->PSSetShader(pPS, 0, 0);
		d3dDeviceContext->PSSetSamplers(0, 1, &texSamplerState);

		// Draw the scene objects
		_sceneObject->Draw(d3dDeviceContext, i);
	}

	//d3dDeviceContext->DrawIndexed(36, 0, 0);

	//for (size_t i = 0; i < _sceneObject->_meshesToRender.size(); i++)
	//{
	//	XMMATRIX world = XMLoadFloat4x4(&_sceneObject->_meshesToRender[i]._mWorld);
	//	XMMATRIX view = XMLoadFloat4x4(&mView);
	//	XMMATRIX proj = XMLoadFloat4x4(&mProj);

	//	XMMATRIX viewProj = view * proj;

	//	//XMMATRIX view = XMLoadFloat4x4(&mView);
	//	//XMMATRIX proj = XMLoadFloat4x4(&mProj);

		// if exists a default technique implemented
		//if (standardEffect->TransformationTechnique)
		//{
		//	//fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&viewProj));
		//	D3DX11_TECHNIQUE_DESC techniqueDesc;
		//	standardEffect->TransformationTechnique->GetDesc(&techniqueDesc);
		//	for (UINT p = 0; p < techniqueDesc.Passes; ++p)
		//	{
		//		// Set effect parameters
		//		standardEffect->SetEyePosW(XMFLOAT3(x, y, z));
		//		standardEffect->world = {
		//			1.0f, 0.0f, 0.0f, 0.0f,
		//			0.0f, 1.0f, 0.0f, 0.0f,
		//			0.0f, 0.0f, 1.0f, 0.0f,
		//			0.0f, 0.0f, -5.0f, 1.0f
		//		};

		//		XMMATRIX world = XMLoadFloat4x4(&standardEffect->world);
		//		XMMATRIX worldInvTranspose = YEMath::MatrixHelper::InverseTranspose(world);
		//		XMMATRIX worldViewProj = world * view * proj;

		//		standardEffect->SetWorld(world);
		//		standardEffect->SetWorldInvTranspose(worldInvTranspose);
		//		standardEffect->SetWorldViewProj(worldViewProj);
		//		standardEffect->TransformationTechnique->GetPassByIndex(p)->Apply(0, d3dDeviceContext);

		//		//XMMATRIX world = XMLoadFloat4x4(&mWorld);

		//		// 36 indices for the box.
		//		d3dDeviceContext->DrawIndexed(36, 0, 0);
		//	}

	//		// Draw the scene objects
	//		_sceneObject->Draw(d3dDeviceContext);
		//}
	//}

	
	//m_SpriteShader->Use();

	//UpdateSpriteConstantBuffer(x,y,z);

	/*ID3D11DeviceContext* context = d3dDeviceContext;
	context->PSSetSamplers(0, 1, &texSamplerState);*/

	//m_Sprite->Render();

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
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(YEngineColors::WHITE.Value)   },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(YEngineColors::WHITE.Value)   },
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(YEngineColors::WHITE.Value)   },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(YEngineColors::WHITE.Value)   },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(YEngineColors::WHITE.Value)   },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(YEngineColors::WHITE.Value)   }
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

void YERenderingDirectX11::LoadMesh(const wchar_t* pFileName)
{
}

void YERenderingDirectX11::InitPipeline()
{
	ID3DBlob* VS, * PS;
	if (FAILED(CompileShaderFromFile(L"C:\\DirectX\\graphicsapplication\\DirectXGraphicsApp\\shaders\\VertexShader.hlsl", 0, "main", "vs_5_0", &VS)))
		YELog("Failed to compile shader from file");
	if (FAILED(CompileShaderFromFile(L"C:\\DirectX\\graphicsapplication\\DirectXGraphicsApp\\shaders\\PixelShader.hlsl", 0, "main", "ps_5_0", &PS)))
		YELog("Failed to compile shader from file ");

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
	standardEffect = new YEStandardEffect(d3dDevice);

	//HRESULT hrEffect = (D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(),
		//0, d3dDevice, &standardEffect->EffectTech));

	//// Done with compiled shader.
	//ReleaseCOM(compiledShader);
	
	D3DX11_PASS_DESC passDesc;
	standardEffect->TransformationTechnique = standardEffect->EffectTech->GetTechniqueByName("Transformation");
	standardEffect->TransformationTechnique->GetPassByIndex(0)->GetDesc(&passDesc);

	//defaultEffectTechnique = defaultColorFX->GetTechniqueByName("Transformation");
	//fxWorldViewProj = defaultColorFX->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void YERenderingDirectX11::CreateVertexLayout()
{
	// Create the vertex input layout.
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;

	standardEffect->TransformationTechnique->GetPassByIndex(0)->GetDesc(&passDesc);

	HRESULT hr = d3dDevice->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &inputLayout);
}

void YERenderingDirectX11::CreatePixelLayout()
{
}

void YERenderingDirectX11::OnRenderUI(bool* open, int spriteid, const char* msg, const char* msg2)
{
	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	static float f = 0.0f;
	static int counter = 0;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground;
	ImGui::SetNextWindowPos(ImVec2(400, 100));

	if (ImGui::Begin("Main, menu!", open, window_flags))
	{
		ImGui::Image((ImTextureID)(intptr_t)_sceneObject->_spritesToRender[spriteid]._texture, ImVec2(540, 309));
	}
	ImGui::End();

	ImGui::SetNextWindowBgAlpha(0.0);
	ImGui::SetNextWindowSize(ImVec2(700, 200));
	ImGui::SetNextWindowPos(ImVec2(400, 460));
	ImGui::GetFont()->Scale = 2.0;
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground;
		ImGui::Begin("Text HUD", NULL, window_flags);
		ImGui::Text((std::string(msg) + "\n").c_str());
		ImGui::Text(msg2);
		ImGui::End();
	}

	ImGui::SetNextWindowBgAlpha(0.0);
	ImGui::SetNextWindowSize(ImVec2(700, 200));
	ImGui::SetNextWindowPos(ImVec2(400, 40));
	ImGui::GetFont()->Scale = 2.0;
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground;
		ImGui::Begin("Text HUD2", NULL, window_flags);
		ImGui::Text("\t\t\t\tPress P to send ball to center");
		ImGui::Text("\t\t\t\tPress 1-7 to change camera angle");
		ImGui::End();
	}
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