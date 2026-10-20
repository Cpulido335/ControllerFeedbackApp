#include "input/input_controller.h"


#include <windows.h>
#include "xinput.h"

#include "application/application_manager.h"
#include <stdio.h>



void poll_controller() //polls controller, relays controller state to g_ApplicationState TODO this is the OLD xinput version this can be removed after SDL3 gamepad API is implmented
{
    DWORD dwResult_controller0;
    DWORD dwResult_controller1;
    DWORD dwResult_controller2;
    DWORD dwResult_controller3;    

        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        // Simply get the state of the controller from XInput.
        dwResult_controller0 = XInputGetState(0, &state);
        dwResult_controller1 = XInputGetState(1, &state);
        dwResult_controller2 = XInputGetState(2, &state);
        dwResult_controller3 = XInputGetState(3, &state);

        if( dwResult_controller0 == ERROR_SUCCESS ||
            dwResult_controller1 == ERROR_SUCCESS ||
            dwResult_controller2 == ERROR_SUCCESS ||
            dwResult_controller3 == ERROR_SUCCESS   ) //if any of the four possible xinput controllers are connected then set the flag to true
        {
            // Controller is connected
            g_ApplicationState.controllerConnected = true;
        } else
        {
            g_ApplicationState.controllerConnected = false;
        }
}



void register_controller_sdl()  //TODO also needs error handling
{
    if (!SDL_HasGamepad()) 
    {
        printf("No gamepads connected.\n");
        g_ApplicationState.controllerConnected = false;
        return;
    } //From here we know at least one gampepad is connected


    int count = 0;
    SDL_JoystickID *ids = SDL_GetGamepads(&count);
    SDL_Gamepad* gamepad = NULL;

    // Iterate over the list of gamepads
    for (int i = 0; i < count; i++) 
    {
        SDL_Gamepad* gamepd = SDL_OpenGamepad(ids[i]);
        if (gamepad == NULL) {
            gamepad = gamepd;
        }
        printf("Gamepad connected: %s\n", SDL_GetGamepadName(gamepd));
        
        
        // Close the other gamepads
        if (i > 0) {
            SDL_CloseGamepad(gamepd);
        }

        SDL_GamepadType type = SDL_GetGamepadType(gamepad);
        register_gamepad_type(type);

        SDL_JoystickID id = SDL_GetGamepadID(gamepad); // TODO is this a stack allocation?
        SDL_GUID controllerSDL_GUID = SDL_GetGamepadGUIDForID(id); ///we're passing a copy of the id to this function doesnt it need to be pointer just based on on how its a 
                                        //GUID? i thought GUID implys a specific instance on your machine of something in that case
                                        //it would to be a pointer to something that already exists and not a copy, the param is even called instance_ID 

        
        SDL_GUIDToString(controllerSDL_GUID, g_ApplicationState.controllerSDL_GUID_string, 128);    

    }

    if (!gamepad) {
        printf("Failed to open gamepad\n");
        return;
    }

     

}

//TODO needs error handling
void register_gamepad_type(SDL_GamepadType gamepadType) //TODO this function acts as a translator between SDL3's controller type enumeration and my own controller type enumeration, honestly i should just exclusively utilize SDL3's
{
     switch (gamepadType)
    {
        case SDL_GAMEPAD_TYPE_XBOXONE:
            g_ApplicationState.controllerTypeDetected = CONTROLLER_TYPE_XBOX_ONE;
            snprintf(g_ApplicationState.controllerTypeString, sizeof(g_ApplicationState.controllerTypeString), "XBOX ONE"); //TODO we could do this with array or const char* i guess ill just to array for now
            g_ApplicationState.controllerConnected = true;
            break;

        case SDL_GAMEPAD_TYPE_PS4:
            g_ApplicationState.controllerTypeDetected = CONTROLLER_TYPE_DS4;
            snprintf(g_ApplicationState.controllerTypeString, sizeof(g_ApplicationState.controllerTypeString), "DUALSHOCK 4"); //TODO we could do this with array or const char* i guess ill just to array for now
            g_ApplicationState.controllerConnected = true;
            break;

        default:
            g_ApplicationState.controllerTypeDetected = CONTROLLER_TYPE_OTHER;
            break;
    }
}

enum ControllerType detect_controller(SDL_JoystickID id) //TODO this isnt used anymore i dont think
{
    SDL_GamepadType type = SDL_GetGamepadTypeForID(id);

    switch (type)
    {
        case SDL_GAMEPAD_TYPE_XBOXONE:
            return CONTROLLER_TYPE_XBOX_ONE;

        case SDL_GAMEPAD_TYPE_PS4:
            return CONTROLLER_TYPE_DS4;

        default:
            return CONTROLLER_TYPE_OTHER;
    }
}