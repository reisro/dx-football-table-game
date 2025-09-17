#include "YEApplication.h"

using namespace YE;

YEngineConfig::YEConfig YEngineConfig::YEConfig::instance;
YEApplication* YEApplication::instance = 0;

YEApplication::YEApplication()
{
}

YEApplication::~YEApplication()
{
	DXLog("\nDestroyed Application....");
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
void YEApplication::Setup(const YEngineConfig::YEConfig& config)
{
	YEngineConfig::YEConfig::instance = config;
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

bool YE::YEApplication::InitEngine()
{
	// Create singletons for this application
	instance = new YEApplication();

	// Create singletons for subsystems
	YEWindow::CreateInstance();
	DXRenderer::CreateInstance();
	DXTimer::CreateInstance();

	instance->_isInitialized = true;

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
	DXRenderer::GetInstance()->Init();

	return true;
}

//-----------------------------------------------------------------------------
// Application Initialization resources
//-----------------------------------------------------------------------------
void YE::YEApplication::Start(DXGame* gameApp)
{
	_gameApp = gameApp;
	_isRunning = true;

	if (instance->_isInitialized)
	{	
		_msg = {};

		while (true)
		{
			if (::PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&_msg);
				::DispatchMessage(&_msg);

				if (_msg.message == WM_QUIT)
					break;

				#if defined DX11_RENDER_SUPPORT

				DXRenderer* renderer = DXRenderer::GetInstance();
				renderer->Render();

				#endif

				_gameApp->update(DXTimer::GetInstance()->GetDeltaTime());
			}
			else
			{
				
			}

			//DXRenderer::GetInstance()->Render();

			// Game loop
			/*while (_gameapp->update(0.0f))
			{
				DXLog("Game Loop.....");
			}*/

			//DXLog("\Window Loop running...");
		}
	}
	else
		DXLog("Application not initialized...");
}

DX_API YEApplication* createDXApplication()
{
	return new YEApplication();
}

YEApplication* YEApplication::GetInstance()
{
	return instance;
}