# Given an array nums of size n, return the majority element. The majority element is the element
# that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
#
# Example 1:
# Input: nums = [3,2,3]
# Output: 3
#
# Example 2:
# Input: nums = [2,2,1,1,1,2,2]
# Output: 2
#
# Constraints:
# n == nums.length
# 1 <= n <= 5 * 104
# -109 <= nums[i] <= 109
#
# Follow-up: Could you solve the problem in linear time and in O(1) space?

from typing import List
from collections import Counter

def majorityElement(nums: List[int]) -> int:
    """
    Given an array nums of size n, return the majority element. The majority element is the element
    that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

    Args:
    nums (List[int]): List of integers.

    Returns:
    int: The majority element.
    """
    n = len(nums)
    c = Counter(nums)
    
    for key, value in c.items():
        if value > n // 2:
            return key

if __name__ == "__main__":
    print(majorityElement([3,2,3]))
    print(majorityElement([2,2,1,1,1,2,2]))
