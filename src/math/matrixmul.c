#include "math/matrixmul.h"

#include "math/vec.h"
#include <math.h>

//"the number of columns in the first matrix must be equal to the number of rows in the second matrix" - Wikipedia
// Matrix A [2 3 5]     Matrix B []   [2  4]   
//          [6 2 9]        *          [7  8] 
//                                    [1  3]

// Matrix A is 2 rows 3 columns, Matrix B is 3 rows 2 columns
// 2x3 * 3x2 (LEGAL) the resulting product will be 2x2

//////////////////////////////////----HELPERS FOR MATRIX MULTIPLICATION----//////////////////////////////////
void convertVec3ToAThreeByOneMatrix(struct vec3 point3D, float outputMatrix[3][1]){ //before we start putting numbers into OUR matrices we will always round them and cast them to int
    outputMatrix[0][0] = point3D.x;
    outputMatrix[1][0] = point3D.y;
    outputMatrix[2][0] = point3D.z;
}

struct vec3 convertThreeByOneMatrixToAVec3(float inputMatrix[3][1]) {
    struct vec3 outputResultPoint3D;

    outputResultPoint3D.x = inputMatrix[0][0];
    outputResultPoint3D.y = inputMatrix[1][0];
    outputResultPoint3D.z = inputMatrix[2][0];

    return outputResultPoint3D;
}

void convertVec2ToATwoByOneMatrix(struct vec3 point2D, float outputMatrix[2][1]) {
    outputMatrix[0][0] = point2D.x;
    outputMatrix[1][0] = point2D.y;
}

void convertATwoByOneMatrixToAVec2(float inputMatrix[2][1], struct vec2 *point2D){
    point2D->x = inputMatrix[0][0];
    point2D->y = inputMatrix[1][0];
}
//////////////////////////////////----HELPERS FOR MATRIX MULTIPLICATION----//////////////////////////////////


void multiply_matrices( int MatrixARows, int CommonDimension, int MatrixBColumns,  //Shoutout VLAs TODO This wont work on some compillers lmao fuck em
                        float MatrixA[MatrixARows][CommonDimension], 
                        float MatrixB[CommonDimension][MatrixBColumns], 
                        float MatrixC[MatrixARows][MatrixBColumns])
{

    for (int i=0; i<MatrixARows; i++)
    {
        for(int j=0; j<MatrixBColumns; j++)
        {
            MatrixC[i][j] = 0;
            for(int k=0; k<CommonDimension; k++) //N is the common dimension between the two matrices
            {
                MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j]; 
            }
        }
    }
}



