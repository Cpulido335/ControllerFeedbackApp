#ifndef DRAW_H
#define DRAW_H

#include <windows.h>
#include <stdint.h> 
#include <stdbool.h> 

#include "globals.h"
#include "geometry/cube.h"
#include "geometry/mesh.h"

//#include "fbx_ascii_parser.h" TODO this shouldnt be here

//for now we will initialize the frame buffer at global scope
struct drawContext {
    uint32_t framebuffer[WINDOW_WIDTH * WINDOW_HEIGHT];
};

extern struct drawContext gDrawContext; //The framebuffer will be global
extern BITMAPINFO bmi; //Same thing with the BMI definition it needs to be global

#define FILLED true
#define NOT_FILLED false


void copyBufferToWindow(HDC deviceContext, int windowWidth, int windowHeight);
void clear_drawContext(); //TODO what is a drawContext? whats the difference between a drawContext and a buffer?
void clear_rectangle_within_drawContext(int x, int y, int width, int depth);
void invert_rectangle_within_drawContext(int x, int y, int width, int depth);

void put_pixel(int x, int y, uint32_t color, int thickness);
void draw_line(float x0, float y0, float x1, float y1, uint32_t color, int thickness);
void draw_rectangle(int x, int y, int width, int height, uint32_t color, int thickness);
void draw_rectangle_top_left(int x, int y, int width, int height, uint32_t color, int thickness, bool filled);
void draw_cube(struct Cube *cube, int thickness);
void draw_circle(int xc, int yc, int r, int thickness, uint32_t color);
void draw_rounded_rectangle( int x, int y, int w, int h, int r, int thickness, uint32_t color);


void draw_init_font(const char* fontBMPImageFilePath);
void blit_bmp_blazing(int srcX, int srcY, int srcWidth, int srcDepth, int destX, int destY);
void draw_text_blazing(const char* text, int topLeftCornerTextboxX, int topLeftCornerTextboxY);

void translate_vertices(struct Vertices *v, float tx, float ty, float tz); //TODO this doesnt belong here

void draw_fbx_model(struct Mesh *mesh, int thickness);


#endif 