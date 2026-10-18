#ifndef CURSOR_HIGHLIGHT_H
#define CURSOR_HIGHLIGHT_H



struct cursorHighlighterRectMapping { //array of structs will be the "map", a particular struct in that array will be a "mapping"
    int cursorHighlightPositionStateID; 
    int cursorHighlightPositionStateIDColumn;
    int rectTopLeftX;
    int rectTopLeftY;
    int rectWidth;
    int rectDepth;
};

void draw_cursor_highlighter();


extern struct cursorHighlighterRectMapping g_gui_cursorHighlighterRectMap[][4];
extern struct cursorHighlighterRectMapping g_editor_cursorHighlighterRectMap[][7];
extern struct cursorHighlighterRectMapping g_preset_panel_cursorHighlighterRectMap[][5];




#endif
