import random
import numpy as np

def matmul(a, b):
    m, k_a = a.shape
    k_b, n = b.shape

    assert(m > 0 and n > 0 and k_a > 0 and k_b > 0)
    assert(k_a == k_b)

    c = np.zeros((m, n))

    for i in range(m):
        for j in range(n):
            for k in range(k_a):
                c[i][j] += a[i][k] * b[k][j]

    return c

def main():
    # Matrix dimensions: A[m][k], B[k][n], C[m][n]
    m = 100
    k = 50
    n = 75

    a = np.random.random((m,k))
    b = np.random.random((k,n))

    assert(np.allclose(np.dot(a, b), matmul(a, b)))

if __name__ == '__main__':
    main()
