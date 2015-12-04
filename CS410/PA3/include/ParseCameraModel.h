/*
 * ParseCameraModel.h
 *
 *  Created on: Oct 10, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_PARSECAMERAMODEL_H_
#define INCLUDE_PARSECAMERAMODEL_H_

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>
#include <cstdlib>
#include <cmath>
#include <Vertex.h>

using namespace std;

class ParseCameraModel {

private:

	Vertex * focal_point;
	Vertex * look_at_point;
	Vertex * v_up_vector;
	float focal_length; // aka 'd'


	int32_t uMin, vMin, uMax, vMax;
	int32_t uSize, vSize;



public:
	ParseCameraModel(char const *filename);

	Vertex * ParseFocalPoint(string);

	void ParseImageSize(string line_to_parse);

	void PrintAllCameraProperties(void);

	void VerifyCameraModel(void);

	Vertex * GetFocalPoint(void) {
		return this->focal_point;
	}

	Vertex * GetLookAtPoint(void) {
		return this->look_at_point;
	}

	Vertex * GetVupVector(void) {
		return this->v_up_vector;
	}

	int32_t GetImageSizeuMin (void) {
		return uMin;
	}

	int32_t GetImageSizevMin (void) {
		return vMin;
	}

	int32_t GetImageSizeuMax (void) {
		return uMax;
	}
	int32_t GetImageSizevMax (void) {
		return vMax;
	}

	int32_t GetImageSizeU (void) {
		return uSize;
	}

	int32_t GetImageSizeV (void) {
		return vSize;
	}

	float GetFocalLength (void) {
		return focal_length;
	}
};

#endif /* INCLUDE_PARSECAMERAMODEL_H_ */

