#ifndef APPLICATION_H
#define APPLICATION_H

#include <windows.h>


struct Application {
    HINSTANCE hInstance;
    HWND windowHandle;  

    char *windowTitle;
    int windowWidth, windowHeight;
};


void application_init(struct Application* app, HINSTANCE hInstance);
HWND Application_CreateWindow(struct Application* app);
void application_update();
void application_destroy();


#endif
