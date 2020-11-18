""" Matrix multiplication """

import numpy as np

def matmul(a, b):
    if a is None or b is None:
        return None

    m, k_a = a.shape
    k_b, n = b.shape

    if k_a != k_b:
        raise ValueError('k_a != k_b')

    c = np.zeros((m, n))

    for i in range(m):
        for j in range(n):
            for k in range(k_a):
                c[i, j] += a[i, k] * b[k, j]

    return c

def main():
    m, k, n = 5, 3, 4

    a = np.random.random((m, k))
    b = np.random.random((k, n))

    print(a)
    print(b)

    try:
        c = matmul(a, b)
        print(c)
        np.testing.assert_allclose(c, np.dot(a, b))
    except ValueError as ve:
        print(ve)

if __name__ == '__main__':
    main()