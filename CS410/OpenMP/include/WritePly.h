/*
 * WritePly.h
 *
 *  Created on: Sep 20, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_WRITEPLY_H_
#define INCLUDE_WRITEPLY_H_

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>
#include <cstdlib>

#include <Vertex.h>
#include <Face.h>
#include <vector>

class WritePly {
private:
	ofstream outputfile;

public:
	WritePly(char const *filename);

	void WriteAttributes(void);

	void WriteVertices(vector<Vertex>);

	void WriteFaces(void);

	void WriteFacesFromVector(vector<Face> inputfaces);

	void CloseWriteFile(void);
};

#endif /* INCLUDE_WRITEPLY_H_ */
