#include "application/application.h"

#include <stdint.h>
#include <stdbool.h>
#include "globals.h"

#include "input/input.h" //I dont know if this is how I want to architect this


//define window procedure
LRESULT CALLBACK WindowCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
            uint32_t VKCode = wParam;

            bool wasDown = (lParam & (1 << 30)) != 0;
            bool isDown = (lParam & (1 << 31)) == 0;


            input_process_keyboard_input(VKCode, wasDown, isDown);
            break;
        }

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


void Application_Init(struct Application* app, HINSTANCE hInstance)
{
    app->hInstance = hInstance;
    app->windowTitle = "Jahsehs App"; //hardcoded
    app->windowWidth = WINDOW_WIDTH;
    app->windowHeight = WINDOW_HEIGHT;
}


HWND Application_CreateWindow(struct Application* app) //TODO Do we actually need to return the window handle here, would that not require us to put this in a another function unesscarily since the main loop is already gonna be in here
{
    WNDCLASS windowClass = {0};
    
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowCallback;
    windowClass.hInstance = app->hInstance;
    windowClass.lpszClassName = "jahseh_window_class_name"; //hardcoded


    if (!RegisterClass(&windowClass)) //register the window class
    {
        OutputDebugStringW(L"Failed to register window class\n");
        return 0;
    }

    DWORD windowStyle = WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION;

    RECT windowRect = {};
    windowRect.left = 0;
    windowRect.top = 0;
    windowRect.right = app->windowWidth;
    windowRect.bottom = app->windowHeight;

    AdjustWindowRect(&windowRect, windowStyle, FALSE);

    app->windowHandle = CreateWindowEx(
        0,
        windowClass.lpszClassName,
        app->windowTitle,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        0,
        0,
        app->hInstance,
        0
    );

    return app->windowHandle;
}


void Application_Update(struct Application *app, float delta)
{

}

