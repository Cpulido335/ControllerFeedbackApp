#include "application/gui.h" //TODO a better word for this would be MAIN_PANEL

//#include "util/clock.h"
#include "globals.h"
#include <stdlib.h>

#include "render/draw.h"
#include "util/clock.h"

#include "geometry/fbx_ascii_parser.h"
#include "math/rotation.h"


/* Global GUI state (singleton) */ //TODO PPROBLEM this is not specific to the GUI/Main panel
struct GUI_STATE g_GuiState = {
    .currentPanel= 2, //0=main, 1=preset, 2=editor
    .cursorPosition = 8,        // start on F10
    .cursorFlashingState = false,
    .lastFlashToggleTime = 0,
    .currentPositionInEditorList =0 
    
};


struct cursorHighlighterRectMapping g_cursorHighlighterRectMap[] = {
    // cursor_id, x,   y,   width, height
    { 0,          35,  37,  186,    12 },   // F10 MENU OPTION
    { 1,          35,  51,  186,    12 },   // F1 MENU OPTION
    { 2,          35,  65,  186,    12 },   // F2 MENU OPTION

    //editor panel
    { 3,         80+10, 100, 300-20, 40}, //editor panel NEW button
    { 4,         80+10, 140, 300-20, 40}, //editor panel EDIT button
    { 5,         80+10, 180, 300-20, 40}, //editor panel LOAD button
    { 6,         80+10, 220, 300-20, 40}, //editor panel SAVE button
    
    { 7,         80+10, 340, 300-20, 40}, //editor panel new button 
    { 8,         80+10, 380, 300-20, 40}, //editor panel new button
    { 9,         80+10, 420, 300-20, 40}, //editor panel new button
    
};


struct redrawZoneMapping g_redrawZoneMap[] = { //TODO I think we can get rid of this
    // cursor_id,      x,   y,   width, height
    { 0,            28, 27, 204, 86 },   // F10 MENU OPTION TOPLEFT KILLZONE
    { 1,            28, 27, 204, 86 },   // F1 MENU OPTION  TOPLEFT KILLZONE
    { 2,            28, 27, 204, 86 },   // F2 MENU OPTION  TOPLEFT KILLZONE


    
};


void gui_init()
{
    g_GuiState.leftCube = createCube(396, 48, 100, 20); //create a heap-allocated cube
    g_GuiState.rightCube = createCube(884, 48, 100, 20);

    g_GuiState.controllerMesh = get_mesh();
    //position the mesh in the right spot
    //reflect_mesh(g_GuiState.controllerMesh);  //TODO MOVE THESE THREE TO INIT GUI REFLECT ROTATE TRANSLATE
    rotate_vertices(g_GuiState.controllerMesh->vertices, 90, 180, 180); //TODO make sure theres no copying going on here and its all heap-allocations
    translate_mesh(g_GuiState.controllerMesh, 600.0f, 340.0f, 0.0f);

    // struct vec3 pivot; //set up the pivot so that the controller mesh can rotate around it
    // pivot.x = 0 + 600; pivot.y =0+340; pivot.z =0;
    // g_GuiState.controllerMeshPivot = &pivot;

    g_GuiState.controllerMeshPivot = (struct vec3){ 600.0f, 340.0f, 0.0f }; //TODO lets just store this by value
}


void gui_update(float delta) //updates all the things within the gui that need to be updated, should take in delta as input because alot of stuff need that
{
    double now = get_time_seconds();

    if (now - g_GuiState.lastFlashToggleTime >= CURSOR_FLASH_PERIOD)
    {
        g_GuiState.cursorFlashingState = !g_GuiState.cursorFlashingState;
        g_GuiState.lastFlashToggleTime = now;
    }

    rotate_vertices_around_point(g_GuiState.controllerMesh->vertices, g_GuiState.controllerMeshPivot, 0, 40*delta, 0); //TODO MOVE THIS TO UPDATE GUI
    rotateCubeAroundOrigin(g_GuiState.leftCube, 100*delta, 20*delta, 40*delta);  //TODO MOVE THIS TO UPDATE GUI
    rotateCubeAroundOrigin(g_GuiState.rightCube, -(100*delta), -(20*delta), -(40*delta));  //TODO MOVE THIS TO UPDATE GUI
}


void gui_draw_cursor_highlighter()
{
    if (!g_GuiState.cursorFlashingState) //if its not flashed then return
        return;
    
    int currentCursorID = g_GuiState.cursorPosition;
    struct cursorHighlighterRectMapping *currentMapping = NULL;
    int cursorHighlighterMapLength = 10; // TODO PROBLEM hardcoded TODO

    for (int i = 0; i < cursorHighlighterMapLength; i++)
    {
        if (g_cursorHighlighterRectMap[i].cursorHighlightPositionStateID == currentCursorID)
        {
            currentMapping = &g_cursorHighlighterRectMap[i];
            break;
        }
    }

    if (!currentMapping)
        return;

    //draw_rectangle_top_left(currentMapping->rectTopLeftX, currentMapping->rectTopLeftY, currentMapping->rectWidth, currentMapping->rectDepth, 0xFFFFFFFF, 2 );
    invert_rectangle_within_drawContext(currentMapping->rectTopLeftX, currentMapping->rectTopLeftY, currentMapping->rectWidth, currentMapping->rectDepth);
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
    draw_text_blazing("F2: VIEW PRESET",  35, 63);
    draw_text_blazing("F3: TOOLS",  35, 77); //++14

    //BOTTOM CENTER
    draw_text_blazing("CONTROLLER DETECTED: DUALSHOCK4 UUID: ai19xj2ow291",   640-((51*12)/2), 650);

    //BOTTOM LEFT
    draw_rounded_rectangle(30, 510, 200, 160, 10, 1,  COLOR_GREEN);

    //BOTTOM RIGHT
    draw_rounded_rectangle(1030, 510, 200, 160, 10, 1,  COLOR_GREEN); //1220 = -mainframe padding -bottom corner rect padding
    //////////////----SETUP----//////////////

    switch(g_GuiState.cursorPosition) 
    {
        case 0: //top left
        case 1:
        case 2: 
            //clear_rectangle_within_drawContext(28, 27, 204, 86); //TODO should we clear before or after?

            draw_rounded_rectangle(30, 30, 200, 80, 10, 1,  COLOR_GREEN);
            draw_text_blazing("F10: EXIT",  35, 35); //top left options
            draw_text_blazing("F1: LOAD PRESET",  35, 49); //top left options
            draw_text_blazing("F2: VIEW PRESET",  35, 63);
            draw_text_blazing("F3: TOOLS",  35, 77); //++14
            break;

        default:
            break;
    }

    draw_cube(g_GuiState.leftCube, 1);  //TODO MOVE THIS TO GUI_DRAWING_TREE
    draw_cube(g_GuiState.rightCube,1); //TODO MOVE THIS TO GUI_DRAWING_TREE

    draw_fbx_model(g_GuiState.controllerMesh, 1); //TODO MOVE THIS TO GUI_DRAWING_TREE

    //gui_draw_cursor_highlighter(); TODO i think this should be global in some way, putting this in here confines it to the main panel?
}