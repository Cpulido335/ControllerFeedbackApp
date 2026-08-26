#ifndef ROTATION_H
#define ROTATION_H

#include "geometry/cube.h"
#include "geometry/fbx_ascii_parser.h"


struct vec3 rotateX(struct vec3 vec3toBeRotated, float angle);
struct vec3 rotateY(struct vec3 vec3toBeRotated, float angle);
struct vec3 rotateZ(struct vec3 vec3toBeRotated, float angle);
void rotateCubeAroundZ(struct Cube *cube, float theta);
void rotateCube(struct Cube *cube, float angleX, float angleY, float angleZ);
struct vec3 rotateVertex(struct vec3 v, float thetaX, float thetaY, float thetaZ);
void rotateCubeAroundOrigin(struct Cube *cube, float thetaX, float thetaY, float thetaZ);

void rotate_vertices(struct Vertices *vertices, float angleX, float angleY, float angleZ);
void rotate_vertices_around_point(struct Vertices *vertices, struct vec3 pivot, float angleX, float angleY, float angleZ);


#endif