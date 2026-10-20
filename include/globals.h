#ifndef GLOBALS_H
#define GLOBALS_H


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define TARGET_FPS 60
#define TARGET_FRAME_TIME (1.0 / TARGET_FPS)


#define IMG_FILEPATH_FONT_DOS "assets/dos_font_bgblack.bmp"      //"assets/dos_bitmap.bmp"
#define IMG_FILEPATH_FONT_BIG "assets/fontBottomRowF.bmp"       //IDEA for transparency, IF A PIXEL IS BLACK, then dont blit it, then we can have text over graphics
#define IMG_FILEPATH_FONT_C64 "assets/commodore64-blackbg-bmp.bmp"
#define IMG_FILEPATH_FONT_C64_SMALL "assets/c64-12-16-16.bmp"


// //Colors for draw.h
// #define COLOR_RED 0xFF0000
// #define COLOR_BLUE 0x0000FF
// #define COLOR_GREEN 0x00FF00

// Fully opaque colors (A = 0xFF)
#define COLOR_RED   0xFFFF0000  // AARRGGBB
#define COLOR_GREEN 0xFF00FF00
#define COLOR_BLUE  0xFF0000FF
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0xFF000000



//cursor
#define CURSOR_FLASH_PERIOD 0.5   // seconds (2 Hz blink)


#define HOME_NUM_ROWS   4
#define HOME_NUM_COLUMNS 1
#define EDITOR_NUM_ROWS 7
#define EDITOR_NUM_COLUMNS 1
#define PRESET_PANEL_NUM_ROWS 5
#define PRESET_PANEL_NUM_COLUMNS 6

#define XBOX_ONE_CONTROLLER_FILEPATH "assets/xbox_one_controller_mesh.fbx"
#define DS4_CONTROLLER_FILEPATH "assets/dualshock4_controller_mesh.fbx"

#endif