/*
 * AllTests.cpp
 *
 *  Created on: Sep 19, 2015
 *      Author: prashantm
 */



#include "gtest/gtest.h"
/*#include "FooTest.cpp"
#include "VertexTest.cpp"
#
#
#include "ParsePlyAttributesTest.cpp" */
//#include "VectorOperationsTest.cpp"
//#include <Transformation.h>
//#include "MatrixOperationsTest.cpp"
//#include "FaceTest.cpp"
//#include "TransformationMatricesTest.cpp"
//#include "ParsePlyTest.cpp"
//#include "WritePlyTest.cpp"
//#include "ParseCameraModelTest.cpp"
//#include "ProjectionMatrixTest.cpp"
#include <Silhouette.h>

int main(int argc, char **argv) {
  // ::testing::InitGoogleTest(&argc, argv);

  // Transformation * mainObj = new Transformation(argc, argv);

  Silhouette * mainObj = new Silhouette(argc, argv);



  cout << "Done! Exiting code." << endl;

  // return RUN_ALL_TESTS();
}
