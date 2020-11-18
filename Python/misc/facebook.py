# Function: Balanced parentheses
# "{{}}" --> Balanced
# "{{{}" --> Not Balanced
# "}}}}{{{{"  --> Not Balanced
# "}"  --> Not Balanced
# "{" --> Not Balanced

from bisect import bisect_left


def balanced_parentheses(string):
    if string is None:
        return True

    count = 0

    for c in string:
        if c == '{':
            count += 1
        elif c == '}':
            count -= 1
            if count < 0:
                return False
        else:
            raise ValueError('Invalid character')

    return count == 0


## Intersection of two sorted arrays of integers
# A: [0, 1, 3, 5, 5, 7, 9]
# B: [1, 5, 9, 9, 19]
# Output: [1, 5, 9]
# O(nlog(m))

def search(l, x, lo=0, hi=None):
    hi = hi if hi is not None else len(l)
    pos = bisect_left(l, x, lo, hi)

    return pos != hi and l[pos] == x


def intersection(a, b):
    if a is None or b is None:
        return None

    intersection_list = []

    for number in b:
        if search(a, number) is True:
            if number not in intersection_list:
                intersection_list.append(number)

    return intersection_list


def main():
    try:
        assert (balanced_parentheses('{{}}') is True)
        assert (balanced_parentheses('{{{}') is False)
        assert (balanced_parentheses('}}}}{{{{') is False)
        assert (balanced_parentheses('}') is False)
        assert (balanced_parentheses('{') is False)
        assert (balanced_parentheses('{c') is False)
    except ValueError as ve:
        print(ve)

    a = [0, 1, 3, 5, 5, 7, 9]
    b = [1, 5, 9, 9, 19]

    if len(a) < len(b):
        a, b = b, a

    print(intersection(a, b))


if __name__ == '__main__':
    main()
