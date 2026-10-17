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
    { 0,          35,  37,  186,    12 },   // F10 MENU OPTION
    { 1,          35,  51,  186,    12 },   // F1 MENU OPTION
    { 2,          35,  65,  186,    12 },   // F2 MENU OPTION
    

    { 3,          80,  160,  300,   40 },   // TOP ROW FIRST CELL
    { 4,          80,  200,  300,   40 },   // 2ND ROW DOWN FIRST CELL
    { 5,          80,  240,  300,   40 },   // 3RD ROW DOWN FIRST CELL
    { 6,          80,  280,  300,   40 },   // 4th ROW DOWN FIRST CELL
    { 7,          80,  320,  300,   40 },   // 5th ROW DOWN FIRST CELL

    { 8,          380,  160,  480,   40 },   // TOP ROW 2nd CELL
    { 9,          380,  200,  480,   40 },   // 2nd row down 2nd CELL
    { 10,         380,  240,  480,   40 },   // 3rd row down 2nd CELL
    { 11,         380,  280,  480,   40 },   // 4th row down 2nd CELL
    { 12,         380,  320,  480,   40 },   // 5th row down 2nd CELL

    { 13,         860,  160,  100,   40 },   // TOP ROW LOAD CELL
    { 14,         860,  200,  100,   40 },   // 2nd row down LOAD CELL
    { 15,         860,  240,  100,   40 },   // 3rd row down LOAD CELL
    { 16,         860,  280,  100,   40 },   // 4th row down LOAD CELL
    { 17,         860,  320,  100,   40 },   // 5th row down LOAD CELL

    { 18,         960,  160,  100,   40 },   // TOP ROW EDIT CELL
    { 19,         960,  200,  100,   40 },   // 2nd row down EDIT CELL
    { 20,         960,  240,  100,   40 },   // 3rd row down EDIT CELL
    { 21,         960,  280,  100,   40 },   // 4th row down EDIT CELL
    { 22,         960,  320,  100,   40 },   // 5th row down EDIT CELL

    { 23,        1060,  160,  100,   40 },   // TOP ROW DELETE CELL
    { 24,        1060,  200,  100,   40 },   // 2nd row down DELETE CELL
    { 25,        1060,  240,  100,   40 },   // 3rd row down DELETE CELL
    { 26,        1060,  280,  100,   40 },   // 4th row down DELETE CELL
    { 27,        1060,  320,  100,   40 },   // 5th row down DELETE CELL

};



void draw_cursor_highlighter() //TODO this functionality needs its own module  
{
    //get the application state current panel 
    //get the application state cursor flashing state 
    
    if (!g_ApplicationState.cursorFlashingState) //if its not flashed then return
        return;
    
    int currentCursorID = g_ApplicationState.cursorPosition; //TODO do we need this variable?
    struct cursorHighlighterRectMapping *currentMapping = NULL;
    int cursorHighlighterMapLength = 99; // TODO PROBLEM hardcoded TODO


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
