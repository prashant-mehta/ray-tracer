/*
 * WritePlyTest.cpp
 *
 *  Created on: Sep 20, 2015
 *      Author: prashantm
 */

#include <WritePly.h>
#include <ParsePly.h>

using namespace std;


namespace {
  class WritePlyTest : public ::testing::Test {
  protected:
	  WritePly *testObj;
	  ParsePly *parseObj;
  };
/*
  TEST_F(WritePlyTest, TestWriteAttributes) {

	  parseObj = new ParsePly("dodecahedron.ply");
	  testObj = new WritePly("dode_output.ply");

	  testObj->WriteAttributes();

	  parseObj->CloseReadFile();

	  testObj->CloseWriteFile();
  }*/

  TEST_F(WritePlyTest, TestWriteFaces) {

  	  parseObj = new ParsePly("dodecahedron.ply");
  	  testObj = new WritePly("dode_output.ply");

  	  testObj->WriteAttributes();
  	  parseObj->ParseAllVertices("vertices.txt");
  	testObj->WriteVertices(parseObj->GetParsedVertices());
  	  testObj->WriteFaces();

  	  parseObj->CloseReadFile();
  	  testObj->CloseWriteFile();
    }

 /* TEST_F(WritePlyTest, TestWriteVertices) {

  	  parseObj = new ParsePly("bunny.ply");
  	  testObj = new WritePly("bunny_output.ply");



  	  testObj->WriteAttributes(parseObj->GetPlyFileAttributes());



  	  testObj->WriteVertices(parseObj->GetParsedVertices());
  	  testObj->WriteFaces(parseObj->GetPlyFaces());

  	  testObj->CloseWriteFile();
    }*/

  TEST_F(WritePlyTest, TestWriteCowVertices) {

    	  parseObj = new ParsePly("bunny.ply");
    	  testObj = new WritePly("bunny_output.ply");



    	  testObj->WriteAttributes();

    	  parseObj->ParseAllVertices("vertices.txt");

    	  testObj->WriteVertices(parseObj->GetParsedVertices());
    	  testObj->WriteFaces();

    	  parseObj->CloseReadFile();
    	  testObj->CloseWriteFile();
      }


}
