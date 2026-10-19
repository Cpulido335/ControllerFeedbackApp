#include "math/rotation.h"
#include "geometry/cube.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "math/vec.h"
#include "math/matrixmul.h"
#include "geometry/fbx_ascii_parser.h" //TODO we need to move struct Vertices out of the fbx parser


struct vec3 rotateX(struct vec3 vec3toBeRotated, float angle)
{
    float radians = angle * (M_PI / 180.0f);  //convert from degrees to radians


    float rotationXProjectionMatrix[3][3] = 
    {
        {1, 0, 0},
        {0, cosf(radians), -sinf(radians)},
        {0, sinf(radians), cosf(radians)},
    };

    //lets first convert our vec 3 to a 3x1 matrix (three rows, one column)

    //declare the a storage matrix for the converted point:
    float threeByOneMatrixToStoreOurVec3Point[3][1] = {0};
    
    //perform the conversion and store the result in outputThreeByOneMatrixToStoreOurVec3Point
    convertVec3ToAThreeByOneMatrix(vec3toBeRotated, threeByOneMatrixToStoreOurVec3Point);

    //now that we have our 3x1 matrix we have to multiply the rotation matrix by the 3x1 and NOT VICE VERSA
    // so it will be: 3x3 * 3x1  = 3x1

    //                 A     B      C

    //lets declare this result matrix
    float finalRotated3DPointResultMatrix[3][1] = {0};
    
    
    //and then run the calculation
    multiply_matrices(3, 3, 1, rotationXProjectionMatrix, threeByOneMatrixToStoreOurVec3Point, finalRotated3DPointResultMatrix);

    //and then finally convert back to a vec3 so we can return the final result of this function
    struct vec3 finalVec3Result = convertThreeByOneMatrixToAVec3(finalRotated3DPointResultMatrix);

    return finalVec3Result;
}


struct vec3 rotateY(struct vec3 vec3toBeRotated, float angle)
{
    float radians = angle * (M_PI / 180.0f);  //convert from degrees to radians

    float rotationYProjectionMatrix[3][3] = 
    {
        { cosf(radians), 0, sinf(radians)},
        { 0,             1, 0},
        {-sinf(radians), 0, cosf(radians)},
    };

    float threeByOneMatrixToStoreOurVec3Point[3][1] = {0};
    convertVec3ToAThreeByOneMatrix(vec3toBeRotated, threeByOneMatrixToStoreOurVec3Point);

    float finalRotated3DPointResultMatrix[3][1] = {0};
    multiply_matrices(3, 3, 1, rotationYProjectionMatrix, threeByOneMatrixToStoreOurVec3Point, finalRotated3DPointResultMatrix);

    struct vec3 finalVec3Result = convertThreeByOneMatrixToAVec3(finalRotated3DPointResultMatrix);

    return finalVec3Result;
}


struct vec3 rotateZ(struct vec3 vec3toBeRotated, float angle)
{
    float radians = angle * (M_PI / 180.0f);  //convert from degrees to radians

    float rotationZProjectionMatrix[3][3] = 
    {
        { cosf(radians), -sinf(radians), 0},
        { sinf(radians),  cosf(radians), 0},
        { 0,              0,             1},
    };

    float threeByOneMatrixToStoreOurVec3Point[3][1] = {0};
    convertVec3ToAThreeByOneMatrix(vec3toBeRotated, threeByOneMatrixToStoreOurVec3Point);

    float finalRotated3DPointResultMatrix[3][1] = {0};
    multiply_matrices(3, 3, 1, rotationZProjectionMatrix, threeByOneMatrixToStoreOurVec3Point, finalRotated3DPointResultMatrix);

    struct vec3 finalVec3Result = convertThreeByOneMatrixToAVec3(finalRotated3DPointResultMatrix);

    return finalVec3Result;
}


void rotateCubeAroundZ(struct Cube *cube, float theta) 
{ 
    for (int i = 0; i < 8; i++) 
    { 
        cube->localVertices[i] = rotateZ(cube->localVertices[i], theta); 
    } 
}


void rotateCube(struct Cube *cube, float angleX, float angleY, float angleZ)
{
    for (int i = 0; i < 8; i++)
    {
        struct vec3 v = cube->localVertices[i];

        //apply rotations in X -> Y -> Z order
        v = rotateX(v, angleX);
        v = rotateY(v, angleY);
        v = rotateZ(v, angleZ);

        cube->localVertices[i] = v;
    }
}


void rotateCubeAroundOrigin(struct Cube *cube, float angleX, float angleY, float angleZ) //degrees not radians
{
    for (int i = 0; i < 8; i++)
    {
        //rotate the CURRENT local vertices
        struct vec3 v = cube->localVertices[i];

        //move cube center to origin
        v.x -= cube->origin.x;
        v.y -= cube->origin.y;
        v.z -= cube->origin.z;

        //rotate around origin (degrees)
        v = rotateX(v, angleX);
        v = rotateY(v, angleY);
        v = rotateZ(v, angleZ);

        //move back to world space
        v.x += cube->origin.x;
        v.y += cube->origin.y;
        v.z += cube->origin.z;

        //write back to the same buffer you draw from
        cube->localVertices[i] = v;
    }
}

void rotate_vertices(struct Vertices *vertices, float angleX, float angleY, float angleZ)
{
    for (int i = 0; i < vertices->length; i++)
    {
        struct vec3 v = vertices->vec3array[i];

        // local-space rotations (origin at model center)
        v = rotateX(v, angleX);
        v = rotateY(v, angleY);
        v = rotateZ(v, angleZ);

        vertices->vec3array[i] = v;
    }
}


void rotate_vertices_around_point(struct Vertices *vertices, struct vec3 *pivot, float angleX, float angleY, float angleZ)
{
    for (int i = 0; i < vertices->length; i++)
    {
        struct vec3 v = vertices->vec3array[i];

        // move pivot to origin
        v.x -= pivot->x;
        v.y -= pivot->y;
        v.z -= pivot->z;

        // rotate in local space
        v = rotateX(v, angleX);
        v = rotateY(v, angleY);
        v = rotateZ(v, angleZ);

        // move back
        v.x += pivot->x;
        v.y += pivot->y;
        v.z += pivot->z;

        vertices->vec3array[i] = v;
    }
}










