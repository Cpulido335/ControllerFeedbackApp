#ifndef MESH_H
#define MESH_H

#include "math/vec.h"


struct Vertices { 
    struct vec3 *vec3array;
    int length;
};

struct Edges {
    int *indices;
    int length;
};


struct Mesh {
    struct Vertices *vertices; //both these fields will both be pointers, they can get massive at scale especially edges so its good to alloc them on the heap
    struct Edges *edges;
};


void translate_mesh(struct Mesh *mesh, float tx, float ty, float tz);
void reflect_mesh(struct Mesh *mesh);
void scale_mesh(struct Mesh *mesh, float scale);
void scale_mesh_pivot(struct vec3 *mesh_pivot, float scale);

#endif