// Program.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Program.h"
#include "Game.h"
#include "Mouse.h"
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
bool                ProcessMessage();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROGRAM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    Game game;
    HDC hdc = GetDC(hWnd);
    Mouse& mouse = Mouse::GetInstance();

    // Main loop:
    while (ProcessMessage())
    {
        gfx::ClearScreen();
        game.Run();
        mouse.wasLButtonDown = mouse.isLButtonDown;
        gfx::CopyBufferToWindow(hdc);
    }

    return 0;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{

    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_PROGRAM), IMAGE_ICON, 32, 32, 0);
    wcex.hIconSm        = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_PROGRAM), IMAGE_ICON, 16, 16, 0);
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszClassName  = szWindowClass;

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   RECT wr = {};
   wr.left = 300;
   wr.right = wr.left + gfx::ScreenWidth;
   wr.top = 150;
   wr.bottom = wr.top + gfx::ScreenHeight;
   AdjustWindowRectEx(&wr, WS_OVERLAPPEDWINDOW, FALSE, 0);

   hWnd = CreateWindowEx(0, szWindowClass, szTitle, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
       wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   gfx::SetWindowHandle(hWnd);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Mouse& mouse = Mouse::GetInstance();
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
    {
        POINTS pt = MAKEPOINTS(lParam);
        //const std::string s = std::to_string(pt.x) + ", " + std::to_string(pt.y) + '\n';
        //OutputDebugStringA(s.c_str());
        mouse.pos = { pt.x, pt.y };
        mouse.isLButtonDown = true;
    }
    break;
    case WM_LBUTTONUP:
    {
        mouse.isLButtonDown = false;
    }
    break;
    case WM_MOUSEMOVE:
    {
        POINTS pt = MAKEPOINTS(lParam);
        mouse.pos = { pt.x, pt.y };
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

bool ProcessMessage()
{
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
        {
            return false;
        }
    }
    return true;
}


