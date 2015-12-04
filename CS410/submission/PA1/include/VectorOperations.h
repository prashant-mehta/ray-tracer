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

using namespace std;

class VectorOperations {
public:
	VectorOperations();

	/*
	 * Function to compute cross prodcut of two vectors
	 *
	 */

	float Magnitude(Vertex *v);

	Vertex * Normalize(Vertex *v);

	Vertex * CrossProduct(Vertex *v1, Vertex *v2);

	//bool TestIfParallel(Vertex *v1, Vertex *v2);

	/*
	 * For computing axis M, non parallel to v
	 * */
	Vertex * NonParallelUnitVector(Vertex *v);

	void PrintVector (Vertex * v);

	float DotProduct(Vertex *v1, Vertex *v2);

	bool testIfOrthogonal (Vertex *v1, Vertex *v2);

	bool testIfUnitVector (Vertex *v);
};

#endif /* INCLUDE_VECTOROPERATIONS_H_ */
