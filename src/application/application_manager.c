#include "application/application_manager.h"




/* Global Application state (singleton) */ 
struct APPLICATION_STATE g_ApplicationState = {
    .currentPanel= 0, //0=gui, 1=preset, 2=editor //TODO not even sure if these numbers are right
    .cursorPositionRow = 1,        // start on F10
    .cursorPositionColumn=0,
    .cursorFlashingState = false,
    .lastFlashToggleTime = 0,
    .currentPositionInEditorList =0,


    .controllerConnected = false,

    .controllerTypeDetected = CONTROLLER_TYPE_OTHER,

    .currentlyRebindingControllerButton = false,
    .quit = false
};

