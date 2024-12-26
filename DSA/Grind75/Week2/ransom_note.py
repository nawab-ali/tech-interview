# Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letter
# from magazine and false otherwise. Each letter in magazine can only be used once in ransomNote.
#
# Example 1:
# Input: ransomNote = "a", magazine = "b"
# Output: false
#
# Example 2:
# Input: ransomNote = "aa", magazine = "ab"
# Output: false
#
# Example 3:
# Input: ransomNote = "aa", magazine = "aab"
# Output: true
#
# Constraints:
# 1 <= ransomNote.length, magazine.length <= 105
# ransomNote and magazine consist of lowercase English letters.

from collections import Counter

# O(n + m), where n is the length of ransomNote and m is the length of magazine.
def constructRansomNote(ransomNote: str, magazine: str) -> bool:
    c1 = Counter(ransomNote)
    c2 = Counter(magazine)

    for key, value in c1.items():
        if c2[key] < value:
            return False
    
    return True

if __name__ == "__main__":
    print(constructRansomNote("a", "b"))
    print(constructRansomNote("aa", "ab"))
    print(constructRansomNote("aa", "aab"))
