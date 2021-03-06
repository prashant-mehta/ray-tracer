/*
 * ParsePlyTest.cpp
 *
 *  Created on: Sep 12, 2015
 *      Author: prashantm
 *      Description: File to parse complete parse file
 */

#include <ParsePly.h>


#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include <Vertex.h>

using namespace std;

namespace {
  class ParsePlyTest : public ::testing::Test {
  protected:
	  ParsePly *testObj;
	  ParsePly *testObj2;
  };
  TEST_F(ParsePlyTest, TestParsePlyReadFile) {

	  cout << "Test print" << endl;
	  testObj = new ParsePly("dodecahedron.txt");

	//  istringstream read_file_stream(testObj->GetFileContents());
	//  string line;
	//  getline(read_file_stream, line);
	//  cout << "First line is " << line  << endl;

	  testObj->CloseReadFile();
  }



  TEST_F(ParsePlyTest, TestNoPlyKeyword) {

  	  testObj = new ParsePly("testply.txt");

  	testObj->CloseReadFile();
    }


  TEST_F(ParsePlyTest, TestParsedNumberOfVerticesFaces) {

  	  testObj = new ParsePly("dodecahedron.txt");


  	  ASSERT_EQ(testObj->GetNumberOfVertices(), 20);

  	ASSERT_EQ(testObj->GetNumberOfFaces(), 12);

  	testObj->CloseReadFile();
    }

  TEST_F(ParsePlyTest, TestParsedVertices) {

  	  testObj = new ParsePly("dodecahedron.txt");

 // 	  testObj->ParseVertexCoordinates("-0.57735 -0.57735 0.57735");

  	  testObj->ParseAllVertices("vertices.txt");

 	  vector<Vertex> parsed_vertices = testObj->GetParsedVertices();

  	  ASSERT_FLOAT_EQ(parsed_vertices.at(0).x_coordinate, -0.57735);
  	ASSERT_FLOAT_EQ(parsed_vertices.at(0).y_coordinate, -0.57735);
  	ASSERT_FLOAT_EQ(parsed_vertices.at(0).z_coordinate, 0.57735);


  	ASSERT_FLOAT_EQ(parsed_vertices.at(3).x_coordinate, -0.934172);
  	  	ASSERT_FLOAT_EQ(parsed_vertices.at(3).y_coordinate, 0.356822);
  	  	ASSERT_FLOAT_EQ(parsed_vertices.at(3).z_coordinate, 0);

  	  testObj->CloseReadFile();
    }

  TEST_F(ParsePlyTest, TestCowdVertices) {

  	  testObj = new ParsePly("cow.ply");

 // 	  testObj->ParseVertexCoordinates("-0.57735 -0.57735 0.57735");

  	testObj->ParseAllVertices("vertices.txt");

 	  vector<Vertex> parsed_vertices = testObj->GetParsedVertices();

  	  ASSERT_FLOAT_EQ(parsed_vertices.at(0).x_coordinate, 0.605538);
  	ASSERT_FLOAT_EQ(parsed_vertices.at(0).y_coordinate, 0.183122);
  	ASSERT_FLOAT_EQ(parsed_vertices.at(0).z_coordinate, -0.472278);


  	ASSERT_FLOAT_EQ(parsed_vertices.at(3).x_coordinate, 0.691245);
   	ASSERT_FLOAT_EQ(parsed_vertices.at(3).y_coordinate, 0.0569483);
   	ASSERT_FLOAT_EQ(parsed_vertices.at(3).z_coordinate, -0.524762);

  	testObj->CloseReadFile();
    }

  TEST_F(ParsePlyTest, TestPrintAttributes) {

  	  testObj = new ParsePly("bunny.ply");


  	  cout << "\n\n ****** Printing model attributes from bunny.ply file ****** \n" << endl;

 	  testObj->PrintPlyAttributes();


 	  cout << "\n***************************************************" << endl;


  	testObj->CloseReadFile();
    }

  TEST_F(ParsePlyTest, TestParsedFaces) {

  	  testObj = new ParsePly("dodecahedron.txt");



  	  testObj->ParseAllVertices("vertices.txt");

  	  testObj->ParseFaces("faces.txt");

 	  vector<Face> parsed_faces = testObj->GetParsedFaces();

 	  vector<uint16_t> f0_vertices = parsed_faces.at(0).getFaceVertexIds();

 	  ASSERT_EQ(parsed_faces.size(), testObj->GetNumberOfFaces());

 	  vector<uint16_t> f5_vertices = parsed_faces.at(5).getFaceVertexIds();

 	  ASSERT_EQ(f0_vertices.at(0), 1);
 	  ASSERT_EQ(f0_vertices.at(1), 2);
 	  ASSERT_EQ(f0_vertices.at(2), 18);
 	  ASSERT_EQ(f0_vertices.at(3), 11);
 	  ASSERT_EQ(f0_vertices.at(4), 14);

 	  ASSERT_EQ(f5_vertices.at(0), 1);
 	  ASSERT_EQ(f5_vertices.at(1), 14);
 	  ASSERT_EQ(f5_vertices.at(2), 5);
 	  ASSERT_EQ(f5_vertices.at(3), 6);
 	  ASSERT_EQ(f5_vertices.at(4), 13);


  	  testObj->CloseReadFile();
    }

  TEST_F(ParsePlyTest, TestCoordsParsedFaces) {

  	  testObj = new ParsePly("dodecahedron.txt");



  	  testObj->ParseAllVertices("vertices.txt");

  	  testObj->ParseFaces("faces.txt");

 	  vector<Face> parsed_faces = testObj->GetParsedFaces();

 	  vector<uint16_t> f0_vertices = parsed_faces.at(0).getFaceVertexIds();

 	  ASSERT_EQ(parsed_faces.size(), testObj->GetNumberOfFaces());

 	  Vertex v2(0.934172, -0.356822, 0, "ignore" );

 	  Vertex f0_v1 = parsed_faces.at(0).getVertexFromFace(1);

 	  ASSERT_FLOAT_EQ(f0_v1.x_coordinate, v2.x_coordinate);
 	  ASSERT_FLOAT_EQ(f0_v1.y_coordinate, v2.y_coordinate);
 	  ASSERT_FLOAT_EQ(f0_v1.z_coordinate, v2.z_coordinate);

  	  testObj->CloseReadFile();
    }

  TEST_F(ParsePlyTest, TestBunnyParsedFaces) {

  	  testObj = new ParsePly("bunny.ply");



  	  testObj->ParseAllVertices("vertices.txt");

  	  testObj->ParseFaces("faces.txt");

 	  vector<Face> parsed_faces = testObj->GetParsedFaces();

 	  vector<uint16_t> f0_vertices = parsed_faces.at(0).getFaceVertexIds();

 	  ASSERT_EQ(parsed_faces.size(), testObj->GetNumberOfFaces());

 	  vector<uint16_t> f5_vertices = parsed_faces.at(5).getFaceVertexIds();

 	  ASSERT_EQ(f0_vertices.at(0), 21216);
 	  ASSERT_EQ(f0_vertices.at(1), 21215);
 	  ASSERT_EQ(f0_vertices.at(2), 20399);



  	  testObj->CloseReadFile();
    }

  TEST_F(ParsePlyTest, TestDodecahedronDistance) {

  	  testObj = new ParsePly("dodecahedron.ply");



  	  testObj->ParseAllVertices("vertices.txt");



 	  cout << testObj->GetRadius() << endl;

  	  testObj->CloseReadFile();
    }

}
