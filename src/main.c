// #define _WIN32_WINNT 0x0A00  //Windows 10 TODO prob get rid of this 
// #define WINVER       0x0A00 //TODO prob get rid of this

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _WIN32_WINNT 0x0A00
#define WINVER       0x0A00


#include <windows.h>
#include "application/application.h"
#include "globals.h"
#include <direct.h>

#include <stdbool.h>
#include "geometry/cube.h"
#include "render/draw.h"
#include "math/rotation.h"

#include <stdio.h> //snprintf todo rm this
#include "application/gui.h"
#include "input/input.h" //TODO not sure if this is how I want to architect this
#include "geometry/fbx_ascii_parser.h"
#include "geometry/mesh.h"

#include "application/preset_panel.h"
#include "application/editor.h"

#include "application/buttonlist.h" //TODO PROBLEM for sure remove this once youre done, the preset functionality needs a (run-once-initialization) phase 

#include "application/application_manager.h"
#include "application/cursor_highlight.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    //_chdir("C:/Users/cjpul/Desktop/ControllFeedbackApp"); //TODO why tf do we need this I never see any app need some stupid ass line like this
    
    struct Application app;
    
    Application_Init(&app, hInstance);
    
    SetProcessDpiAwarenessContext(
    DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 //this apparanrley stops windows from scaling DPI in newer versions but makes it not compatiable with older than win10
    );
    
    HWND hwnd = Application_CreateWindow(&app);

    MSG Msg;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    if(hwnd) //if WindowHandle
    {
        //draw_init();
        draw_init_font(IMG_FILEPATH_FONT_C64_SMALL);
       

        //init the clock
        LARGE_INTEGER cpu_frequency;
        QueryPerformanceFrequency(&cpu_frequency);

        LARGE_INTEGER last_counter;
        QueryPerformanceCounter(&last_counter);

        //struct Cube cube = createCube(100, 100, 100, 200); //create a cube  //TODO MOVE THIS TO INIT GUI
        // struct Cube lil_cube_left = createCube(396, 48, 100, 20); //create a cube
        // struct Cube lil_cube_right = createCube(884, 48, 100, 20); //create a cube
 


        // struct Mesh *mesh = get_mesh(); //TODO MOVE THIS TO INIT GUI
        
        // reflect_mesh(mesh);  //TODO MOVE THESE THREE TO INIT GUI REFLECT ROTATE TRANSLATE
        // rotate_vertices(mesh->vertices, -90, 180, 0);
        // translate_mesh(mesh, 600.0f, 340.0f, 0.0f);
        

        // struct vec3 pivot; //TODO MOVE THIS TO INIT GUI
        // pivot.x = 0 + 600; pivot.y =0+340; pivot.z =0;
        gui_init();
        
        //TODO you see how theres a GUI init there needs to be like a preset init where we initialize the preset structs in memory 
        editor_panel_init();
        
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
                // if (message.message == WM_QUIT)
                //     running = false;

                TranslateMessage(&message);
                DispatchMessage(&message);        // Send message to the WindowProc (WindowCallback)
            }

            clear_drawContext();   





            //rotateCubeAroundOrigin(&cube, 100*delta, 20*delta, 40*delta);
            //rotateCubeAroundZ(&cube, 20);
            
            
            
            // rotate_vertices_around_point(mesh->vertices, pivot, 0, 40*delta, 0); //TODO MOVE THIS TO UPDATE GUI

            // rotateCubeAroundOrigin(&lil_cube_left, 100*delta, 20*delta, 40*delta);  //TODO MOVE THIS TO UPDATE GUI
            // rotateCubeAroundOrigin(&lil_cube_right, -(100*delta), -(20*delta), -(40*delta));  //TODO MOVE THIS TO UPDATE GUI

            // draw_cube(&lil_cube_left, 1);  //TODO MOVE THIS TO GUI_DRAWING_TREE
            // draw_cube(&lil_cube_right,1); //TODO MOVE THIS TO GUI_DRAWING_TREE

            // draw_fbx_model(mesh, 1); //TODO MOVE THIS TO GUI_DRAWING_TREE


            gui_update(delta); //called once per frame TODO This function used to be the thing that was responsible for flashing the cursor now its applicaiton_update
            application_update();
            //gui_drawing_tree();
            //preset_panel_drawing_tree();
            switch(g_ApplicationState.currentPanel) //TODO you need to double check that there is issue with having both the window and handle_input within this tree and before gui_update delta
            {
                case 0:
                    gui_drawing_tree();
                    handle_gui_input();
                    break;
                case 1:
                    preset_panel_drawing_tree();
                    break;
                case 2:
                    editor_panel_drawing_tree();
                    handle_editor_input();
                    break;
            }
                


            //CURSOR
            
            // gui_draw_cursor_highlighter(); //TODO THIS CAN ALSO BE MOVED WITHIN THE GUI_DRAWING_TREE() FUNCTION
            draw_cursor_highlighter();

            // --- DRAW TO SCREEN ---
            HDC deviceContext = GetDC(hwnd); //TODO wtf is going on here

            //draw_rectangle_top_left(28, 27, 204, 86, COLOR_RED, 1); //TOP LEFT KILLZONE


            // --- FRAME END ---5
            LARGE_INTEGER frame_end;
            QueryPerformanceCounter(&frame_end);

            int64_t frame_ticks = frame_end.QuadPart - frame_start.QuadPart;
            float frame_time = (float)frame_ticks / (float)cpu_frequency.QuadPart;

            //sleepy time to cap FPS
            if (frame_time < TARGET_FRAME_TIME)
            {
                DWORD sleep_ms = (DWORD)((TARGET_FRAME_TIME - frame_time) * 1000.0);
                if (sleep_ms > 0)
                    Sleep(sleep_ms);

                // measure again after sleep for accurate FPS display
                QueryPerformanceCounter(&frame_end);
                frame_ticks = frame_end.QuadPart - frame_start.QuadPart;
                frame_time = (float)frame_ticks / (float)cpu_frequency.QuadPart;
            }

            //FPS display (uses full frame time including sleep)
            int fps = (int)(1.0f / frame_time);
            char buffer[256];

            // snprintf(
            //     buffer,
            //     sizeof(buffer),
            //     "FPS: %d",
            //     fps
            // );
            //draw_text_blazing(buffer, 1100, 80);

            copyBufferToWindow(deviceContext, WINDOW_WIDTH, WINDOW_HEIGHT);
            ReleaseDC(hwnd, deviceContext); //windows expects you to release this to avoid DC leaks
        }

    }


    return Msg.wParam;
}