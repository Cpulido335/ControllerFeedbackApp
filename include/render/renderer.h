#ifndef RENDERER_H
#define RENDERER_H


#include "globals.h"
#include "math/vec.h"

//projection matrix
extern float PROJECTION_MATRIX[2][3];
//TODO i guess the whole point of the renderer is exculsivley projection, in that case I dont know if having a seperate render module is the best idea but im not sure

//the idea is for every single 3d point we multiply it by the projection matrix, in this class we're going to define the cube as a global 
//and also define 3d points (Vec3)

//lets do it like this for not WERE GOING TO DO IT WRONG ON PURPOSE TO LEARN, im sure the actual way you're
//supposed do it is have an array that or even 3 rows by 1 column array like [3][1] since the guy in the video said its supposed to be a 3x1 
//matrix: that makes me think it is supposed to be a 3x1 matrix to more easily follow mathmatical conventions, my assumption is that 
//the mathmatical convetion is that in most math sources vec3s are expressed as a 3x1 matrix. I HAVE NOT DOUBLE CHECKED IF THIS IS TRUE 


//Why we should define types in the header file and not the source file:  
//"Defining vec3 in a header file allows you to include it in multiple source files (.c)  that need to use the vec3 type,
//preventing redundant definitions and ensuring consistency across your project."

struct vec2 projectA3dPointIn2DSpace(struct vec3 ThreeDPoint);


#endif

