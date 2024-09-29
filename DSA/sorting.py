# Implementation of common sorting algorithms.

import heapq
import random

# Heapsort
# O(nlogn)
def heapsort(l: list) -> list:
    heap = l[:] # Create a copy of the list to avoid modifying the original list
    heapq.heapify(heap) # Convert the list into a heap in-place
    return [heapq.heappop(heap) for _ in range(len(heap))] # Pop elements one by one

# Quicksort
# Average case: O(nlogn)
# Worst case: O(n^2)
def quicksort(l: list) -> list:
    if len(l) <= 1:
        return l
    
    # Choose the pivot element
    pivot = l[len(l) // 2]

    # Partition the array into three parts:
    # Elements less than the pivot
    # Elements equal to the pivot
    # Elements greater than the pivot
    less = [x for x in l if x < pivot]
    equal = [x for x in l if x == pivot]
    greater = [x for x in l if x > pivot]

    return quicksort(less) + equal + quicksort(greater)

# In-place quicksort
def quicksort_inplace(l: list, low: int, high: int):
    if low < high:
        pivot = partition(l, low, high)
        quicksort_inplace(l, low, pivot - 1)
        quicksort_inplace(l, pivot + 1, high)

def partition(l: list, low: int, high: int) -> int:
    pivot = l[high] # Choose the last element as the pivot
    i = low - 1 # Index of smaller element

    # The algorithm maintains an index i that marks the boundary between elements smaller than or equal to the pivot
    # and those greater than the pivot. As it iterates through the array, it swaps elements to ensure that all
    # elements smaller than or equal to the pivot are to the left of the boundary i.
    for j in range(low, high):
        if l[j] <= pivot:
            i += 1
            l[j], l[i] = l[i], l[j]

    l[i + 1], l[high] = l[high], l[i + 1]

    return i + 1

# Merge sort
# O(nlogn)
def mergesort(l: list) -> list:
    if len(l) <= 1:
        return l

    mid = len(l) // 2
    left = mergesort(l[:mid])
    right = mergesort(l[mid:])
    return merge(left, right)

def merge(left: list, right: list) -> list:
    result = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i = i + 1
        else:
            result.append(right[j])
            j = j + 1

    result.extend(left[i:])
    result.extend(right[j:])
    return result

if __name__ == "__main__":
    x = [random.randint(1, 10000) for _ in range(10000)]
    assert(heapsort(x) == sorted(x))
    assert(quicksort(x) == sorted(x))
    assert(mergesort(x) == sorted(x))
    quicksort_inplace(x, 0, len(x) - 1)
    assert(x == sorted(x))
