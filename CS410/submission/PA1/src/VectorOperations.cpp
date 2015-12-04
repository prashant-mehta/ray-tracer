/*
 * VectorOperations.cpp
 *
 *  Created on: Sep 19, 2015
 *      Author: prashantm
 */

#include <VectorOperations.h>

VectorOperations::VectorOperations() {
	// TODO Auto-generated constructor stub

}

float VectorOperations::Magnitude(Vertex *v){


	return sqrtf(v->x_coordinate*v->x_coordinate + v->y_coordinate*v->y_coordinate + v->z_coordinate*v->z_coordinate);

}

Vertex * VectorOperations::Normalize(Vertex *v){
	// Take magnitude and divide it by each co-ordinate

	float magnitude;
	Vertex *normalized = new Vertex();

	magnitude = Magnitude(v);

	normalized->x_coordinate = v->x_coordinate / magnitude;

	normalized->y_coordinate = v->y_coordinate / magnitude;

	normalized->z_coordinate = v->z_coordinate / magnitude;

	return normalized;
}

Vertex * VectorOperations::CrossProduct(Vertex *v1, Vertex *v2){
	Vertex *result = new Vertex();

	result->x_coordinate = v1->y_coordinate*v2->z_coordinate - v1->z_coordinate*v2->y_coordinate;

	result->y_coordinate = v1->z_coordinate*v2->x_coordinate - v1->x_coordinate*v2->z_coordinate;

	result->z_coordinate = v1->x_coordinate*v2->y_coordinate - v1->y_coordinate*v2->x_coordinate;

	return result;
}

Vertex * VectorOperations::NonParallelUnitVector(Vertex *v){

	Vertex * nonParallel = new Vertex(v->x_coordinate, v->y_coordinate, v->z_coordinate, "ignore");

	// Find smallest term in v
	if ( (nonParallel->x_coordinate < nonParallel->y_coordinate && nonParallel->x_coordinate < nonParallel->z_coordinate)
			|| (fabs(nonParallel->x_coordinate) < 0.000001 && fabs(nonParallel->y_coordinate) < 0.000001
					&& fabs(nonParallel->z_coordinate - 1) < 0.000001  )) {
		nonParallel->x_coordinate = 1;
	}
	else if ( (nonParallel->y_coordinate < nonParallel->z_coordinate &&
			nonParallel->y_coordinate < nonParallel->x_coordinate) || ( fabs(nonParallel->y_coordinate) < 0.000001
					&& fabs(nonParallel->z_coordinate) < 0.000001 && fabs(nonParallel->x_coordinate - 1) < 0.000001  ) ) {
		nonParallel->y_coordinate = 1;
	}
	else {
		nonParallel->z_coordinate = 1;
	}

	return Normalize(nonParallel);
}


float VectorOperations::DotProduct(Vertex *v1, Vertex *v2){
	float result;

	result = v1->x_coordinate*v2->x_coordinate + v1->y_coordinate*v2->y_coordinate + v1->z_coordinate*v2->z_coordinate;

	return result;
}

bool VectorOperations::testIfOrthogonal (Vertex *v1, Vertex *v2){

	if (this->DotProduct(v1, v2) == 0) {
		return true;
	}
	else {
		return false;
	}

}

bool VectorOperations::testIfUnitVector (Vertex *v){

	if (fabs(this->Magnitude(v) - 1.00) < 0.000001) {
		return true;
	}
	else {
		return false;
	}
}

void VectorOperations::PrintVector(Vertex * v) {
	cout << "Vector (x, y, z) is (" << v->x_coordinate << ", " <<
			v->y_coordinate << ", " << v->z_coordinate << ")" << endl;

}
