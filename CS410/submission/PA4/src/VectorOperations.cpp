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
			|| (nonParallel->x_coordinate < -EPSILON && nonParallel->y_coordinate < -EPSILON
					&& (nonParallel->z_coordinate - 1.0) < -EPSILON  )) {
		nonParallel->x_coordinate = 1.0;
	}
	else if ( (nonParallel->y_coordinate < nonParallel->z_coordinate &&
			nonParallel->y_coordinate < nonParallel->x_coordinate) || (nonParallel->y_coordinate < -EPSILON
					&& nonParallel->z_coordinate < -EPSILON && (nonParallel->x_coordinate - 1.0) < -EPSILON  ) ) {
		nonParallel->y_coordinate = 1.0;
	}
	else {
		nonParallel->z_coordinate = 1.0;
	}

	return Normalize(nonParallel);
}


float VectorOperations::DotProduct(Vertex *v1, Vertex *v2){
	float result;

	result = v1->x_coordinate*v2->x_coordinate + v1->y_coordinate*v2->y_coordinate + v1->z_coordinate*v2->z_coordinate;

	return result;
}

bool VectorOperations::testIfOrthogonal (Vertex *v1, Vertex *v2){

	if (this->DotProduct(v1, v2) < EPSILON) {
		return true;
	}
	else {
		return false;
	}

}

bool VectorOperations::testIfUnitVector (Vertex *v){

	if (fabs(this->Magnitude(v) - 1.00) < EPSILON) {
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
	return sqrt((x*x)+(y*y)+(z*z));
}

Vertex * VectorOperations::GetVector (Vertex *v1, Vertex *v2) {
	Vertex * v = new Vertex();

	v->x_coordinate = v1->x_coordinate - v2->x_coordinate;
	v->y_coordinate = v1->y_coordinate - v2->y_coordinate;
	v->z_coordinate = v1->z_coordinate - v2->z_coordinate;

	return v;

}
Vertex * VectorOperations::GetNormalizedVector (Vertex *v1, Vertex *v2) {

	Vertex *N;

	Vertex *v = this->GetVector(v1,v2);

	N = this->Normalize(v);

	delete v;

	return N;

}

Vertex * VectorOperations::ScaleVector(Vertex *v, float scalar) {

	Vertex * result = new Vertex;

	result->x_coordinate = v->x_coordinate * scalar;
	result->y_coordinate = v->y_coordinate * scalar;
	result->z_coordinate = v->z_coordinate * scalar;

	return result;
}

Vertex * VectorOperations::AddVectors(Vertex *v1, Vertex *v2) {
	Vertex * result = new Vertex();
	result->x_coordinate = v1->x_coordinate + v2->x_coordinate;
	result->y_coordinate = v1->y_coordinate + v2->y_coordinate;
	result->z_coordinate = v1->z_coordinate + v2->z_coordinate;

	return result;
}


void VectorOperations::PrintVector(Vertex * v) {
	cout << "Vector (x, y, z) is (" << v->x_coordinate << ", " <<
			v->y_coordinate << ", " << v->z_coordinate << ")" << endl;

}

float * VectorOperations::SolveForIntersection(Vertex L, Vertex A, Vertex B, Vertex C, Vertex U) {
	float * result = new float[3]();

	float M;

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

	//result = this->matrix_operations->LUDecomposition(rhs, lhs);

	this->matrix_operations->Determinant(rhs);

	no_solution = false;
	if (this->matrix_operations->deteminant_zero == true) {
		no_solution = true;
	}

	float ei_minus_hf = rhs[4]*rhs[8] - rhs[5]*rhs[7];
	float gf_minus_di = rhs[2]*rhs[7] - rhs[1]*rhs[8];
	float dh_minus_eg = rhs[1]*rhs[5] - rhs[4]*rhs[2];
	float ak_minus_gb = (rhs[0]*lhs[1] - lhs[0]*rhs[3]);
	float jc_minus_al = lhs[0]*rhs[6] - rhs[0]*lhs[2];
	float bl_minus_kc = rhs[3]*lhs[2] - lhs[1]*rhs[6];

	M = rhs[0]*ei_minus_hf + rhs[3]*gf_minus_di + rhs[6]*dh_minus_eg;

	result[0] = (lhs[0]*ei_minus_hf + lhs[1]*gf_minus_di + lhs[2]*dh_minus_eg) / M;

	result[1] = (rhs[8]*ak_minus_gb + rhs[5]*jc_minus_al + rhs[2]*bl_minus_kc) / M;

	result[2] = -(rhs[7]*ak_minus_gb + rhs[4]*jc_minus_al + rhs[1]*bl_minus_kc) / M;




	delete lhs;
	delete rhs;

	return result;


}
