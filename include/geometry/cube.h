#ifndef CUBE_H
#define CUBE_H

#include "math/vec.h"   

struct Cube {
    struct vec3 vertices[8];      // 8 vertices in world coordinates
    struct vec3 localVertices[8]; // 8 vertices in local space relative to origin
    struct vec3 origin;           // cube center in world coordinates
};


struct Cube *createCube(float cx, float cy, float cz, float size);

#endif
