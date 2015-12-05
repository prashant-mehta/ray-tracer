/*
 * Vertex.h
 *
 *  Created on: Sep 11, 2015
 *      Author: prashantm
 */


#ifndef INCLUDE_VERTEX_H_
#define INCLUDE_VERTEX_H_



#include <iostream>
#include <cfloat>
using namespace std;

#define EPSILON 0.000000001 // Previously 10^-6

class Vertex {
public:
	float x_coordinate, y_coordinate, z_coordinate;
	const char * properties;
	Vertex ();
	Vertex (const float, const float, const float, const char *);

	void PrintVertex(void);


};

#endif /* INCLUDE_VERTEX_H_ */
