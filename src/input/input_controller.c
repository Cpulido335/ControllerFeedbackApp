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
            break;

        case SDL_GAMEPAD_TYPE_PS4:
            g_ApplicationState.controllerTypeDetected = CONTROLLER_TYPE_DS4;
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