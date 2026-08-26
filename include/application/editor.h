#ifndef EDITOR_H
#define EDTIOR_H




#include <stdbool.h>
#include "application/buttonlist.h"


struct EDITOR_PANEL_DATA {
    int cursorPosition;
    bool cursorFlashingState;
    double lastFlashToggleTime;   // seconds
    
    struct ControllerButton buttons[32];
    struct Profile currentEditorProfile;
};

extern struct EDITOR_PANEL_DATA g_EditorPanelState;


void editor_panel_init();
void editor_panel_update(float delta);
void editor_panel_drawing_tree();







#endif 