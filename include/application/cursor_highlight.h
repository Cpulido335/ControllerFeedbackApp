#ifndef CURSOR_HIGHLIGHT_H
#define CURSOR_HIGHLIGHT_H


#include "globals.h"



struct cursorHighlighterRectMapping { //array of structs will be the "map", a particular struct in that array will be a "mapping"
    int cursorHighlightPositionStateID; 
    int cursorHighlightPositionStateIDColumn;
    int rectTopLeftX;
    int rectTopLeftY;
    int rectWidth;
    int rectDepth;
};

void draw_cursor_highlighter();


extern struct cursorHighlighterRectMapping g_gui_cursorHighlighterRectMap[HOME_NUM_COLUMNS][HOME_NUM_ROWS];
extern struct cursorHighlighterRectMapping g_editor_cursorHighlighterRectMap[EDITOR_NUM_COLUMNS][EDITOR_NUM_ROWS];
extern struct cursorHighlighterRectMapping g_preset_panel_cursorHighlighterRectMap[PRESET_PANEL_NUM_COLUMNS][PRESET_PANEL_NUM_ROWS];




#endif
