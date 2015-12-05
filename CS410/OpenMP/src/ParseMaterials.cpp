/*
 * ParseMaterials.cpp
 *
 *  Created on: Oct 31, 2015
 *      Author: prashantm
 */

#include <ParseMaterials.h>

ParseMaterials::ParseMaterials(char const *filename, vector<Face>& faces, uint32_t model_number) {
	// TODO Auto-generated constructor stub


	ifstream inputfile;

	inputfile.open(filename);


	if (! inputfile.is_open()){
			cout << "Materials file open failed. Exiting the code now." << endl;
			exit(EXIT_FAILURE);
	}

	string read_line;


	while (getline(inputfile, read_line) ) {

		if (read_line[0] == 'L') {
			this->ParseLightSource(read_line);
		}
		else if (read_line[0] == 'M') {
			this->ParseMaterialProperties(read_line, faces, model_number);
		}
		else {
			cout << "Unrecognizable start of line in materials file." << endl;
		}


	}

	inputfile.close();

}

void ParseMaterials::ParseLightSource(string line_to_parse) {
	uint64_t next_pos = 0;
	uint64_t last_pos = 0;
	char *pEnd;

	string substr;

	LightSource parsed_light;

	next_pos = line_to_parse.find(" ", last_pos);
	strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
	last_pos = next_pos + 1;

	next_pos = line_to_parse.find(" ", last_pos);
	parsed_light.rValue  = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
	last_pos = next_pos + 1;

	next_pos = line_to_parse.find(" ", last_pos);
	parsed_light.gValue  = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
	last_pos = next_pos + 1;

	next_pos = line_to_parse.find(" ", last_pos);
	parsed_light.bValue  = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
	last_pos = next_pos + 1;


	next_pos = line_to_parse.find(" ", last_pos);
	substr = line_to_parse.substr(last_pos, next_pos - last_pos);
	if (substr == "A") {
		// It's an ambient light
		parsed_light.isAmbient = true;
		ambient_light_source_index = light_sources.size();
	}
	else {
	// Parse for light position
		parsed_light.x_coordinate = strtof(substr.c_str(), &pEnd);
		last_pos = next_pos + 1;

		next_pos = line_to_parse.find(" ", last_pos);
		parsed_light.y_coordinate  = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
		last_pos = next_pos + 1;

		parsed_light.z_coordinate = strtof(line_to_parse.substr(last_pos, line_to_parse.size()).c_str(), &pEnd);
		parsed_light.properties = "light source";
	}

	light_sources.push_back(parsed_light);

}

void ParseMaterials::ParseMaterialProperties(string line_to_parse, vector<Face>& faces, uint32_t model_number) {
	uint64_t next_pos = 0;
	uint64_t last_pos = 0;
	char *pEnd;

	string substr;

	LightSource parsed_light;

	uint32_t first_polygon, last_polygon;

	float kr, kg, kb, ks, alpha, kt;

	// Skip 'M'
	next_pos = line_to_parse.find(" ", last_pos);
	strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
	last_pos = next_pos + 1;

	next_pos = line_to_parse.find(" ", last_pos);
	uint32_t current_model = strtol(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), NULL, 10);

	if ( current_model != model_number) {
		return;
	}
	else {
		last_pos = next_pos + 1;

		next_pos = line_to_parse.find(" ", last_pos);
		first_polygon = strtol(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), NULL, 10);
		last_pos = next_pos + 1;

		next_pos = line_to_parse.find(" ", last_pos);
		last_polygon = strtol(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), NULL, 10);
		last_pos = next_pos + 1;

		// Get diffuse reflectance
		next_pos = line_to_parse.find(" ", last_pos);
		kr = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
		last_pos = next_pos + 1;

		next_pos = line_to_parse.find(" ", last_pos);
		kg = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
		last_pos = next_pos + 1;

		next_pos = line_to_parse.find(" ", last_pos);
		kb = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
		last_pos = next_pos + 1;

		// Get specular reflectance
		next_pos = line_to_parse.find(" ", last_pos);
		ks = strtof(line_to_parse.substr(last_pos,  next_pos - last_pos).c_str(), &pEnd);
		last_pos = next_pos + 1;

		// Get shininess exponent
		next_pos = line_to_parse.find(" ", last_pos);
		alpha = strtof(line_to_parse.substr(last_pos,  next_pos - last_pos).c_str(), &pEnd);
		last_pos = next_pos + 1;

		// Get translucency
		kt = strtof(line_to_parse.substr(last_pos, line_to_parse.size()).c_str(), &pEnd);

	//	cout << "ks, alpha is " << ks << " " << alpha << endl;

	}

	for (int i = first_polygon; i <= last_polygon; i++) {
		// Apply properties to all polygons

		faces.at(i).setDiffuseReflectance(kr, kg, kb);

		faces.at(i).setSpecularReflectance(ks);

		faces.at(i).setShininessExponent(alpha);

		faces.at(i).setTranslucency(kt);
	}

//	cout << "Bounds " << first_polygon << " " << last_polygon << endl;
//	cout << "faces "  << faces.at(845).getShininessExponent()<< endl;

}
