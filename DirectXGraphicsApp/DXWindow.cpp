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

#if defined DX11_RENDER_SUPPORT

    DXRenderingDirectX11* renderer = dynamic_cast<DXRenderingDirectX11*>(DXRenderer::GetInstance());

    renderer->renderWindow = hWnd;
    renderer->Init();

    ImGui_ImplDX11_Init(renderer->d3dDevice, renderer->d3dDeviceContext);

#endif 

    DXLog("\nCreated Window....");

    Show();
}

void DXWindow::Show()
{
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

        return 0;

    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}