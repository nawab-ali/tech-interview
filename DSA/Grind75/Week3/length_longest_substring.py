# Given a string s, find the length of the longest substring without repeating characters.
#
# Example 1:
# Input: s = "abcabcbb"
# Output: 3
# Explanation: The answer is "abc", with the length of 3.
#
# Example 2:
# Input: s = "bbbbb"
# Output: 1
# Explanation: The answer is "b", with the length of 1.
#
# Example 3:
# Input: s = "pwwkew"
# Output: 3
# Explanation: The answer is "wke", with the length of 3.
# Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
#
# Constraints:
# 0 <= s.length <= 5 * 104
# s consists of English letters, digits, symbols and spaces.

def lengthLongestSubstring(s: str) -> int:
    """
    The function uses a sliding window approach with two pointers to keep track of the current substring
    without repeating characters. A set is used to store the characters in the current window. The outer loop
    iterates through the string with the right pointer (j), and the inner loop adjusts the left pointer (i) to
    ensure no characters are repeated. The maximum length of the substring is updated during each iteration.
    """
    char_set = set()
    i, max_len = 0, 0

    for j in range(len(s)):
        while s[j] in char_set:
            char_set.remove(s[i])
            i += 1
        char_set.add(s[j])
        max_len = max(max_len, j-i+1)
    
    return max_len

if __name__ == "__main__":
    print(lengthLongestSubstring("abcabcbb")) # 3
    print(lengthLongestSubstring("bbbbb")) # 1
    print(lengthLongestSubstring("pwwkew")) # 3
