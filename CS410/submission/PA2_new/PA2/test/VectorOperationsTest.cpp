/*
 * VectorOperationsTest.cpp
 *
 *  Created on: Sep 19, 2015
 *      Author: prashantm
 */

#include <VectorOperations.h>
#include <Vertex.h>
namespace {
class VectorOperationsTest: public ::testing::Test {
protected:
	VectorOperations *testObj;
};

TEST_F(VectorOperationsTest, TestCrossProduct) {
	testObj = new VectorOperations();
	Vertex *v1 = new Vertex(12.231, -0.123, 995.0145, "test string");
	Vertex *v2 = new Vertex(45.0154, 17.80146, -0.01357, "test string");

	Vertex *v3 = testObj->CrossProduct(v1, v2);

	Vertex actual_result(-17712.70915206, 44791.14169797, 223.26655146, "ignore string");

	ASSERT_FLOAT_EQ(v3->x_coordinate, actual_result.x_coordinate);
	ASSERT_FLOAT_EQ(v3->y_coordinate, actual_result.y_coordinate);
	ASSERT_FLOAT_EQ(v3->z_coordinate, actual_result.z_coordinate);
	delete(testObj);
}

TEST_F(VectorOperationsTest, TestNormalize) {
	testObj = new VectorOperations();
	Vertex *v1 = new Vertex(3, 1, 2, "test string");

	Vertex *v3 = testObj->Normalize(v1);

	Vertex actual_result(0.801783726, 0.267261242, 0.534522484, "ignore string");

	ASSERT_FLOAT_EQ(v3->x_coordinate, actual_result.x_coordinate);
	ASSERT_FLOAT_EQ(v3->y_coordinate, actual_result.y_coordinate);
	ASSERT_FLOAT_EQ(v3->z_coordinate, actual_result.z_coordinate);

	delete(testObj);
}

TEST_F(VectorOperationsTest, TestMagnitude) {
	testObj = new VectorOperations();
	Vertex *v1 = new Vertex(-0.153, 100.512, 2.0123, "test string");

	Vertex *v = testObj->Normalize(v1);

	ASSERT_FLOAT_EQ(testObj->Magnitude(v), 1);

	delete(testObj);

}

TEST_F(VectorOperationsTest, TestNonParallelVector) {
	testObj = new VectorOperations();
	Vertex *v1 = new Vertex(-0.153, 100.512, 2.0123, "test string");

	Vertex *v = testObj->NonParallelUnitVector(v1);

	ASSERT_FLOAT_EQ(testObj->Magnitude(v), 1);

	//Vertex *v2 = new Vertex(0.25, -1, 9, "test string");

	//Vertex *v3 = new Vertex(1, -4, 36, "test string");

	Vertex *cross = testObj->CrossProduct(v1, v);

	cout << "Cross product's x-coord is " << cross->x_coordinate << endl;

	cout << "Cross product's y-coord is " << cross->y_coordinate << endl;

	cout << "Cross product's z-coord is " << cross->z_coordinate << endl;
	delete(testObj);

}


TEST_F(VectorOperationsTest, TestIfOrthogonal) {
	testObj = new VectorOperations();
	Vertex *v1 = new Vertex(5, -1, 2, "test string");

	Vertex *v2 = new Vertex(3, -11, -13, "test string");

	Vertex *v3 = new Vertex(1, -11, -2, "test string");

	float result = testObj->DotProduct(v1, v3);

	ASSERT_FLOAT_EQ(result, 12);


	ASSERT_TRUE(testObj->testIfOrthogonal(v1, v2));

	ASSERT_FALSE(testObj->testIfUnitVector(v1));

	cout << testObj->Magnitude(testObj->Normalize(v1)) << endl;

	testObj->PrintVector(v1);




	ASSERT_TRUE(testObj->testIfUnitVector(testObj->Normalize(v1)));

	testObj->PrintVector(v1);
	delete(testObj);
}

TEST_F(VectorOperationsTest, Test3DDistance) {
	testObj = new VectorOperations();
	Vertex *v1 = new Vertex(-7, -4, 3, "test string");

	Vertex *v2 = new Vertex(17, 6, 2.5, "test string");



	float result = testObj->Distance(v1, v2);

	ASSERT_FLOAT_EQ(result, 26.004807);


	delete(testObj);
}

}
