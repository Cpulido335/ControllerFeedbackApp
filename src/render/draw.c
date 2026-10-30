#include "render/draw.h"

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "render/renderer.h"
#include "render/fontmap.h"
#include "geometry/mesh.h"

//externs
struct drawContext gDrawContext;  //is this a meyers singleton? TODO should we also move this into the draw_init func?

//statics 
static struct fontMapping *staticCurrentFontmap = NULL; 
static uint32_t staticAtlasWidthPixels;
static uint32_t *staticPtrFontAtlasUint32 = NULL;

#define BMP_DATA_OFFSET_BYTEPOSITION 10

BITMAPINFO bmi = 
{
    .bmiHeader = {
    .biSize = sizeof(BITMAPINFOHEADER),
    .biWidth = WINDOW_WIDTH,
    .biHeight = -WINDOW_HEIGHT,  // negative = top-down bitmap
    .biPlanes = 1,
    .biBitCount = 32,
    .biCompression = BI_RGB,
    }
};


void copyBufferToWindow(HDC deviceContext, int windowWidth, int windowHeight) //TODO why is this here but also in the window callback?
{
	StretchDIBits(
        deviceContext,
        0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
        0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
        gDrawContext.framebuffer, //theres one global instance of the framebuffer
        &bmi,                
        DIB_RGB_COLORS,
        SRCCOPY
    );    
}


void clear_drawContext()
{
    for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {
        gDrawContext.framebuffer[i] = 0x000000; //pitch black
    }
}


void clear_rectangle_within_drawContext(int x, int y, int width, int depth)
{
    // Clamp rectangle to the window bounds
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + width > WINDOW_WIDTH)  width = WINDOW_WIDTH - x;
    if (y + depth > WINDOW_HEIGHT) depth = WINDOW_HEIGHT - y;

    for (int row = y; row < y + depth; row++)
    {
        for (int col = x; col < x + width; col++)
        {
            gDrawContext.framebuffer[row * WINDOW_WIDTH + col] = 0x000000; //pitch black
        }
    }
}

void invert_rectangle_within_drawContext(int x, int y, int width, int depth)
{
    // Clamp rectangle to the window bounds
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + width > WINDOW_WIDTH)  width = WINDOW_WIDTH - x;
    if (y + depth > WINDOW_HEIGHT) depth = WINDOW_HEIGHT - y;

    for (int row = y; row < y + depth; row++)
    {
        for (int col = x; col < x + width; col++)
        {
            gDrawContext.framebuffer[row * WINDOW_WIDTH + col] ^= 0x00FFFFFF; //bitwise inversion
        }
    }
}


void put_pixel(int x, int y, uint32_t color, int thickness)
{
    if (thickness <= 0)
        return;

    int half = thickness / 2;

    for (int dy = -half; dy < thickness - half; dy++)
    {
        for (int dx = -half; dx < thickness - half; dx++)
        {
            int px = x + dx;
            int py = y + dy;

            if (px < 0 || py < 0 || px >= WINDOW_WIDTH || py >= WINDOW_HEIGHT)
                continue;

            gDrawContext.framebuffer[py * WINDOW_WIDTH + px] = color;
        }
    }
}


void draw_line(float x0, float y0, float x1, float y1, uint32_t color, int thickness) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    float steps = fmaxf(fabsf(dx), fabsf(dy));

    if (steps == 0) {  // single point
        put_pixel((int)roundf(x0), (int)roundf(y0), color, thickness);
        return;
    }

    float x_inc = dx / steps;
    float y_inc = dy / steps;
    float x = x0;
    float y = y0;

    for (int i = 0; i <= (int)steps; i++) {
        put_pixel((int)roundf(x), (int)roundf(y), color, thickness);
        x += x_inc;
        y += y_inc;
    }
}


void draw_rectangle(int x, int y, int width, int height, uint32_t color, int thickness) // lets to from center first
{   
    //assume the rectangle has no rotation to understand the variable names(e. g. top right corner), declare 4 corners
    struct vec2 topLeftCorner;
    struct vec2 topRightCorner;
    struct vec2 bottomLeftCorner;
    struct vec2 bottomRightCorner;
    
    topLeftCorner.x = (int)round(x - (0.5 * width)); topLeftCorner.y  = (int)round(y + (0.5 * height));
    topRightCorner.x = (int)round(x + (0.5 * width)); topRightCorner.y = (int)round(y + (0.5 * height));
    bottomLeftCorner.x = (int)round(x - (0.5 * width)); bottomLeftCorner.y = (int)round(y - (0.5 * height));
    bottomRightCorner.x = (int)round(x + (0.5 * width)); bottomRightCorner.y = (int)round(y - (0.5 * height));

    draw_line(topLeftCorner.x, topLeftCorner.y, topRightCorner.x, topRightCorner.y, color, thickness); //Top edge
    draw_line(bottomLeftCorner.x, bottomLeftCorner.y, bottomRightCorner.x, bottomRightCorner.y, color, thickness); //Bottom edge
    draw_line(topLeftCorner.x, topLeftCorner.y, bottomLeftCorner.x, bottomLeftCorner.y, color, thickness); //Left edge
    draw_line(topRightCorner.x, topRightCorner.y, bottomRightCorner.x, bottomRightCorner.y, color, thickness); //Right edge
}

void draw_rectangle_top_left(int x, int y, int width, int height, uint32_t color, int thickness, bool filled)
{
    struct vec2 topLeftCorner;
    struct vec2 topRightCorner;
    struct vec2 bottomLeftCorner;
    struct vec2 bottomRightCorner;

    topLeftCorner.x = x; topLeftCorner.y = y;
    topRightCorner.x = x + width; topRightCorner.y = y;
    bottomLeftCorner.x = x; bottomLeftCorner.y = y + height;
    bottomRightCorner.x = x + width;  bottomRightCorner.y = y + height;


    draw_line(topLeftCorner.x, topLeftCorner.y, topRightCorner.x, topRightCorner.y, color, thickness);     // Top edge
    draw_line(bottomLeftCorner.x, bottomLeftCorner.y,  bottomRightCorner.x, bottomRightCorner.y, color, thickness); // Bottom edge
    draw_line(topLeftCorner.x, topLeftCorner.y, bottomLeftCorner.x, bottomLeftCorner.y,  color, thickness);    //left edge
    draw_line(topRightCorner.x, topRightCorner.y, bottomRightCorner.x, bottomRightCorner.y,  color, thickness); //right edge

    if(filled)
    {
        for(int row=0; row<height; row++)
            draw_line(topLeftCorner.x, topLeftCorner.y + row, topRightCorner.x, topRightCorner.y + row, color, 1);
    }
}



void draw_cube(struct Cube *cube, int thickness)
{
    //we need to convert(smash) all vertices of the cube into 2d by using projection
    struct vec2 smashedCubeBottomLeftBack = projectA3dPointIn2DSpace(cube->localVertices[0]);
    struct vec2 smashedCubeBottomRightBack = projectA3dPointIn2DSpace(cube->localVertices[1]);
    struct vec2 smashedTopRightBack = projectA3dPointIn2DSpace(cube->localVertices[2]);
    struct vec2 smashedCubeTopLeftBack = projectA3dPointIn2DSpace(cube->localVertices[3]);
    
    struct vec2 smashedCubeBottomLeftFront = projectA3dPointIn2DSpace(cube->localVertices[4]);
    struct vec2 smashedCubeBottomRightFront= projectA3dPointIn2DSpace(cube->localVertices[5]);
    struct vec2 smashedCubeTopRightFront = projectA3dPointIn2DSpace(cube->localVertices[6]);
    struct vec2 smashedCubeTopLeftFront = projectA3dPointIn2DSpace(cube->localVertices[7]);

    
    //draw back face
    draw_line((int)smashedCubeBottomLeftBack.x,  (int)smashedCubeBottomLeftBack.y,
            (int)smashedCubeBottomRightBack.x, (int)smashedCubeBottomRightBack.y, COLOR_RED, thickness);

    draw_line((int)smashedCubeBottomRightBack.x, (int)smashedCubeBottomRightBack.y,
            (int)smashedTopRightBack.x,        (int)smashedTopRightBack.y, COLOR_RED, thickness);

    draw_line((int)smashedTopRightBack.x,        (int)smashedTopRightBack.y,
            (int)smashedCubeTopLeftBack.x,     (int)smashedCubeTopLeftBack.y, COLOR_RED, thickness);

    draw_line((int)smashedCubeTopLeftBack.x,     (int)smashedCubeTopLeftBack.y,
            (int)smashedCubeBottomLeftBack.x,  (int)smashedCubeBottomLeftBack.y, COLOR_RED, thickness);


    //draw front face
    draw_line((int)smashedCubeBottomLeftFront.x,  (int)smashedCubeBottomLeftFront.y,
            (int)smashedCubeBottomRightFront.x, (int)smashedCubeBottomRightFront.y, COLOR_GREEN, thickness);

    draw_line((int)smashedCubeBottomRightFront.x, (int)smashedCubeBottomRightFront.y,
            (int)smashedCubeTopRightFront.x,    (int)smashedCubeTopRightFront.y, COLOR_GREEN, thickness);

    draw_line((int)smashedCubeTopRightFront.x,    (int)smashedCubeTopRightFront.y,
            (int)smashedCubeTopLeftFront.x,     (int)smashedCubeTopLeftFront.y, COLOR_GREEN, thickness);

    draw_line((int)smashedCubeTopLeftFront.x,     (int)smashedCubeTopLeftFront.y,
            (int)smashedCubeBottomLeftFront.x,  (int)smashedCubeBottomLeftFront.y, COLOR_GREEN, thickness);


    //connect back face → front face
    draw_line((int)smashedCubeBottomLeftBack.x,   (int)smashedCubeBottomLeftBack.y,
            (int)smashedCubeBottomLeftFront.x,  (int)smashedCubeBottomLeftFront.y, COLOR_BLUE, thickness);

    draw_line((int)smashedCubeBottomRightBack.x,  (int)smashedCubeBottomRightBack.y,
            (int)smashedCubeBottomRightFront.x, (int)smashedCubeBottomRightFront.y, COLOR_BLUE, thickness);

    draw_line((int)smashedTopRightBack.x,         (int)smashedTopRightBack.y,
            (int)smashedCubeTopRightFront.x,    (int)smashedCubeTopRightFront.y, COLOR_BLUE, thickness);

    draw_line((int)smashedCubeTopLeftBack.x,      (int)smashedCubeTopLeftBack.y,
            (int)smashedCubeTopLeftFront.x,     (int)smashedCubeTopLeftFront.y, COLOR_BLUE, thickness);

}

//////////////////////////////////----HELPERS FOR CIRCLE DRAWING----//////////////////////////////////
void plotOctants(int xc, int yc, int x, int y, uint32_t color, int thickness){ //helper to plot 8-way symmetry (adjust for center) 
    put_pixel(xc+x, yc-y, color, thickness); //octant 1
    put_pixel(xc+y, yc-x, color, thickness); //octant 2
    put_pixel(xc+y, yc+x, color, thickness); //octant 3
    put_pixel(xc+x, yc+y, color, thickness); //octant 4 
    put_pixel(xc-x, yc+y, color, thickness); //octant 5
    put_pixel(xc-y, yc+x, color, thickness); //octant 6
    put_pixel(xc-y, yc-x, color, thickness); //octant 7
    put_pixel(xc-x, yc-y, color, thickness); //octant 8
}

void plotOctantsTopRight(int cx, int cy, int x, int y, uint32_t color, int thickness) {
    put_pixel(cx+x, cy-y, color, thickness); //octant 1
    put_pixel(cx+y, cy-x, color, thickness); //octant 2
}

void plotOctantsTopLeft(int cx, int cy, int x, int y, uint32_t color, int thickness) {
    put_pixel(cx-y, cy-x, color, thickness); //octant 7
    put_pixel(cx-x, cy-y, color, thickness); //octant 8
}

void plotOctantsBottomLeft(int cx, int cy, int x, int y, uint32_t color, int thickness) {
    put_pixel(cx-x, cy+y, color, thickness); //octant 5
    put_pixel(cx-y, cy+x, color, thickness); //octant 6
}

void plotOctantsBottomRight(int cx, int cy, int x, int y, uint32_t color, int thickness) {
    put_pixel(cx+y, cy+x, color, thickness); //octant 3
    put_pixel(cx+x, cy+y, color, thickness); //octant 4 
}
//////////////////////////////////----HELPERS FOR CIRCLE DRAWING----//////////////////////////////////



//Mid-point circle algo fast version
void draw_circle(int cx, int cy, int r, int thickness, uint32_t color)
{
    int x = 0, y = r;
    int P = 1 - r; // Initial decision parameter

    // Plot initial point and its symmetric points (adjust for center)
    //plotOctants(cx, cy, x, y, color); // Function to plot all 8 points <<TODO we dont need to call this right here. why is this here?
    while (x < y) {
        x++; // Always move right (x increases)
        if (P <= 0) {
            // Midpoint is inside: next point is (x+1, y)
            P = P + 2 * x + 1;
        } else {
            // Midpoint is outside: next point is (x+1, y-1)
            y--;
            P = P + 2 * x - 2 * y + 1;
        }
        plotOctants(cx, cy, x, y, color, thickness); // Plot symmetric points
    }
}


void draw_button_circle(int x, int y, int r, uint32_t color, bool filled)
{
    draw_circle(x, y, r, 1, color);

    if (filled)
        for (int dy = -r; dy <= r; dy++)
        {
            int dx = (int)sqrt(r * r - dy * dy);
            draw_line(x - dx, y + dy, x + dx, y + dy, color, 1);
        }
}


void midPointCircleForRoundedRectanglesCorners( int r, uint32_t color, int rectX, int rectY, int rectW, int rectH, int thickness) 
{
    int x = 0, y = r;
    int P = 1 - r; // Initial decision parameter

    // Plot initial point and its symmetric points (adjust for center)
    //plotOctants(cx, cy, x, y, color); // Function to plot all 8 points

    while (x < y) {
        x++; // Always move right (x increases)
        if (P <= 0) {
            // Midpoint is inside: next point is (x+1, y)
            P = P + 2 * x + 1;
        } else {
            // Midpoint is outside: next point is (x+1, y-1)
            y--;
            P = P + 2 * x - 2 * y + 1;
        }
        plotOctantsTopRight(rectX + rectW - r, rectY + r, x, y, color, thickness); // to find the topright the center of the circle should be placed cx = rectX + rectW - rectRecession/radiusOfTheCircle
        plotOctantsTopLeft(rectX + r, rectY + r, x, y, color, thickness);
        plotOctantsBottomLeft(rectX + r, rectY + rectH - r, x, y, color, thickness);
        plotOctantsBottomRight(rectX + rectW - r, rectY + rectH - r, x, y, color, thickness);
    }
}


void draw_rounded_rectangle(int x, int y, int w, int h, int r, int thickness, uint32_t color)
{
    //define 4 lines
    //pick a distance the lines are recessed from their corner, this distance will be uniform 
    //use the MPCA to draw a quadrant between the two
    int recession = r; //lets set the recession equal to the radius this is the only thing that makes sense in my head for now

    //left side
    struct vec2 left_edge_top = {x, y+recession}; //remember y increases downward
    struct vec2 left_edge_bottom = {x, y+h-recession}; //so the y + height, subtract the recession to bring it back up 
    
    draw_line(left_edge_top.x, left_edge_top.y, left_edge_bottom.x, left_edge_bottom.y, color, thickness);

    //right side
    struct vec2 right_edge_top = {x+w, y+recession};
    struct vec2 right_edge_bottom = {x+w, y+h-recession}; //keep in mind h usually means height but it should be d for depth

    //the left and right side should mirror eachother 
    draw_line(right_edge_top.x, right_edge_top.y, right_edge_bottom.x, right_edge_bottom.y, color, thickness);

    //top edge
    struct vec2 top_edge_left_end = {x+recession, y};
    struct vec2 top_edge_right_end = {x+w-recession, y};
    draw_line(top_edge_left_end.x, top_edge_left_end.y, top_edge_right_end.x, top_edge_right_end.y, color, thickness);

    //bottom edge
    struct vec2 bottom_edge_left_end = {x+recession, y+h}; //h should be d for depth, y increases downward
    struct vec2 bottom_edge_right_end = {x+w-recession, y+h};
    draw_line(bottom_edge_left_end.x, bottom_edge_left_end.y, bottom_edge_right_end.x, bottom_edge_right_end.y, color, thickness);

    midPointCircleForRoundedRectanglesCorners(12, color, x, y, w, h, thickness);
}


void draw_init_font(const char* fontBMPImageFilePath)
{
    //open a bitmap, build read, uint32 rgb values into a data stream, 
    FILE *filePointer = fopen(fontBMPImageFilePath, "rb"); //TODO no error handling here
    if(!filePointer)
    {
        perror("filePointer not created!");
        // return -1;
    }
    

    fseek(filePointer, 0, SEEK_END);
    long fileSize = ftell(filePointer);
    fseek(filePointer, 0, SEEK_SET);


    //read in the entire BMP datastream from the font.bmp file
    uint8_t *pBmpByteStream = malloc(fileSize);
    size_t bytesRead = fread(pBmpByteStream, 1, fileSize, filePointer);

    
    int dataOffsetAmountBytes = ((uint32_t)pBmpByteStream[BMP_DATA_OFFSET_BYTEPOSITION])                  |
                                ((uint32_t)pBmpByteStream[BMP_DATA_OFFSET_BYTEPOSITION + 1] << 8)         |
                                ((uint32_t)pBmpByteStream[BMP_DATA_OFFSET_BYTEPOSITION + 2] << 16)        |
                                ((uint32_t)pBmpByteStream[BMP_DATA_OFFSET_BYTEPOSITION + 3] << 24);

    uint32_t bmpWidthPixels =
                                ((uint32_t)pBmpByteStream[18])              |
                                ((uint32_t)pBmpByteStream[19] << 8)         |
                                ((uint32_t)pBmpByteStream[20] << 16)        |
                                ((uint32_t)pBmpByteStream[21] << 24);

    uint32_t bmpHeightPixels =
                                ((uint32_t)pBmpByteStream[22])              |
                                ((uint32_t)pBmpByteStream[23] << 8)         |
                                ((uint32_t)pBmpByteStream[24] << 16)        |
                                ((uint32_t)pBmpByteStream[25] << 24);



    int rowSizeBytes = bmpWidthPixels * 4; //4bytes per pixel
    
    int topDownBufferSize = fileSize - dataOffsetAmountBytes;   //for an uncompressed, 32bit color depth, BGRA, standard bmp                            
    
    uint8_t *staticPtrFontAtlas = malloc(topDownBufferSize);              
    
    for (int y = 0; y < bmpHeightPixels; y++) //flip it << this creates topDown buffer with no header
    {
        memcpy( staticPtrFontAtlas + y * rowSizeBytes,     
                pBmpByteStream + dataOffsetAmountBytes + (bmpHeightPixels - 1 - y) * rowSizeBytes,      
                rowSizeBytes);
    }

    //okay this is fucked but since the gContext.framebuffer is uint32 and the staticPtrFontAtlas buffer is uint8_t
    //we have to to do this annoying ass conversion, it's pretty straightfoward though,
    //  iterate through every byte in the fontAtlasBuffer and copy it to the corresponding 8bit sequence in the uint32 in gcontext.framebuffer
    //  its a 1 to 1 translation
    staticPtrFontAtlasUint32 = malloc(bmpWidthPixels * bmpHeightPixels * sizeof(uint32_t));
    //RIGHT HERE: maybe set the alpha channel of all pixels to zero will fix it???
    int newBufferIndex = 0;
    for(int i=0; i< topDownBufferSize; i+=4)// atlasBuffer size == topDownBuf size, jump 4 bytes at a time
    {
        uint8_t blueChannel = staticPtrFontAtlas[i];    //B
        uint8_t greenChannel = staticPtrFontAtlas[i+1]; //G
        uint8_t redChannel = staticPtrFontAtlas[i+2];   //R
        uint8_t alphaChannel = staticPtrFontAtlas[i+3]; //A

        if(greenChannel > 80)
        {
            int pauseHere=1;
        }
        uint32_t *currentPixel = &staticPtrFontAtlasUint32[newBufferIndex];

        ((uint8_t*)currentPixel)[0] = blueChannel; //pointer casting
        ((uint8_t*)currentPixel)[1] = greenChannel;
        ((uint8_t*)currentPixel)[2] = redChannel;
        
        
        //right here to fix the transparancy problem, we could say if R,G & B are all lesser than lets say 100 then we well just set the alpha channel to zero
        if(blueChannel < 100 && greenChannel < 100 && redChannel < 100)
        {
            //((uint8_t*)currentPixel)[1] = 255; //lets try if the pixel is black set it to green
        } else {
            ((uint8_t*)currentPixel)[3] = 0; //its just completely ignoring the alpha channel? but why??
        }
        
        

        //increment the newBufferIndex after the byte manipulation is finished for the current pixel
        newBufferIndex++;
    } 
    //todo get rid of the old atlas and rename these god awful variables

    //close the file pointer
    fclose(filePointer);
    //after this we can free the buffers and close the file pointer
    free(pBmpByteStream);
    free(staticPtrFontAtlas);

    //the last thing we should do is set a static pointer for draw.c to the specific font map
    //TODO for now we will just hardcode it commodore64small's font map
    staticCurrentFontmap = g_fontMapC64Small;
    staticAtlasWidthPixels = bmpWidthPixels;
}

//blit a rectanglular-bitmap to the framebuffer from an external source bitmap
void blit_bmp_blazing(int srcX, int srcY, int srcWidth, int srcDepth, int destX, int destY)
{
    if (destX < 0 || destY < 0 || srcX < 0 || srcY < 0)
        return;

    if (destX + srcWidth > WINDOW_WIDTH)
        return;

    if (srcX + srcWidth > staticAtlasWidthPixels)
        return;

    //after the staticFontMapAtlas is initialized, we can just copy it row by row straight from the
    //atlas and into the framebuffer.
    
    //static uint8_t *staticPtrFontAtlas TODO remove me << remeber we have this initialized
    int rowLengthPixels = srcWidth;
    int currentRowInDest = destY;
    for(int currentRowInSrc = srcY; currentRowInSrc < srcY + srcDepth; currentRowInSrc++) //for every row in the font cutout
    {
        memcpy( gDrawContext.framebuffer + (currentRowInDest * WINDOW_WIDTH) + destX, //copy the currentrow from the first index in the row to the end of the row which is firstPixelOfTheRow + srcWidth
                staticPtrFontAtlasUint32 +  (currentRowInSrc * staticAtlasWidthPixels) + srcX,
                rowLengthPixels * sizeof(uint32_t));
        
        currentRowInDest++;  //increment currentRowInDest and currentRowInSrc in parrellell      
    }

}


void draw_text_blazing(const char* text, int topLeftCornerTextboxX, int topLeftCornerTextboxY)
{
    int fontCharacterSpacing = 12;

    int length = strlen(text);
    int currentXPos = topLeftCornerTextboxX;
    for(int currentCharIndex = 0; currentCharIndex < length; currentCharIndex++)
    {
        struct fontMapping* pFontMapping = getGlyphFromFontMap(text[currentCharIndex], staticCurrentFontmap);
        blit_bmp_blazing(   pFontMapping->topLeftX, pFontMapping->topLeftY, 
                            pFontMapping->width, pFontMapping->depth,
                            currentXPos, topLeftCornerTextboxY );
        
        currentXPos += fontCharacterSpacing; //TODO this is wonky the width should either be a variable accessible in the map or something else 
    }
}


void draw_fbx_model(struct Mesh *mesh, int thickness)
{
    int first_index = -1;
    int prev_index  = -1;

    for (int i = 0; i < mesh->edges->length; i++)
    {
        int idx = mesh->edges->indices[i];
        int end_of_polygon = 0;

        if (idx < 0)
        {
            idx = (-idx) - 1;   //FBX decode
            end_of_polygon = 1;
        }

        //first vertex of polygon
        if (first_index == -1)
        {
            first_index = idx;
            prev_index  = idx;
            continue;
        }

        if (prev_index < 0 || prev_index >= mesh->vertices->length ||  idx < 0 || idx >= mesh->vertices->length)
        {
            printf("INVALID INDEX! prev_index=%d, idx=%d, vertex_count=%d, edge_position=%d\n", prev_index, idx, mesh->vertices->length, i);
            break;
        }

        //project previous and current vertices
        struct vec2 p0 =projectA3dPointIn2DSpace(mesh->vertices->vec3array[prev_index]);
        struct vec2 p1 = projectA3dPointIn2DSpace(mesh->vertices->vec3array[idx]);

        draw_line((int)p0.x, (int)p0.y,(int)p1.x, (int)p1.y, COLOR_GREEN, thickness);

        if (end_of_polygon)
        {
            //close polygon: current -> first
            struct vec2 pf = projectA3dPointIn2DSpace(mesh->vertices->vec3array[first_index]);

            draw_line((int)p1.x, (int)p1.y, (int)pf.x, (int)pf.y, COLOR_GREEN, thickness );

            //reset for next polygon
            first_index = -1;
            prev_index  = -1;
        }
        else
        {
            prev_index = idx;
        }
    }
}


