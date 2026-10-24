#include "application/gui.h" //TODO a better word for this would be MAIN_PANEL

//#include "util/clock.h"
#include "globals.h"
#include <stdlib.h>

#include "render/draw.h"
#include "util/clock.h"

#include "geometry/fbx_ascii_parser.h"
#include "math/rotation.h"

#include "application/application_manager.h"
#include "input/input_controller.h"

#include <stdio.h>


struct GUI_STATE g_GuiState = { 
    
};




void gui_init()
{
    g_GuiState.leftCube = createCube(396, 48, 100, 20); //create a heap-allocated cube
    g_GuiState.rightCube = createCube(884, 48, 100, 20);

    g_GuiState.controllerMeshXboxOne = get_mesh(XBOX_ONE_CONTROLLER_FILEPATH);
    g_GuiState.controllerMeshDS4 = get_mesh(DS4_CONTROLLER_FILEPATH);
    
    //position the mesh in the right spot   
    //reflect_mesh(g_GuiState.controllerMesh);  //TODO MOVE THESE THREE TO INIT GUI REFLECT ROTATE TRANSLATE
    //rotate_vertices(g_GuiState.controllerMesh->vertices, 90, 180, 0); //DS4
     
    //translate_mesh(g_GuiState.controllerMesh, 600.0f, 340.0f, 0.0f); DS4 MODEL

    //TODO for now lets just initialize them both we can leave this block when we want to optimize to only initiialize a mesh when its selected but its kind of overkill and 
    // will make code sloppier
    // switch(g_ApplicationState.controllerTypeDetected)    //TODO add default
    // {
    //     case CONTROLLER_TYPE_DS4:
    //         rotate_vertices(g_GuiState.controllerMeshDS4->vertices, 90, 180, 180); //DS4
    //         translate_mesh(g_GuiState.controllerMeshDS4, 600.0f, 340.0f, 0.0f); //XBOX_ONE ODEL
    //         g_GuiState.controllerMeshPivot = malloc(sizeof(struct vec3));

    //         if (g_GuiState.controllerMeshPivot != NULL) {
    //             *g_GuiState.controllerMeshPivot = (struct vec3) { 600.0f, 340.0f, 0.0f };
    //         }
    //         break;
        
        
    //     case CONTROLLER_TYPE_XBOX_ONE:
    //         rotate_vertices(g_GuiState.controllerMeshXboxOne->vertices, 90, 180, 0); //TODO make sure theres no copying going on here and its all heap-allocations
    //         scale_mesh(g_GuiState.controllerMeshXboxOne, 500.0f);
    //         translate_mesh(g_GuiState.controllerMeshXboxOne, 600.0f, 340.0f, 0.0f); //XBOX_ONE ODEL
    //         g_GuiState.controllerMeshPivot = malloc(sizeof(struct vec3));

    //         if (g_GuiState.controllerMeshPivot != NULL) {
    //             *g_GuiState.controllerMeshPivot = (struct vec3) { 600.0f, 340.0f, 0.0f };
    //         }
    //         break;

    // }

    //TODO for now lets just initialize them both
    rotate_vertices(g_GuiState.controllerMeshDS4->vertices, 90, 180, 180); //DS4
    translate_mesh(g_GuiState.controllerMeshDS4, 600.0f, 340.0f, 0.0f); //XBOX_ONE ODEL
    g_GuiState.controllerMeshPivot = malloc(sizeof(struct vec3));

    rotate_vertices(g_GuiState.controllerMeshXboxOne->vertices, 90, 180, 0); //TODO make sure theres no copying going on here and its all heap-allocations
    scale_mesh(g_GuiState.controllerMeshXboxOne, 500.0f);
    translate_mesh(g_GuiState.controllerMeshXboxOne, 600.0f, 340.0f, 0.0f); //XBOX_ONE ODEL
    g_GuiState.controllerMeshPivot = malloc(sizeof(struct vec3));

    if (g_GuiState.controllerMeshPivot != NULL) {
        *g_GuiState.controllerMeshPivot = (struct vec3) { 600.0f, 340.0f, 0.0f };
    }
} 

void gui_update(float delta) //updates all the things within the gui that need to be updated, should take in delta as input because alot of stuff need that
{   

    rotateCubeAroundOrigin(g_GuiState.leftCube, 100*delta,20*delta, 40*delta);  //TODO MOVE THIS TO UPDATE GUI
    rotateCubeAroundOrigin(g_GuiState.rightCube, -(100*delta), -(20*delta), -(40*delta));  //TODO MOVE THIS TO UPDATE GUI

    
    
    switch(g_ApplicationState.controllerTypeDetected)  //TODO add default
    {
        case CONTROLLER_TYPE_DS4:
            rotate_vertices_around_point(g_GuiState.controllerMeshDS4->vertices, g_GuiState.controllerMeshPivot, 0, 40*delta, 0); //TODO MOVE THIS TO UPDATE GUI
            break;
        
        
        case CONTROLLER_TYPE_XBOX_ONE:
            rotate_vertices_around_point(g_GuiState.controllerMeshXboxOne->vertices, g_GuiState.controllerMeshPivot, 0, 40*delta, 0); //TODO MOVE THIS TO UPDATE GUI
            break;

    }
}





void gui_drawing_tree()
{
    //////////////----SETUP----//////////////
    //GUI
    
    //MAINFRAME    
    draw_rounded_rectangle(20, 20, (WINDOW_WIDTH)-60, (WINDOW_HEIGHT)-60, 10, 2, COLOR_GREEN);
    
    //TOPCENTER
    draw_text_blazing("JAHCORP_OS CONTROLLER FEEDBACK GUI",  640-((34*12)/2), 40);
    
    //TOPLEFT
    draw_rounded_rectangle(30, 30, 200, 80, 10, 1,  COLOR_GREEN);
    draw_text_blazing("F10: EXIT",  35, 35); //top left options
    draw_text_blazing("F1: LOAD PRESET",  35, 49); //top left options
    draw_text_blazing("F2: EDITOR",  35, 63);
    draw_text_blazing("F3: TOOLS",  35, 77); //++14

    //BOTTOM CENTER
    char controllerGUID_reading_string[256];  
    
    
    snprintf(controllerGUID_reading_string, sizeof(controllerGUID_reading_string), "CONTROLLER DETECTED:%s GUID:%.*s", 
                                    g_ApplicationState.controllerTypeString, 18, g_ApplicationState.controllerSDL_GUID_string);
    
    
    
    if(g_ApplicationState.controllerConnected)
    {
        draw_text_blazing(controllerGUID_reading_string,   640-((51*12)/2), 600);
    }
    else {
        draw_text_blazing("CONTROLLER NOT CONNECTED",   640-((51*12)/2), 600);
    }


    //analag stick tracker 
    //-32,768 - 32,767
    

    //MIDDLE LOWER LEFT DPAD
    draw_rectangle_top_left(69, 418, 42, 26, COLOR_GREEN, 1,  g_ApplicationState.controllerButtonDpadLeft);  // LEFT // FILL THE RECTANGLES IN WHILE THE BOOL IS TRUE 
    draw_rectangle_top_left(149, 418, 42, 26, COLOR_GREEN, 1, g_ApplicationState.controllerButtonDpadRight); // RIGHT
    draw_rectangle_top_left(117, 450, 26, 42, COLOR_GREEN, 1, g_ApplicationState.controllerButtonDpadDown); //DOWN DPAD
    draw_rectangle_top_left(117, 370, 26, 42, COLOR_GREEN, 1,g_ApplicationState.controllerButtonDpadUp); //DPAD UP


    // MIDDLE LOWER RIGHT FACE BUTTONS
    draw_button_circle(1130, 391, 13, COLOR_GREEN, g_ApplicationState.controllerButtonNorth); 
    draw_button_circle(1170, 431, 13, COLOR_GREEN, g_ApplicationState.controllerButtonEast);  
    draw_button_circle(1090, 431, 13, COLOR_GREEN, g_ApplicationState.controllerButtonWest);  
    draw_button_circle(1130, 471, 13, COLOR_GREEN, g_ApplicationState.controllerButtonSouth); 
    
    

    
    //BOTTOM LEFT
    draw_rounded_rectangle(30, 510, 200, 160, 10, 1,  COLOR_GREEN);
    draw_circle(130 + g_ApplicationState.controllerLeftStickX * 94 / 32768, 590 + g_ApplicationState.controllerLeftStickY * 74 / 32768, 6, 1, COLOR_GREEN); 

    draw_rectangle_top_left(240, 510, 20, 160, COLOR_GREEN, 1, false); //LEFT trigger
    int leftFill = g_ApplicationState.controllerLeftTrigger * 158 / 32767;
    if (leftFill > 0)
        draw_rectangle_top_left(241, 669 - leftFill, 18, leftFill, COLOR_GREEN, 1, true);

    //BOTTOM RIGHT
    draw_rounded_rectangle(1030, 510, 200, 160, 10, 1,  COLOR_GREEN); //1220 = -mainframe padding -bottom corner rect padding
    draw_circle(1130 + g_ApplicationState.controllerRightStickX * 94 / 32768, 590 + g_ApplicationState.controllerRightStickY * 74 / 32768, 6, 1, COLOR_GREEN);
    
    
    draw_rectangle_top_left(1000, 510, 20, 160, COLOR_GREEN, 1, false); //Right Trigger
    int rightFill = g_ApplicationState.controllerRightTrigger * 158 / 32767;
    if (rightFill > 0)
        draw_rectangle_top_left(1001, 669 - rightFill, 18, rightFill, COLOR_GREEN, 1, true);
    //////////////----SETUP----//////////////

    // switch(g_GuiState.cursorPositionRow) //TODO idek wtf this is supposed to do you can probablby just remove it all
    // {
    //     case 0: //top left
    //     case 1:
    //     case 2: 
    //         //clear_rectangle_within_drawContext(28, 27, 204, 86); //TODO should we clear before or after?

    //         draw_rounded_rectangle(30, 30, 200, 80, 10, 1,  COLOR_GREEN);
    //         draw_text_blazing("F10: EXIT",  35, 35); //top left options
    //         draw_text_blazing("F1: LOAD PRESET",  35, 49); //top left options
    //         draw_text_blazing("F2: VIEW PRESET",  35, 63);
    //         draw_text_blazing("F3: TOOLS",  35, 77); //++14
    //         break;

    //     default:
    //         break;
    // }

    draw_cube(g_GuiState.leftCube, 1);  //TODO MOVE THIS TO GUI_DRAWING_TREE
    draw_cube(g_GuiState.rightCube,1); //TODO MOVE THIS TO GUI_DRAWING_TREE


    switch(g_ApplicationState.controllerTypeDetected)  //TODO add default
    {
        case CONTROLLER_TYPE_DS4:
            draw_fbx_model(g_GuiState.controllerMeshDS4, 1); 
            break;
        
        case CONTROLLER_TYPE_XBOX_ONE:
            draw_fbx_model(g_GuiState.controllerMeshXboxOne, 1); 
            break;
    }

    //gui_draw_cursor_highlighter(); TODO i think this should be global in some way, putting this in here confines it to the main panel?
}