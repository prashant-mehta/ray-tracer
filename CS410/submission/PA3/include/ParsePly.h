/*
 * ParsePly.h
 *
 *  Created on: Sep 12, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_PARSEPLY_H_
#define INCLUDE_PARSEPLY_H_



#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>
#include <cstdlib>
#include <ParsePlyAttributes.h>
#include <Vertex.h>
#include <Face.h>
#include <vector>
#include <cmath>
#include <VectorOperations.h>

using namespace std;

class ParsePly {

private:
	ifstream inputfile;
	// string file_contents;

	// Store complete file contents in these three separate parts
	// string attributes_from_input;
	// string vertices_from_input;
	// string faces_from_input;

	vector<Vertex> vertices;

	Vertex * mean_vertex;
	Vertex * minimum_bounds;
	Vertex * maximum_bounds;

	float radius;

	vector<Face> faces;

	ofstream vertex_properties_file;

	ofstream vertices_file;

	// ParsePlyAttributes object
	ParsePlyAttributes* parseAttributesObj;
	VectorOperations * vector_operations;
	string input_filename;



public:

	bool all_triangles;

	ParsePly(string filename);


	/* Function to return all file attributes as a string */
	// string GetPlyFileAttributes(void){return attributes_from_input;}



	/*
	 * This function will print all ply attributes as specified in the problem specification
	 *
	 */

	void PrintPlyAttributes(void);

	void PrintVerticesMeanAndBounds(void);

	// Functions to parse number of vertices and faces from single line string
	void ParseNumberOfVertices(string);

	void ParseNumberOfFaces(string);

	uint64_t GetNumberOfVertices(void){
			return parseAttributesObj->GetNumberOfVertices();
		}

	uint64_t GetNumberOfFaces(void){
		return parseAttributesObj->GetNumberOfFaces();
	}

	void ComputeRadius(void);

	float GetRadius(void) {
		return radius;
	}
	/*************************************************************************/

	// Function to parse vertex co-ordinates from single line and add it to vertices vector

	Vertex * GetMeanVertex(void){
		return this->mean_vertex;
	}

	void ParseVertexLine(string);


	void ParseVertexCoordinates(string);


	void ParseFaceVertices(string);

	vector<Vertex> GetParsedVertices(void){
		return vertices;
	}

	vector<Face> GetParsedFaces(void){
			return this->faces;
	}
	// string GetPlyFaces(void){return faces_from_input;}

	void ParseAllVertices(string filename);

	/*
	 * Parse faces from faces.txt file
	 *  */
	void ParseFaces(string filename);

	void CloseReadFile(void);
};

#endif /* INCLUDE_PARSEPLY_H_ */
