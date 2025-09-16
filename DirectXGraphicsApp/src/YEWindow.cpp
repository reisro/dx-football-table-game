#include "YEWindow.h"
#include "YEWinAppWindow.h"

YEWindow* YEWindow::instance = 0;

YEWindow::YEWindow():
    width(1366),
    height(768)
{
	Create();
}

YEWindow::YEWindow(int width, int height):
    width(width),
    height(height)
{
	Create();
}

YEWindow::YEWindow(const YEWindow& rhs):
    width(rhs.width),
    height(rhs.height)
{
}

YEWindow::~YEWindow()
{
	DXLog("\nDestroyed Window....");    
}

YEWindow* YEWindow::CreateInstance()
{
    if (YEngineConfig::DXConfig::instance.platform == YEngineConfig::Platform::Windows)
    {
        instance = new YEWinAppWindow();
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
    DXLog("\nCreated Window....");
}

void YEWindow::Show(uint16_t _width, uint16_t _height)
{
}

void YEWindow::Update()
{
    DXLog("\nUpdate Window....");
}
