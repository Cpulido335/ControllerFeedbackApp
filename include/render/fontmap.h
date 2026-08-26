#ifndef FONT_H
#define FONT_H


#define FONT_GLYPH_WIDTH  30
#define FONT_GLYPH_DEPTH 30
#define FONT_MAP_LENGTH 95

#define FONT_GLYPH_WIDTH_DOS 15
#define FONT_GLYPH_DEPTH_DOS 15

#define FONT_GLYPH_WIDTH_C64 28
#define FONT_GLYPH_DEPTH_C64 28

#define FONT_GLYPH_WIDTH_C64_SMALL 12
#define FONT_GLYPH_DEPTH_C64_SMALL 16

struct fontMapping
{
    char asciiChar;
    int topLeftX;
    int topLeftY;
    int width;
    int depth;
};

extern struct fontMapping g_fontMapBig[];
extern struct fontMapping g_fontMapDOS[];
extern struct fontMapping g_fontMapC64[];
extern struct fontMapping g_fontMapC64Small[];


struct fontMapping* getGlyphFromFontMap(const char asciiChar, struct fontMapping fontMap[]);


#endif

