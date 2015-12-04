/*
 * CreateTriangles.cpp
 *
 *  Created on: Oct 11, 2015
 *      Author: prashantm
 */

#include <CreateTriangles.h>

CreateTriangles::CreateTriangles(vector<Face> inputfaces) {
	// TODO Auto-generated constructor stub

	uint64_t input_number_of_faces = inputfaces.size();

	triangles.clear();



	Vertex first_vertex;
	uint64_t first_vertex_id;
	float *k; // diffuse reflectance

	for (uint64_t i = 0; i < input_number_of_faces; i++) {

		// If already a triangle - keep the face and continue
		if(inputfaces.at(i).getSizeOfFace() == 3) {
			triangles.push_back(inputfaces.at(i));
			continue;
		}
		first_vertex = inputfaces.at(i).getVertexFromFace(0);
		first_vertex_id = inputfaces.at(i).getVertexIdFromFace(0);


		// Get first vertex and create triangles with all other edges which do not contain the first vertex
		// Creating facesize - 2 triangles
		for (uint32_t j = 0; j < inputfaces.at(i).getSizeOfFace() - 2; j++) {
			Face triangle_to_add;
			triangle_to_add.addVertexToFace(first_vertex, first_vertex_id);
			triangle_to_add.addVertexToFace(inputfaces.at(i).getVertexFromFace(j+1),
					inputfaces.at(i).getVertexIdFromFace(j+1));
			triangle_to_add.addVertexToFace(inputfaces.at(i).getVertexFromFace(j+2),
								inputfaces.at(i).getVertexIdFromFace(j+2));

			k = inputfaces.at(i).getDiffuseReflectance();

			triangle_to_add.setDiffuseReflectance(k[0], k[1], k[2]);
			triangle_to_add.setSpecularReflectance(inputfaces.at(i).getSpecularReflectance());
			triangle_to_add.setShininessExponent(inputfaces.at(i).getShininessExponent());

			triangles.push_back(triangle_to_add);

		}


	}

}

