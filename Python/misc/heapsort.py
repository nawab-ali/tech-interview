import heapq


def heapsort(array):
    if array is None:
        return None

    n = len(array)
    heapq.heapify(array)
    sorted_array = [heapq.heappop(array) for _ in range(n)]

    return sorted_array


def main():
    array = [9, 5, 7, 3, 2, 1, 8, 0, 4, 6]
    array = heapsort(array)
    print(array)


if __name__ == '__main__':
    main()