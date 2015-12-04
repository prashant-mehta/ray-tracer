/*
 * ProjectionMatrix.h
 *
 *  Created on: Oct 10, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_PROJECTIONMATRIX_H_
#define INCLUDE_PROJECTIONMATRIX_H_

#include <Vertex.h>
#include <MatrixOperations.h>
#include <TransformationMatrices.h>


class ProjectionMatrix {

private:
	Vertex focal_point;
	Vertex look_at_point;
	Vertex vup_vector;

	float focal_length;

	float * P;
	float * R;
	float * T;
	float * M;

	Vertex * nVec;
	Vertex * uVec;
	Vertex * vVec;

	VectorOperations * vector_operations;
	MatrixOperations * matrix_operations;
	TransformationMatrices * transformation_matrices;

public:
	ProjectionMatrix(Vertex fp, Vertex lp, Vertex vup, float d);

	void TranslationMatrix (void);

	float * GetTranslationMatrix(void) {
		return this->T;
	}

	// (Look-at-point - focal point) viz n vector
	void CalculateOpticalAxis(void);

	Vertex * GetnVector(void) {
		return this->nVec;
	}

	void CalculateuAxis(void);

	Vertex * GetuVector(void) {
		return this->uVec;
	}

	void CalculatevAxis(void);

	Vertex * GetvVector(void) {
		return this->vVec;
	}

	void CalculateRMatrix(void);

	float * GetRMatrix(void) {
		return this->R;
	}

	void CalculatePMatrix(void);

	float * GetPMatrix(void) {
		return this->P;
	}

	// M = PRT
	void CalculateProjectionMatrix(void);

	float * GetProjectionMatrix(void) {
		return this->M;
	}
};

#endif /* INCLUDE_PROJECTIONMATRIX_H_ */
