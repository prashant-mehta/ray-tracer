/*
 * Casting.h
 *
 *  Created on: Oct 10, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_CASTING_H_
#define INCLUDE_CASTING_H_

#include <ProjectionMatrix.h>
#include <Face.h>
#include <ParseCameraModel.h>
#include <ParsePly.h>
#include <TransformationMatrices.h>
#include <WritePpm.h>
#include <CreateTriangles.h>
#include <WritePly.h>
#include <ParseMaterials.h>
#include <algorithm>

using namespace std;


class Casting {


private:
	vector<string> input_models;
	string camera_filename;
	string materials_filename;
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

	ParseMaterials * parse_materials;

	// Camera characteristics
	Vertex * vup_vector;
	float focal_length;
	Vertex * focal_point;
	Vertex * look_at_point;
	int32_t uMin, uMax, vMin, vMax;
	int32_t uSize, vSize;

	// Object characteristics
	Vertex mean_vertex;

	// Mean vertices, num_triangles and radii of each model
	vector<Vertex> mean_vertices;
	vector<uint64_t> num_triangles_in_model;
	vector<float> radii;


	// For storing all polygons

	vector<Face> all_triangles;

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
	Vertex *ZeroVertex;



	float min_color, max_color;


public:
	Casting(int argc, char **argv);
	void CastingForModel(void);
	void ParseArguments(int argc, char **argv);
	Vertex * ComputeSurfaceNormal(Vertex A, Vertex B, Vertex C, Vertex *V);
	Vertex * ComputePointOfIntersection(Vertex L, float t);
	Vertex * ComputeReflectedRay(Vertex *N, Vertex *L);
	void AmbientReflection(uint32_t a, uint32_t b, float *diffuse_reflectance, LightSource ls);

	void DiffuseReflection(uint32_t a, uint32_t b, float *diffuse_reflectance, LightSource ls, float cosTheta);

	void SpecularReflection(uint32_t a, uint32_t b, float specular_reflectance, float shininess_exponent, LightSource ls, float VdotR);

	bool RayTriangleIntersection(Face, Vertex, Vertex, float);
};

#endif /* INCLUDE_SILHOUETTE_H_ */
