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

void scale_mesh(struct Mesh *mesh, float scale)
{
    for (int i = 0; i < mesh->vertices->length; i++)
    {
        mesh->vertices->vec3array[i].x *= scale;
        mesh->vertices->vec3array[i].y *= scale;
        mesh->vertices->vec3array[i].z *= scale;
    }
}

void scale_mesh_pivot(struct vec3 *mesh_pivot, float scale) //TODO why would you need to scale a mesh pivot this probably can be removed??
{
    mesh_pivot->x *= scale;
    mesh_pivot->y *= scale;
    mesh_pivot->z *= scale;
}
