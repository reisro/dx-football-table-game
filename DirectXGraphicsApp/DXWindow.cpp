#include "DXWindow.h"
#include "DXRenderingDirectX11.h"

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

void DXWindow::CreateInstance()
{
}

void DXWindow::Setup()
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("DXApp"), NULL };
    ::RegisterClassEx(&wc);
    hWnd = ::CreateWindow(wc.lpszClassName, _T("Rain Forest Engine"), WS_OVERLAPPEDWINDOW, 100, 100, width, height, NULL, NULL, wc.hInstance, NULL);

    dxRenderer->GetInstance()->renderWindow = hWnd;
}

void DXWindow::Create()
{
    Setup();

    // Show the window
    ::ShowWindow(hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hWnd);

    //// Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    //// Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    //// Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hWnd);
    //ImGui_ImplDX11_Init(dxRendering->d3dDevice, dxRendering->d3dDeviceContext);

    msg = {};
    
    while (::GetMessage(&msg, NULL, 0U, 0U) > 0)
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    DXLog("\nCreated Window....");
}

void DXWindow::Show()
{
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

        return 0;

    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}