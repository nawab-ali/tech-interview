# Generate all permutations of a list
# O(n!)

from itertools import permutations

def permute(input_list):
    if input_list is None or len(input_list) == 0:
        return []

    if len(input_list) == 1:
        return [input_list]

    l = []

    for i in range(len(input_list)):
        n = input_list[i]
        rem_list = input_list[:i] + input_list[i + 1:]
        for p in permute(rem_list):
            l.append([n] + p)

    return l


def main():
    numbers = [1, 2, 3, 4, 5, 5, 4, 3, 2]
    nodupe_numbers = list(set(numbers))

    for p in permutations(nodupe_numbers):
        print(list(p))

    for p in permute(list('ABC')):
        print(p)


if __name__ == '__main__':
    main()