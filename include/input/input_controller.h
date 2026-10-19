#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <SDL3/SDL.h>


void poll_controller();


enum ControllerType detect_controller(SDL_JoystickID id);



#endif