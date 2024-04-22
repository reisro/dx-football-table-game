#include "DXWindow.h"
#include "DXRenderingDirectX11.h"

DXWindow::DXWindow():
    width(1366),
    height(768)
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

void DXWindow::CreateInstance()
{
}

void DXWindow::Setup()
{
}

void DXWindow::Create()
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("DXApp"), NULL };
    ::RegisterClassEx(&wc);
    hWnd = ::CreateWindow(wc.lpszClassName, _T("Rain Forest Engine"), WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, wc.hInstance, NULL);

    DXLog("\nCreated Window....");

    Show();
}

void DXWindow::Show()
{


#if defined DX11_RENDER_SUPPORT

    DXRenderingDirectX11* renderer = dynamic_cast<DXRenderingDirectX11*>(DXRenderer::GetInstance());

    renderer->renderWindow = hWnd;
    renderer->Init();

#endif

    // Show the window
    ::ShowWindow(hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hWnd);

    msg = {};

    while (true)
    {
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }

        DXRenderer::GetInstance()->Render();
    }
}

LRESULT __stdcall DXWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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