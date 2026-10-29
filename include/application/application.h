#ifndef APPLICATION_H
#define APPLICATION_H

#include <windows.h>


struct Application {
    HINSTANCE hInstance;
    HWND windowHandle;  

    char *windowTitle;
    int windowWidth, windowHeight;

    //bool isRunning
};


void Application_Init(struct Application* app, HINSTANCE hInstance);
HWND Application_CreateWindow(struct Application* app);
void application_update();


#endif
