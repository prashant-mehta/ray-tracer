/*
 * ParsePlyAttributes.h
 *
 *  Created on: Sep 12, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_PARSEPLYATTRIBUTES_H_
#define INCLUDE_PARSEPLYATTRIBUTES_H_

#include <iostream>
#include <stdint.h>
#include <string>
using namespace std;

class ParsePlyAttributes {
private:
	string attributes_to_parse;
	uint64_t number_of_vertices;

	uint64_t number_of_faces;

	uint64_t number_of_properties;

public:
	ParsePlyAttributes();
	ParsePlyAttributes(string);

	void SetNumberOfVertices(uint64_t parsed_number_of_vertices){
			number_of_vertices = parsed_number_of_vertices;
	}

	void SetNumberOfFaces(uint64_t parsed_number_of_faces){
			number_of_faces = parsed_number_of_faces;
	}


	void SetNumberOfProperties(uint64_t parsed_number_of_properties){
				number_of_properties = parsed_number_of_properties;
	}

	uint64_t GetNumberOfVertices(void){
		return number_of_vertices;
	}

	uint64_t GetNumberOfFaces(void){
		return number_of_faces;
	}

	uint64_t GetNumberOfProperties(void){
			return number_of_properties;
	}


	virtual ~ParsePlyAttributes();
};



#endif /* INCLUDE_PARSEPLYATTRIBUTES_H_ */
