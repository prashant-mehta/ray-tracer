/*
 * ProjectionMatrix.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: prashantm
 */

#include <ProjectionMatrix.h>

ProjectionMatrix::ProjectionMatrix(Vertex fp, Vertex lp, Vertex vup, float d) {
	// TODO Auto-generated constructor stub

	focal_point = fp;
	look_at_point = lp;
	vup_vector = vup;
	focal_length = d;

	this->transformation_matrices = new TransformationMatrices();
	this->vector_operations = new VectorOperations();
	this->matrix_operations = new MatrixOperations();

	this->TranslationMatrix();

	this->CalculateOpticalAxis();
	this->CalculateuAxis();
	this->CalculatevAxis();
	this->CalculateRMatrix();

	this->CalculatePMatrix();

	this->CalculateProjectionMatrix();


}

void ProjectionMatrix::TranslationMatrix (void) {

	T = this->transformation_matrices->TranslationMatrix(-focal_point.x_coordinate,
			-focal_point.y_coordinate, -focal_point.z_coordinate);
}

void ProjectionMatrix::CalculateOpticalAxis(void) {
	Vertex N(look_at_point.x_coordinate - focal_point.x_coordinate, look_at_point.y_coordinate - focal_point.y_coordinate,
			look_at_point.z_coordinate - focal_point.z_coordinate, "ignore");

	this->nVec = this->vector_operations->Normalize(&N);
}

void ProjectionMatrix::CalculateuAxis(void) {
	Vertex * U = this->vector_operations->CrossProduct(&vup_vector, this->nVec);

	this->uVec = this->vector_operations->Normalize(U);
}


void ProjectionMatrix::CalculatevAxis(void) {
	this->vVec = this->vector_operations->CrossProduct(this->nVec, this->uVec);

}

void ProjectionMatrix::CalculateRMatrix(void) {
	this->R = this->transformation_matrices->GetUnitTransformationMatrix();

	this->R[0] = this->uVec->x_coordinate;
	this->R[1] = this->uVec->y_coordinate;
	this->R[2] = this->uVec->z_coordinate;

	this->R[4] = this->vVec->x_coordinate;
	this->R[5] = this->vVec->y_coordinate;
	this->R[6] = this->vVec->z_coordinate;

	this->R[8] = this->nVec->x_coordinate;
	this->R[9] = this->nVec->y_coordinate;
	this->R[10] = this->nVec->z_coordinate;
}


void ProjectionMatrix::CalculatePMatrix(void) {
	this->P = this->transformation_matrices->GetUnitTransformationMatrix();


	this->P[14] = 1.0 / focal_length;
	this->P[15] = 0.0;
}

void ProjectionMatrix::CalculateProjectionMatrix(void) {

	this->M = this->matrix_operations->MatrixMultiply(this->P, this->matrix_operations->MatrixMultiply(this->R,
			this->T, 4, 4, 4), 4, 4, 4);
}
