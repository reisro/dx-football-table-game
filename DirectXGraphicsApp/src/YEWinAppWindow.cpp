#include "YEWinAppWindow.h"
#include "YERenderingDirectX11.h"
#include "../3rdparty/dear_imgui/backends/imgui_impl_win32.h"

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

YEWinAppWindow::YEWinAppWindow()
{
}

YEWinAppWindow::YEWinAppWindow(dxInt width, dxInt height):
    YEWindow(width, height)
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

void YEWinAppWindow::OnResize(YERenderer* renderer)
{
    #ifdef DX11_RENDER_SUPPORT
    
    YERenderingDirectX11* rendererDX = dynamic_cast<YERenderingDirectX11*>(renderer);

    #endif
}

LRESULT __stdcall YEWinAppWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

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

    case WM_SIZE:
    {
        if (YERenderer::initialized)
        {
            YERenderer* renderer = YERenderer::GetInstance();

            if (renderer)
            {
                YEWindow::GetInstance()->_width = LOWORD(lParam);
                YEWindow::GetInstance()->_height = HIWORD(lParam);

                if (wParam == SIZE_RESTORED)
                {
					DXLog("Window Restored...");

                    YEWindow::GetInstance()->OnResize(renderer);
                }
            }
        }
    }
    break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}