/*
 * VectorOperations.cpp
 *
 *  Created on: Sep 19, 2015
 *      Author: prashantm
 */

#include <VectorOperations.h>

VectorOperations::VectorOperations() {
	// TODO Auto-generated constructor stub

	this->matrix_operations = new MatrixOperations();
	no_solution = false;
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
			|| (nonParallel->x_coordinate < 0.000001 && nonParallel->y_coordinate < 0.000001
					&& (nonParallel->z_coordinate - 1) < 0.000001  )) {
		nonParallel->x_coordinate = 1;
	}
	else if ( (nonParallel->y_coordinate < nonParallel->z_coordinate &&
			nonParallel->y_coordinate < nonParallel->x_coordinate) || (nonParallel->y_coordinate < 0.000001
					&& nonParallel->z_coordinate < 0.000001 && (nonParallel->x_coordinate - 1) < 0.000001  ) ) {
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

float VectorOperations::Distance(Vertex *v1, Vertex *v2) {
	float x, y, z;
	x = v1->x_coordinate - v2->x_coordinate;
	y = v1->y_coordinate - v2->y_coordinate;
	z = v1->z_coordinate - v2->z_coordinate;
	return sqrtf((x*x)+(y*y)+(z*z));
}


void VectorOperations::PrintVector(Vertex * v) {
	cout << "Vector (x, y, z) is (" << v->x_coordinate << ", " <<
			v->y_coordinate << ", " << v->z_coordinate << ")" << endl;

}

float * VectorOperations::SolveForIntersection(Vertex L, Vertex A, Vertex B, Vertex C, Vertex U) {
	float * result;

	float * lhs = new float[3];

	float * rhs = new float[9];

	lhs[0] = L.x_coordinate - A.x_coordinate;
	lhs[1] = L.y_coordinate - A.y_coordinate;
	lhs[2] = L.z_coordinate - A.z_coordinate;

	rhs[0] = B.x_coordinate - A.x_coordinate;
	rhs[1] = C.x_coordinate - A.x_coordinate;
	rhs[2] = - U.x_coordinate;

	rhs[3] = B.y_coordinate - A.y_coordinate;
	rhs[4] = C.y_coordinate - A.y_coordinate;
	rhs[5] = - U.y_coordinate;

	rhs[6] = B.z_coordinate - A.z_coordinate;
	rhs[7] = C.z_coordinate - A.z_coordinate;
	rhs[8] = - U.z_coordinate;

	result = this->matrix_operations->GaussianElimination(rhs, lhs);

	no_solution = false;
	if (this->matrix_operations->deteminant_zero == true) {
		no_solution = true;
	}

	delete lhs;
	delete rhs;

	return result;


}
