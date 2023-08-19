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
    msg = {};
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
    // Registering the window class
    wndClass.lpfnWndProc = WindowProc;
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = titleName;

    RegisterClass(&wndClass);

    // Creating the window
    hWnd = CreateWindowEx(0, "WindowTitle", titleName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);

    if (hWnd == NULL)
    {
        MessageBoxA(0, "Failed to create window.", "Fatal Error", MB_OK | MB_ICONEXCLAMATION | MB_APPLMODAL);
    }

    ShowWindow(hWnd, cmdShow);

    msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DXLog("	\n Created Window....");
}

LRESULT DXWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}