#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <SDL3/SDL.h>


void poll_controller();
void register_controller_sdl();
enum ControllerType detect_controller(SDL_JoystickID id);
void register_gamepad_type(SDL_GamepadType gamepadType);
void handle_joystick_input();


#endif