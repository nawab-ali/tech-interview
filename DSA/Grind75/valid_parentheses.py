# Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is
# valid. An input string is valid if:
#
# Open brackets must be closed by the same type of brackets.
# Open brackets must be closed in the correct order.
# Every close bracket has a corresponding open bracket of the same type.
#
# Input: s = "()"
# Output: true
#
# Input: s = "()[]{}"
# Output: true
#
# Input: s = "(]"
# Output: false
#
# Input: s = "([])"
# Output: true
#
# Constraints:
# 1 <= s.length <= 104
# s consists of parentheses only '()[]{}' 

# O(n)
def check_syntax(s: str) -> bool:
    stack = []
    bracket_map = {')': '(', ']': '[', '}': '{'}
    
    for c in s:
        if c in bracket_map.values():
            stack.append(c)
        elif c in bracket_map:
            if not stack or stack.pop() != bracket_map[c]:
                return False
        else:
            return False
    
    return not stack
    
if __name__ == "__main__":
    print(check_syntax("()"))        # Expected output: True
    print(check_syntax("()[]{}"))    # Expected output: True
    print(check_syntax("(]"))        # Expected output: False
    print(check_syntax("([])"))      # Expected output: True
    print(check_syntax("([)]"))      # Expected output: False
    print(check_syntax("{[]}"))      # Expected output: True    
