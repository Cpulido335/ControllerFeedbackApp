#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include <stdbool.h>

struct APPLICATION_STATE {
    int currentPanel;
    int cursorPositionRow;
    int cursorPositionColumn;
    bool cursorFlashingState;
    double lastFlashToggleTime;   // seconds

    //editor 
    int currentPositionInEditorList;
    //Editor panel specific button selected logic //if 0 is pressed editor list entry is selected, changes to rebind, 

    const char *currentSelectedProfile; 

    //controller

    bool controllerConnected;

};

extern struct APPLICATION_STATE g_ApplicationState;



#endif


