/**
 * @file unit_tests.cpp
 * @brief This file implements the unit tests.
 * @author Nawab Ali
 */

#include "matmul.h"
#include<gtest/gtest.h>

// Unit tests for matrix multipication
TEST (MatMulTest, Dummy) {
	ASSERT_EQ(0, 0);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return(RUN_ALL_TESTS());
}
