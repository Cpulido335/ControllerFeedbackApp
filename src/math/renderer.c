#include "render/renderer.h"

#include "math/matrixmul.h"
#include "globals.h"


float PROJECTION_MATRIX[2][3] = 
{
    {1,0,0},
    {0,1,0}
};


#define PROJECTION_MATRIX_ROWS          2 //M
#define PROJECTION_MATRIX_COLUMNS       3 //N (Common Dimension)
#define THREE_D_POINT_MATRIX_COLUMNS    1 //P


struct vec2 projectA3dPointIn2DSpace(struct vec3 ThreeDPoint)
{
    //create a 2x1 matrix to because mutliply matrices returns a matrix and not a vec2
    float matrix_product[2][1] = {0}; //TODO: doublecheck this, this should be a 2 by 1 but figure out why it should be a 2by1 and not just the simple answer because it was throwing it error

    float matrixB[3][1] = {0};

    convertVec3ToAThreeByOneMatrix(ThreeDPoint, matrixB);

    multiply_matrices(  PROJECTION_MATRIX_ROWS, PROJECTION_MATRIX_COLUMNS, THREE_D_POINT_MATRIX_COLUMNS,//in c when you pass an array(any of the matrices to a function, 
                        PROJECTION_MATRIX, matrixB, matrix_product);                                    //it decays to a pointer to its first element so none of these are being copied

    struct vec2 output2Dpoint;

    convertATwoByOneMatrixToAVec2(matrix_product, &output2Dpoint); 

    
    // Flip Y and center in window
    //output2Dpoint.x += WINDOW_WIDTH / 2.0f;
    //output2Dpoint.y = WINDOW_HEIGHT / 2.0f - output2Dpoint.y;


    return output2Dpoint;
}


