#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include <stdbool.h>
#include <SDL3/SDL.h>


enum ControllerType  
{
    CONTROLLER_TYPE_DS4,
    CONTROLLER_TYPE_XBOX_ONE,
    CONTROLLER_TYPE_OTHER

};
// #define CONTROLLER_TYPE_DS4 0
// #define CONTROLLER_TYPE_XBOX_ONE 1
// #define CONTROLLER_TYPE_OTHER 2


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
    int controllerTypeDetected;

    //SDL_GUID controllerSDL_GUID; //TODO should this be initilizaed to {0} or how should this work wont it be garbage until assigned?

    char controllerTypeString[64];
    char controllerSDL_GUID_string[128]; //TODO is this a practical way to initialize this in memory?

};

extern struct APPLICATION_STATE g_ApplicationState;



#endif


