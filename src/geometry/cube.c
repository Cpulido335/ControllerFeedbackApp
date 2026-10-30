#include "geometry/cube.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

//create a cube centered at (cx, cy, cz) with side length 'size'
struct Cube *createCube(float cx, float cy, float cz, float size) {
    struct Cube *cube = malloc(sizeof *cube); //CUBE ITS SELF IS HEAP ALLOC
    if (!cube)
        return NULL;
    float half = size / 2.0f;

    // Define all 8 localVertices
    cube->localVertices[0] = (struct vec3){ cx - half, cy - half, cz - half }; 
    cube->localVertices[1] = (struct vec3){ cx + half, cy - half, cz - half };
    cube->localVertices[2] = (struct vec3){ cx + half, cy + half, cz - half };
    cube->localVertices[3] = (struct vec3){ cx - half, cy + half, cz - half };
    cube->localVertices[4] = (struct vec3){ cx - half, cy - half, cz + half };
    cube->localVertices[5] = (struct vec3){ cx + half, cy - half, cz + half };
    cube->localVertices[6] = (struct vec3){ cx + half, cy + half, cz + half };
    cube->localVertices[7] = (struct vec3){ cx - half, cy + half, cz + half };

    cube->origin.x = cx; //TODO -> pointer to origin but the origins individual coordinate values are on the stack with '.' instead of -> (weird?)
    cube->origin.y = cy;
    cube->origin.z = cz;

    return cube;
}

void destroy_cube(struct Cube *cube)
{
    if(!cube)
    {
        printf("Destroy Cube: ERROR: *cube is NULL\n");
        return;
    }

    free(cube);
}
