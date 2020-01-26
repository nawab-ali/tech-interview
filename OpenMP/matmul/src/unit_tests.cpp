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

TEST (MatMulTest, SerialMatmulThrowInvalidArgForEmptyMatrix) {
	matrix_t a;
	matrix_t b;

	EXPECT_THROW(serial_matmul(a, b), invalid_argument);
}

TEST (MatMulTest, SerialMatmulThrowInvalidArgForDimMismatch) {
	matrix_t a(10, vector<double>(5, 0.0));
	matrix_t b(10, vector<double>(5, 0.0));

	EXPECT_THROW(serial_matmul(a, b), invalid_argument);
}

TEST (MatMulTest, SerialMatmul) {
	int z = 0;
	matrix_t A(3, vector<double>(3, 0.0));
	matrix_t B(3, vector<double>(3, 0.0));
	matrix_t C_prime = {{15,18,21}, {42,54,66}, {69,90,111}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			A[i][j] = B[i][j] = z++;
		}
	}

	matrix_t C = serial_matmul(A, B);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_EQ(C[i][j], C_prime[i][j]);
		}
	}
}

TEST (MatMulTest, ParallelMatmul) {
	int z = 0;
	matrix_t A(3, vector<double>(3, 0.0));
	matrix_t B(3, vector<double>(3, 0.0));
	matrix_t C_prime = {{15,18,21}, {42,54,66}, {69,90,111}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			A[i][j] = B[i][j] = z++;
		}
	}

	matrix_t C = parallel_matmul(A, B);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_EQ(C[i][j], C_prime[i][j]);
		}
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return(RUN_ALL_TESTS());
}
