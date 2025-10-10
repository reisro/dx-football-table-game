#include "YEApplication.h"

using namespace YE;

YEngineConfig::YEConfig YEngineConfig::YEConfig::instance;
YEApplication* YEApplication::instance = 0;

/// <summary>
/// Constructors Implementation
/// </summary>
YEApplication::YEApplication():
	_isRunning {false}
{
}

/// <summary>
/// Destructors Implementation
/// </summary>
YEApplication::~YEApplication()
{
	DXLog("\nDestroyed Application....");
}

//-----------------------------------------------------------------------------
// Application Setup Configuration
//-----------------------------------------------------------------------------
void YEApplication::Setup(const YEngineConfig::YEConfig& config)
{
	YEngineConfig::YEConfig::instance = config;
}

//-----------------------------------------------------------------------------
// Engine Subsystem Initialization
//-----------------------------------------------------------------------------
bool YE::YEApplication::InitEngine()
{
	// Create singletons for this application
	instance = new YEApplication();

	// Create singletons for subsystems
	YERenderer::CreateInstance();
	DXTimer::CreateInstance();

	instance->_isInitialized = true;

	return instance->_isInitialized;
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
bool YEApplication::Init()
{
	if (!InitRenderer())
	{
		DXLog("Failed to initialize renderer...");
		return false;
	}

	return instance->_isInitialized;
}

//-----------------------------------------------------------------------------
// Application Subsystem Window Initialization
//-----------------------------------------------------------------------------
bool YE::YEApplication::InitWindow()
{
	YEWindow::GetInstance()->Create();

	return true;
}

//-----------------------------------------------------------------------------
// Application Subsystem Renderer Initialization
//-----------------------------------------------------------------------------
bool YEApplication::InitRenderer()
{
	instance->_renderer = YERenderer::GetInstance();
	instance->_renderer->Init();

	return true;
}

void YE::YEApplication::CreatePrimitive(GamePrimitives primitive)
{
	if (instance->_renderer)
	{
		instance->_renderer->createGeometryCmd = true;

		switch (primitive)
		{
		case GamePrimitives::Cube:
			instance->_renderer->CreateDefaultCube();
			break;
		case GamePrimitives::Cylinder:
			instance->_renderer->CreateDefaultCube();
			break;
		default:
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// Application Main Loop / Game Client Code
//-----------------------------------------------------------------------------
void YE::YEApplication::Run(YEGame* gameApp)
{
	_gameApp = gameApp;
	_isRunning = true;

	// Check if application instance was properly initialized
	if (instance->_isInitialized)
	{	
		// Start up game components
		_gameApp->init();

		_msg = {};

		// Keep updating game until user closes the application
		while (true)
		{
			// Listen for window messages
			if (::PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&_msg);
				::DispatchMessage(&_msg);

				if (_msg.message == WM_QUIT)
					break;
			}
			else // No messages to process, keep updating game application
			{
				#if defined DX11_RENDER_SUPPORT

				// Render application frame
				_renderer->Render();

				#endif

				// Game application state related resources update
				_gameApp->update(DXTimer::GetInstance()->GetDeltaTime());
			}
		}

		// After exiting main loop, release renderer resources
		_renderer->Cleanup();
	}
	else
		DXLog("Application not initialized...");

	// After game is not updating 
	// Release game resources
	_gameApp->shutdown();
}

DX_API YEApplication* createDXApplication()
{
	return new YEApplication();
}

YEApplication* YEApplication::GetInstance()
{
	return instance;
}