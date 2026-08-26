#include "application/buttonlist.h"

#include <stdlib.h>
#include <string.h>



int populateProfile(struct ControllerButton* arrayOfControllerButtons, struct Profile* profile)
{
    //create the list of bindings set all to default as first
    profile->bindings = malloc(sizeof(struct Binding) * 21);
    if (!profile->bindings) return -1;

    
    for(int i=0; i<21; i++) //TODO PROBLEM well start with just 12 buttons
    {
        profile->bindings[i].ptrToAControllerButton = &arrayOfControllerButtons[i]; //set that the corresponding member of the controller button array
        profile->bindings[i].stringThatIsTheKeyTheButtonIsBindedTo = "DEFAULT";
    }

    //profile->bindings = controllerBindings; //PROBLEM TODO how does this work with pointer decaying?? were saying its equal to a *controller its equal to an array? or the address of the first member of the array
    strcpy(profile->name, "Default Profile");   //PROBLEM TODO not sure if this is the best way to do this

    return 0; //or return the length of bindings or something idk
}


int parse_buttonlist(const char *path, struct ControllerButton *out, int max)
{
    FILE *f = fopen(path, "r");
    if (!f) return -1;

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), f) && count < max) {
        if (line[0] == '#' || line[0] == '\n')
            continue;

        struct ControllerButton *b = &out[count];
        char type_str[16];
        char bitmask_str[16];

        sscanf(line,
            "%31s %d %15s %15s %d %d",
            b->name,
            &b->id,
            type_str,
            bitmask_str,
            &b->axis_min,
            &b->axis_max
        );

        if (strcmp(type_str, "button") == 0) {
            b->type = BTN_BUTTON;
            sscanf(bitmask_str, "%x", &b->bitmask);
        } else {
            b->type = BTN_AXIS;
            b->bitmask = 0;
        }

        count++;
    }

    fclose(f);
    return count;
}



int create_bindinglist_from_profile(const char *path, struct ControllerButton *out, int max)
{
    FILE *f = fopen(path, "r");
    if (!f) return -1;

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), f) && count < max) {
        if (line[0] == '#' || line[0] == '\n')
            continue;

        struct ControllerButton *b = &out[count];
        char type_str[16];
        char bitmask_str[16];

        sscanf(line,
            "%31s %d %15s %15s %d %d",
            b->name,
            &b->id,
            type_str,
            bitmask_str,
            &b->axis_min,
            &b->axis_max
        );

        if (strcmp(type_str, "button") == 0) {
            b->type = BTN_BUTTON;
            sscanf(bitmask_str, "%x", &b->bitmask);
        } else {
            b->type = BTN_AXIS;
            b->bitmask = 0;
        }

        count++;
    }

    fclose(f);
    return count;
}