#include "application/application_manager.h"




/* Global Application state (singleton) */ 
struct APPLICATION_STATE g_ApplicationState = {
    .currentPanel= 2, //0=gui, 1=preset, 2=editor
    .cursorPositionRow = 6,        // start on F10
    .cursorPositionColumn=0,
    .cursorFlashingState = false,
    .lastFlashToggleTime = 0,
    .currentPositionInEditorList =0,

    .currentSelectedProfile = "data/profiles/xbox360example.preset", //TODO define this path with a global var 


    .controllerConnected = false,

    .controllerTypeDetected = CONTROLLER_TYPE_DS4
};

