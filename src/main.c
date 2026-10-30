#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _WIN32_WINNT 0x0A00
#define WINVER       0x0A00


#include <windows.h>
#include "application/application.h"
#include "globals.h"
#include <direct.h>

#include <stdbool.h>
#include "render/draw.h"
#include "application/gui.h"
#include "input/input.h" //TODO not sure if this is how I want to architect this
#include "application/application_manager.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    struct Application app;
    
    application_init(&app, hInstance);
    
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ); //this apparanrley stops windows from scaling DPI in newer versions but makes it not compatiable with older than win10
   
    HWND hwnd = Application_CreateWindow(&app);

    MSG Msg;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    if(hwnd) //if WindowHandle
    {   

        LARGE_INTEGER cpu_frequency; //init the clock
        QueryPerformanceFrequency(&cpu_frequency);

        LARGE_INTEGER last_counter;
        QueryPerformanceCounter(&last_counter);

    
        
        while(true) //MAIN LOOP
        {
            // --- FRAME START ---
            LARGE_INTEGER frame_start;
            QueryPerformanceCounter(&frame_start);

            // --- COMPUTE DELTA FOR FRAME LOGIC (rotation, animation, etc.) ---
            static LARGE_INTEGER last_frame_start = {0};
            if (last_frame_start.QuadPart == 0)
                last_frame_start = frame_start; // initialize on first frame

            int64_t counter_elapsed = frame_start.QuadPart - last_frame_start.QuadPart;
            float delta = (float)counter_elapsed / (float)cpu_frequency.QuadPart; // in seconds

            last_frame_start = frame_start; // update for next frame logic

            //message loop processes windows messages
            MSG message;
            while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
            {
                // if (message.message == WM_QUIT) TODO put this back maybe maybe not we need free all memory allocations before we quit the program
                //     running = false;

                TranslateMessage(&message);
                DispatchMessage(&message);        // Send message to the WindowProc (WindowCallback)
            }


            application_update(delta); //MEAT AND POTATOES FUNCTION
                        

            // --- DRAW TO SCREEN ---
            HDC deviceContext = GetDC(hwnd); //TODO wtf is going on here


            // --- FRAME END ---5
            LARGE_INTEGER frame_end;
            QueryPerformanceCounter(&frame_end);

            int64_t frame_ticks = frame_end.QuadPart - frame_start.QuadPart;
            float frame_time = (float)frame_ticks / (float)cpu_frequency.QuadPart;

           
            if (frame_time < TARGET_FRAME_TIME) {  //sleepy time to cap FPS
                DWORD sleep_ms = (DWORD)((TARGET_FRAME_TIME - frame_time) * 1000.0);
                if (sleep_ms > 0)
                    Sleep(sleep_ms);

                // measure again after sleep for accurate FPS display
                QueryPerformanceCounter(&frame_end);
                frame_ticks = frame_end.QuadPart - frame_start.QuadPart;
                frame_time = (float)frame_ticks / (float)cpu_frequency.QuadPart;
            }


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