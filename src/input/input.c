#include "input/input.h"

#include <windows.h>

#include "application/gui.h" //TODO not sure if this how I want to architect this
#include "application/application_manager.h"

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


void handle_gui_input() //TODO change the name of this to "handle_application_input" maybe idk still dont know
{
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
        if (g_ApplicationState.cursorPosition < 9)
            g_ApplicationState.cursorPosition++;
    }

    // W key: only trigger on DOWN edge
    if (wDown && !prevW)
    {
        if (g_ApplicationState.cursorPosition > 0)
            g_ApplicationState.cursorPosition--;
    }


     // Down arrow: increase because were scrolling down and its going DEEPER into the list currentPositionInList on DOWN edge
    if (downArrow && !prevDown &&  g_ApplicationState.currentPositionInEditorList < 9) //TODO basically 9 is the maximum times we can scroll in the list before the depth is maxed out and scrolling at all after that will cause a seg fault because there is no more space in the editor list for additional entries
    {
        g_ApplicationState.currentPositionInEditorList++;
    }

    // Up arrow: decrement currentPositionInList on DOWN edge
    if (upArrow && !prevUp && g_ApplicationState.currentPositionInEditorList > 0)
    {
        g_ApplicationState.currentPositionInEditorList--;
    }

    if (isKeyPressed(DC_ENTER) && g_ApplicationState.cursorPosition ==  3) 
    {
        g_ApplicationState.currentPanel = 2; //TODO I thought the editor was 1 not 2?????? im so confused
    }

    
    //Editor panel key list logic
    if (isKeyPressed(DC_0) /* && editor panel is being dispalyed */) 
    {
        //find the corresponding entry in Profile
    }



    prevS = sDown;
    prevW = wDown;

    prevDown = downArrow;  //up and down on keypad for scrolling through editor list
    prevUp = upArrow;  //up and down on keypad for scrolling through editor list

    //printf("gGuiState.cursorPosition: %d\n", g_GuiState.cursorPosition);
}




//handles the input when the editor page is active
void handle_editor_input()
{
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
        if (g_ApplicationState.cursorPosition < 9)
            g_ApplicationState.cursorPosition++;
    }

    // W key: only trigger on DOWN edge
    if (wDown && !prevW)
    {
        if (g_ApplicationState.cursorPosition > 0)
            g_ApplicationState.cursorPosition--;
    }


     // Down arrow: increase because were scrolling down and its going DEEPER into the list currentPositionInList on DOWN edge
    if (downArrow && !prevDown &&  g_ApplicationState.currentPositionInEditorList < 9) //TODO basically 9 is the maximum times we can scroll in the list before the depth is maxed out and scrolling at all after that will cause a seg fault because there is no more space in the editor list for additional entries
    {
        g_ApplicationState.currentPositionInEditorList++;
    }

    // Up arrow: decrement currentPositionInList on DOWN edge
    if (upArrow && !prevUp && g_ApplicationState.currentPositionInEditorList > 0)
    {
        g_ApplicationState.currentPositionInEditorList--;
    }

    if (isKeyPressed(DC_ENTER) && g_ApplicationState.cursorPosition ==  2) //if the cursor is on the LOAD button in the editor panel and enter is pressed: switch to the preset panel and then the preset panels list view of presets with load highlighted
    {
        g_ApplicationState.currentPanel = 1; // switch to the preset panel
        g_ApplicationState.cursorPosition =  0; // TODO GO INTO THE LOAD ON THE ACTUAL LIST VIEW OF THE PRESETS 
    }


    if (isKeyPressed(DC_ENTER) && g_ApplicationState.cursorPosition ==  4) //if the cursor is on the home button in the editor panel and enter is pressed: switch to the home panel
    {
        g_ApplicationState.currentPanel = 0;
        g_ApplicationState.cursorPosition =  0; //after switching to home panel set cursor position to 0
    }


    if (isKeyPressed(DC_ENTER) && g_ApplicationState.cursorPosition ==  5) //if the cursor is on the PRESETS button in the editor panel and enter is pressed: switch to the PRESETS panel
    {
        g_ApplicationState.currentPanel = 1;
        g_ApplicationState.cursorPosition =  0; //after switching to preset panel set cursor position to 0
    }

    
    //Editor panel key list logic
    if (isKeyPressed(DC_0) /* && editor panel is being dispalyed */) 
    {
        //find the corresponding entry in Profile
    }



    prevS = sDown;
    prevW = wDown;

    prevDown = downArrow;  //up and down on keypad for scrolling through editor list
    prevUp = upArrow;  //up and down on keypad for scrolling through editor list

    //printf("gGuiState.cursorPosition: %d\n", g_GuiState.cursorPosition);
}




void handle_preset_panel_input()
{
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
        if (g_ApplicationState.cursorPosition < 99) //TODO make sure you fix this 99 is way more
            g_ApplicationState.cursorPosition++;
    }

    // W key: only trigger on DOWN edge
    if (wDown && !prevW)
    {
        if (g_ApplicationState.cursorPosition > 0)
            g_ApplicationState.cursorPosition--;
    }


     // Down arrow: increase because were scrolling down and its going DEEPER into the list currentPositionInList on DOWN edge
    if (downArrow && !prevDown &&  g_ApplicationState.currentPositionInEditorList < 99) //TODO FIX IT HERE TOObasically 9 is the maximum times we can scroll in the list before the depth is maxed out and scrolling at all after that will cause a seg fault because there is no more space in the editor list for additional entries
    {
        g_ApplicationState.currentPositionInEditorList++;
    }

    // Up arrow: decrement currentPositionInList on DOWN edge
    if (upArrow && !prevUp && g_ApplicationState.currentPositionInEditorList > 0)
    {
        g_ApplicationState.currentPositionInEditorList--;
    }

    if (isKeyPressed(DC_ENTER) && g_ApplicationState.cursorPosition ==  1) //if the cursor is on the home button in the editor panel and enter is pressed: switch to the home panel
    {
        g_ApplicationState.currentPanel = 0; //switch to home
        g_ApplicationState.cursorPosition =  0; //after switching to home panel set cursor position to 0
    }


    if (isKeyPressed(DC_ENTER) && g_ApplicationState.cursorPosition ==  2) //if the cursor is on the editor button in the presets panel and enter is pressed: switch to the editor panel
    {
        g_ApplicationState.currentPanel = 2; //switch to editor panel
        g_ApplicationState.cursorPosition =  0; //after switching to the editor panel set cursor position to 0
    }

    
    //prset panel panel key list logic //TODO THIS WAS JUST COPIED FROM OTHER FUNCTION IT HASNT BEEN TOUCHED YET 
    if (isKeyPressed(DC_0) /* && editor panel is being dispalyed */) 
    {
        //find the corresponding entry in Profile
    }



    prevS = sDown;
    prevW = wDown;

    prevDown = downArrow;  //up and down on keypad for scrolling through editor list
    prevUp = upArrow;  //up and down on keypad for scrolling through editor list

    //printf("gGuiState.cursorPosition: %d\n", g_GuiState.cursorPosition);
}