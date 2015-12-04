/*
 * MatrixOperations.h
 *
 *  Created on: Sep 12, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_MATRIXOPERATIONS_H_
#define INCLUDE_MATRIXOPERATIONS_H_

#define operand_one(i, k) operand_one[(i)*(operand_one_columns)+(k)]
#define operand_two(k, j) operand_two[(k)*(operand_two_columns)+(j)]
#define result(i, j) result[(i)*(operand_two_columns)+(j)]


#include <stdint.h>
#include <iostream>
#include <Vertex.h>
#include <vector>

using namespace std;
class MatrixOperations {
public:
	MatrixOperations();

	void MatrixMultiply(float operand_one[4][4], float operand_two[4][4], float result[4][4]);

	float* MatrixMultiply(float* operand_one, float* operand_two, uint64_t operand_one_rows,
			uint64_t common_dimension, uint64_t operand_two_columns);

	float* MatrixTranspose(float* operand_one, uint64_t operand_one_rows, uint64_t operand_one_columns);

	vector<Vertex> MatrixMultiply(float* operand_one, vector<Vertex> operand_two, uint64_t operand_one_rows,
			uint64_t operand_one_columns, uint64_t operand_two_columns);

	void PrintMatrix(float* operand_one);

};

#endif /* INCLUDE_MATRIXOPERATIONS_H_ */
