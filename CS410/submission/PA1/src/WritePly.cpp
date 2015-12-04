/*
 * WritePly.cpp
 *
 *  Created on: Sep 20, 2015
 *      Author: prashantm
 */

#include <WritePly.h>

WritePly::WritePly(char const *filename) {
	// TODO Auto-generated constructor stub
	outputfile.open(filename);
}

void WritePly::WriteAttributes(void){

	ifstream inputfile;
	inputfile.open("attributes.txt");

	string read_line;

	while (getline(inputfile, read_line))
	{
		outputfile << read_line;
		outputfile << "\n";
	}

	inputfile.close();
}

void WritePly::CloseWriteFile(void){
	outputfile.close();
}

void WritePly::WriteFaces(void){
	ifstream inputfile;
	inputfile.open("faces.txt");

	string read_line;

	while (getline(inputfile, read_line))
	{
		outputfile << read_line;
		outputfile << "\n";
	}

	inputfile.close();
}

void WritePly::WriteVertices(vector<Vertex> vertices){

	uint64_t num_of_vertices = vertices.size();

	ifstream inputfile;
	inputfile.open("properties.txt");

	string read_line;

	for (uint64_t i = 0; i < num_of_vertices; i++){
		outputfile << vertices.at(i).x_coordinate << " ";
		outputfile << vertices.at(i).y_coordinate << " ";
		outputfile << vertices.at(i).z_coordinate << " ";
		if (getline(inputfile, read_line)){
			outputfile << read_line;

		}
		outputfile << "\n" ;
	}

	inputfile.close();
}
