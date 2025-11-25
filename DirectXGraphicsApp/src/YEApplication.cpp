#include "YEApplication.h"
#include "YEGameContext.h"

using namespace YE;

YEngineConfig::YEConfig YEngineConfig::YEConfig::instance;
YEApplication* YEApplication::instance = 0;

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
YEApplication::YEApplication():
	_isRunning {false}
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
YEApplication::~YEApplication()
{
	YELog("\nDestroyed Application....");
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
	YEPhysics::CreateInstance();
	YETimer::CreateInstance();

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
		YELog("Failed to initialize renderer...");
		return false;
	}

	if (!InitPhysics())
	{
		YELog("Failed to initialize physics...");
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

bool YE::YEApplication::InitPhysics()
{
	instance->_physics = YEPhysics::GetInstance();
	instance->_physics->Init();

	return true;
}

void YE::YEApplication::CreatePrimitive(GamePrimitives primitive)
{
	if (instance->_renderer)
	{
		instance->_renderer->createGeometryCmd = false;

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

void YEApplication::Import3DModel()
{
	instance->_renderer->LoadMesh(L"C:\\Game Assets\\football_ball.fbx");
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
		// Set up game context
		_gameContext.sceneObject = _renderer->GetSceneObject();

		// Get game context from renderer
		_gameApp->SetGameContext(_gameContext);

		// Init physics simulations
		instance->_physics->Simulate();

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
				_gameApp->update(YETimer::GetInstance()->GetDeltaTime());
			}
		}

		// After exiting main loop, release renderer resources
		_renderer->Cleanup();
	}
	else
		YELog("Application not initialized...");

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