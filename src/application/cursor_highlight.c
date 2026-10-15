#include "application/cursor_highlight.h"

#include "application/application_manager.h" //for g_ApplicationState 
#include <stddef.h>

#include "render/draw.h"


struct cursorHighlighterRectMapping g_gui_cursorHighlighterRectMap[] = { //TODO so this is a map of mappings or an array that is a struct of structs?
    // cursor_id, x,   y,   width, height
    { 0,          35,  37,  186,    12 },   // F10 MENU OPTION
    { 1,          35,  51,  186,    12 },   // F1 MENU OPTION
    { 2,          35,  65,  186,    12 },   // F2 MENU OPTION
    { 3,          35,  79,  186,    12 },   // F3 MENU OPTION
    
};


struct cursorHighlighterRectMapping g_editor_cursorHighlighterRectMap[] = { //TODO so this is a map of mappings or an array that is a struct of structs?
    // cursor_id, x,   y,   width, height

    //editor panel
    { 0,         80+10, 100, 300-20, 40}, //editor panel NEW button
    { 1,         80+10, 140, 300-20, 40}, //editor panel EDIT button
    { 2,         80+10, 180, 300-20, 40}, //editor panel LOAD button
    { 3,         80+10, 220, 300-20, 40}, //editor panel SAVE button
    
    { 4,         80+10, 340, 300-20, 40}, //editor panel HOME button 
    { 5,         80+10, 380, 300-20, 40}, //editor panel PRESETS button
    { 6,         80+10, 420, 300-20, 40}, //editor panel NEW button
    
};



struct cursorHighlighterRectMapping g_preset_panel_cursorHighlighterRectMap[] = { //TODO so this is a map of mappings or an array that is a struct of structs?
    // cursor_id, x,   y,   width, height
    
};



void draw_cursor_highlighter() //TODO this functionality needs its own module  
{
    //get the application state current panel 
    //get the application state cursor flashing state 
    
    if (!g_ApplicationState.cursorFlashingState) //if its not flashed then return
        return;
    
    int currentCursorID = g_ApplicationState.cursorPosition; //TODO do we need this variable?
    struct cursorHighlighterRectMapping *currentMapping = NULL;
    int cursorHighlighterMapLength = 10; // TODO PROBLEM hardcoded TODO


    //right about here we'll do a switch on the current panel of the application state
    struct cursorHighlighterRectMapping* cursorHighlighterRectMap;
    
    switch (g_ApplicationState.currentPanel)
    {
        case 0:
            cursorHighlighterRectMap = g_gui_cursorHighlighterRectMap;
            break;
        case 1:
            cursorHighlighterRectMap = g_preset_panel_cursorHighlighterRectMap;
            break;
        case 2:
            cursorHighlighterRectMap = g_editor_cursorHighlighterRectMap;
            break;
    }


    for (int i = 0; i < cursorHighlighterMapLength; i++)
    {
        if (cursorHighlighterRectMap[i].cursorHighlightPositionStateID == currentCursorID)
        {
            currentMapping = &cursorHighlighterRectMap[i];
            break;
        }
    }

    if (!currentMapping)
        return;

    //draw_rectangle_top_left(currentMapping->rectTopLeftX, currentMapping->rectTopLeftY, currentMapping->rectWidth, currentMapping->rectDepth, 0xFFFFFFFF, 2 );
    invert_rectangle_within_drawContext(currentMapping->rectTopLeftX, currentMapping->rectTopLeftY, currentMapping->rectWidth, currentMapping->rectDepth);
}
