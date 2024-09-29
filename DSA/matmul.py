# Matrix multiplication
# O(N^3)

import numpy as np

def matmul(a: np.array, b: np.array) -> np.array:
    if a is None or b is None:
        return None
    
    if a.shape[1] != b.shape[0]:
        raise ValueError("Error: Invalid matrix dimensions")
    
    M, K = a.shape
    _, N = b.shape
    
    c = np.zeros((M, N))

    for m in range(M):
        for n in range(N):
            for k in range(K):
                c[m][n] += a[m][k] * b[k][n]
    
    return c

def main():
    M, K, N = 5, 4, 3
    
    a = np.random.random((M, K))
    b = np.random.random((K, N))
    
    print(a, '\n')
    print(b, '\n')
    
    try:
        c = matmul(a, b)
        np.testing.assert_allclose(c, np.dot(a, b))
        print(c, '\n')
    except ValueError as e:
        print(e)

if __name__ == "__main__":
    main()
