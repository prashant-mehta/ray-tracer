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
#include <random>
#include <omp.h>

using namespace std;


const int anti_aliasing_pixels = 5;
const int scale_factorsU[] = {0, -1, -1, 1, 1};
const int scale_factorsV[] = {0, -1, 1, -1, 1};

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
	float radius;

	// Vector to store pixel colors
	vector<Pixel> pixel_colors[5];

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
	Vertex * ComputePointOfIntersection(Vertex L, float t, Vertex UnitVector);
	Vertex * ComputeReflectedRay(Vertex *N, Vertex *L);
	void AmbientReflection(float *diffuse_reflectance, LightSource ls, Pixel *current_pixel);

	float meanRValue(vector<Pixel> const (&pixels)[5], int a, int b);
	float meanGValue(vector<Pixel> const (&pixels)[5], int a, int b);
	float meanBValue(vector<Pixel> const (&pixels)[5], int a, int b);

	void DiffuseReflection(float *diffuse_reflectance, LightSource ls, float cosTheta, Pixel *current_pixel);

	void SpecularReflection(float specular_reflectance, float shininess_exponent, LightSource ls, float VdotR, Pixel *current_pixel);

	bool RayTriangleIntersection(Face, Vertex, Vertex, float);

	void MergeTrianglesFromModels(void);

	void FindClosestPolygon(Vertex L, Vertex RayPolygonToFP, Pixel *current_pixel, uint64_t start_triangle, uint64_t last_triangle, uint64_t current_triangle);

	void Reflection(Vertex L, Vertex RayPolygonToFP, Pixel *current_pixel, int32_t recursion_level);

	bool RaySphereIntersection(Vertex *L, Vertex **RayFPToPolygon, float radiusSquare, float cSquare);
	void ComputeRayFPToPolygon(Vertex *L, Vertex **RayFPToPolygon);
};

#endif /* INCLUDE_SILHOUETTE_H_ */
