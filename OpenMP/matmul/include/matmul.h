/**
 * @file matmul.h
 * @brief This file implements matrix multiplication routines.
 * @author Nawab Ali
 */

#ifndef MATMUL_H
#define MATMUL_H

#include<vector>
#include<stdexcept>
using namespace std;

typedef vector<vector<double>> matrix_t;

/**
 * @brief Is matrix m empty?
 * @param m Matrix m
 * @return True if m is empty
 */
bool is_matrix_empty(matrix_t& m) {
	if (!m.size()) {
		return(true);
	} else if (!m[0].size()) {
		return(true);
	} else {
		return(false);
	}
}

/**
 * @brief Multiply 2 matrices serially
 * @param a Matrix A
 * @param b Matrix B
 * @return Matrix C = A x B
 */
matrix_t serial_matmul(matrix_t& a, matrix_t& b) {
	long a_rows = 0;
	long b_rows = 0;
	long a_cols = 0;
	long b_cols = 0;

	if (is_matrix_empty(a) || is_matrix_empty(b)) {
		throw invalid_argument("Empty A or B matrix");
	}

	return(a);
}

#endif //MATMUL_H
