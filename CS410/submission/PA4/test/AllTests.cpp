/*
 * AllTests.cpp
 *
 *  Created on: Sep 19, 2015
 *      Author: prashantm
 */



//#include "gtest/gtest.h"
/*#include "FooTest.cpp"
#include "VertexTest.cpp"
#include "ParsePlyAttributesTest.cpp"
#include "VectorOperationsTest.cpp"
#include <Transformation.h>
#include "MatrixOperationsTest.cpp"
#include "FaceTest.cpp"
#include "TransformationMatricesTest.cpp"
#include "ParsePlyTest.cpp"
#include "WritePlyTest.cpp"
#include "ParseCameraModelTest.cpp"
#include "ProjectionMatrixTest.cpp"
#include <Silhouette.h>
#include "LightSourceTest.cpp"
#include "ParseMaterialsTest.cpp"*/
//#include "FaceTest.cpp"
//#include "ParseMaterialsTest.cpp"
#include "Casting.h"
#include <chrono>

using namespace std::chrono;

int main(int argc, char **argv) {
 // ::testing::InitGoogleTest(&argc, argv);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

Casting * mainObj = new Casting(argc, argv);

high_resolution_clock::time_point t2 = high_resolution_clock::now();

auto duration = duration_cast<seconds>( t2 - t1 ).count();



  cout << "Execution time - " << duration << endl;
  cout << "Done! Exiting code." << endl;

  //return RUN_ALL_TESTS();
}
