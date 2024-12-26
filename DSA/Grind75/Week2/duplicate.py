# Given an integer array nums, return true if any value appears at least twice in the array, and return
# false if every element is distinct.
#
# Example 1:
# Input: nums = [1,2,3,1]
# Output: true
# Explanation:
# The element 1 occurs at the indices 0 and 3.
#
# Example 2:
# Input: nums = [1,2,3,4]
# Output: false
# Explanation:
# All elements are distinct.
#
# Example 3:
# Input: nums = [1,1,1,3,3,4,3,2,4,2]
# Output: true
#
# Constraints:
# 1 <= nums.length <= 105
# -109 <= nums[i] <= 109

from typing import List
from collections import Counter

def containsDuplicate(nums: List[int]) -> bool:
    c = Counter(nums)

    for _, value in c.items():
        if value > 1:
            return True
    
    return False

def containsDuplicateUsingSet(nums: List[int]) -> bool:
    # Using a set for O(1) lookups
    unique = set()
    
    for element in nums:
        if element in unique:
            return True
        unique.add(element)
    
    return False

if __name__ == "__main__":
    print(containsDuplicateUsingSet([1,2,3,1]))
    print(containsDuplicateUsingSet([1,2,3,4]))
    print(containsDuplicateUsingSet([1,1,1,3,3,4,3,2,4,2]))
