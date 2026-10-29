#ifndef BUTTONLIST_H
#define BUTTONLIST_H

#include <stdio.h>
#include <string.h>

enum ButtonType {
    BTN_BUTTON,
    BTN_AXIS
};

struct ControllerButton {
    char        name[32];
    int         id;
    enum ButtonType  type;
    unsigned int bitmask;   // 0 if not used
    int         axis_min;   // ignored for buttons
    int         axis_max;
    char        key_that_its_binded_to[32];
};



struct Profile {  //TODO maybe add int ButtonCount, uint16 leftStickDeadzone, uint16 rightStickdeadZone
    char name[128]; //Maybe profile controller type thats a very big maybe because we probably don't need that the buttons will just tell you what kind of controller it is along with SDL3 telling you what kind of controller it is
    struct ControllerButton  *arrayOfControllerButton; //A button can be an axes too
    int numButtons;
};



int parse_buttonlist(const char *path, struct ControllerButton *out, int max);
void create_profile_from_preset_filepath(const char *path, struct ControllerButton *buttons, struct Profile *profile,  char* profile_name);




#endif 
