/*
 * ParseMaterials.h
 *
 *  Created on: Oct 31, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_PARSEMATERIALS_H_
#define INCLUDE_PARSEMATERIALS_H_

#include <vector>
#include <Face.h>
#include <LightSource.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

class ParseMaterials {
public:
	vector<LightSource> light_sources;
	uint32_t ambient_light_source_index;

	ParseMaterials(char const *filename, vector<Face>& faces, uint32_t model_number);

	void ParseLightSource(string line_to_parse);

	void ParseMaterialProperties(string line_to_parse, vector<Face>& faces, uint32_t model_number);
};

#endif /* INCLUDE_PARSEMATERIALS_H_ */
