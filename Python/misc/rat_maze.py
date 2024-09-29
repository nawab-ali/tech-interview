# Find all possible paths from [0,0] to [n-1,n-1] in a NxN maze using backtracking
# Possible moves: Right and Down
# O(2^(n^2))

def is_valid_move(maze, x, y):
    if maze is None:
        return None

    n = len(maze)
    return 0 <= x < n and 0 <= y < n and maze[x][y] == 1


def solve_maze_util(maze, output, x, y):
    if maze is None or output is None:
        return None

    n = len(maze)
    assert (0 <= x < n and 0 <= y < n)

    if x == n - 1 and y == n - 1:
        return
    else:
        output[x][y] = 1

        if is_valid_move(maze, x + 1, y):
            solve_maze_util(maze, output, x + 1, y)
        elif is_valid_move(maze, x, y + 1):
            solve_maze_util(maze, output, x, y + 1)
        else:
            output[x][y] = 0


def solve_maze(maze):
    if maze is None:
        return None

    n = len(maze)
    output = [[0 for _ in range(n)] for _ in range(n)]
    output[0][0] = output[n - 1][n - 1] = 1

    solve_maze_util(maze, output, 0, 0)

    return output


def main():
    maze = [[1, 0, 0, 0],
            [1, 1, 0, 1],
            [0, 1, 0, 0],
            [1, 1, 1, 1]]

    output = solve_maze(maze)

    for row in output:
        print(row)


if __name__ == '__main__':
    main()