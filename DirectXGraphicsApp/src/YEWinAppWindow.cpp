#include "YEWinAppWindow.h"
#include "DXRenderingDirectX11.h"

YEWinAppWindow::YEWinAppWindow()
{
}

YEWinAppWindow::YEWinAppWindow(dxInt width, dxInt height):
    YEWindow(width, height),
    _width(width),
	_height(height)
{
}

YEWinAppWindow::YEWinAppWindow(const YEWinAppWindow& rhs)
{
}

YEWinAppWindow::~YEWinAppWindow()
{
}

void YEWinAppWindow::CreateInstance()
{
}

void YEWinAppWindow::Setup()
{
}

void YEWinAppWindow::Create()
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("DXApp"), NULL };
    ::RegisterClassEx(&wc);
    hWnd = ::CreateWindow(wc.lpszClassName, _T("Yakira Engine v0.2"), WS_OVERLAPPEDWINDOW, 0, 0, _width, _height, NULL, NULL, wc.hInstance, NULL);
}

void YEWinAppWindow::Show()
{
	YEWindow::Show();

    // Show the window
    ::ShowWindow(hWnd, SW_SHOWDEFAULT);
}

void YEWinAppWindow::Update()
{
    ::UpdateWindow(hWnd);
   
}

LRESULT __stdcall YEWinAppWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hWnd, &ps);
    }

    break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
