#ifndef PRESET_PANEL_H
#define PRESET_PANEL_H

#include <stdbool.h>


struct PRESET_PANEL_STATE {
    int cursorPosition;
    bool cursorFlashingState;
    double lastFlashToggleTime;   // seconds

    //create 5 preset entries first you need 5 ControllerButton arrays
    struct ControllerButton *buttons1;
    struct ControllerButton *buttons2;
    struct ControllerButton *buttons3;
    struct ControllerButton *buttons4;
    struct ControllerButton *buttons5;

    //then you need 5 profiles
    struct Profile *profile1;
    struct Profile *profile2;
    struct Profile *profile3;
    struct Profile *profile4;
    struct Profile *profile5;
};

extern struct PRESET_PANEL_STATE g_PresetPanelState;


void preset_panel_init();
void preset_panel_update(float delta);
void preset_panel_drawing_tree();
void handle_preset_panel_input();

int load_presets(const char* presets_folder_filepath);








#endif