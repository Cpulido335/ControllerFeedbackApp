#ifndef GUI_H
#define GUI_H

#include <stdbool.h>

#include "geometry/cube.h"
#include "geometry/mesh.h"

struct GUI_STATE { //A BETTER WORD FOR THIS WOULD BE GUI SCENE 
    struct Cube *leftCube;
    struct Cube *rightCube;
    struct Mesh *controllerMeshDS4; //TODO lets just have them both for now. clean code > optimization
    struct Mesh *controllerMeshXboxOne;
    struct vec3 *controllerMeshPivot;
};



struct redrawZoneMapping { //the redraw zone will be around the cursor position //TODO IS THIS EVEN USED ANYMORE???
    int cursorHighlightPositionStateID; 
    int rectTopLeftX;
    int rectTopLeftY;
    int rectWidth;
    int rectDepth;
};

extern struct GUI_STATE g_GuiState;
extern struct redrawZoneMapping g_redrawZoneMap[];

void gui_init();
void gui_update(float delta);
void gui_draw_cursor_highlighter();


void gui_drawing_tree();


#endif //!GUI_H