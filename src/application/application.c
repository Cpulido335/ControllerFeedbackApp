#include "application/application.h"

#include <stdint.h>
#include <stdbool.h>
#include "globals.h"

#include "input/input.h" //I dont know if this is how I want to architect this
#include "input/input_controller.h"
#include "util/clock.h"
#include "application/application_manager.h"
#include "application/cursor_highlight.h"
#include "application/buttonlist.h"

#include <stdio.h>
#include <SDL3/SDL.h> //using SDL3 for gamepad API



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

        case WM_CLOSE: //TODO is this what should kick off the chain of all the free/destroy/cleanup memory functions?
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY: //TODO is this what should kick off the chain of all the free/destroy/cleanup memory functions?
            PostQuitMessage(0); 
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


void application_init(struct Application* app, HINSTANCE hInstance)
{
    app->hInstance = hInstance;
    app->windowTitle = "Controller Feedback GUI"; //hardcoded
    app->windowWidth = WINDOW_WIDTH;
    app->windowHeight = WINDOW_HEIGHT;

    //initiazilize SDL3s gamepad subsystem
    if (!SDL_Init(SDL_INIT_GAMEPAD))
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return;
    }

    register_controller_sdl(); // call once on Init and everytime theres hotplugging, hotplugging can be detected with SDL3 API via SDL_EVENT_GAMEPAD_ADDED and SDL_EVENT_GAMEPAD_REMOVED

        
    g_ApplicationState.buttons1 = malloc(sizeof(struct ControllerButton) * 128); //TODO 128 buttons in a preset is still hardcoded fckn everywhere
    g_ApplicationState.buttons2 = malloc(sizeof(struct ControllerButton) * 128);
    g_ApplicationState.buttons3 = malloc(sizeof(struct ControllerButton) * 128);
    g_ApplicationState.buttons4 = malloc(sizeof(struct ControllerButton) * 128);
    g_ApplicationState.buttons5 = malloc(sizeof(struct ControllerButton) * 128);

    g_ApplicationState.profile1 = malloc(sizeof(struct Profile));
    g_ApplicationState.profile2 = malloc(sizeof(struct Profile)); //TODO we should probably have error checking all over this entire function for good practice
    g_ApplicationState.profile3 = malloc(sizeof(struct Profile));
    g_ApplicationState.profile4 = malloc(sizeof(struct Profile));
    g_ApplicationState.profile5 = malloc(sizeof(struct Profile));

    g_ApplicationState.currentSelectedProfile = g_ApplicationState.profile5; //Selecting Profile 5 for now
    g_ApplicationState.currentSelectedButtonInCurrentSelectedProfile = &g_ApplicationState.currentSelectedProfile->arrayOfControllerButton[0]; //select the first button in the profile on init
}


void application_update()
{
    double now = get_time_seconds();

    if (now - g_ApplicationState.lastFlashToggleTime >= CURSOR_FLASH_PERIOD)
    {
        g_ApplicationState.cursorFlashingState = !g_ApplicationState.cursorFlashingState;
        g_ApplicationState.lastFlashToggleTime = now;
    }

    //TODO right here we need do the SDL stuff for the gamepad subsystem
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_GAMEPAD_ADDED:
                register_controller_sdl();
                break;

            case SDL_EVENT_GAMEPAD_REMOVED:
                register_controller_sdl();
                break;

        }
    }
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



void application_destroy()
{
    free(g_ApplicationState.buttons1);
    free(g_ApplicationState.buttons2);
    free(g_ApplicationState.buttons3);
    free(g_ApplicationState.buttons4);
    free(g_ApplicationState.buttons5);


    free(g_ApplicationState.profile1);
    free(g_ApplicationState.profile2);
    free(g_ApplicationState.profile3);
    free(g_ApplicationState.profile4);
    free(g_ApplicationState.profile5);

}

