/*
 * Face.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: prashantm
 */

#include <Face.h>

Face::Face() {
	// TODO Auto-generated constructor stub
	this->size = 0;
	this->vertex.begin();
	this->vertex_ids.begin();
}

void Face::addVertexToFace(Vertex v, uint64_t vertex_id){
	this->vertex.push_back(v);
	this->vertex_ids.push_back(vertex_id);
	this->size++;
}

Vertex Face::getVertexFromFace(uint16_t index){
	return this->vertex.at(index);
}

vector<Vertex> Face::getAllVerticesFromFace (void){
	return this->vertex;
}

uint16_t Face::getSizeOfFace(void) {
	return this->size;
}


vector<uint64_t> Face::getFaceVertexIds (void){
	return this->vertex_ids;
}
