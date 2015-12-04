/*
 * ParseCameraModelTest.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: prashantm
 */

#include <ParseCameraModel.h>

#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include <Vertex.h>

using namespace std;

namespace {
  class ParseCameraModelTest : public ::testing::Test {
  protected:
	  ParseCameraModel *testObj;

  };
  TEST_F(ParseCameraModelTest, TestParsedPoints) {

	  testObj = new ParseCameraModel("camera.txt");

	//  istringstream read_file_stream(testObj->GetFileContents());
	//  string line;
	//  getline(read_file_stream, line);
	//  cout << "First line is " << line  << endl;


	  Vertex fp(0, 0.2, 0, "ignore");
	  Vertex lap(0, 0, 100, "ignore");
	  Vertex vup(0, 0, 1, "ignore");

	  Vertex * testFp = testObj->GetFocalPoint();

	  Vertex *testLap = testObj->GetLookAtPoint();

	  Vertex *testVup = testObj->GetVupVector();

	  ASSERT_FLOAT_EQ(testFp->x_coordinate, fp.x_coordinate);
	  ASSERT_FLOAT_EQ(testFp->y_coordinate, fp.y_coordinate);
	  ASSERT_FLOAT_EQ(testFp->z_coordinate, fp.z_coordinate);

	  ASSERT_FLOAT_EQ(testLap->x_coordinate, lap.x_coordinate);
	  ASSERT_FLOAT_EQ(testLap->y_coordinate, lap.y_coordinate);
	  ASSERT_FLOAT_EQ(testLap->z_coordinate, lap.z_coordinate);

	  ASSERT_FLOAT_EQ(testVup->x_coordinate, vup.x_coordinate);
	  ASSERT_FLOAT_EQ(testVup->y_coordinate, vup.y_coordinate);
	  ASSERT_FLOAT_EQ(testVup->z_coordinate, vup.z_coordinate);
  }

  TEST_F(ParseCameraModelTest, TestImageSize) {

  	  testObj = new ParseCameraModel("camera.txt");

  	//  istringstream read_file_stream(testObj->GetFileContents());
  	//  string line;
  	//  getline(read_file_stream, line);
  	//  cout << "First line is " << line  << endl;

  	  ASSERT_FLOAT_EQ(testObj->GetFocalLength(), 340.0);

  	  ASSERT_EQ(testObj->GetImageSizeU(), 256);
  	  ASSERT_EQ(testObj->GetImageSizeV(), 256);

  	  ASSERT_EQ(testObj->GetImageSizeuMax(), 127);
  	  ASSERT_EQ(testObj->GetImageSizeuMin(), -128);

  	  ASSERT_EQ(testObj->GetImageSizevMax(), 127);
  	  ASSERT_EQ(testObj->GetImageSizevMin(), -128);
  }



}
