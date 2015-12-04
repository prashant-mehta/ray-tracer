/*
 * Transformation.cpp
 *
 *  Created on: Sep 20, 2015
 *      Author: prashantm
 */

#include <Transformation.h>

Transformation::Transformation(int argc, char **argv) {
	// TODO Auto-generated constructor stub



	// Get input and output filenames from command line arguments
	this->ParseFileNames(argc, argv);

	cout << "Input file name is " << inputfilename << endl;
	cout << "Output file name is " << outputfilename << endl;

	// Print input model file attributes
	cout << "\n ****** Printing model attributes from " << inputfilename
			<< " file ****** \n" << endl;

	parsePlyObj = new ParsePly(inputfilename.c_str());
	parsePlyObj->PrintPlyAttributes();

	cout << "\n**********************************************************"
			<< endl;

	// Get inputs

	this->transformationMatricesObj = new TransformationMatrices();

	this->transformation_matrix = this->transformationMatricesObj->GetUnitTransformationMatrix();



	string input_command;

	cout << '>' ;
	getline(cin, input_command);


	// Parse input command until first character of input_command is not 'W'

	while (input_command.at(0) != 'W') {


		this->ProcessInputCommand(input_command);

		this->transformationMatricesObj->PrintTransformationMatrix(this->transformation_matrix);

		cout << '>' ;
		getline(cin, input_command);



	}

	cout << "Applying transformation to your input file and writing the results to the output file"  << endl;
	// this->transformationMatricesObj->PrintTransformationMatrix(this->transformation_matrix);

	this->writePlyObj = new WritePly(outputfilename.c_str());
	this->matrixOperationsObj = new MatrixOperations();

	this->writePlyObj->WriteAttributes();

	this->parsePlyObj->ParseAllVertices("vertices.txt");

	vector<Vertex> transformedVertices;

	transformedVertices = this->matrixOperationsObj->MatrixMultiply(this->transformation_matrix,
			this->parsePlyObj->GetParsedVertices(), 4, 4, this->parsePlyObj->GetNumberOfVertices());
	this->writePlyObj->WriteVertices(transformedVertices);

	this->writePlyObj->WriteFaces();
	this->writePlyObj->CloseWriteFile();
	// Apply transformation matrix to complete points




}

void Transformation::ParseFileNames(int argc, char **argv) {
	if (argc > 3) {
		cout
				<< "More than two input arguments. Considering first two as input and output\
				file names respectively."
				<< endl;

	}

	inputfilename = argv[1];
	outputfilename = argv[2];
}

void Transformation::ProcessInputCommand(string input_command) {

	if (input_command.at(0) != 'S' && input_command.at(0) != 'T'
			&& input_command.at(0) != 'R') {
		cout << INVALID_INPUT_ERROR << endl;
		return;
	}
	else {
		Vertex input_transformation;
		if (input_command.at(0) == 'R') {
			input_transformation = this->ParseInputCommand(input_command, true);
		} else {
			input_transformation = this->ParseInputCommand(input_command,
					false);
		}

		// Check input_transformation:
		// cout << "Input transformation is " << input_transformation.x_coordinate <<
				// input_transformation.y_coordinate << input_transformation.z_coordinate
				// << input_transformation.properties << endl;

		this->transformation_matrix = this->transformationMatricesObj->TransformationMatrix(input_transformation,
				input_command.at(0), this->transformation_matrix);

	}

}

Vertex Transformation::ParseInputCommand(string input_command,
		bool isRotate) {

	uint64_t next_pos = 0;
	uint64_t last_pos = 0;
	char *pEnd;

	Vertex parsedParameters;


	//	cout << "Number of properties are " << this->parseAttributesObj->GetNumberOfProperties() << endl;

	next_pos = input_command.find(" ", last_pos);


	// Skipping the first command parameter in parsing
	last_pos = next_pos + 1;

	next_pos = input_command.find(" ", last_pos);


	parsedParameters.x_coordinate = strtof(
			input_command.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);

	last_pos = next_pos + 1;

	next_pos = input_command.find(" ", last_pos);

	parsedParameters.y_coordinate = strtof(
			input_command.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);

	last_pos = next_pos + 1;

	if (! isRotate) {

		parsedParameters.z_coordinate = strtof(
			input_command.substr(last_pos, input_command.size()).c_str(), &pEnd);

		return parsedParameters;
	}
	else {
		next_pos = input_command.find(" ", last_pos);

		parsedParameters.z_coordinate = strtof(
					input_command.substr(last_pos, next_pos - last_pos).c_str(), &pEnd);

		last_pos = next_pos + 1;

		parsedParameters.properties = input_command.substr(last_pos, input_command.size()).c_str();

		return parsedParameters;
	}

}



Transformation::~Transformation() {
	// TODO Auto-generated destructor stub

	delete(this->parsePlyObj);
	delete(this->writePlyObj);
	delete(this->transformationMatricesObj);
	delete(this->matrixOperationsObj);
}

