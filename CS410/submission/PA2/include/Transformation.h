/*
 * Transformation.h
 *
 *  Created on: Sep 20, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_TRANSFORMATION_H_
#define INCLUDE_TRANSFORMATION_H_

#define INVALID_INPUT_ERROR "Invalid command! Valid commands are 'S sx sy sz', 'T tx ty tz', 'R rx ry rz theta' or 'W'"

#include <WritePly.h>
#include <ParsePly.h>
#include <TransformationMatrices.h>

class Transformation {
private:
	float *transformation_matrix;

	ParsePly * parsePlyObj;

	string inputfilename, outputfilename;

	TransformationMatrices * transformationMatricesObj;

	MatrixOperations * matrixOperationsObj;

	WritePly * writePlyObj;

public:
	Transformation(int argc, char **argv);
	void ParseFileNames(int argc, char **argv);

	void ProcessInputCommand(string input_command);

	Vertex ParseInputCommand(string input_command, bool isRotate);

	virtual ~Transformation();
};

#endif /* INCLUDE_TRANSFORMATION_H_ */
