# Count all possible paths from top left to bottom right of an MxN matrix

# O(2^n)
def num_paths(m, n):
    if m == 0 or n == 0:
        return 1
    else:
        return num_paths(m - 1, n) + num_paths(m, n - 1)


# O(mn)
def num_paths_dp(m, n):
    count = [[0 for _ in range(n + 1)] for _ in range(m + 1)]

    for i in range(m + 1):
        for j in range(n + 1):
            if i == 0 or j == 0:
                count[i][j] = 1
            else:
                count[i][j] = count[i - 1][j] + count[i][j - 1]

    return count[m][n]


def main():
    print(num_paths(5, 5))
    print(num_paths_dp(5, 5))


if __name__ == '__main__':
    main()