/*
 * Silhouette.h
 *
 *  Created on: Oct 10, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_SILHOUETTE_H_
#define INCLUDE_SILHOUETTE_H_

#include <ProjectionMatrix.h>
#include <Face.h>
#include <ParseCameraModel.h>
#include <ParsePly.h>
#include <TransformationMatrices.h>
#include <WritePpm.h>
#include <CreateTriangles.h>
#include <WritePly.h>


class Silhouette {


private:
	vector<string> input_models;
	string camera_filename;
	string output_filename;

	uint16_t number_of_models;
	ofstream outputfile;

	ParseCameraModel * parse_camera_model;
	ProjectionMatrix * projection_matrix;
	ParsePly * parse_ply;
	WritePpm * write_ppm;
	VectorOperations * vector_operations;
	WritePly * write_ply;

	MatrixOperations * matrix_operations;

	CreateTriangles * create_triangles;

	// Camera characteristics
	Vertex * vup_vector;
	float focal_length;
	Vertex * focal_point;
	Vertex * look_at_point;
	int32_t uMin, uMax, vMin, vMax;
	int32_t uSize, vSize;

	// Object characteristics
	Vertex mean_vertex;

	// For ray-sphere intersection
	float radius, radiusSquare;
	float c, cSquare;
	Vertex * U;
	float v, vSquare;

	// Vector to store pixel colors
	vector<Pixel> pixel_colors;

	// Projection matrix characteristics
	Vertex * uVec;
	Vertex * vVec;
	Vertex * nVec;

	Vertex fpPlusdn;

public:
	Silhouette(int argc, char **argv);
	void SilhouetteForModel(const char *);
	void ParseArguments(int argc, char **argv);
};

#endif /* INCLUDE_SILHOUETTE_H_ */
