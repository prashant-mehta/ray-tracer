/*
 * TransformationMatrices.h
 *
 *  Created on: Sep 13, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_TRANSFORMATIONMATRICES_H_
#define INCLUDE_TRANSFORMATIONMATRICES_H_

#include <cmath>
#include <MatrixOperations.h>
#include <VectorOperations.h>
#include <stdlib.h>

#define matrix(i, j) matrix[(i)*(4)+(j)]
#define PI 3.14159265

class TransformationMatrices {

private:
	VectorOperations * vector_operations;
	MatrixOperations * matrix_operations;

public:
	TransformationMatrices();

	float* GetUnitTransformationMatrix(void);

	float* ScaleMatrix(float x_axis, float y_axis, float z_axis);

	float* TranslationMatrix(float x_coordinate, float y_coordinate, float z_coordinate);

	float* RotationMatrixAcrossZ(float angle_of_rotation);

	float* RotationOmegaMatrix(float x_axis, float y_axis, float z_axis);

	float* RotationMatrix(float x_axis, float y_axis, float z_axis, float angle_of_rotation);

	float* TransformationMatrix(Vertex input_parameters, char const transform, float* transformation_matrix);

	void PrintTransformationMatrix(float *transformation_matrix);
};

#endif /* INCLUDE_TRANSFORMATIONMATRICES_H_ */
