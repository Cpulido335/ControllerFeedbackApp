#include "input/input.h"

#include <windows.h>

#include "application/gui.h" //TODO not sure if this how I want to architect this
#include "application/application_manager.h"
#include "application/buttonlist.h"
#include "globals.h"

#include <stdio.h> //TODO for deubbing handle_input function REMOVE


struct keyState getKeyState(uint32_t keycode)
{
    return staticKeyboardInputMap.keys[keycode]; //return keyState
}

bool isKeyPressed(uint32_t keycode)
{
    return staticKeyboardInputMap.keys[keycode].isDown;
}

bool isKeyReleased(uint32_t keycode)
{
    return !staticKeyboardInputMap.keys[keycode].isDown;
}

bool wasKeyPressed(uint32_t keycode)
{
    return ((!staticKeyboardInputMap.keys[keycode].wasDown) && (staticKeyboardInputMap.keys[keycode].isDown)); //TODO idek
}

void input_process_keyboard_input(uint32_t VKCode, bool wasDown, bool isDown)
{
    if(wasDown != isDown) //if wasDown is not equal to isDown then there has been a change in the state of our key and we need to process it
    {
        if(VKCode >= 'A' && VKCode <= 'Z')
        {
            uint32_t jahKeycode = VKCode - 'A';
            staticKeyboardInputMap.keys[jahKeycode].isDown = isDown;
            staticKeyboardInputMap.keys[jahKeycode].wasDown = wasDown;
        }
        else if (VKCode == VK_UP) //TODO WTF USE A SWITCH 
        {
            staticKeyboardInputMap.keys[DC_UP].isDown = isDown;
            staticKeyboardInputMap.keys[DC_UP].wasDown = wasDown;
        }
        else if (VKCode == VK_DOWN)
        {
            staticKeyboardInputMap.keys[DC_DOWN].isDown = isDown;
            staticKeyboardInputMap.keys[DC_DOWN].wasDown = wasDown;
        }
        else if (VKCode == VK_LEFT)
        {
            staticKeyboardInputMap.keys[DC_LEFT].isDown = isDown;
            staticKeyboardInputMap.keys[DC_LEFT].wasDown = wasDown;
        }
        else if (VKCode == VK_RIGHT)
        {
            staticKeyboardInputMap.keys[DC_RIGHT].isDown = isDown;
            staticKeyboardInputMap.keys[DC_RIGHT].wasDown = wasDown;
        }
        else if (VKCode >= '0' && VKCode <= '9')
        {
            uint32_t dc_keycode = VKCode - '0' + DC_0;
            staticKeyboardInputMap.keys[dc_keycode].isDown = isDown;
            staticKeyboardInputMap.keys[dc_keycode].wasDown = wasDown;
        }
        else if (VKCode == VK_OEM_MINUS)
        {
            staticKeyboardInputMap.keys[DC_MINUS].isDown = isDown;
            staticKeyboardInputMap.keys[DC_MINUS].wasDown = wasDown;
        }
        else if (VKCode == VK_OEM_PLUS)
        {
            staticKeyboardInputMap.keys[DC_PLUS].isDown = isDown;
            staticKeyboardInputMap.keys[DC_PLUS].wasDown = wasDown;
        }
        else if (VKCode == VK_SHIFT)
        {
            staticKeyboardInputMap.keys[DC_SHIFT].isDown = isDown;
            staticKeyboardInputMap.keys[DC_SHIFT].wasDown = wasDown;
        }
        else if (VKCode == VK_CONTROL)
        {
            staticKeyboardInputMap.keys[DC_CONTROL].isDown = isDown;
            staticKeyboardInputMap.keys[DC_CONTROL].wasDown = wasDown;
        }
        else if (VKCode == VK_MENU)
        {
            staticKeyboardInputMap.keys[DC_ALT].isDown = isDown;
            staticKeyboardInputMap.keys[DC_ALT].wasDown = wasDown;
        }
        else if (VKCode == VK_SPACE)
        {
            staticKeyboardInputMap.keys[DC_SPACE].isDown = isDown;
            staticKeyboardInputMap.keys[DC_SPACE].wasDown = wasDown;
        }
        else if (VKCode == VK_ESCAPE)
        {
            staticKeyboardInputMap.keys[DC_ESCAPE].isDown = isDown;
            staticKeyboardInputMap.keys[DC_ESCAPE].wasDown = wasDown;
        }
        else if (VKCode == VK_CAPITAL)
        {
            staticKeyboardInputMap.keys[DC_CAPSLOCK].isDown = isDown;
            staticKeyboardInputMap.keys[DC_CAPSLOCK].wasDown = wasDown;
        }
        else if (VKCode == VK_TAB)
        {
            staticKeyboardInputMap.keys[DC_TAB].isDown = isDown;
            staticKeyboardInputMap.keys[DC_TAB].wasDown = wasDown;
        }
        else if (VKCode == VK_RETURN)
        {
            staticKeyboardInputMap.keys[DC_ENTER].isDown = isDown;
            staticKeyboardInputMap.keys[DC_ENTER].wasDown = wasDown;
        }
        else if (VKCode == VK_BACK)
        {
            staticKeyboardInputMap.keys[DC_BACKSPACE].isDown = isDown;
            staticKeyboardInputMap.keys[DC_BACKSPACE].wasDown = wasDown;
        }
        else if (VKCode == VK_OEM_3)
        {
            staticKeyboardInputMap.keys[DC_TILDE].isDown = isDown;
            staticKeyboardInputMap.keys[DC_TILDE].wasDown = wasDown;
        }
    }
}

static bool prevEnter = false;

static bool enter_just_pressed()
{
    bool enter = isKeyPressed(DC_ENTER);
    bool justPressed = enter && !prevEnter;
    prevEnter = enter;
    return justPressed;
}


void handle_gui_input() //TODO change the name of this to "handle_application_input" maybe idk still dont know
{
    bool enter = enter_just_pressed();
    static bool prevS = false;
    static bool prevW = false;
    static bool prevDown = false; //up and down on keypad for scrolling through editor list
    static bool prevUp = false; //up and down on keypad for scrolling through editor list


    bool sDown = isKeyPressed(DC_S);
    bool wDown = isKeyPressed(DC_W);
    bool downArrow = isKeyPressed(DC_DOWN); //up and down on keypad for scrolling through editor list
    bool upArrow   = isKeyPressed(DC_UP);   //up and down on keypad for scrolling through editor list
    

  
    // S key: only trigger on DOWN edge
    if (sDown && !prevS)
    {
        if (g_ApplicationState.cursorPositionRow < HOME_NUM_ROWS-1)
            g_ApplicationState.cursorPositionRow++;
    }

    // W key: only trigger on DOWN edge
    if (wDown && !prevW)
    {
        if (g_ApplicationState.cursorPositionRow > 0)
            g_ApplicationState.cursorPositionRow--;
    }


    if (enter && g_ApplicationState.cursorPositionRow ==  1) //F1: LOAD PRESET"
    {
        g_ApplicationState.currentPanel = 1; 
        g_ApplicationState.cursorPositionColumn = 3; // set the column to the preset panel load column 
        g_ApplicationState.cursorPositionRow = 0;  
    }


    if (enter && g_ApplicationState.cursorPositionRow ==  2) //F2: EDITOR
    {
        g_ApplicationState.currentPanel = 1; //TODO I thought the editor was 1 not 2?????? im so confused
    }

    
    //Editor panel key list logic
    if (isKeyPressed(DC_0) /* && editor panel is being dispalyed */) 
    {
        //find the corresponding entry in Profile
    }


    if (isKeyPressed(DC_Y)) //switch viewed model to DS4 
    {
        g_ApplicationState.controllerTypeDetected = CONTROLLER_TYPE_DS4; 
    }

    if (isKeyPressed(DC_U))  //switch viewed model to XboxOne Controller
    {
        g_ApplicationState.controllerTypeDetected = CONTROLLER_TYPE_XBOX_ONE;
    }


    
    
    prevS = sDown;
    prevW = wDown;

    //printf("gGuiState.cursorPositionRow: %d\n", g_GuiState.cursorPositionRow);
}




//handles the input when the editor page is active
void handle_editor_input()
{
    bool enter = enter_just_pressed();

    static bool prevS = false;
    static bool prevW = false;
    static bool prevA = false;
    static bool prevD = false;
    static bool prevDown = false; //up and down on keypad for scrolling through editor list
    static bool prevUp = false; //up and down on keypad for scrolling through editor list

    bool sDown = isKeyPressed(DC_S);
    bool wDown = isKeyPressed(DC_W);
    bool aDown = isKeyPressed(DC_A); //TODO this is copy and pasted code for input edge detection there is for sure a much better way of doing this 
    bool dDown = isKeyPressed(DC_D);
    bool downArrow = isKeyPressed(DC_DOWN); //up and down on keypad for scrolling through editor list
    bool upArrow   = isKeyPressed(DC_UP);   //up and down on keypad for scrolling through editor list

    // S key: only trigger on DOWN edge
    if (sDown && !prevS)
    {
        if (g_ApplicationState.cursorPositionRow < EDITOR_NUM_ROWS-1)
            g_ApplicationState.cursorPositionRow++;
    }

    // W key: only trigger on DOWN edge
    if (wDown && !prevW)
    {
        if (g_ApplicationState.cursorPositionRow > 0)
            g_ApplicationState.cursorPositionRow--;
    }


    if (aDown && !prevA)
    {
        if (g_ApplicationState.cursorPositionColumn > 0)
            g_ApplicationState.cursorPositionColumn--;
    }


    if (dDown && !prevD)
    {
        if (g_ApplicationState.cursorPositionColumn < EDITOR_NUM_COLUMNS) //TODO don't think there's 10 columns (11 columns)
            g_ApplicationState.cursorPositionColumn++;
    }


     // Down arrow: increase because were scrolling down and its going DEEPER into the list currentPositionInList on DOWN edge
    if (downArrow && !prevDown &&  g_ApplicationState.currentPositionInEditorList < g_ApplicationState.currentEditorProfile->numButtons - 12) //TODO basically 9 is the maximum times we can scroll in the list before the depth is maxed out and scrolling at all after that will cause a seg fault because there is no more space in the editor list for additional entries
    { //in the above line you want to take the number of buttons in the currentEditorProfile and then subtract 12 because the editor list of buttons displays 12 button entries at a time, if you don't subrtract 12 and scroll to the bottom it will try to reach into unauthroized memory and seg fault
        g_ApplicationState.currentPositionInEditorList++;
    }

    // Up arrow: decrement currentPositionInList on DOWN edge
    if (upArrow && !prevUp && g_ApplicationState.currentPositionInEditorList > 0)
    {
        g_ApplicationState.currentPositionInEditorList--;
    }

    if (isKeyPressed(DC_ENTER) && g_ApplicationState.cursorPositionRow ==  2) //if the cursor is on the LOAD button in the editor panel and enter is pressed: switch to the preset panel and then the preset panels list view of presets with load highlighted
    {
        g_ApplicationState.currentPanel = 1; // switch to the preset panel
        g_ApplicationState.cursorPositionRow =  0; // TODO GO INTO THE LOAD ON THE ACTUAL LIST VIEW OF THE PRESETS 
        g_ApplicationState.cursorPositionColumn = 3; //3 is LOAD button column
    }


    if (isKeyPressed(DC_ENTER) && g_ApplicationState.cursorPositionRow ==  4) //if the cursor is on the home button in the editor panel and enter is pressed: switch to the home panel
    {
        g_ApplicationState.currentPanel = 0;
        g_ApplicationState.cursorPositionRow =  0; //after switching to home panel set cursor position to 0
    }


    if (isKeyPressed(DC_ENTER) && g_ApplicationState.cursorPositionRow ==  5) //if the cursor is on the PRESETS button in the editor panel and enter is pressed: switch to the PRESETS panel
    {
        g_ApplicationState.currentPanel = 1;
        g_ApplicationState.cursorPositionRow =  0; //after switching to preset panel set cursor position to 0
    }

    
    //Editor panel key list logic
    if (isKeyPressed(DC_0) /* && editor panel is being dispalyed */) 
    {
        //find the corresponding entry in Profile
    }



    prevS = sDown;
    prevW = wDown;
    prevA = aDown;
    prevD = dDown; 

    prevDown = downArrow;  //up and down on keypad for scrolling through editor list
    prevUp = upArrow;  //up and down on keypad for scrolling through editor list

    //printf("gGuiState.cursorPositionRow: %d\n", g_GuiState.cursorPositionRow);
}




void handle_preset_panel_input()
{
    bool enter = enter_just_pressed();

    static bool prevS = false;
    static bool prevW = false;
    static bool prevA = false;
    static bool prevD = false;
    static bool prevDown = false; //up and down on keypad for scrolling through editor list
    static bool prevUp = false; //up and down on keypad for scrolling through editor list


    bool sDown = isKeyPressed(DC_S);
    bool wDown = isKeyPressed(DC_W);
    bool aDown = isKeyPressed(DC_A);
    bool dDown = isKeyPressed(DC_D);
    bool downArrow = isKeyPressed(DC_DOWN); //up and down on keypad for scrolling through editor list
    bool upArrow   = isKeyPressed(DC_UP);   //up and down on keypad for scrolling through editor list



    // S key: only trigger on DOWN edge
    if (sDown && !prevS)
    {
        if (g_ApplicationState.cursorPositionRow < 99) //TODO make sure you fix this 99 is way more
            g_ApplicationState.cursorPositionRow++;
    }

    // W key: only trigger on DOWN edge
    if (wDown && !prevW)
    {
        if (g_ApplicationState.cursorPositionRow > 0)
            g_ApplicationState.cursorPositionRow--;
    }


    if (aDown && !prevA)
    {
        if (g_ApplicationState.cursorPositionColumn > 0)
            g_ApplicationState.cursorPositionColumn--;
    }


    if (dDown && !prevD)
    {
        if (g_ApplicationState.cursorPositionColumn < 10) //TODO don't think there's 10 columns (11 columns)
            g_ApplicationState.cursorPositionColumn++;
    }



    if (enter && g_ApplicationState.cursorPositionRow ==  1 && g_ApplicationState.cursorPositionColumn == 0) //if the cursor is on the home button in the editor panel and enter is pressed: switch to the home panel
    {
        g_ApplicationState.currentPanel = 0; //switch to home
        g_ApplicationState.cursorPositionRow =  0; //after switching to home panel set cursor position to 0
    }


    if (enter && g_ApplicationState.cursorPositionRow ==  2 && g_ApplicationState.cursorPositionColumn == 0) //if the cursor is on the editor button in the presets panel and enter is pressed: switch to the editor panel
    {
        g_ApplicationState.currentPanel = 2; //switch to editor panel
        g_ApplicationState.cursorPositionRow =  0; //after switching to the editor panel set cursor position to 0
    }

    
    
    //LOAD entries //////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (enter && g_ApplicationState.cursorPositionRow ==  0 && g_ApplicationState.cursorPositionColumn == 3) 
    {
        g_ApplicationState.currentPositionInEditorList = 0;
        g_ApplicationState.cursorPositionRow =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.cursorPositionColumn =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.currentEditorProfile = g_ApplicationState.profile1;
        g_ApplicationState.currentPanel = 2;
    }

    if (enter && g_ApplicationState.cursorPositionRow ==  1 && g_ApplicationState.cursorPositionColumn == 3) 
    {
        g_ApplicationState.currentPositionInEditorList = 0;
        g_ApplicationState.cursorPositionRow =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.cursorPositionColumn =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.currentEditorProfile = g_ApplicationState.profile2;
        g_ApplicationState.currentPanel = 2;
    }

    if (enter && g_ApplicationState.cursorPositionRow ==  2 && g_ApplicationState.cursorPositionColumn == 3) 
    {
        g_ApplicationState.currentPositionInEditorList = 0;
        g_ApplicationState.cursorPositionRow =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.cursorPositionColumn =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.currentEditorProfile = g_ApplicationState.profile3;
        g_ApplicationState.currentPanel = 2;
    }

    if (enter && g_ApplicationState.cursorPositionRow ==  3 && g_ApplicationState.cursorPositionColumn == 3) 
    {
        g_ApplicationState.currentPositionInEditorList = 0;
        g_ApplicationState.cursorPositionRow =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.cursorPositionColumn =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.currentEditorProfile = g_ApplicationState.profile4;
        g_ApplicationState.currentPanel = 2;
    }

    if (enter && g_ApplicationState.cursorPositionRow ==  4 && g_ApplicationState.cursorPositionColumn == 3) 
    {
        g_ApplicationState.currentPositionInEditorList = 0;
        g_ApplicationState.cursorPositionRow =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.cursorPositionColumn =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.currentEditorProfile = g_ApplicationState.profile5;
        g_ApplicationState.currentPanel = 2;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




    //EDIT entries ////////////////////////////////////////////////////////////////////////////////////////////////////////// TODO for now the edit buttons just do the exact same thing as the load buttons
    if (enter && g_ApplicationState.cursorPositionRow ==  0 && g_ApplicationState.cursorPositionColumn == 4) 
    {
        g_ApplicationState.currentPositionInEditorList = 0;
        g_ApplicationState.cursorPositionRow =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.cursorPositionColumn =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.currentEditorProfile = g_ApplicationState.profile1;
        g_ApplicationState.currentPanel = 2;
    }

    if (enter && g_ApplicationState.cursorPositionRow ==  1 && g_ApplicationState.cursorPositionColumn == 4) 
    {
        g_ApplicationState.currentPositionInEditorList = 0;
        g_ApplicationState.cursorPositionRow =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.cursorPositionColumn =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.currentEditorProfile = g_ApplicationState.profile2;
        g_ApplicationState.currentPanel = 2;
    }

    if (enter && g_ApplicationState.cursorPositionRow ==  2 && g_ApplicationState.cursorPositionColumn == 4) 
    {
        g_ApplicationState.currentPositionInEditorList = 0;
        g_ApplicationState.cursorPositionRow =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.cursorPositionColumn =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.currentEditorProfile = g_ApplicationState.profile3;
        g_ApplicationState.currentPanel = 2;
    }

    if (enter && g_ApplicationState.cursorPositionRow ==  3 && g_ApplicationState.cursorPositionColumn == 4) 
    {
        g_ApplicationState.currentPositionInEditorList = 0;
        g_ApplicationState.cursorPositionRow =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.cursorPositionColumn =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.currentEditorProfile = g_ApplicationState.profile4;
        g_ApplicationState.currentPanel = 2;
    }

    if (enter && g_ApplicationState.cursorPositionRow ==  4 && g_ApplicationState.cursorPositionColumn == 4) 
    {
        g_ApplicationState.currentPositionInEditorList = 0;
        g_ApplicationState.cursorPositionRow =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.cursorPositionColumn =  0; //before switching to editor panel set cursor position to 0
        g_ApplicationState.currentEditorProfile = g_ApplicationState.profile5;
        g_ApplicationState.currentPanel = 2;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    
    //prset panel panel key list logic //TODO THIS WAS JUST COPIED FROM OTHER FUNCTION IT HASNT BEEN TOUCHED YET 
    if (isKeyPressed(DC_0) /* && editor panel is being dispalyed */) 
    {
        //find the corresponding entry in Profile
    }


    prevS = sDown;
    prevW = wDown;
    prevA = aDown;
    prevD = dDown; 

    
}



void send_keyboard_input(WORD key, bool pressed)
{
    INPUT input = {0};

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = pressed ? 0 : KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}



WORD binding_to_vk(const char *binding)
{
    if (!binding || strncmp(binding, "KB_", 3) != 0)
        return 0; //"default" or invalid binding

    const char *key = binding + 3;

    //Letters and numbers
    if (strlen(key) == 1)
    {
        if (key[0] >= 'a' && key[0] <= 'z')
            return key[0] - 'a' + 'A';

        if (key[0] >= 'A' && key[0] <= 'Z')
            return key[0];

        if (key[0] >= '0' && key[0] <= '9')
            return key[0];
    }

    // Special keyboard keys
    if (!strcmp(key, "ENTER"))     return VK_RETURN;
    if (!strcmp(key, "SPACE"))     return VK_SPACE;
    if (!strcmp(key, "ESCAPE"))    return VK_ESCAPE;
    if (!strcmp(key, "TAB"))       return VK_TAB;
    if (!strcmp(key, "BACKSPACE")) return VK_BACK;
    if (!strcmp(key, "SHIFT"))     return VK_SHIFT;
    if (!strcmp(key, "CTRL"))      return VK_CONTROL;
    if (!strcmp(key, "ALT"))       return VK_MENU;
    if (!strcmp(key, "CAPSLOCK"))  return VK_CAPITAL;

    if (!strcmp(key, "UP"))        return VK_UP;
    if (!strcmp(key, "DOWN"))      return VK_DOWN;
    if (!strcmp(key, "LEFT"))      return VK_LEFT;
    if (!strcmp(key, "RIGHT"))     return VK_RIGHT;

    if (!strcmp(key, "DELETE"))    return VK_DELETE;
    if (!strcmp(key, "INSERT"))    return VK_INSERT;
    if (!strcmp(key, "HOME"))      return VK_HOME;
    if (!strcmp(key, "END"))       return VK_END;

    //F1 to F24
    if (key[0] == 'F')
    {
        char *end;
        long number = strtol(key + 1, &end, 10);

        if (end != key + 1 && *end == '\0' && number >= 1 && number <= 24)
            return VK_F1 + number - 1;
    }

    return 0;
}


SDL_GamepadButton controller_button_from_name(const char *name)
{
    if (!strcmp(name, "A") || !strcmp(name, "CROSS"))       return SDL_GAMEPAD_BUTTON_SOUTH; //Handle both PS style and Xbox Style might need some sort of flag here for ohter styles
    if (!strcmp(name, "B") || !strcmp(name, "CIRCLE"))      return SDL_GAMEPAD_BUTTON_EAST;
    if (!strcmp(name, "X") || !strcmp(name, "SQUARE"))      return SDL_GAMEPAD_BUTTON_WEST;
    if (!strcmp(name, "Y") || !strcmp(name, "TRIANGLE"))    return SDL_GAMEPAD_BUTTON_NORTH;

    if (!strcmp(name, "LB") || !strcmp(name, "L1"))         return SDL_GAMEPAD_BUTTON_LEFT_SHOULDER;
    if (!strcmp(name, "RB") || !strcmp(name, "R1"))         return SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER;

    if (!strcmp(name, "BACK") || !strcmp(name, "SHARE"))    return SDL_GAMEPAD_BUTTON_BACK;
    if (!strcmp(name, "START") || !strcmp(name, "OPTIONS")) return SDL_GAMEPAD_BUTTON_START;
    if (!strcmp(name, "GUIDE") || !strcmp(name, "PS"))      return SDL_GAMEPAD_BUTTON_GUIDE;

    if (!strcmp(name, "LSTICK_PRESS") || !strcmp(name, "L3")) return SDL_GAMEPAD_BUTTON_LEFT_STICK;
    if (!strcmp(name, "RSTICK_PRESS") || !strcmp(name, "R3")) return SDL_GAMEPAD_BUTTON_RIGHT_STICK;

    if (!strcmp(name, "DPAD_UP"))    return SDL_GAMEPAD_BUTTON_DPAD_UP;
    if (!strcmp(name, "DPAD_DOWN"))  return SDL_GAMEPAD_BUTTON_DPAD_DOWN;
    if (!strcmp(name, "DPAD_LEFT"))  return SDL_GAMEPAD_BUTTON_DPAD_LEFT;
    if (!strcmp(name, "DPAD_RIGHT")) return SDL_GAMEPAD_BUTTON_DPAD_RIGHT;

    if (!strcmp(name, "TOUCHPAD"))      return SDL_GAMEPAD_BUTTON_TOUCHPAD;
    if (!strcmp(name, "BACK_PADDLE_L")) return SDL_GAMEPAD_BUTTON_LEFT_PADDLE1;
    if (!strcmp(name, "BACK_PADDLE_R")) return SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1;

    return SDL_GAMEPAD_BUTTON_INVALID;
}



void process_controller_bindings(struct Profile *profile) //TODO this can be called in the main loop repeatedley
{
    static bool prevButtonDown[SDL_GAMEPAD_BUTTON_COUNT] = {0}; //entire array of booleans 'buttonDown' for debouncing all possible inputs of a gamepad

    if (!profile || !g_ApplicationState.current_gamepad) //TODO more explanatory error checking
        return;

    for (int i = 0; i < profile->numButtons; i++)
    {
        struct ControllerButton *button = &profile->arrayOfControllerButton[i];

        SDL_GamepadButton sdlButton = controller_button_from_name(button->name);

        if (sdlButton == SDL_GAMEPAD_BUTTON_INVALID)
            continue;

        bool down = SDL_GetGamepadButton(g_ApplicationState.current_gamepad, sdlButton);
        WORD vk = binding_to_vk(button->key_that_its_binded_to);

        if (vk && down != prevButtonDown[sdlButton])
            send_keyboard_input(vk, down);

        prevButtonDown[sdlButton] = down;
    }
}