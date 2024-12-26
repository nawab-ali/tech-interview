# Given the root of a binary tree, return its maximum depth. A binary tree's maximum depth is the number of
# nodes along the longest path from the root node down to the farthest leaf node.
#
# Example 1:
# Input: root = [3,9,20,null,null,15,7]
# Output: 3
#
# Example 2:
# Input: root = [1,null,2]
# Output: 2
#
# Constraints:
# The number of nodes in the tree is in the range [0, 104].
# -100 <= Node.val <= 100

from typing import Optional

class TreeNode:
    def __init__(self, val: int=0, left: Optional['TreeNode']=None, right: Optional['TreeNode']=None):
        self.val = val
        self.left = left
        self.right = right

def maxDepth(root: Optional[TreeNode]) -> int:
    if not root:
        return 0
    return 1 + max(maxDepth(root.left), maxDepth(root.right))

if __name__ == "__main__":
    # Example tree: [3,9,20,None,None,15,7]
    root = TreeNode(3)
    root.left = TreeNode(9)
    root.right = TreeNode(20)
    root.right.left = TreeNode(15)
    root.right.right = TreeNode(7)
    
    print(maxDepth(root))  # Output should be 3
