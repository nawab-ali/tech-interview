# Given two strings s and t, return true if t is an anagram of s, and false otherwise.
#
# Input: s = "anagram", t = "nagaram"
# Output: true
#
# Input: s = "rat", t = "car"
# Output: false
#
# Constraints:
# 1 <= s.length, t.length <= 5 * 104
# s and t consist of lowercase English letters.

from collections import Counter

# O(n)
def isAnagram(s: str, t: str) -> bool:
    ds, dt = {}, {}

    for c in s:
        ds[c] = ds.get(c, 0) + 1

    for c in t:
        dt[c] = dt.get(c, 0) + 1

    return ds == dt

def isAnagramCounter(s: str, t: str) -> bool:
    return Counter(s) == Counter(t)

if __name__ == "__main__":
    print(isAnagramCounter("anagram", "nagaram"))
    print(isAnagramCounter("rat", "car"))
