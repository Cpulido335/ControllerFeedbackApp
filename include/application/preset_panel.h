#ifndef PRESET_PANEL_H
#define PRESET_PANEL_H

#include <stdbool.h>


struct PRESET_PANEL_STATE {
    int cursorPosition;
    bool cursorFlashingState;
    double lastFlashToggleTime;   // seconds
};

extern struct PRESET_PANEL_STATE g_PresetPanelState;


void preset_panel_init();
void preset_panel_update(float delta);
void preset_panel_drawing_tree();

int load_presets(const char* presets_folder_filepath);








#endif