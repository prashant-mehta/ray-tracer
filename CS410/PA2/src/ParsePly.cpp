/*
 * ParsePly.cpp
 *
 *  Created on: Sep 12, 2015
 *      Author: prashantm
 */

#include <ParsePly.h>

ParsePly::ParsePly(char const *filename) {
	// TODO Auto-generated constructor stub

	parseAttributesObj = new ParsePlyAttributes();
	vector_operations = new VectorOperations();
	// Open file (TODO - Check for error)
	inputfile.open(filename);



	if (! inputfile.is_open()){
		cout << "File open failed. Exiting the code now." << endl;
		exit(EXIT_FAILURE);
	}

	string read_line;

	// Add line by line string to file_contents.
	// TODO - Check for ply keyword at start

	getline(inputfile, read_line);

	if (read_line.substr(0, 3) != "ply"){
		// If ply keyword not found in input file
		cout << "First line is " << read_line << endl;
		cout << "\"ply\" not found at the start of input file. Exiting the code now. " << endl;
		return;
	}

	string attributes_from_input;



	// Parse attributes
	attributes_from_input += read_line;
	attributes_from_input.push_back('\n');
	uint64_t parsed_number_of_properties = 0;
	while (getline(inputfile, read_line))
	{
		attributes_from_input += read_line;
		attributes_from_input.push_back('\n');
		if (read_line.substr(0, 10) == "end_header"){
			break;
		}
		else if(read_line.find("element vertex") != string::npos){
			// Found line containing element vertex
			this->ParseNumberOfVertices(read_line);
		}
		else if(read_line.find("element face") != string::npos){
			// Found line containing element face
			this->ParseNumberOfFaces(read_line);
		}
		else if(read_line.find("property float") != string::npos){
			// For counting number of properties Subtract -1 because one 'property' should not be counted
			//cout << "Found a property" << endl;

			parsed_number_of_properties++;
		}

	}

	ofstream outputfile;
	outputfile.open("attributes.txt");

	outputfile << attributes_from_input;
	outputfile.close();

	attributes_from_input.clear();

	//cout << "Number of parsed properties are " << parsed_number_of_properties << endl;

	this->parseAttributesObj->SetNumberOfProperties(parsed_number_of_properties);

	//cout << "Number of properties are " << 4 << this->parseAttributesObj->GetNumberOfProperties() << endl;

	// Parse vertices
	uint64_t number_of_vertices = this->GetNumberOfVertices();
	uint64_t parsed_vertices_count = 0;

	vertex_properties_file.open("properties.txt");
	vertices_file.open("vertices.txt");

	while (parsed_vertices_count < number_of_vertices){
		getline(inputfile, read_line);
		// vertices_file << read_line << "\n";


		this->ParseVertexLine(read_line);

		parsed_vertices_count++;

	}

	vertex_properties_file.close();
	vertices_file.close();

	// TODO Parse for faces

	outputfile.open("faces.txt");

	while (getline(inputfile, read_line))
	{

		outputfile << read_line;

		outputfile << '\n';
	}

	outputfile.close();

	all_triangles = true;

}

// Use this function to parse all vertices from filename file
void ParsePly::ParseAllVertices(char const* filename) {

	// Parse vertices
	uint64_t number_of_vertices = this->GetNumberOfVertices();
	uint64_t parsed_vertices_count = 0;
	mean_vertex = new Vertex();
	minimum_bounds = new Vertex();
	maximum_bounds = new Vertex();

	vertices.clear();

	ifstream vertices_input_file;
	string read_line;

	vertices_input_file.open(filename);

	while (parsed_vertices_count < number_of_vertices){
		getline(vertices_input_file, read_line);


		this->ParseVertexCoordinates(read_line);

		parsed_vertices_count++;

	}

	mean_vertex->x_coordinate = mean_vertex->x_coordinate / number_of_vertices;
	mean_vertex->y_coordinate = mean_vertex->y_coordinate / number_of_vertices;
	mean_vertex->z_coordinate = mean_vertex->z_coordinate / number_of_vertices;

	// Calculate radius of sphere around object (max distance from mean)

	this->ComputeRadius();


	vertices_input_file.close();

}

void ParsePly::ComputeRadius(void) {
	float distance;
	float max_distance = 0.0;
	uint64_t number_of_vertices = this->GetNumberOfVertices();
	for (int i = 0; i < number_of_vertices; i++) {
		distance = this->vector_operations->Distance(&this->vertices.at(i), mean_vertex);

		if (fabs(distance) > max_distance) {
			max_distance = fabs(distance);
		}

	}

	radius = max_distance;
}

void ParsePly::PrintPlyAttributes(void){

	cout << "Number of vertices in the model are " << this->GetNumberOfVertices() << endl;
	cout << "Number of faces in the model are " << this->GetNumberOfFaces() << endl;


	PrintVerticesMeanAndBounds();

	return;
}

void ParsePly::PrintVerticesMeanAndBounds(void){

	this->ParseAllVertices("vertices.txt");

	cout << "Mean vertex (x, y, z) is (" << mean_vertex->x_coordinate << ", " <<  mean_vertex->y_coordinate
			<< ", " <<  mean_vertex->z_coordinate  << ")" << endl;

	cout << "Minimum bounds (x, y, z) are (" << minimum_bounds->x_coordinate << ", " <<  minimum_bounds->y_coordinate
			<< ", " <<  minimum_bounds->z_coordinate  << ")" << endl;

	cout << "Maximum bounds (x, y, z) are (" << maximum_bounds->x_coordinate << ", " <<  maximum_bounds->y_coordinate
			<< ", " <<  maximum_bounds->z_coordinate  << ")" << endl;

	vertices.clear();

}

void ParsePly::ParseNumberOfVertices(string line_to_parse){

	char *pEnd;
	// Based on "element vertex " characters get characters from 15 till end
	string string_number_of_vertices =line_to_parse.substr(15);
	parseAttributesObj->SetNumberOfVertices((uint64_t) strtol(string_number_of_vertices.c_str(), &pEnd, 10));
	return;
}

void ParsePly::ParseNumberOfFaces(string line_to_parse){

	char *pEnd;
	// Based on "element face " charactes get characters from 13 till end
	string string_number_of_faces =line_to_parse.substr(13);
	parseAttributesObj->SetNumberOfFaces((uint64_t) strtol(string_number_of_faces.c_str(), &pEnd, 10));
	return;
}

void ParsePly::ParseVertexLine(string line_to_parse){
/*
 * Reference - http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 *
 */
//	cout << "line to be parsed is " << line_to_parse << endl;
	uint64_t parsed_floats_count = 0;
	uint64_t next_pos = 0;
	uint64_t last_pos = 0;
	char *pEnd;

	// Vertex vertex_to_add;
	uint64_t number_of_properties = this->parseAttributesObj->GetNumberOfProperties();

//	cout << "Number of properties are " << this->parseAttributesObj->GetNumberOfProperties() << endl;


	next_pos = line_to_parse.find(" ", last_pos);

	// x_coord
	vertices_file << line_to_parse.substr(last_pos, next_pos - last_pos) << " ";

	last_pos = next_pos + 1;


	next_pos = line_to_parse.find(" ", last_pos);

	// y_coord
	vertices_file << line_to_parse.substr(last_pos, next_pos - last_pos) << " ";

	last_pos = next_pos + 1;

	next_pos = line_to_parse.find(" ", last_pos);

	// z_coord
	vertices_file << line_to_parse.substr(last_pos, next_pos - last_pos) << "\n";

	if (next_pos != string::npos){
	last_pos = next_pos + 1;

	//cout << "last_pos is" << last_pos << " next_pos is" << next_pos << endl;
	if ((last_pos != line_to_parse.size())) {
	//	cout << line_to_parse.size() << endl;
		vertex_properties_file << line_to_parse.substr(last_pos, line_to_parse.size()).c_str();
		vertex_properties_file << "\n";
		// cout << vertex_to_add.properties << endl;

	}
	}
	/*while(parsed_floats_count < number_of_properties - 1){

		next_pos = line_to_parse.find(' ', last_pos);



//	while((next_pos = line_to_parse.find(' ', last_pos)) != string::npos){
		if (parsed_floats_count == 0){
			vertex_to_add.x_coordinate = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
		}
		else if (parsed_floats_count == 1){
			vertex_to_add.y_coordinate = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
		}
		else if (parsed_floats_count == 2){
			vertex_to_add.z_coordinate = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
			parsed_floats_count++;
			last_pos = next_pos + 1;
			break;
		}
		parsed_floats_count++;
		last_pos = next_pos + 1;
	}

	//vertex_to_add.properties = line_to_parse.substr(last_pos).c_str();
	if (parsed_floats_count == 2) {
				vertex_to_add.z_coordinate = strtof(line_to_parse.substr(last_pos).c_str(), &pEnd);
	}
	else{
		vertex_to_add.properties = line_to_parse.substr(last_pos).c_str();
	} */


}


void ParsePly::ParseVertexCoordinates(string line_to_parse){
/*
 * Reference - http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 *
 */
//	cout << "line to be parsed is " << line_to_parse << endl;

	uint64_t next_pos = 0;
	uint64_t last_pos = 0;
	char *pEnd;

	Vertex vertex_to_add;
	uint64_t number_of_properties = this->parseAttributesObj->GetNumberOfProperties();

//	cout << "Number of properties are " << this->parseAttributesObj->GetNumberOfProperties() << endl;


	next_pos = line_to_parse.find(" ", last_pos);

	vertex_to_add.x_coordinate = strtod(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);

	last_pos = next_pos + 1;


	next_pos = line_to_parse.find(" ", last_pos);

	vertex_to_add.y_coordinate = strtod(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);

	last_pos = next_pos + 1;

	// next_pos = line_to_parse.find(" ", last_pos);

	vertex_to_add.z_coordinate = strtod(line_to_parse.substr(last_pos, line_to_parse.size()).c_str(), &pEnd);


	/*while(parsed_floats_count < number_of_properties - 1){

		next_pos = line_to_parse.find(' ', last_pos);



//	while((next_pos = line_to_parse.find(' ', last_pos)) != string::npos){
		if (parsed_floats_count == 0){
			vertex_to_add.x_coordinate = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
		}
		else if (parsed_floats_count == 1){
			vertex_to_add.y_coordinate = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
		}
		else if (parsed_floats_count == 2){
			vertex_to_add.z_coordinate = strtof(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);
			parsed_floats_count++;
			last_pos = next_pos + 1;
			break;
		}
		parsed_floats_count++;
		last_pos = next_pos + 1;
	}

	//vertex_to_add.properties = line_to_parse.substr(last_pos).c_str();
	if (parsed_floats_count == 2) {
				vertex_to_add.z_coordinate = strtof(line_to_parse.substr(last_pos).c_str(), &pEnd);
	}
	else{
		vertex_to_add.properties = line_to_parse.substr(last_pos).c_str();
	} */


	// Calculate for min, max and mean

	mean_vertex->x_coordinate += vertex_to_add.x_coordinate;
	mean_vertex->y_coordinate += vertex_to_add.y_coordinate;
	mean_vertex->z_coordinate += vertex_to_add.z_coordinate;


	minimum_bounds->x_coordinate = fmin(vertex_to_add.x_coordinate, minimum_bounds->x_coordinate);
	minimum_bounds->y_coordinate = fmin(vertex_to_add.y_coordinate, minimum_bounds->y_coordinate);
	minimum_bounds->z_coordinate = fmin(vertex_to_add.z_coordinate, minimum_bounds->z_coordinate);

	maximum_bounds->x_coordinate = fmax(vertex_to_add.x_coordinate, maximum_bounds->x_coordinate);
	maximum_bounds->y_coordinate = fmax(vertex_to_add.y_coordinate, maximum_bounds->y_coordinate);
	maximum_bounds->z_coordinate = fmax(vertex_to_add.z_coordinate, maximum_bounds->z_coordinate);



	// Push the vertex to vector
	vertices.push_back(vertex_to_add);


}


/*
 * This must be called after parsing vertices. That is vertices vector in this class should contain all the vertices
 * */
void ParsePly::ParseFaces(char const* filename) {
	this->faces.clear();

	// Parse vertices
	uint64_t number_of_faces = this->GetNumberOfFaces();
	uint64_t parsed_faces_count = 0;

	ifstream faces_input_file;
	string read_line;

	faces_input_file.open(filename);

	while (parsed_faces_count < number_of_faces){
		getline(faces_input_file, read_line);


		this->ParseFaceVertices(read_line);

		parsed_faces_count++;

	}



	faces_input_file.close();



}

void ParsePly::ParseFaceVertices(string line_to_parse) {

	uint64_t next_pos = 0;
	uint64_t last_pos = 0;

	uint16_t vertices_added = 0;
	uint16_t size_of_face = 0;

	uint64_t vertex_id;

	Vertex vertex_in_face;
	Face face_to_add;

	next_pos = line_to_parse.find(" ", last_pos);



	size_of_face = strtoul(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), NULL, 10);

	last_pos = next_pos + 1;

	while (vertices_added < size_of_face - 1) {
		next_pos = line_to_parse.find(" ", last_pos);

		vertex_id = strtoul(line_to_parse.substr(last_pos, next_pos - last_pos).c_str(), NULL, 10);

		face_to_add.addVertexToFace(this->vertices.at(vertex_id), vertex_id);

		last_pos = next_pos + 1;
		vertices_added++;
	}

	next_pos = line_to_parse.find(" ", last_pos);
	vertex_id = strtoul(line_to_parse.substr(last_pos, line_to_parse.size()).c_str(), NULL, 10);

	face_to_add.addVertexToFace(this->vertices.at(vertex_id), vertex_id);

	if (size_of_face != 3 ) all_triangles = false;

	this->faces.push_back(face_to_add);

	if (face_to_add.getSizeOfFace() != size_of_face) {
		cout << "Error in parsing face vertices" << endl;
		exit (EXIT_FAILURE);
	}

}

void ParsePly::CloseReadFile(void){
	inputfile.close();
}
