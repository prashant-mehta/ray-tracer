/*
 * ProjectionMatrixTest.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: prashantm
 */

#include <ProjectionMatrix.h>

#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include <Vertex.h>
#include <MatrixOperations.h>
#include <VectorOperations.h>
#include <cmath>
using namespace std;

namespace {
  class ProjectionMatrixTest : public ::testing::Test {
  protected:
	  ProjectionMatrix *testObj;
	  MatrixOperations *matrix_operations;
	  VectorOperations *vector_operations;

  };

  TEST_F(ProjectionMatrixTest, TestTranslationMatrix) {
	  Vertex fp(9, 0, 9, "ignore");
	  Vertex lp(100, 0, 1, "ignore");
	  Vertex vup(1, 0, 0, "ignore");
	  testObj = new ProjectionMatrix(fp, lp, vup, 4);
	  matrix_operations = new MatrixOperations();

	  float *matrix = testObj->GetTranslationMatrix();

	  ASSERT_FLOAT_EQ(matrix[3], -9);
	  ASSERT_FLOAT_EQ(matrix[7], 0);
	  ASSERT_FLOAT_EQ(matrix[10], 1);
	  ASSERT_FLOAT_EQ(matrix[11], -9);



	  // Changing matrix affects array from projection matrix class
	  matrix[3] = 45;

	  ASSERT_FLOAT_EQ(testObj->GetTranslationMatrix()[3], 45);

	  matrix_operations->PrintMatrix(matrix);

  }

  TEST_F(ProjectionMatrixTest, TestnVector) {
	  Vertex fp(9, 0, 9, "ignore");
	  Vertex lp(100, 0, 1, "ignore");
	  Vertex vup(1, 0, 0, "ignore");
	  testObj = new ProjectionMatrix(fp, lp, vup, 4);

	  vector_operations = new VectorOperations();
	  Vertex * n = testObj->GetnVector();

	  vector_operations->PrintVector(n);

	  ASSERT_FLOAT_EQ(n->x_coordinate, 91/sqrtf(8345));
	  ASSERT_FLOAT_EQ(n->y_coordinate, 0);
	  ASSERT_FLOAT_EQ(n->z_coordinate, -8/sqrtf(8345));

  }

  TEST_F(ProjectionMatrixTest, TestuVector) {
	  Vertex fp(9, 0, 9, "ignore");
	  Vertex lp(100, 0, 1, "ignore");
	  Vertex vup(1, 0, 0, "ignore");
	  testObj = new ProjectionMatrix(fp, lp, vup, 4);

	  vector_operations = new VectorOperations();
	  Vertex * u = testObj->GetuVector();

	  vector_operations->PrintVector(u);

	  ASSERT_FLOAT_EQ(u->x_coordinate, 0);
	  ASSERT_FLOAT_EQ(u->y_coordinate, 1);
	  ASSERT_FLOAT_EQ(u->z_coordinate, 0);

  }

  TEST_F(ProjectionMatrixTest, TestvVector) {
	  Vertex fp(9, 0, 9, "ignore");
	  Vertex lp(100, 0, 1, "ignore");
	  Vertex vup(1, 0, 0, "ignore");
	  testObj = new ProjectionMatrix(fp, lp, vup, 4);

	  vector_operations = new VectorOperations();
	  Vertex * v = testObj->GetvVector();

	  vector_operations->PrintVector(v);

	  ASSERT_FLOAT_EQ(v->x_coordinate, 8/sqrtf(8345));
	  ASSERT_FLOAT_EQ(v->y_coordinate, 0);
	  ASSERT_FLOAT_EQ(v->z_coordinate, 91/sqrtf(8345));

  }

  TEST_F(ProjectionMatrixTest, TestPRTMatrix) {
	  Vertex fp(9, 0, 9, "ignore");
	  Vertex lp(100, 0, 1, "ignore");
	  Vertex vup(1, 0, 0, "ignore");
	  testObj = new ProjectionMatrix(fp, lp, vup, 4.0);

	  matrix_operations = new MatrixOperations();

	  matrix_operations->PrintMatrix(testObj->GetRMatrix());

	  matrix_operations->PrintMatrix(testObj->GetPMatrix());

	  float * M = testObj->GetProjectionMatrix();

	  matrix_operations->PrintMatrix(M);

	  float result[16] = {0,1,0,0,8/sqrtf(8345),0,91/sqrtf(8345), -891/sqrtf(8345),
	  91/sqrtf(8345), 0, -8/sqrtf(8345), -747/sqrtf(8345), 91/sqrtf(8345)/4, 0, -2/sqrtf(8345), -747/sqrtf(8345)/4};

	  for (int i=0; i<16;i++) {
		  ASSERT_FLOAT_EQ(M[i],result[i]);
	  }

  }



}
