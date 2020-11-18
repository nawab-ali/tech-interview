# Flood fill a MxN screen
# Given a 2D screen, location of a pixel in the screen and a color, replace color of the given pixel and all adjacent
# same colored pixels with the given color.

# O(MN)
def flood_fill(screen, x, y, prev_color, new_color):
    if screen is None:
        return None

    m = len(screen)
    n = len(screen[0])

    if x < 0 or x >= m or y < 0 or y >= n or screen[x][y] != prev_color or screen[x][y] == new_color:
        return

    screen[x][y] = new_color

    flood_fill(screen, x - 1, y, prev_color, new_color)
    flood_fill(screen, x + 1, y, prev_color, new_color)
    flood_fill(screen, x, y - 1, prev_color, new_color)
    flood_fill(screen, x, y + 1, prev_color, new_color)


def main():
    screen = [[1, 1, 1, 1, 1, 1, 1, 1],
              [1, 1, 1, 1, 1, 1, 0, 0],
              [1, 0, 0, 1, 1, 0, 1, 1],
              [1, 2, 2, 2, 2, 0, 1, 0],
              [1, 1, 1, 2, 2, 0, 1, 0],
              [1, 1, 1, 2, 2, 2, 2, 0],
              [1, 1, 1, 1, 1, 2, 1, 1],
              [1, 1, 1, 1, 1, 2, 2, 1]]

    flood_fill(screen, 4, 4, screen[4][4], 3)

    for row in screen:
        print(row)


if __name__ == '__main__':
    main()