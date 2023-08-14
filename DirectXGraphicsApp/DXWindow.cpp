#include "DXWindow.h"

DXWindow::DXWindow():
    width(1920), height(1080)
{
	dxRendering = DX_NULL;

    hWnd = NULL;
    titleName = "DirectX Graphics Application - Rain Forest Engine";
    hInstance = (HINSTANCE)GetModuleHandle(NULL);
    wndClass = {};
    windowName = "";
    cmdShow = 10;
}

DXWindow::DXWindow(int width, int height):
    width(width), height(height)
{
    dxRendering = DX_NULL;

    hWnd = NULL;
    titleName = "DirectX Graphics Application - Rain Forest Engine";
    hInstance = (HINSTANCE)GetModuleHandle(NULL);
    wndClass = {};
    windowName = "";
    cmdShow = 10;
}

DXWindow::DXWindow(const DXWindow& rhs):
    width(rhs.width), height(rhs.height)
{
    dxRendering = DX_NULL;

    hWnd = rhs.hWnd;
    titleName = rhs.titleName;
    hInstance = rhs.hInstance;
    wndClass = rhs.wndClass;
    windowName = rhs.windowName;
    cmdShow = rhs.cmdShow;
}

DXWindow::~DXWindow()
{
}

void DXWindow::Create()
{
	DebugLog("	\n Created Window...");
}

LRESULT DXWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}
