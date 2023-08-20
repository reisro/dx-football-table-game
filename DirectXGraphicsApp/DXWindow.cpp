#include "DXWindow.h"

DXWindow::DXWindow():
    width(1920),
    height(1080)
{
	
}

DXWindow::DXWindow(int width, int height):
    width(width),
    height(height)
{
    
}

DXWindow::DXWindow(const DXWindow& rhs):
    width(rhs.width),
    height(rhs.height)
{
    
}

DXWindow::~DXWindow()
{
}

void DXWindow::Create()
{
    DXLog("\n\tCreated Window....");
}