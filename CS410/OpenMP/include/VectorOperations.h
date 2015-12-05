/*
 * VectorOperations.h
 *
 *  Created on: Sep 19, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_VECTOROPERATIONS_H_
#define INCLUDE_VECTOROPERATIONS_H_

#include <cmath>
#include <iostream>
#include "Vertex.h"
#include "MatrixOperations.h"

using namespace std;

class VectorOperations {

private:
	MatrixOperations * matrix_operations;

public:
	VectorOperations();

	/*
	 * Function to compute cross prodcut of two vectors
	 *
	 */


	float Magnitude(Vertex *v);

	Vertex * Normalize(Vertex *v);

	float Distance(Vertex *v1, Vertex *v2);

	Vertex * CrossProduct(Vertex *v1, Vertex *v2);

	Vertex * ScaleVector(Vertex *v, float scalar);

	Vertex * AddVectors(Vertex *v1, Vertex *v2);


	//bool TestIfParallel(Vertex *v1, Vertex *v2);

	/*
	 * For computing axis M, non parallel to v
	 * */
	Vertex * NonParallelUnitVector(Vertex *v);

	void PrintVector (Vertex * v);

	float DotProduct(Vertex *v1, Vertex *v2);

	bool testIfOrthogonal (Vertex *v1, Vertex *v2);

	bool testIfUnitVector (Vertex *v);

	float * SolveForIntersection(Vertex L, Vertex A, Vertex B, Vertex C, Vertex U, bool &no_solution);

	Vertex * GetVector (Vertex *v1, Vertex *v2);
	Vertex * GetNormalizedVector (Vertex *v1, Vertex *v2);
};

#endif /* INCLUDE_VECTOROPERATIONS_H_ */
