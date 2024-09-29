/**
 * @file matmul.h
 * @brief This file implements matrix multiplication routines.
 * @author Nawab Ali
 */

#ifndef MATMUL_H
#define MATMUL_H

#include<omp.h>
#include<vector>
#include<iostream>
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
 * @param A Matrix A[M,K]
 * @param B Matrix B[K,N]
 * @return Matrix C = A x B
 */
matrix_t serial_matmul(matrix_t& A, matrix_t& B) {
	if (is_matrix_empty(A) || is_matrix_empty(B)) {
		throw invalid_argument("Empty A or B matrix");
	}

	long M = A.size();
	long K_A = A[0].size();
	long K_B = B.size();
	long N = B[0].size();

	if (K_A != K_B) {
		throw invalid_argument("Matrix dimensions do not match");
	}

	matrix_t C(M, vector<double>(N, 0.0));

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < K_A; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	return(C);
}

/**
 * @brief Multiply 2 matrices in parallel using OpenMP
 * @param A Matrix A[M,K]
 * @param B Matrix B[K,N]
 * @return Matrix C = A x B
 */
matrix_t parallel_matmul(matrix_t& A, matrix_t& B) {
	if (is_matrix_empty(A) || is_matrix_empty(B)) {
		throw invalid_argument("Empty A or B matrix");
	}

	int i, j, k;
	int chunk = 1;
	long M = A.size();
	long K_A = A[0].size();
	long K_B = B.size();
	long N = B[0].size();

	if (K_A != K_B) {
		throw invalid_argument("Matrix dimensions do not match");
	}

	matrix_t C(M, vector<double>(N, 0.0));

#pragma omp parallel for shared(A, B, C, chunk) private(i, j, k) schedule(static, chunk)
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < K_A; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	return(C);
}

#endif //MATMUL_H
