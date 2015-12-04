/*
 * ParseCameraModel.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: prashantm
 */

#include <ParseCameraModel.h>

ParseCameraModel::ParseCameraModel(char const *filename) {
	// TODO Auto-generated constructor stub

	ifstream inputfile;

	inputfile.open(filename);

	if (! inputfile.is_open()){
			cout << "Camera model file open failed. Exiting the code now." << endl;
			exit(EXIT_FAILURE);
	}

	string read_line;


	// Parse camera's focal point
	getline(inputfile, read_line);
	this->focal_point = this->ParseFocalPoint(read_line);

	// Parse look-at-point
	getline(inputfile, read_line);
	this->look_at_point = this->ParseFocalPoint(read_line);

	// Parse VUP vector
	getline(inputfile, read_line);
	this->v_up_vector = this->ParseFocalPoint(read_line);

	// Parse focal length
	getline(inputfile, read_line);
	focal_length = strtod(read_line.substr(0, read_line.size()).c_str(), NULL);

	// Parse image size
	getline(inputfile, read_line);
	this->ParseImageSize(read_line);

	this->VerifyCameraModel();

	inputfile.close();

}

Vertex * ParseCameraModel::ParseFocalPoint(string line_to_parse){

	uint64_t next_pos = 0;
	uint64_t last_pos = 0;
	char *pEnd;

	Vertex * parsed_vertex = new Vertex();

	next_pos = line_to_parse.find(" ", last_pos);


	parsed_vertex->x_coordinate = strtod(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);

	last_pos = next_pos + 1;


	next_pos = line_to_parse.find(" ", last_pos);

	parsed_vertex->y_coordinate = strtod(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);

	last_pos = next_pos + 1;

	// next_pos = line_to_parse.find(" ", last_pos);

	parsed_vertex->z_coordinate = strtod(line_to_parse.substr(last_pos, line_to_parse.size()).c_str(), &pEnd);


	parsed_vertex->properties = "camera model";

	return parsed_vertex;
}

void ParseCameraModel::ParseImageSize(string line_to_parse) {

	uint64_t next_pos = 0;
	uint64_t last_pos = 0;
	char *pEnd;



	next_pos = line_to_parse.find(" ", last_pos);

	uMin = strtol(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), NULL, 10);

	last_pos = next_pos + 1;

	next_pos = line_to_parse.find(" ", last_pos);

	vMin = strtol(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), NULL, 10);

	last_pos = next_pos + 1;

	next_pos = line_to_parse.find(" ", last_pos);

	uMax = strtol(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), NULL, 10);

	last_pos = next_pos + 1;

	vMax = strtol(line_to_parse.substr(last_pos, line_to_parse.size()).c_str(), NULL, 10);

	uSize = uMax - uMin + 1;

	vSize = vMax - vMin + 1;
}

void ParseCameraModel::VerifyCameraModel(void) {
	if ((fabs(focal_length) < 0.0000001) || (uMin > uMax) || (vMin > vMax)) {
		cout << "Error in camera model parameters. Exiting the code now." << endl;
		exit(EXIT_FAILURE);
	}

	return;

}

void ParseCameraModel::PrintAllCameraProperties(void) {
	cout << "Focal Point is " << endl;
	this->focal_point->PrintVertex();
	cout << "Look at Point is " <<  endl;
	this->look_at_point->PrintVertex();
	cout << "VUP vector is " << endl;
	this->v_up_vector->PrintVertex();
	cout << "Focal length is " << this->focal_length << endl;
	cout << "Image limits ( " << uMin << ", " << vMin << ") and ( " << uMax << ", " << vMax << ")"   << endl;
	cout << "Image size is ( " << uSize << ", " << vSize << ")"  << endl;
}
