#include "application/application_manager.h"




/* Global Application state (singleton) */ 
struct APPLICATION_STATE g_ApplicationState = {
    .currentPanel= 2, //0=gui, 1=preset, 2=editor
    .cursorPosition = 8,        // start on F10
    .cursorFlashingState = false,
    .lastFlashToggleTime = 0,
    .currentPositionInEditorList =0 
    
};

