#include "YEWindow.h"
#include "YEWinAppWindow.h"

YEWindow* YEWindow::instance = 0;

YEWindow::YEWindow():
    _width(1366),
    _height(768)
{
	Create();
}

YEWindow::YEWindow(dxInt width, dxInt height):
    _width(width),
    _height(height)
{
	Create();
}

YEWindow::YEWindow(const YEWindow& rhs):
    _width(rhs._width),
    _height(rhs._height)
{
}

YEWindow::~YEWindow()
{
	YELog("\nDestroyed Window....");    
}

YEWindow* YEWindow::CreateInstance()
{
    if (YEngineConfig::YEConfig::instance.platform == YEngineConfig::Platform::Windows)
    {
		instance = new YEWinAppWindow(YEngineConfig::YEConfig::instance.resolution.width, YEngineConfig::YEConfig::instance.resolution.height);
    }

	return instance;
}

YEWindow* YEWindow::GetInstance()
{
    return instance;
}

void YEWindow::Setup()
{
}

void YEWindow::Create()
{
    YELog("\nCreated Window instance....");
}

void YEWindow::Show()
{
}

void YEWindow::Update()
{
    YELog("\nUpdate Window....");
}

void YEWindow::OnResize(YERenderer* renderer)
{
    YELog("\nResize Window....");
}
