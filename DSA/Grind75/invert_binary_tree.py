# Given the root of a binary tree, invert the tree, and return its root.
#
# Input: root = [4,2,7,1,3,6,9]
# Output: [4,7,2,9,6,3,1]
#
# Input: root = [2,1,3]
# Output: [2,3,1]
#
# Input: root = []
# Output: []
#
# Constraints:
# The number of nodes in the tree is in the range [0, 100].
# -100 <= Node.val <= 100

from typing import Optional, List

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# Swap the left and right children of every node in the tree recursively to invert the tree
# O(n)
def invertBinaryTree(root: Optional[TreeNode]) -> Optional[TreeNode]:
    if not root:
        return None
    
    # Swap the left and right children
    root.left, root.right = root.right, root.left

    # Recursively invert the left and right subtrees
    invertBinaryTree(root.left)
    invertBinaryTree(root.right)
    
    return root

def preorderTraversal(root: Optional[TreeNode]) -> List[int]:
    if root:
        return [root.val] + preorderTraversal(root.left) + preorderTraversal(root.right)
    else:
        return []

if __name__ == "__main__":
    # Input: [4, 2, 7, 1, 3, 6, 9]
    root = TreeNode(4)
    root.left = TreeNode(2)
    root.right = TreeNode(7)
    root.left.left = TreeNode(1)
    root.left.right = TreeNode(3)
    root.right.left = TreeNode(6)
    root.right.right = TreeNode(9)

    print(preorderTraversal(invertBinaryTree(root)))

    root = TreeNode(2)
    root.left = TreeNode(1)
    root.right = TreeNode(3)
    
    print(preorderTraversal(invertBinaryTree(root)))
    print(preorderTraversal(invertBinaryTree(None)))
