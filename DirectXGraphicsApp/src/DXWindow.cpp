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
	DXLog("\nDestroyed Window....");    
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
    hWnd = ::CreateWindow(wc.lpszClassName, _T("Yakira Engine v0.2"), WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, wc.hInstance, NULL);

    DXLog("\nCreated Window....");

	Show();
}

void DXWindow::Show()
{
#if defined DX11_RENDER_SUPPORT

    /*DXRenderingDirectX11* renderer = dynamic_cast<DXRenderingDirectX11*>(DXRenderer::GetInstance());

    renderer->renderWindow = hWnd;
    renderer->Init();*/

	bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Direct3D11;
    bgfxInit.platformData.nwh = hWnd;
    bgfxInit.platformData.ndt = GetModuleHandle(NULL);
	bgfxInit.resolution.width = width;
	bgfxInit.resolution.height = height;
	bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
	bgfx::init(bgfxInit);

#endif

    // Show the window
    ::ShowWindow(hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hWnd);

    msg = {};

    bgfx::setViewClear(0
        , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
        , 0x578a3dff
        , 1.0f
        , 0
    );

    while (true)
    {
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }

        //DXRenderer::GetInstance()->Render();

        bgfx::setViewRect(0, 0, 0, width, height);
        bgfx::touch(0);

        bgfx::frame();

        DXLog("\Window Loop running...");
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