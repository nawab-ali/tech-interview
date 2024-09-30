/**
 * @file main.cpp
 * @brief This file implements the main thread of execution.
 * @author Nawab Ali
 */

#include "matmul.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int M = 1000;
    int K = 2250;
    int N = 1500;

    matrix_t A(M, vector<double>(K, 0.0));
    matrix_t B(K, vector<double>(N, 0.0));

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            A[i][j] = i + j;
        }
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = i * j;
        }
    }

    matrix_t C = parallel_matmul(A, B);

    return (0);
}
