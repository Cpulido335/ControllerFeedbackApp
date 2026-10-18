#include "input/input_controller.h"


#include <windows.h>
#include "xinput.h"

#include "application/application_manager.h"


void poll_controller() //polls controller, relays controller state to g_ApplicationState
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