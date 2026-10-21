#ifndef PRESET_PANEL_H
#define PRESET_PANEL_H

#include <stdbool.h>


struct PRESET_PANEL_STATE {
    int cursorPositionRow;
    bool cursorFlashingState;
    double lastFlashToggleTime;   // seconds

};

extern struct PRESET_PANEL_STATE g_PresetPanelState;


void preset_panel_init();
void preset_panel_update(float delta);
void preset_panel_drawing_tree();
void handle_preset_panel_input();

int load_presets(const char* presets_folder_filepath);








#endif