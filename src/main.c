#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _WIN32_WINNT 0x0A00
#define WINVER       0x0A00


#include <windows.h>
#include "application/application.h"
#include "globals.h"
#include "util/clock.h"
#include <direct.h>
#include <stdbool.h>
#include "render/draw.h"
#include "application/application_manager.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    struct Application app;
    
    application_init(&app, hInstance);
    clock_init();
    
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ); //this apparanrley stops windows from scaling DPI in newer versions but makes it not compatiable with older than win10
   
    HWND hwnd = Application_CreateWindow(&app);

    MSG Msg;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    if(hwnd) //if WindowHandle
    {   
        float delta;
        
        while(true) //MAIN LOOP
        {            
            delta = clock_frame_start(); //at the start of the frame delta is computed 
            
            //message loop processes windows messages
            MSG message;
            while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&message);
                DispatchMessage(&message);        // Send message to the WindowProc (WindowCallback)
            }


            application_update(delta); //MEAT AND POTATOES FUNCTION
                        
            // --- DRAW TO SCREEN ---
            HDC deviceContext = GetDC(hwnd); 

            clock_frame_end(); //at the end of the frame a loop exists taht can slow down the fps / execution of the main loop

            copyBufferToWindow(deviceContext, WINDOW_WIDTH, WINDOW_HEIGHT);
            ReleaseDC(hwnd, deviceContext); //windows expects you to release this to avoid DC leaks

            if (g_ApplicationState.quit == TRUE) {
                application_destroy();
                break; //EXIT THE LOOP AFTER
            }
        }

    }


    return Msg.wParam;
}