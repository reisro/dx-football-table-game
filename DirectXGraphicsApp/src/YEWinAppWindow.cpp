#include "YEWinAppWindow.h"

YEWinAPIWindow::YEWinAPIWindow()
{
}

YEWinAPIWindow::YEWinAPIWindow(int width, int height)
{
}

YEWinAPIWindow::YEWinAPIWindow(const YEWinAPIWindow& rhs)
{
}

YEWinAPIWindow::~YEWinAPIWindow()
{
}

void YEWinAPIWindow::CreateInstance()
{
}

void YEWinAPIWindow::Setup()
{
}

void YEWinAPIWindow::Create()
{
}

void YEWinAPIWindow::Show(uint16_t _width, uint16_t _height)
{
	YEWindow::Show(_width, _height);
}

LRESULT __stdcall YEWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
