#ifndef BUTTONLIST_H
#define BUTTONLIST_H

#include <stdio.h>
#include <string.h>

enum ButtonType {
    BTN_BUTTON,
    BTN_AXIS
};

struct ControllerButton {
    char        name[32];
    int         id;
    enum ButtonType  type;
    unsigned int bitmask;   // 0 if not used
    int         axis_min;   // ignored for buttons
    int         axis_max;
    char        key_that_its_binded_to[32];
};


struct nlist { /* table entry: */ //TODO PUT THIS IN UTIL MAYBE? TODO where does this even get used???
    struct nlist *next; /* next entry in chain */
    struct ControllerButton* ptrToAControllerButton; /* defined name */
    char *correspondingBinding; //CorrespondingBindingID?
};



//we need some struct that is a list of mappings from string id to string binded_key
// struct Binding {
//     struct ControllerButton*  ptrToAControllerButton;
//     char *stringThatIsTheKeyTheButtonIsBindedTo;
// };

struct Profile { //so your idea is that a Profile has a member that is a list of controller buttons?
    char name[128]; 
    // struct Binding* bindings; //TODO PROBLEM, is this heap alloc?
    struct ControllerButton  *arrayOfControllerButton; //21 keys 
};

// int populateProfile(struct ControllerButton* arrayOfControllerButtons, struct Profile* profile);

// struct nlist createnlist() //TODO PROBLEM unused get rid of this when youre done using as an example
// {
//     struct ControllerButton cb;
//     struct ControllerButton cb = {"cb", 12, 1, 0x0001, 0, 255};

//     struct nlist* firstNode; 
//     struct nlist* secondNode;
//     struct nlist firstNode = { &secondNode,  &cb, "KB_ENTER", };
// }


int parse_buttonlist(const char *path, struct ControllerButton *out, int max);
void create_profile_from_preset_filepath(const char *path, struct ControllerButton *buttons, int max, struct Profile *profile,  char* profile_name);

// int create_bindinglist_from_profile(const char *path, struct ControllerButton *out, int max); //TODO PROBLEM unused so far


#endif 
