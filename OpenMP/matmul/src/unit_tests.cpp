/**
 * @file unit_tests.cpp
 * @brief This file implements the unit tests.
 * @author Nawab Ali
 */

#include "matmul.h"
#include<gtest/gtest.h>

// Unit tests for matrix multipication
TEST (MatMulTest, TestForEmptyMatrixEmptyRows) {
	matrix_t m;
	ASSERT_EQ(is_matrix_empty(m), true);
}

TEST (MatMulTest, TestForEmptyMatrixEmptyColumns) {
	matrix_t a;
	vector<double> b;

	a.push_back(b);
	ASSERT_EQ(is_matrix_empty(a), true);
}

TEST (MatMulTest, TestForEmptyMatrixFalse) {
	matrix_t a;
	vector<double> b;

	b.push_back(3.0);
	a.push_back(b);

	ASSERT_EQ(is_matrix_empty(a), false);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return(RUN_ALL_TESTS());
}
