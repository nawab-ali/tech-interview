# Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to
# target. You may assume that each input would have exactly one solution, and you may not use the same element twice.
# You can return the answer in any order.
#
# Input: nums = [2,7,11,15], target = 9
# Output: [0,1]
# Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
#
# Input: nums = [3,2,4], target = 6
# Output: [1,2]
#
# Input: nums = [3,3], target = 6
# Output: [0,1]

# O(n)
def two_sum(nums: list, target: int) -> list:
    d = {}

    # Iterate through the list and check for the complement
    for i, num in enumerate(nums):
        complement = target - num

        if complement in d:
            return [d[complement], i]
        
        # Add the number and its index to the dictionary
        d[num] = i

if __name__ == "__main__":
    print(two_sum([2,7,11,15], 9))
    print(two_sum([3,2,4], 6))
    print(two_sum([3,3], 6))
