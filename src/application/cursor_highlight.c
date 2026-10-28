#include "application/cursor_highlight.h"

#include "application/application_manager.h" //for g_ApplicationState 
#include <stddef.h>

#include "render/draw.h"

#include <stdio.h> //TODO remove when done debugging




struct cursorHighlighterRectMapping g_gui_cursorHighlighterRectMap[HOME_NUM_COLUMNS][HOME_NUM_ROWS] = { //TODO so this is a map of mappings or an array that is a struct of structs?
    //cursor_id_row, cursor_id_col, x, y, width, height
    {
        { 0,   0,       35,  37,  186,   12 },   // F10 MENU OPTION
        { 1,   0,       35,  51,  186,   12 },   // F1 MENU OPTION
        { 2,   0,       35,  65,  186,   12 },   // F2 MENU OPTION
        { 3,   0,       35,  79,  186,   12 },   // F3 MENU OPTION
    }
};


struct cursorHighlighterRectMapping g_editor_cursorHighlighterRectMap[EDITOR_NUM_COLUMNS][EDITOR_NUM_ROWS] = { //TODO so this is a map of mappings or an array that is a struct of structs?
  
    {   //COLUMN 0: THE EDITOR MENU OPTIONS
        // row, column, x, y, width, height
        { 0, 0, 90, 100, 280, 40 }, // NEW
        { 1, 0, 90, 140, 280, 40 }, // EDIT
        { 2, 0, 90, 180, 280, 40 }, // LOAD
        { 3, 0, 90, 220, 280, 40 }, // SAVE
        { 4, 0, 90, 340, 280, 40 }, // HOME
        { 5, 0, 90, 380, 280, 40 }, // PRESETS
        { 6, 0, 90, 420, 280, 40 }, // OTHER
        { 7, 0, 90, 460, 280, 40 }, // OTHER
    },

    {   //COLUMN 1: CURRENT PRESET BUTTON LIST
        // row, column, x, y, width, height
        {  0, 1, 440, 120, 600, 40 },
        {  1, 1, 440, 160, 600, 40 },
        {  2, 1, 440, 200, 600, 40 },
        {  3, 1, 440, 240, 600, 40 },
        {  4, 1, 440, 280, 600, 40 },
        {  5, 1, 440, 320, 600, 40 },
        {  6, 1, 440, 360, 600, 40 },
        {  7, 1, 440, 400, 600, 40 },
        {  8, 1, 440, 440, 600, 40 },
        {  9, 1, 440, 480, 600, 40 },
        { 10, 1, 440, 520, 600, 40 },
        { 11, 1, 440, 560, 600, 40 },
    }
};



struct cursorHighlighterRectMapping g_preset_panel_cursorHighlighterRectMap[PRESET_PANEL_NUM_COLUMNS][PRESET_PANEL_NUM_ROWS] = { //TODO so this is a map of mappings or an array that is a struct of structs?
    //cursor_id_row, cursor_id_col, x, y, width, height

    {   //COLUMN 0 - MENU
        { 0,   0,       35,   37,   186,   12 },   // F10 MENU OPTION
        { 1,   0,       35,   51,   186,   12 },   // F1 MENU OPTION
        { 2,   0,       35,   65,   186,   12 },   // F2 MENU OPTION
        { 0,   0,        0,    0,     0,    0 },   // UNUSED
        { 0,   0,        0,    0,     0,    0 },   // UNUSED
    },

    {   //COLUMN 1 - FIRST CELL
        { 0,   1,       80,  160,   300,   40 },   // TOP ROW FIRST CELL
        { 1,   1,       80,  200,   300,   40 },   // 2ND ROW DOWN FIRST CELL
        { 2,   1,       80,  240,   300,   40 },   // 3RD ROW DOWN FIRST CELL
        { 3,   1,       80,  280,   300,   40 },   // 4TH ROW DOWN FIRST CELL
        { 4,   1,       80,  320,   300,   40 },   // 5TH ROW DOWN FIRST CELL
    },

    {   //COLUMN 2 - 2ND CELL
        { 0,   2,      380,  160,   480,   40 },   // TOP ROW 2ND CELL
        { 1,   2,      380,  200,   480,   40 },   // 2ND ROW DOWN 2ND CELL
        { 2,   2,      380,  240,   480,   40 },   // 3RD ROW DOWN 2ND CELL
        { 3,   2,      380,  280,   480,   40 },   // 4TH ROW DOWN 2ND CELL
        { 4,   2,      380,  320,   480,   40 },   // 5TH ROW DOWN 2ND CELL
    },

    {   //COLUMN 3 - LOAD
        { 0,   3,      860,  160,   100,   40 },   // TOP ROW LOAD CELL
        { 1,   3,      860,  200,   100,   40 },   // 2ND ROW DOWN LOAD CELL
        { 2,   3,      860,  240,   100,   40 },   // 3RD ROW DOWN LOAD CELL
        { 3,   3,      860,  280,   100,   40 },   // 4TH ROW DOWN LOAD CELL
        { 4,   3,      860,  320,   100,   40 },   // 5TH ROW DOWN LOAD CELL
    },

    {   //COLUMN 4 - EDIT
        { 0,   4,      960,  160,   100,   40 },   // TOP ROW EDIT CELL
        { 1,   4,      960,  200,   100,   40 },   // 2ND ROW DOWN EDIT CELL
        { 2,   4,      960,  240,   100,   40 },   // 3RD ROW DOWN EDIT CELL
        { 3,   4,      960,  280,   100,   40 },   // 4TH ROW DOWN EDIT CELL
        { 4,   4,      960,  320,   100,   40 },   // 5TH ROW DOWN EDIT CELL
    },

    {   //COLUMN 5 - DELETE
        { 0,   5,     1060,  160,   100,   40 },   // TOP ROW DELETE CELL
        { 1,   5,     1060,  200,   100,   40 },   // 2ND ROW DOWN DELETE CELL
        { 2,   5,     1060,  240,   100,   40 },   // 3RD ROW DOWN DELETE CELL
        { 3,   5,     1060,  280,   100,   40 },   // 4TH ROW DOWN DELETE CELL
        { 4,   5,     1060,  320,   100,   40 },   // 5TH ROW DOWN DELETE CELL
    }

};



void draw_cursor_highlighter() //TODO this functionality needs its own module  
{
    //get the application state current panel 
    //get the application state cursor flashing state 
    
    if (!g_ApplicationState.cursorFlashingState) //if its not flashed then return
        return;
    
    struct cursorHighlighterRectMapping *currentMapping = NULL;
    int cursorHighlighterMapLength = 99; // TODO PROBLEM hardcoded TODO

    int row = g_ApplicationState.cursorPositionRow;
    int column = g_ApplicationState.cursorPositionColumn;

    //right about here we'll do a switch on the current panel of the application state
    struct cursorHighlighterRectMapping* cursorHighlighterRectMap;
    
    switch (g_ApplicationState.currentPanel)
    {
        case 0: //GUI
            if (column != 0 || row < 0 || row >= 4)
                return;

            currentMapping = &g_gui_cursorHighlighterRectMap[column][row];
            break;

        case 1: //PRESETS
            if (column < 0 || column >= 6 || row < 0 || row >= 5)
                return;

            if (column == 0 && row >= 3)
                return;

            currentMapping = &g_preset_panel_cursorHighlighterRectMap[column][row];
            break;

        case 2: //EDITOR
            if (column < 0 || column >= EDITOR_NUM_COLUMNS || row < 0 || row >= EDITOR_NUM_ROWS) //TODO ADD THE GLOBAL MAXS TO ALL THESE ERROR CHECKING STATEMETNS VERY IMPORATANT!!!!!!
                return;
            if(row == 2)
                printf("breakpoint\n");
            
            currentMapping = &g_editor_cursorHighlighterRectMap[column][row];
            break;

        default:
            return;
    }



    printf("Row: %d            Column: %d\n", g_ApplicationState.cursorPositionRow, g_ApplicationState.cursorPositionColumn);

    if (!currentMapping)
        return;

    //draw_rectangle_top_left(currentMapping->rectTopLeftX, currentMapping->rectTopLeftY, currentMapping->rectWidth, currentMapping->rectDepth, 0xFFFFFFFF, 2 );
    invert_rectangle_within_drawContext(currentMapping->rectTopLeftX, currentMapping->rectTopLeftY, currentMapping->rectWidth, currentMapping->rectDepth);
}
