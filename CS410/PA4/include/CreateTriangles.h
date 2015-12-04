/*
 * CreateTriangles.h
 *
 *  Created on: Oct 11, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_CREATETRIANGLES_H_
#define INCLUDE_CREATETRIANGLES_H_

#include <Face.h>
#include <ParsePly.h>


/* Take the easy way out right now. Just re-use the first vertex of each face
 * to create triangles. No need to changed vertices.
 *
 */
class CreateTriangles {
private:
	vector<Face> triangles;


public:
	CreateTriangles(const vector<Face>& );

	vector<Face> GetTriangles(void) {
		return this->triangles;
	}
};

#endif /* INCLUDE_CREATETRIANGLES_H_ */
