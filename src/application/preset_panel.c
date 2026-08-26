#include "application/preset_panel.h"

#include <stdbool.h>
#include "render/draw.h"
#include "globals.h"



/* Global GUI state (singleton) */
struct PRESET_PANEL_STATE g_PresetPanelState = {
    .cursorPosition = 0,        // start on F10
    .cursorFlashingState = false,
    .lastFlashToggleTime = 0
};


void preset_panel_drawing_tree() //FFS just clear the whole screen this is is ridiclous
{
    //MAINFRAME    
    draw_rounded_rectangle(20, 20, (WINDOW_WIDTH)-60, (WINDOW_HEIGHT)-60, 10, 2, COLOR_GREEN);
    //TOPCENTER
    draw_text_blazing("PRESETS",  640-((7*12)/2), 40);

    //INNER FRAME
    draw_rectangle_top_left(80, 80, (WINDOW_WIDTH)-200, 40, COLOR_GREEN, 1, NOT_FILLED); //ROW 0 X=80 =80
        draw_rectangle_top_left(80, 80, 300, 40, COLOR_GREEN, 1, NOT_FILLED); //preset name
        
        draw_rectangle_top_left(860, 80, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //load
        draw_rectangle_top_left(960, 80, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //edit
        draw_rectangle_top_left(1060, 80, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //delete 
    
    
    draw_rectangle_top_left(80, 120, (WINDOW_WIDTH)-200, 40, COLOR_GREEN, 1, NOT_FILLED); //ROW 1 row1.y = row0.y + 40
        draw_rectangle_top_left(80, 120, 300, 40, COLOR_GREEN, 1, NOT_FILLED);

        draw_rectangle_top_left(860, 120, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //load
        draw_rectangle_top_left(960, 120, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //edit
        draw_rectangle_top_left(1060, 120, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //delete 
    
    
    draw_rectangle_top_left(80, 160, (WINDOW_WIDTH)-200, 40, COLOR_GREEN, 1, NOT_FILLED); //ROW 2
        draw_rectangle_top_left(80, 160, 300, 40, COLOR_GREEN, 1, NOT_FILLED);

        draw_rectangle_top_left(860, 160, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //load
        draw_rectangle_top_left(960, 160, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //edit
        draw_rectangle_top_left(1060, 160, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //delete 

    draw_rectangle_top_left(80, 200, (WINDOW_WIDTH)-200, 40, COLOR_GREEN, 1, NOT_FILLED); 
        draw_rectangle_top_left(80, 200, 300, 40, COLOR_GREEN, 1, NOT_FILLED);

        draw_rectangle_top_left(860, 200, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //load
        draw_rectangle_top_left(960, 200, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //edit
        draw_rectangle_top_left(1060, 200, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //delete 

     draw_rectangle_top_left(80, 240, (WINDOW_WIDTH)-200, 40, COLOR_GREEN, 1, NOT_FILLED);
        draw_rectangle_top_left(80, 240, 300, 40, COLOR_GREEN, 1, NOT_FILLED);

        draw_rectangle_top_left(860, 240, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //load
        draw_rectangle_top_left(960, 240, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //edit
        draw_rectangle_top_left(1060, 240, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //delete 



    switch(g_PresetPanelState.cursorPosition) 
    {
        case 0: //top left
        case 1:
        case 2: 
            //clear_rectangle_within_drawContext(28, 27, 204, 86); //TODO should we clear before or after?

            // draw_rounded_rectangle(30, 30, 200, 80, 10, 1,  COLOR_GREEN);
            // draw_text_blazing("F10: EXIT",  35, 35); //top left options
            // draw_text_blazing("F1: LOAD PRESET",  35, 49); //top left options
            // draw_text_blazing("F2: VIEW PRESET",  35, 63);
            // draw_text_blazing("F3: TOOLS",  35, 77); //++14
            break;

        default:
            break;
    }
}