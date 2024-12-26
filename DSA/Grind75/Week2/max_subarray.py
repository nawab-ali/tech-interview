# Given an integer array nums, find the subarray with the largest sum, and return its sum.
#
# Example 1:
# Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
# Output: 6
# Explanation: The subarray [4,-1,2,1] has the largest sum 6.
#
# Example 2:
# Input: nums = [1]
# Output: 1
# Explanation: The subarray [1] has the largest sum 1.
#
# Example 3:
# Input: nums = [5,4,-1,7,8]
# Output: 23
# Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
#
# Constraints:
# 1 <= nums.length <= 105
# -104 <= nums[i] <= 104

from typing import List

def maxSubarray(nums: List[int]) -> int:
    maxSum = nums[0]
    currentSum = nums[0]
    
    for num in nums[1:]:
        currentSum = max(num, currentSum + num)
        maxSum = max(maxSum, currentSum)
    
    return maxSum

if __name__ == "__main__":
    print(maxSubarray([-2,1,-3,4,-1,2,1,-5,4]))
    print(maxSubarray([1]))
    print(maxSubarray([5,4,-1,7,8]))
