/*
 * Vertex.h
 *
 *  Created on: Sep 11, 2015
 *      Author: prashantm
 */


#ifndef INCLUDE_VERTEX_H_
#define INCLUDE_VERTEX_H_

#include <iostream>
using namespace std;

class Vertex {
public:
	float x_coordinate, y_coordinate, z_coordinate;
	const char * properties;
	Vertex ();
	Vertex (const float, const float, const float, const char *);

	void PrintVertex(void);


};

#endif /* INCLUDE_VERTEX_H_ */
