#include "application/editor.h"

#include <stdbool.h>
#include "render/draw.h"
#include "globals.h"

#include "application/gui.h" //TODO PROBLEM I dont wanna have a specific input handler for cursor position, list position, flashing
#include "application/application_manager.h"
//cursor etc eachly  unique for each panel thats stupid they should all just use the same one and logic will dictate its functionality per each panel




void editor_panel_init()
{
    // g_EditorPanelData.currentSelectedProfile = g_ApplicationState.profile5; //Selecting Profile 5 for now //TODO moved this to g_ApplicationState this can be removed
}


void editor_panel_drawing_tree() //FFS just clear the whole screen this is is ridiclous
{
    //MAINFRAME    
    draw_rounded_rectangle(20, 20, (WINDOW_WIDTH)-60, (WINDOW_HEIGHT)-60, 10, 2, COLOR_GREEN);
    //TOPCENTER
    draw_text_blazing("EDITOR",  640-((6*12)/2), 40);

    
    draw_rounded_rectangle(80, 80, 300, 200, 10, 1, COLOR_GREEN); //inside this rounded rect will have options
    draw_rectangle_top_left(80+10, 100, 300-20, 80, COLOR_GREEN, 1, NOT_FILLED); //new
    draw_text_blazing("NEW",  210, 110);

    draw_rectangle_top_left(80+10, 140, 300-20, 80, COLOR_GREEN, 1, NOT_FILLED); //edit
    draw_text_blazing("EDIT",  204, 150);
    
    draw_rectangle_top_left(80+10, 180, 300-20, 80, COLOR_GREEN, 1, NOT_FILLED); //load
    draw_text_blazing("LOAD",  204, 190);
    //draw_rectangle_top_left(80+10, 220, 300-20, 80, COLOR_GREEN, 1, NOT_FILLED); //style (Implied button??)
    draw_text_blazing("SAVE",  204, 230);

    draw_rounded_rectangle(80, 320, 300, 200, 10, 1, COLOR_GREEN);
    
    draw_rectangle_top_left(80+10, 340, 300-20, 80, COLOR_GREEN, 1, NOT_FILLED); //home
    draw_text_blazing("HOME",  204, 350);
    
    draw_rectangle_top_left(80+10, 380, 300-20, 80, COLOR_GREEN, 1, NOT_FILLED); //presets
    draw_text_blazing("PRESETS",  188, 390);
    
    draw_rectangle_top_left(80+10, 420, 300-20, 80, COLOR_GREEN, 1, NOT_FILLED); //other
     draw_text_blazing("OTHER",  196, 430);
    
    
    
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200 , 80, 600, 520, COLOR_GREEN, 1, NOT_FILLED); //list of buttons on controller
    
    //each and every button listing 
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 80, 600, 40, COLOR_GREEN, 1, FILLED);
        draw_text_blazing(g_ApplicationState.currentSelectedProfile->name, (WINDOW_WIDTH/2) -200, 80); //TODO needa name change here
    
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 120, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 160, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 200, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 240, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 280, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 320, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 360, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 400, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 440, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 480, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 520, 600, 40, COLOR_GREEN, 1, NOT_FILLED);
    draw_rectangle_top_left((WINDOW_WIDTH/2) -200, 560, 600, 40, COLOR_GREEN, 1, NOT_FILLED);



    //TODO you need to put this in an if block aka If there is a current profile selected then execute this code otherwise its gonna seg fault
    int currentYvalue = 126;
    for (int i = g_ApplicationState.currentPositionInEditorList; i < 12 + g_ApplicationState.currentPositionInEditorList; i++)
    {
        struct ControllerButton *button = &g_ApplicationState.currentSelectedProfile->arrayOfControllerButton[i];

        draw_text_blazing(button->name, (WINDOW_WIDTH/2) - 200 + 8, currentYvalue);

        if (g_ApplicationState.currentlyRebindingControllerButton && button == g_ApplicationState.currentSelectedButtonInCurrentSelectedProfile)
        {
            draw_text_blazing("PRESS KEY TO BIND...", (WINDOW_WIDTH/2) + 8, currentYvalue);
        }
        else
        {
            draw_text_blazing(button->key_that_its_binded_to, (WINDOW_WIDTH/2) + 8, currentYvalue);
        }

        currentYvalue += 40;
    }
        
    


}