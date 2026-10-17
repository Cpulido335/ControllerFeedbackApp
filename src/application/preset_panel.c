#include "application/preset_panel.h"

#include <stdbool.h>
#include <stdio.h>
#include "render/draw.h"
#include "globals.h"

#include "application/buttonlist.h"
#include <dirent.h> //POSIX library for reading directories



/* Global GUI state (singleton) */
struct PRESET_PANEL_STATE g_PresetPanelState = {
    .cursorPosition = 0,        // start on F10 //TODO can probably remove all this stuff the cursor stuff is handled in application state
    .cursorFlashingState = false,
    .lastFlashToggleTime = 0
};


void preset_panel_init()
{
    g_PresetPanelState.buttons1 = malloc(sizeof(struct ControllerButton) * 21); //TODO 21 buttons in a preset is still hardcoded fckn everywhere
    g_PresetPanelState.buttons2 = malloc(sizeof(struct ControllerButton) * 21);
    g_PresetPanelState.buttons3 = malloc(sizeof(struct ControllerButton) * 21);
    g_PresetPanelState.buttons4 = malloc(sizeof(struct ControllerButton) * 21);
    g_PresetPanelState.buttons5 = malloc(sizeof(struct ControllerButton) * 21);

    g_PresetPanelState.profile1 = malloc(sizeof(struct Profile));
    g_PresetPanelState.profile2 = malloc(sizeof(struct Profile));
    g_PresetPanelState.profile3 = malloc(sizeof(struct Profile));
    g_PresetPanelState.profile4 = malloc(sizeof(struct Profile));
    g_PresetPanelState.profile5 = malloc(sizeof(struct Profile));
}

void preset_panel_drawing_tree() //FFS just clear the whole screen this is is ridiclous
{
    //MAINFRAME    
    draw_rounded_rectangle(20, 20, (WINDOW_WIDTH)-60, (WINDOW_HEIGHT)-60, 10, 2, COLOR_GREEN);
    //TOPCENTER
    draw_text_blazing("PRESETS",  640-((7*12)/2), 40);

    //TOPLEFT
    draw_rounded_rectangle(30, 30, 200, 80, 10, 1,  COLOR_GREEN);
    draw_text_blazing("F10: EXIT",  35, 35); //top left options
    draw_text_blazing("F1: HOME",  35, 49); //top left options
    draw_text_blazing("F2: EDITOR",  35, 63);


    //INNER FRAME
    draw_rectangle_top_left(80, 160, (WINDOW_WIDTH)-200, 40, COLOR_GREEN, 1, NOT_FILLED); //ROW 0 X=80 =80
        draw_rectangle_top_left(80, 160, 300, 40, COLOR_GREEN, 1, NOT_FILLED); //preset name
            draw_text_blazing(g_PresetPanelState.profile1->name, 400, 170);
        draw_rectangle_top_left(860, 160, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //load
            draw_text_blazing("LOAD", 884, 170);
        draw_rectangle_top_left(960, 160, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //edit
            draw_text_blazing("EDIT", 984, 170);
        draw_rectangle_top_left(1060, 160, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //delete
            draw_text_blazing("DELETE", 1072, 170); 
    
    
    draw_rectangle_top_left(80, 200, (WINDOW_WIDTH)-200, 40, COLOR_GREEN, 1, NOT_FILLED); //ROW 1 row1.y = row0.y + 40
        draw_rectangle_top_left(80, 200, 300, 40, COLOR_GREEN, 1, NOT_FILLED);
            draw_text_blazing(g_PresetPanelState.profile2->name, 400, 210);
        draw_rectangle_top_left(860, 200, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //load
            draw_text_blazing("LOAD", 884, 210);
        draw_rectangle_top_left(960, 200, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //edit
            draw_text_blazing("EDIT", 984, 210);
        draw_rectangle_top_left(1060, 200, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //delete 
            draw_text_blazing("DELETE", 1072, 210);
    
    draw_rectangle_top_left(80, 240, (WINDOW_WIDTH)-200, 40, COLOR_GREEN, 1, NOT_FILLED); //ROW 2
        draw_rectangle_top_left(80, 240, 300, 40, COLOR_GREEN, 1, NOT_FILLED);
            draw_text_blazing(g_PresetPanelState.profile3->name, 400, 250);

        draw_rectangle_top_left(860, 240, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //load
            draw_text_blazing("LOAD", 884, 250);
        draw_rectangle_top_left(960, 240, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //edit
            draw_text_blazing("EDIT", 984, 250);
        draw_rectangle_top_left(1060, 240, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //delete
            draw_text_blazing("DELETE", 1072, 250); 

    draw_rectangle_top_left(80, 240, (WINDOW_WIDTH)-200, 40, COLOR_GREEN, 1, NOT_FILLED); 
        draw_rectangle_top_left(80, 280, 300, 40, COLOR_GREEN, 1, NOT_FILLED);
            draw_text_blazing(g_PresetPanelState.profile4->name, 400, 290);

        draw_rectangle_top_left(860, 280, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //load
            draw_text_blazing("LOAD", 884, 290);
        draw_rectangle_top_left(960, 280, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //edit
            draw_text_blazing("EDIT", 984, 290);
        draw_rectangle_top_left(1060, 280, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //delete 
            draw_text_blazing("DELETE", 1072, 290);

     draw_rectangle_top_left(80, 320, (WINDOW_WIDTH)-200, 40, COLOR_GREEN, 1, NOT_FILLED);
        draw_rectangle_top_left(80, 320, 300, 40, COLOR_GREEN, 1, NOT_FILLED);
            draw_text_blazing(g_PresetPanelState.profile5->name, 400, 330);


        draw_rectangle_top_left(860, 320, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //load
            draw_text_blazing("LOAD", 884, 330);
        draw_rectangle_top_left(960, 320, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //edit
            draw_text_blazing("EDIT", 984, 330);
        draw_rectangle_top_left(1060, 320, 100, 40, COLOR_GREEN, 1, NOT_FILLED); //delete 
            draw_text_blazing("DELETE", 1072, 330);



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


int load_presets(const char* presets_folder_filepath) //TODO for this we're gonna need the posix library 
{
    printf("%s\n\n", presets_folder_filepath);

    DIR *directory;
    struct dirent *entry;

    directory = opendir(presets_folder_filepath);

    if (directory == NULL)
    {
        printf("Error opening directory!\n"); //TODO isnt there something else other than printf thats more practical for error messages?
        return 1;
    }


    //the first part of each profiles file path will just be the path to the directory
    char profilepath1[128];
    char profilepath2[128];
    char profilepath3[128];
    char profilepath4[128];
    char profilepath5[128];

    strcpy(profilepath1, presets_folder_filepath);
    strcpy(profilepath2, presets_folder_filepath);
    strcpy(profilepath3, presets_folder_filepath);
    strcpy(profilepath4, presets_folder_filepath);
    strcpy(profilepath5, presets_folder_filepath);

    //The program will only use 5 presets, using more than 5 presets in memory is more complicated than the program needs to be.
    //dont need to make arrays for these 2 just gonna use a switch statement and have the profile structs numbered 1-5 in memory
    int i = 1; //TODO starting at 1 and going to 5 because the profilepaths start at 1 and switch statement starts at 1 so its neater 
    while ((entry = readdir(directory)) != NULL && i <= 5) //TODO harcoded 5 for five presets in the directory
    {   
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) { //the first 2 in directory are '.' and '..' we need to skip over these 
            continue;
        }



        switch(i)
        {
            case 1:
                strcat(profilepath1, "/");
                strcat(profilepath1, entry->d_name);
                printf("%s\n", profilepath1);
                
                create_profile_from_preset_filepath(profilepath1, g_PresetPanelState.buttons1, 21, g_PresetPanelState.profile1, entry->d_name);
                break;
            case 2:
                strcat(profilepath2, "/");
                strcat(profilepath2, entry->d_name);
                printf("%s\n", profilepath2);
                printf("entry->d_name %s\n", entry->d_name);
                
                create_profile_from_preset_filepath(profilepath2, g_PresetPanelState.buttons2, 21, g_PresetPanelState.profile2, entry->d_name);
                break;
            case 3:
                strcat(profilepath3, "/");
                strcat(profilepath3, entry->d_name);
                printf("%s\n", profilepath3);
                
                create_profile_from_preset_filepath(profilepath3, g_PresetPanelState.buttons3, 21, g_PresetPanelState.profile3, entry->d_name);
                break;
            case 4:
                strcat(profilepath4, "/");
                strcat(profilepath4, entry->d_name);
                printf("%s\n", profilepath4);
                
                
                create_profile_from_preset_filepath(profilepath4, g_PresetPanelState.buttons4, 21, g_PresetPanelState.profile4, entry->d_name);
                break;     
            case 5:
                strcat(profilepath5, "/");
                strcat(profilepath5, entry->d_name);
                printf("%s\n", profilepath5);
                
                create_profile_from_preset_filepath(profilepath5, g_PresetPanelState.buttons5, 21, g_PresetPanelState.profile5, entry->d_name);
                break; 
        }

        i++;
    }
    
}