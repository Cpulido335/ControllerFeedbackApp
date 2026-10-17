#include "application/buttonlist.h"

#include <stdlib.h>
#include <string.h>


int parse_buttonlist(const char *path, struct ControllerButton *out, int max) //TODO name this function to something better
{
    FILE *fileptr = fopen(path, "r");
    if (!fileptr) return -1;

    char line[256];
    int count = 0;

    while (count < max && fgets(line, sizeof(line), fileptr))
    {
        if (line[0] == '#' || line[0] == '\n')
            continue;

        struct ControllerButton *button = &out[count];

        char type_str[16];
        char bitmask_str[16];
        char min_str[16];
        char max_str[16];
        char key_str[32];

        int fields = sscanf(line,
            "%31s %d %15s %15s %15s %15s %31s", //string format specificier
            button->name,
            &button->id,
            type_str,
            bitmask_str,
            min_str,
            max_str,
            button->key_that_its_binded_to
        );

        if (fields != 7) { //TODO this number 7 could change in the future
            fprintf(stderr, "Invalid line: %s", line);
            fclose(fileptr);
            return -1;
        }


        if (strcmp(type_str, "button") == 0) 
        {
            button->type = BTN_BUTTON;

            if (sscanf(bitmask_str, "%x",
                       &button->bitmask) != 1) {
                fclose(fileptr);
                return -1;
            }

            button->axis_min = 0;
            button->axis_max = 0;
        }
        else if (strcmp(type_str, "axis") == 0) 
        {
            button->type = BTN_AXIS;
            button->bitmask = 0;

            if (sscanf(min_str, "%d",
                       &button->axis_min) != 1 ||
                sscanf(max_str, "%d",
                       &button->axis_max) != 1) {
                fclose(fileptr);
                return -1;
            }
        }
        else 
        {
            fclose(fileptr);
            return -1;
        }

        //store key_str in your binding field here.
        // Exact assignment depends on its declared type.

        count++;
    }

    fclose(fileptr);
    return count;
}


//Takes in a an array of ControllerButtons modifys a Profile struct
void create_profile_from_preset_filepath(const char *path, struct ControllerButton *buttons, int max, struct Profile *profile, char* profile_name)
{
    //TODO we might be able to create the ControllerButton array with a heap allocation within the scope of this function but idk 
    parse_buttonlist(path, buttons, max);

    profile->arrayOfControllerButton = buttons;
    profile->name = profile_name;

    //get the filename from the path
}


