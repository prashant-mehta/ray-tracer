/*
 * MatrixOperations.cpp
 *
 *  Created on: Sep 12, 2015
 *      Author: prashantm
 */

// TODO: Matrix product of array and vector of vertices. Matrix transpose, Cross product and dot product

#include <MatrixOperations.h>

MatrixOperations::MatrixOperations() {
	// TODO Auto-generated constructor stub
	deteminant_zero = false;


}

float MatrixOperations::Determinant(float *matrix) {
	float result;

	deteminant_zero = false;

	result = matrix[0]*(matrix[4]*matrix[8] - matrix[5]*matrix[7]) - matrix[1]*(matrix[3]*matrix[8] - matrix[5]*matrix[6])
			+ matrix[2]*(matrix[3]*matrix[7] - matrix[4]*matrix[6]);



	if (fabs(result) < EPSILON ) deteminant_zero = true;

	return result;
}

// Print a 4x4 matrix

void MatrixOperations::PrintMatrix(float* operand_one) {


	// cout << "From print matrix" << operand_one[0] << endl;

	uint64_t operand_one_columns = 4;

	for ( int i = 0; i < 4; i++ ){
		for ( int k = 0; k < 4; k++ ){
			cout << operand_one(i, k) << ", ";
		}
		cout << endl;
	}

	cout << endl;

}

// 4x4 matrix multiply operation
void MatrixOperations::MatrixMultiply(float operand_one[4][4], float operand_two[4][4], float result[4][4]){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			result[i][j] = 0.0;
			for (int k = 0; k < 4; k++){
				result[i][j] += operand_one[i][k]*operand_two[k][j];
			}

		}
	}
}

float* MatrixOperations::MatrixMultiply(float* operand_one, float* operand_two, uint64_t operand_one_rows,
		uint64_t operand_one_columns, uint64_t operand_two_columns){

	float* result = new float[operand_one_rows*operand_two_columns];

	for (int i = 0; i < operand_one_rows; i++){

		for (int j = 0; j < operand_two_columns; j++){

			result(i, j) = 0.0;

			for (int k = 0; k < operand_one_columns; k++){

				result(i, j) += operand_one(i, k)*operand_two(k, j);

			}

		}
	}

	return result;
}

vector<Vertex> MatrixOperations::MatrixMultiply(float* operand_one, vector<Vertex> operand_two, uint64_t operand_one_rows,
		uint64_t operand_one_columns, uint64_t operand_two_columns){


	vector<Vertex> result;



	Vertex transformedvertex;

	for (int i = 0; i < operand_two_columns; i++) {

		transformedvertex.x_coordinate  = operand_two.at(i).x_coordinate*operand_one[0];
		transformedvertex.x_coordinate += operand_two.at(i).y_coordinate*operand_one[1];
		transformedvertex.x_coordinate += operand_two.at(i).z_coordinate*operand_one[2];
		transformedvertex.x_coordinate += operand_one[3];

		transformedvertex.y_coordinate  = operand_two.at(i).x_coordinate*operand_one[4];
		transformedvertex.y_coordinate += operand_two.at(i).y_coordinate*operand_one[5];
		transformedvertex.y_coordinate += operand_two.at(i).z_coordinate*operand_one[6];
		transformedvertex.y_coordinate += operand_one[7];

		transformedvertex.z_coordinate  = operand_two.at(i).x_coordinate*operand_one[8];
		transformedvertex.z_coordinate += operand_two.at(i).y_coordinate*operand_one[9];
		transformedvertex.z_coordinate += operand_two.at(i).z_coordinate*operand_one[10];
		transformedvertex.z_coordinate += operand_one[11];

//		transformedvertex.x_coordinate  = operand_two.at(i).x_coordinate*operand_one[12];
//		transformedvertex.x_coordinate += operand_two.at(i).y_coordinate*operand_one[13];
//		transformedvertex.x_coordinate += operand_two.at(i).z_coordinate*operand_one[14];
//		transformedvertex.x_coordinate += operand_one[15];

		result.push_back(transformedvertex);

	}

	return result;
}

float* MatrixOperations::MatrixTranspose(float* operand_one, uint64_t operand_one_rows, uint64_t operand_one_columns){

	float* result = new float[operand_one_rows*operand_one_columns];

	for (int i = 0; i < operand_one_columns; i++) {
		for (int j = 0; j < operand_one_rows; j++) {
			result[i*operand_one_rows + j] = operand_one[i+ j*operand_one_columns];

		}

	}
	return result;
}

/*
 * Reference from - http://m.njit.edu/~bukiet/M611/numcode/gauss.c
 * */
float * MatrixOperations::GaussianElimination(float *matrix3, float *column) {
	float * result = new float[3];

	float factor, temp;

	this->Determinant(matrix3);

	if (deteminant_zero == true) {
		result[0] = 0.0;
		result[1] = 0.0;
		result[2] = 0.0;
		return result;
	}

	for (int i = 0; i < 2; i++) {
		for (int j = i + 1; j < 3; j++) {
			factor = matrix3(j, i) / matrix3(i, i);

			for (int k = i; k < 3; k++) {
				matrix3(j, k) -= (factor * matrix3(i, k));
			}
			column[j] -= (factor * column[i]);
		}
	}

	// Backward substitution
	result[2] = column[2] / matrix3[8];

	for (int i = 1; i >= 0; i--) {
		temp = column[i];
		for (int j = i + 1; j < 3; j++) {
			temp -= (matrix3(i, j) * result[j]);
		}
		result[i] = temp / matrix3(i, i);
	}

	return result;

}


float * MatrixOperations::LUDecomposition(float *matrix3, float *column) {
	float * result = new float[3]();
	float * Z = new float[3]();
	float * L = new float[9]();
	float * U = new float[9]();

	float sum, temp;
	int i, j, k;

	this->Determinant(matrix3);

	if (deteminant_zero == true) {
		return result;
	}

	for (i = 0; i < 3; i++) {
		U(i, i) = 1;
		for (j = i; j < 3; j++) {
			sum = 0;
			for (k = 0; k < i; k++) {
				sum += L(j, k)*U(k, i);
			}
			L(j, i) = matrix3(j, i) - sum;
		}

		for (j = i + 1; j < 3; j++ ){
            sum = 0;
            for(k = 0; k < i; k++ ) {
                sum += L(i, k)*U(k, j);
            }
            U(i, j) = (matrix3(i, j) - sum) / L(i, i);
		}
	}


	// Finding Z -> LZ = b
	for (i = 0; i < 3; i++) {
		sum = 0;
		for (j = 0; j < i; j++) {
			sum += L(i, j)*Z[j];
		}
		Z[i] = (column[i] - sum) / L(i, i);
	}


	// Finding X -> UX = Z
	for (i = 2; i >= 0; i--) {
		sum = 0;
		for (j = 2; j > i ; j--) {
			sum += U(i, j) * result[j];
		}
		result[i] = (Z[i] - sum) / U(i, i);
	}



	delete L;
	delete U;
	delete Z;

	return result;
}
