# Given an array of integers A and a sum B, find all unique combinations in A where the sum is equal to B.
# Each number in A may only be used once in the combination.
# NP-hard problem. O(2^n)

def combinations_util(input_list, target_sum, local, index=0, current_sum=0):
    if input_list is None or target_sum < 0:
        return None

    if current_sum == target_sum:
        print(local)
        return

    for i in range(index, len(input_list)):
        if current_sum + input_list[i] > target_sum:
            continue

        # Check for repetitions
        if i == 1 and input_list[i] == input_list[i - 1] and i > index:
            continue

        local.append(input_list[i])
        combinations_util(input_list, target_sum, local, i + 1, current_sum + input_list[i])

        local.remove(local[len(local) - 1])


def combinations(input_list, target_sum):
    local = []

    input_list.sort()
    combinations_util(input_list, target_sum, local)


def main():
    target_sum = 8
    input_list = [10, 1, 2, 7, 6, 1, 5]

    combinations(input_list, target_sum)


if __name__ == '__main__':
    main()