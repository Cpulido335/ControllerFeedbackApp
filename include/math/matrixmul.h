#ifndef MATRIXMUL_H
#define MATRIXMUL_H

#include "math/vec.h"


void convertVec3ToAThreeByOneMatrix(struct vec3 point3D, float outputMatrix[3][1]);
void convertVec2ToATwoByOneMatrix(struct vec3 point2D, float outputMatrix[2][1]);
struct vec3 convertThreeByOneMatrixToAVec3(float inputMatrix[3][1]);
void convertATwoByOneMatrixToAVec2(float inputMatrix[2][1], struct vec2 *point2D); //TODO these dont match 


void multiply_matrices( int MatrixARows, int CommonDimension, int MatrixBColumns,
                        float MatrixA[MatrixARows][CommonDimension], 
                        float MatrixB[CommonDimension][MatrixBColumns], 
                        float MatrixC[MatrixARows][MatrixBColumns]);


#endif