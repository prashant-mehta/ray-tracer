/*
 * FaceTest.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: prashantm
 */

#include <Face.h>

#include <string>
#include "gtest/gtest.h"
#include "Vertex.h"

using namespace std;

namespace {
  class FaceTest : public ::testing::Test {
  protected:
    Vertex *v1, *v2, *v3;
    Face *testObj;
  };
  TEST_F(FaceTest, TestFaceSize) {
	  Vertex v1(12.0, -15.1234, 0.123, "0.145 8.945");
	  Vertex v2(12.0, -15.1234, 0.123, "0.145 8.945");
	  Vertex v3(12.0, -15.1234, 0.123, "0.145 8.945");

	  testObj = new Face();
	  ASSERT_EQ(testObj->getSizeOfFace(), 0);
	  testObj->addVertexToFace(v1, 3);
	  ASSERT_EQ(testObj->getSizeOfFace(), 1);
	  testObj->addVertexToFace(v2, 6);
	  ASSERT_EQ(testObj->getSizeOfFace(), 2);
	  testObj->addVertexToFace(v3, 9);

	  ASSERT_EQ(testObj->getSizeOfFace(), 3);

  }

  TEST_F(FaceTest, TestAddVertex) {
  	  Vertex v1(2.01, -15.1234, 0.123, "0.145 8.945");
  	  Vertex v2(1.0, 95.034, 12.3, "0.145 8.945");
  	  Vertex v3(12.90, 5.1234, 123, "0.145 8.945");

  	  Vertex getv3;

  	  testObj = new Face();

  	  testObj->addVertexToFace(v1, 2);

  	  testObj->addVertexToFace(v2, 1);

  	  testObj->addVertexToFace(v3, 8);

  	  getv3 = testObj->getVertexFromFace(2);

  	  Vertex getv1 = testObj->getVertexFromFace(0);

  	  Vertex getv2 = testObj->getVertexFromFace(1);

  	  ASSERT_FLOAT_EQ(getv3.x_coordinate, 12.90);
  	  ASSERT_FLOAT_EQ(getv3.y_coordinate, 5.1234);
  	  ASSERT_FLOAT_EQ(getv3.z_coordinate, 123);

  	  ASSERT_FLOAT_EQ(getv1.x_coordinate, 2.01);
  	  ASSERT_FLOAT_EQ(getv1.y_coordinate, -15.1234);
  	  ASSERT_FLOAT_EQ(getv1.z_coordinate, 0.123);

  	  ASSERT_FLOAT_EQ(getv2.x_coordinate, 1.0);
  	  ASSERT_FLOAT_EQ(getv2.y_coordinate, 95.034);
  	  ASSERT_FLOAT_EQ(getv2.z_coordinate, 12.3);

    }

  TEST_F(FaceTest, TestGetAllVertices) {
  	  Vertex v1(2.01, -15.1234, 0.123, "0.145 8.945");
  	  Vertex v2(1.0, 95.034, 12.3, "0.145 8.945");
  	  Vertex v3(12.90, 5.1234, 123, "0.145 8.945");

  	  Vertex getv3;

  	  testObj = new Face();

  	  testObj->addVertexToFace(v1, 18);

  	  testObj->addVertexToFace(v2, 97);

  	  testObj->addVertexToFace(v3, 108);

  	  vector<Vertex> getVertices = testObj->getAllVerticesFromFace();


  	  ASSERT_FLOAT_EQ(getVertices.at(2).x_coordinate, 12.90);
  	  ASSERT_FLOAT_EQ(getVertices.at(2).y_coordinate, 5.1234);
  	  ASSERT_FLOAT_EQ(getVertices.at(2).z_coordinate, 123);

  	  ASSERT_FLOAT_EQ(getVertices.at(0).x_coordinate, 2.01);
  	  ASSERT_FLOAT_EQ(getVertices.at(0).y_coordinate, -15.1234);
  	  ASSERT_FLOAT_EQ(getVertices.at(0).z_coordinate, 0.123);

  	  ASSERT_FLOAT_EQ(getVertices.at(1).x_coordinate, 1.0);
  	  ASSERT_FLOAT_EQ(getVertices.at(1).y_coordinate, 95.034);
  	  ASSERT_FLOAT_EQ(getVertices.at(1).z_coordinate, 12.3);

    }

  TEST_F(FaceTest, TestChangeVertex) {
  	  Vertex v1(2.01, -15.1234, 0.123, "0.145 8.945");
  	  Vertex v2(1.0, 95.034, 12.3, "0.145 8.945");
  	  Vertex v3(12.90, 5.1234, 123, "0.145 8.945");

  	  Vertex getv3;

  	  testObj = new Face();

  	  testObj->addVertexToFace(v1, 18);

  	  testObj->addVertexToFace(v2, 17);

  	  testObj->addVertexToFace(v3, 19);

  	  getv3 = testObj->getVertexFromFace(1);
  	  getv3 = testObj->getVertexFromFace(2);

  	  Vertex getv1 = testObj->getVertexFromFace(0);

  	  Vertex getv2 = testObj->getVertexFromFace(1);





  	  ASSERT_FLOAT_EQ(getv3.x_coordinate, 12.90);
  	  ASSERT_FLOAT_EQ(getv3.y_coordinate, 5.1234);
  	  ASSERT_FLOAT_EQ(getv3.z_coordinate, 123);



  	  ASSERT_FLOAT_EQ(getv1.x_coordinate, 2.01);
  	  ASSERT_FLOAT_EQ(getv1.y_coordinate, -15.1234);
  	  ASSERT_FLOAT_EQ(getv1.z_coordinate, 0.123);

  	  ASSERT_FLOAT_EQ(getv2.x_coordinate, 1.0);
  	  ASSERT_FLOAT_EQ(getv2.y_coordinate, 95.034);
  	  ASSERT_FLOAT_EQ(getv2.z_coordinate, 12.3);

    }


  TEST_F(FaceTest, VectorOfFaces) {
    	  Vertex v1(2.01, -15.1234, 0.123, "0.145 8.945");
    	  Vertex v2(1.0, 95.034, 12.3, "0.145 8.945");
    	  Vertex v3(12.90, 5.1234, 123, "0.145 8.945");

    	  Vertex v4(12.01, -15.1234, 0.123, "0.145 8.945");
    	  Vertex v5(1.90, -95.034, 12.3, "0.145 8.945");
    	  Vertex v6(12.90, 5.1234, 1.23, "0.145 8.945");

    	  Vertex v7(2.01, -15.234, 90.123, "0.145 8.945");
    	  Vertex v8(11.0, 95.034, 12.3, "0.145 8.945");
    	  Vertex v9(2.90, 5.1234, 123.15, "0.145 8.945");



    	  Vertex getv3;

    	  testObj = new Face();

    	  vector<Face> testVector;


    	  testObj->addVertexToFace(v1, 3);

    	  testObj->addVertexToFace(v2, 4);

    	  testObj->addVertexToFace(v3, 5);


    	  testVector.push_back(*testObj);

    	  testObj = new Face();

    	  testObj->addVertexToFace(v4, 12);

    	  testObj->addVertexToFace(v5, 11);

    	  testObj->addVertexToFace(v6, 10);

    	  testVector.push_back(*testObj);

    	  testObj = new Face();

    	  testObj->addVertexToFace(v7, 47);

    	  testObj->addVertexToFace(v8, 32);

    	  testObj->addVertexToFace(v9, 56);

    	  testVector.push_back(*testObj);


    	  Vertex getv0_3 = testVector.at(0).getVertexFromFace(2);

    	  Vertex getv1_2 = testVector.at(1).getVertexFromFace(1);

    	  Vertex getv2_1 = testVector.at(2).getVertexFromFace(0);

    	  Vertex getv2_2 = testVector.at(2).getVertexFromFace(1);

    	  vector<uint16_t> f0_indices = testVector.at(0).getFaceVertexIds();

    	  vector<uint16_t> f1_indices = testVector.at(1).getFaceVertexIds();

    	  vector<uint16_t> f2_indices = testVector.at(2).getFaceVertexIds();

    	  ASSERT_EQ(f0_indices.at(0), 3);
    	  ASSERT_EQ(f0_indices.at(1), 4);
    	  ASSERT_EQ(f0_indices.at(2), 5);

    	  ASSERT_EQ(f1_indices.at(0), 12);
    	  ASSERT_EQ(f1_indices.at(1), 11);
    	  ASSERT_EQ(f1_indices.at(2), 10);

    	  ASSERT_EQ(f2_indices.at(0), 47);
    	  ASSERT_EQ(f2_indices.at(1), 32);
    	  ASSERT_EQ(f2_indices.at(2), 56);

    	  ASSERT_FLOAT_EQ(getv0_3.x_coordinate, 12.90);
    	  ASSERT_FLOAT_EQ(getv0_3.y_coordinate, 5.1234);
    	  ASSERT_FLOAT_EQ(getv0_3.z_coordinate, 123);

    	  ASSERT_FLOAT_EQ(getv1_2.x_coordinate, 1.90);
    	  ASSERT_FLOAT_EQ(getv1_2.y_coordinate, -95.034);
    	  ASSERT_FLOAT_EQ(getv1_2.z_coordinate, 12.3);

    	  ASSERT_FLOAT_EQ(getv2_1.x_coordinate, 2.01);
    	  ASSERT_FLOAT_EQ(getv2_1.y_coordinate, -15.234);
    	  ASSERT_FLOAT_EQ(getv2_1.z_coordinate, 90.123);


    	  ASSERT_FLOAT_EQ(getv2_2.x_coordinate, 11.0);
    	  ASSERT_FLOAT_EQ(getv2_2.y_coordinate, 95.034);
    	  ASSERT_FLOAT_EQ(getv2_2.z_coordinate, 12.3);



      }


}

