/*
 * Face.h
 *
 *  Created on: Oct 7, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_FACE_H_
#define INCLUDE_FACE_H_
#include "Vertex.h"
#include "FaceProperties.h"
#include <stdint.h>
#include <vector>

/*
 * Class to store one face object
 * */
class Face : public FaceProperties {

private:
	uint16_t size;
	vector<Vertex> vertex;
	vector<uint64_t> vertex_ids;

public:
	Face();

	/*
	 * Add vertex to face and vertex id based on its index in
	 * the ply file
	 * * */
	void addVertexToFace(Vertex v, uint64_t vertex_id);

	/*
	 * Get size of face
	 * * */
	uint16_t getSizeOfFace(void);

	/*
	 * Get vertex at 'index' from face
	 * */
	Vertex getVertexFromFace(uint16_t index);

	uint64_t getVertexIdFromFace(uint16_t index) {
		return this->vertex_ids.at(index);
	}

	/*
	 * Get a vector of vertices in the face
	 * */
	vector<Vertex> getAllVerticesFromFace (void);

	vector<uint64_t> getFaceVertexIds (void);
};

#endif /* INCLUDE_FACE_H_ */
