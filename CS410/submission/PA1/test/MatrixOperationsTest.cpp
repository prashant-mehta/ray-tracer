/*
 * MatrixOperationsTest.cpp
 *
 *  Created on: Sep 12, 2015
 *      Author: prashantm
 */

#include <MatrixOperations.h>

#include <iostream>
#include "gtest/gtest.h"
#include <Vertex.h>
#include <vector>

using namespace std;

namespace {
  class MatrixOperationsTest : public ::testing::Test {
  protected:
	  MatrixOperations *testObj;
  };
  TEST_F(MatrixOperationsTest, Test4x4MatrixMultiply) {

	  testObj = new MatrixOperations();

	  float A[4][4] = {{12, 3, 32, 4},
	  {45, 785, 2.587, 53.6},
	  {85, 25.78, 63, 1.08},
	  {95.28, 0.542, 5.005, 1}};

	  float B[4][4] = {{5, 453.12, 18.2, 0.015},
			  {2, 55.58, 4, 0.151},
			  {87.12, 34.21, 66, 0.48},
			  {-19.45, 7.0123, 12.45, -84.78}
	  };

	  float C[4][4];
	  testObj->MatrixMultiply(A, B, C);

	  float result[4][4] = {{2776.04, 6726.949200000001, 2392.2000, -323.127},
		  {977.85944, 64485.060549999995, 4797.062, -4423.756240000001},
		  {5944.114, 42110.855684, 5821.566, -56.15462},
		  {894.06959, 43381.631, 2079.044, -80.866558}
	  };

	  for (int i = 0; i < 4; i++){
		  for (int j = 0; j < 4; j++){
			  ASSERT_FLOAT_EQ(C[i][j], result[i][j]);
		  }
	  }

  }

  TEST_F(MatrixOperationsTest, TestMatrixMultiply) {

  	  testObj = new MatrixOperations();


/*  	float **A = new float*[4];
  	  	  for (int i=0; i < 4; i++)
  	  		  A[i] = new float[4];
  	float **B = new float*[4];
  	  	  for (int i=0; i < 4; i++)
  	  		  B[i] = new float[4];
*/
  	  float A[] = {12, 3, 32, 4, 45, 785, 2.587, 53.6,  	  85, 25.78, 63, 1.08,  	  95.28, 0.542, 5.005, 1};



  	  float B[] = {5, 453.12, 18.2, 0.015,
  			  2, 55.58, 4, 0.151,
  			  87.12, 34.21, 66, 0.48,
  			  -19.45, 7.0123, 12.45, -84.78};

  	  float *C; // = new float[16];

  	 C = testObj->MatrixMultiply((float *) A, (float *) B,  4, 4, 4);


  	  float result[16] = {2776.04, 6726.949200000001, 2392.2000, -323.127,
  		  977.85944, 64485.060549999995, 4797.062, -4423.756240000001,
  		  5944.114, 42110.855684, 5821.566, -56.15462,
  		  894.06959, 43381.631, 2079.044, -80.866558  	  };


  	  for (int i = 0; i < 4; i++){
  		  for (int j = 0; j < 4; j++){
  			  ASSERT_FLOAT_EQ(C[(i*4) + j], result[(i*4) +j]);
  			  //cout << C[(i*4) + j] << endl;
  		  }
  	  }



    }

  TEST_F(MatrixOperationsTest, TestMatrixMultiplySecond) {

  	  testObj = new MatrixOperations();


/*  	float **A = new float*[4];
  	  	  for (int i=0; i < 4; i++)
  	  		  A[i] = new float[4];
  	float **B = new float*[4];
  	  	  for (int i=0; i < 4; i++)
  	  		  B[i] = new float[4];
*/
  	  float A[] = {12, 3, 32, 4, 45, 785};



  	  float B[] = {5, 453.12, 18.2, 0.015,
  			  2, -55.28, 4, 0.151};

  	  float *C; // = new float[16];

  	 C = testObj->MatrixMultiply((float *) A, (float *) B,  3, 2, 4);


  	  float result[12] = {66, 5271.6, 230.39999999999998, 0.633,
  	  168, 14278.72, 598.4, 1.084,
  	  1795, -23004.4, 3959, 119.21};


  	  for (int i = 0; i < 3; i++){
  		  for (int j = 0; j < 4; j++){
  			  ASSERT_FLOAT_EQ(C[(i*4) + j], result[(i*4) +j]);
  			  //cout << C[(i*4) + j] << endl;
  		  }
  	  }



    }

  TEST_F(MatrixOperationsTest, TestMatrixTranspose) {

	  testObj = new MatrixOperations();

	  // A 2 * 5 matrix
	  float testMatrix[] = { 14.654, 123.51, 0.1, 10.08, 0, 5, 0.32, -99.54, 0.612, -24.967};

	  float *result = testObj->MatrixTranspose(testMatrix, 2, 5);

//	  for (int i = 0; i < 10; i++)
	//	  cout << result[i] << endl;



	  for (int i = 0; i < 5; i++) {
	  		  for (int j = 0; j < 2; j++) {
//	  			  cout << result[i*2 + j] << endl;
	  			  ASSERT_FLOAT_EQ(result[i*2 + j], testMatrix[i + j*5]);
	  		  }

	  	  }


  }

  TEST_F(MatrixOperationsTest, TestPrintMatrix) {

	  testObj = new MatrixOperations();

	 float A[16] = {12, 3, 32, 4,
	  	  45, 785, 2.587, 53.6,
	  	  85, 25.78, 63, 1.08,
	  	  95.28, 0.542, 5.005, 1};

	 testObj->PrintMatrix(A);
  }

  TEST_F(MatrixOperationsTest, TestMatrixVectorProduct) {

	  testObj = new MatrixOperations();

	 float A[16] = {12, 3, 32, 4,
	  	  45, 785, 2.587, 53.6,
	  	  85, 25.78, 63, 1.08,
	  	  95.28, 0.542, 5.005, 1};


	 vector<Vertex> testVector;
	 Vertex v1(1, 2, 3, "test");

	 Vertex v2(4, 5, 6, "test");
	 Vertex v3(7, 8, 9, "test");

	 testVector.push_back(v1);
	 testVector.push_back(v2);
	 testVector.push_back(v3);

	 testVector = testObj->MatrixMultiply(A, testVector, 4, 4, 3);

	 cout << testVector.at(0).x_coordinate << endl;





  }


}
