#ifndef GUI_H
#define GUI_H

#include <stdbool.h>

#include "geometry/cube.h"
#include "geometry/mesh.h"

struct GUI_STATE {
    int currentPanel;
    int cursorPosition;
    bool cursorFlashingState;
    double lastFlashToggleTime;   // seconds

    //editor 
    int currentPositionInEditorList;
    //Editor panel specific button selected logic //if 0 is pressed editor list entry is selected, changes to rebind, 

    struct Cube *leftCube;
    struct Cube *rightCube;
    struct Mesh *controllerMesh;
    struct vec3 controllerMeshPivot;
};

//cursor position state list
//F10 = 0
//F1 = 1
//F2 =2
struct cursorHighlighterRectMapping { //array of structs will be the "map", a particular struct in that array will be a "mapping"
    int cursorHighlightPositionStateID; 
    int rectTopLeftX;
    int rectTopLeftY;
    int rectWidth;
    int rectDepth;
};

struct redrawZoneMapping { //the redraw zone will be around the cursor position
    int cursorHighlightPositionStateID; 
    int rectTopLeftX;
    int rectTopLeftY;
    int rectWidth;
    int rectDepth;
};


extern struct GUI_STATE g_GuiState;
extern struct cursorHighlighterRectMapping g_cursorHighlighterRectMap[];
extern struct redrawZoneMapping g_redrawZoneMap[];

void gui_init();
void gui_update(float delta);
void gui_draw_cursor_highlighter();


void gui_drawing_tree();


#endif //!GUI_H