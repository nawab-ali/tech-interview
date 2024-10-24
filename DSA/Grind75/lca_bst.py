# Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.
# The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and
# q as descendants (where we allow a node to be a descendant of itself).
#
# Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
# Output: 6
# Explanation: The LCA of nodes 2 and 8 is 6.
#
# Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
# Output: 2
# Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
#
# Input: root = [2,1], p = 2, q = 1
# Output: 2
#
# Constraints:
# The number of nodes in the tree is in the range [2, 105].
# -109 <= Node.val <= 109
# All Node.val are unique.
# p != q
# p and q will exist in the BST.

from typing import Optional

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# O(log n)
def lowestCommonAncestor(root: TreeNode, p: TreeNode, q: TreeNode) -> Optional[TreeNode]:
    if not root:
        return None
    if p.val <= root.val <= q.val or q.val <= root.val <= p.val:
        return root
    elif p.val <= root.val and q.val <= root.val:
        return lowestCommonAncestor(root.left, p, q)
    else:
        return lowestCommonAncestor(root.right, p, q)

if __name__ == "__main__":
    root = TreeNode(6)
    root.left = TreeNode(2)
    root.right = TreeNode(8)
    root.left.left = TreeNode(0)
    root.left.right = TreeNode(4)
    root.left.right.left = TreeNode(3)
    root.left.right.right = TreeNode(5)
    root.right.left = TreeNode(7)
    root.right.right = TreeNode(9)

    p = root.left   # Node with value 2
    q = root.right  # Node with value 8

    result = lowestCommonAncestor(root, p, q)
    print(result.val)  # Expected output: 6
