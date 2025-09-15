#include "YEWindow.h"

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
	return new YEWindow();
}

YEWindow* YEWindow::GetInstance()
{
    static YEWindow* instance = nullptr;

    if (instance == nullptr)
    {
        instance = new YEWindow();
    }

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
