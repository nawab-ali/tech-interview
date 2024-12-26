# Given a binary tree, determine if it is height-balanced. A height-balanced binary tree is a binary tree
# in which the depth of the two subtrees of every node never differs by more than one.
#
# Input: root = [3,9,20,null,null,15,7]
# Output: true
#
# Input: root = [1,2,2,3,3,null,null,4,4]
# Output: false
#
# Input: root = []
# Output: true
#
# Constraints:
# The number of nodes in the tree is in the range [0, 5000].
# -104 <= Node.val <= 104

from typing import Optional, Tuple

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def height(root: Optional[TreeNode]) -> int:
    if not root:
        return 0
    
    return 1 + max(height(root.left), height(root.right))

def isBinaryTreeBalanced(root: Optional[TreeNode]) -> bool:
    if not root:
        return True

    return (isBinaryTreeBalanced(root.left) and
            isBinaryTreeBalanced(root.right) and
            abs(height(root.left) - height(root.right) <= 1))

def checkHeightAndBalance(root: Optional[TreeNode]) -> Tuple[int, bool]:
    if not root:
        return 0, True
    
    hl, bl = checkHeightAndBalance(root.left)
    hr, br = checkHeightAndBalance(root.right)

    height = 1 + max(hl, hr)
    balance = bl and br and abs(hl - hr) <= 1

    return height, balance

def isBinaryTreeBalancedOpt(root: Optional[TreeNode]) -> bool:
    if not root:
        return True
    
    _, balanced = checkHeightAndBalance(root)
    return balanced

if __name__ == "__main__":
    # Input: root = [3,9,20,null,null,15,7]
    root = TreeNode(3)
    root.left = TreeNode(9)
    root.right = TreeNode(20)
    root.right.left = TreeNode(15)
    root.right.right = TreeNode(7)

    print(isBinaryTreeBalancedOpt(root))  # Expected output: True
