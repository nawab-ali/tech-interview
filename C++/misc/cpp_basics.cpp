#include <algorithm>
#include <cassert>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void for_loop(const vector<int> &v) {
    for (const int &e : v) {
        cout << e << " ";
    }
    cout << endl;
}

double mean(const vector<int> &v) {
    double sum = accumulate(v.begin(), v.end(), 0);

    return (sum / v.size());
}

int sum(const vector<int> &v) {
    int sum = 0;

    for_each(v.begin(), v.end(), [&sum](const int &n) { sum += n; });

    return (sum);
}

double **allocate_mem_2D_array(const int &rows, const int &cols) {
    assert(rows > 0 && cols > 0);
    double **array = new double *[rows];

    for (int i = 0; i < rows; i++) {
        array[i] = new double[cols];
    }

    return (array);
}

void deallocate_mem_2D_array(double **array, const int rows) {
    assert(rows > 0);

    for (int i = 0; i < rows; i++) {
        delete[] array[i];
    }

    delete[] array;
}

double **matmul(double **a, double **b, const int M, const int N, const int K) {
    assert(M > 0 && N > 0 && K > 0);
    double **c = allocate_mem_2D_array(M, N);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int p = 0; p < K; p++) {
                c[i][j] += a[i][p] * b[p][j];
            }
        }
    }

    return (c);
}

void DGEMM(void) {
    double **c;
    const int M = 5;
    const int N = 5;
    const int K = 5;

    double **a = allocate_mem_2D_array(M, K);
    double **b = allocate_mem_2D_array(K, N);

    cout << setprecision(2) << fixed;
    srand(time(0));

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            a[i][j] = rand() % 5;
        }
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            b[i][j] = rand() % 5;
        }
    }

    c = matmul(a, b, M, N, K);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << c[i][j] << "\t";
        }
        cout << endl;
    }

    deallocate_mem_2D_array(a, M);
    deallocate_mem_2D_array(b, K);
    deallocate_mem_2D_array(c, M);
}

int main(int argc, char **argv) {
    auto v = {1, 2, 3, 4, 5};

    DGEMM();
    for_loop(v);
    cout << mean(v) << endl;
    cout << sum(v) << endl;

    return 0;
}
