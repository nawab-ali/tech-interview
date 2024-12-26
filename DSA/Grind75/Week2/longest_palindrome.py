# Given a string s which consists of lowercase or uppercase letters, return the length of the longest 
# palindrome that can be built with those letters.
#
# Letters are case sensitive, for example, "Aa" is not considered a palindrome.
#
# Example 1:
# Input: s = "abccccdd"
# Output: 7
# Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.
#
# Example 2:
# Input: s = "a"
# Output: 1
# Explanation: The longest palindrome that can be built is "a", whose length is 1.
#
# Constraints:
# 1 <= s.length <= 2000
# s consists of lowercase and/or uppercase English letters only.

from collections import Counter

# Characters with even counts can fully contribute to the palindrome.
# Characters with odd counts can contribute only their largest even subset, and at most one odd character can be
# placed in the center of the palindrome.
def longestPalindrome(s: str) -> int:
    length = 0
    has_odd = False

    c = Counter(s)

    for _, value in c.items():
        if value % 2 == 0:
            length += value
        else:
            length += value - 1
            has_odd = True

    if has_odd:
        length += 1
    
    return length

if __name__ == "__main__":
    print(longestPalindrome("abccccdd"))
    print(longestPalindrome("a"))
    print(longestPalindrome("Aa"))
