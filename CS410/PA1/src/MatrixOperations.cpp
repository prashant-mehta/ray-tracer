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
			result[i][j] = 0;
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

			result(i, j) = 0;

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