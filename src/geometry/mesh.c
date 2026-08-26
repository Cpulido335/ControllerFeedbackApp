#include "geometry/mesh.h"

void translate_mesh(struct Mesh *mesh, float tx, float ty, float tz)
{
    for (int i = 0; i < mesh->vertices->length; i++)
    {
        mesh->vertices->vec3array[i].x += tx;
        mesh->vertices->vec3array[i].y += ty;
        mesh->vertices->vec3array[i].z += tz;
    }
}

void reflect_mesh(struct Mesh *mesh)
{
    for (int i = 0; i < mesh->vertices->length; i++)
    {
        mesh->vertices->vec3array[i].x = -mesh->vertices->vec3array[i].x;
    }
}
