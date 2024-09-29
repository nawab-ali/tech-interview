# Given an array of integers A and a sum B, find all unique combinations in A where the sum is equal to B.
# Each number in A may only be used once in the combination.
# NP-hard problem. O(2^n)

import itertools

def combinations(numbers, target, results, partial=[]):
    if numbers is None or target < 0:
        return None

    s = sum(partial)
    if s == target:
        results.append(partial)

    if s > target:
        return

    for i in range(len(numbers)):
        n = numbers[i]
        remaining = numbers[i + 1:]
        combinations(remaining, target, results, partial + [n])


def main():
    target = 8
    results = []
    numbers = [10, 1, 2, 7, 6, 1, 5]

    numbers.sort()
    combinations(numbers, target, results)

    results.sort()
    uniq_results = [k for k, _ in itertools.groupby(results)]
    print(uniq_results)


if __name__ == '__main__':
    main()