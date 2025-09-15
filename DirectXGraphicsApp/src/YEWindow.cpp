#include "YEWindow.h"
#include "DXRenderingDirectX11.h"
#include "YEWinAppWindow.h"

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

void YEWindow::CreateInstance()
{
}

void YEWindow::Setup()
{
}

void YEWindow::Create()
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("DXApp"), NULL };
    ::RegisterClassEx(&wc);
    hWnd = ::CreateWindow(wc.lpszClassName, _T("Yakira Engine v0.2"), WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, wc.hInstance, NULL);

    DXLog("\nCreated Window....");
}

void YEWindow::Show(uint16_t _width, uint16_t _height)
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

        // Game loop
        /*while (_gameapp->update(0.0f))
        {
            DXLog("Game Loop.....");
        }*/

        DXLog("\Window Loop running...");
    }
}