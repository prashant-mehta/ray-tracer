/*
 * TransformationMatrices.cpp
 *
 *  Created on: Sep 13, 2015
 *      Author: prashantm
 */

#include <TransformationMatrices.h>

TransformationMatrices::TransformationMatrices() {
	// TODO Auto-generated constructor stub

	this->vector_operations = new VectorOperations();
	this->matrix_operations = new MatrixOperations();
}

float* TransformationMatrices::GetUnitTransformationMatrix(void){
	float* matrix = new float[16];

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (i == j){
				matrix(i, j) = 1;
			}
			else{
				matrix(i, j) = 0;
			}

		}
	}
	return matrix;
}


float* TransformationMatrices::ScaleMatrix(float x_axis, float y_axis, float z_axis){
	float *matrix = this->GetUnitTransformationMatrix();

	matrix[0] = x_axis;

	matrix[5] = y_axis;

	matrix[10] = z_axis;

	// this->PrintTransformationMatrix(matrix);

	// cout << "Printed matrix" << endl;

	return matrix;
}

float* TransformationMatrices::TranslationMatrix(float x_coordinate, float y_coordinate, float z_coordinate){
	float *matrix = this->GetUnitTransformationMatrix();

	matrix[3] = x_coordinate;

	matrix[7] = y_coordinate;

	matrix[11] = z_coordinate;



	return matrix;

}

float* TransformationMatrices::RotationMatrixAcrossZ(float angle_of_rotation){
	float *matrix = this->GetUnitTransformationMatrix();

	float angle_in_radians = angle_of_rotation * PI / 180 ;

	matrix[0] = cosf(angle_in_radians);
	matrix[1] = - sinf(angle_in_radians);

	matrix[4] = sinf(angle_in_radians);
	matrix[5] = cosf(angle_in_radians);

	return matrix;

}

float* TransformationMatrices::RotationOmegaMatrix(float x_axis, float y_axis, float z_axis){
	Vertex * W = new Vertex(x_axis, y_axis, z_axis, "ignore this");



	Vertex * w = this->vector_operations->Normalize(W);


	// this->vector_operations->PrintVector(w);

	Vertex * m = this->vector_operations->NonParallelUnitVector(w);
	Vertex * U = this->vector_operations->CrossProduct(w, m);
	Vertex * u = this->vector_operations->Normalize(U);

	Vertex * V = this->vector_operations->CrossProduct(w, u);

	Vertex * v = this->vector_operations->Normalize(V);

	float *matrix = this->GetUnitTransformationMatrix();


/*
	if (this->vector_operations->testIfOrthogonal(u, V) == true)
		cout << "u and V are orthogonal" << endl;

	if (this->vector_operations->testIfOrthogonal(u, w) == true)
			cout << "u and w are orthogonal" << endl;

	if (this->vector_operations->testIfOrthogonal(V, w) == true)
			cout << "V and w are orthogonal" << endl;


	if (this->vector_operations->testIfUnitVector(u) == true)
			cout << "u is unit vector" << endl;

	if (this->vector_operations->testIfUnitVector(V) == true)
				cout << "V is unit vector" << endl;

	if (this->vector_operations->testIfUnitVector(w) == true)
				cout << "w is unit vector" << endl;
*/

	matrix[0] = u->x_coordinate;
	matrix[1] = u->y_coordinate;
	matrix[2] = u->z_coordinate;

	matrix[4] = V->x_coordinate;
	matrix[5] = V->y_coordinate;
	matrix[6] = V->z_coordinate;

	matrix[8] = w->x_coordinate;
	matrix[9] = w->y_coordinate;
	matrix[10] = w->z_coordinate;


	// this->matrix_operations->PrintMatrix(matrix);

	delete(W);
	delete(w);
	delete(m);
	delete(U);
	delete(V);

	return matrix;
}

float* TransformationMatrices::RotationMatrix(float x_axis, float y_axis, float z_axis, float angle_of_rotation){

	float *r_omega = this->RotationOmegaMatrix(x_axis, y_axis, z_axis);

	float *r_z_theta = this->RotationMatrixAcrossZ(angle_of_rotation);

	float *r_omega_transpose = this->matrix_operations->MatrixTranspose(r_omega, 4, 4);


	// this->matrix_operations->PrintMatrix(r_z_theta);

	return this->matrix_operations->MatrixMultiply(this->matrix_operations->MatrixMultiply(r_omega_transpose,
			r_z_theta, 4, 4, 4), r_omega, 4, 4, 4);

}

float* TransformationMatrices::TransformationMatrix(Vertex input_parameters,
		char const transform, float* transformation_matrix){

	char *pEnd;

	float *matrix;

	if (transform == 'R') { // Parse theta and apply rotation
		// cout <<  " Apply rotation " << endl;

		// Convert angle of rotation from vertex properties (string) into float
		float angle_of_rotation = strtof(input_parameters.properties, &pEnd);

		// cout << angle_of_rotation << endl;

		matrix = this->matrix_operations->MatrixMultiply(this->RotationMatrix(input_parameters.x_coordinate,
						input_parameters.y_coordinate, input_parameters.z_coordinate, angle_of_rotation), transformation_matrix, 4, 4, 4);
	}
	else if ( transform == 'S' ) {
		// cout <<  " Apply scaling " << endl;

		matrix = this->matrix_operations->MatrixMultiply(this->ScaleMatrix(input_parameters.x_coordinate,
				input_parameters.y_coordinate, input_parameters.z_coordinate), transformation_matrix, 4, 4, 4);
	}
	else if ( transform == 'T' ) {
		// cout <<  " Apply translation " << endl;
		matrix = this->matrix_operations->MatrixMultiply(this->TranslationMatrix(input_parameters.x_coordinate,
				input_parameters.y_coordinate, input_parameters.z_coordinate), transformation_matrix, 4, 4, 4);

	}

	return matrix;


}


void TransformationMatrices::PrintTransformationMatrix(float *transformation_matrix) {

	// cout << "Present transformation matrix is :" << transformation_matrix[0] <<  endl;

	this->matrix_operations->PrintMatrix(transformation_matrix);

}
