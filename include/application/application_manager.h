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


struct APPLICATION_STATE {
    int currentPanel;
    int cursorPositionRow;
    int cursorPositionColumn;
    bool cursorFlashingState;
    double lastFlashToggleTime;   // seconds

    //editor 
    int currentPositionInEditorList;
    //Editor panel specific button selected logic //if 0 is pressed editor list entry is selected, changes to rebind, 

    struct Profile *currentSelectedProfile; //TODO RENAME THESE ARE THE SAME THING AND CHANGE THE NAME OF currentSelectedProfile to currentSelectedProfileName or currentSelectedProfilePath whichever fits better because i forgot
    struct ControllerButton *currentSelectedButtonInCurrentSelectedProfile; //in the editor list the correspeonding button in the proifle would be the currently highlighed entry 

    //controller
    SDL_Gamepad *current_gamepad;
    bool controllerConnected;
    int controllerTypeDetected;


    char controllerTypeString[64];
    char controllerSDL_GUID_string[128]; //TODO is this a practical way to initialize this in memory?


    //controller axes
    int controllerLeftStickX;
    int controllerLeftStickY;
    
    int controllerRightStickX;
    int controllerRightStickY;

    int controllerLeftTrigger;
    int controllerRightTrigger;


    //controller buttons 
    bool controllerButtonNorth;                              
    bool controllerButtonEast;
    bool controllerButtonWest;
    bool controllerButtonSouth;

    bool controllerButtonBack;
    bool controllerButtonGuide;
    bool controllerButtonStart;

    bool controllerButtonLeftStick;
    bool controllerButtonRightStick;

    bool controllerButtonLeftShoulder;
    bool controllerButtonRightShoulder;

    bool controllerButtonDpadUp;
    bool controllerButtonDpadDown;
    bool controllerButtonDpadLeft;
    bool controllerButtonDpadRight;

    bool controllerButtonMisc1;

    bool controllerButtonRightPaddle1;
    bool controllerButtonLeftPaddle1;
    bool controllerButtonRightPaddle2;
    bool controllerButtonLeftPaddle2;

    bool controllerButtonTouchpad;

    bool controllerButtonMisc2;
    bool controllerButtonMisc3;
    bool controllerButtonMisc4;
    bool controllerButtonMisc5;
    bool controllerButtonMisc6;

    //Profiles
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

    bool currentlyRebindingControllerButton;
};

extern struct APPLICATION_STATE g_ApplicationState;


#endif


