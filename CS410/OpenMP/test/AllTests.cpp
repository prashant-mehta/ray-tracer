/*
 * AllTests.cpp
 *
 *  Created on: Sep 19, 2015
 *      Author: prashantm
 */



#include "gtest/gtest.h"
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

int main(int argc, char **argv) {
 // ::testing::InitGoogleTest(&argc, argv);


Casting * mainObj = new Casting(argc, argv);


  cout << "Done! Exiting code." << endl;

  //return RUN_ALL_TESTS();
}
