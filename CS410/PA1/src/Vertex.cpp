/*
 * Vertex.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: prashantm
 */

#include "Vertex.h"

Vertex::Vertex() {
	// TODO Auto-generated constructor stub

	x_coordinate = 0;
	y_coordinate = 0;
	z_coordinate = 0;

	properties = "";

}

Vertex::Vertex(const float x_parameter, const float y_parameter, const float z_parameter, const char * properties_parameter) {
	// TODO Auto-generated constructor stub
	x_coordinate = x_parameter;
	y_coordinate = y_parameter;
	z_coordinate = z_parameter;
	properties = properties_parameter;
}
