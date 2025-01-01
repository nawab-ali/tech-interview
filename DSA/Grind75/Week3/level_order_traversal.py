"""
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right,
level by level).

Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
"""

from collections import deque
from typing import List, Optional

class TreeNode:
    def __init__(self, val: int=0, left: Optional['TreeNode']=None, right: Optional['TreeNode']=None):
        self.val = val
        self.left = left
        self.right = right

def levelOrderTraversal(root: Optional[TreeNode]) -> List[List[int]]:
    if not root:
        return []
    
    level = []
    result = []
    queue = deque([root, None])  # None is used as a marker for the end of a level

    while queue:
        node = queue.popleft()

        if node:
            level.append(node.val)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        else:
            result.append(level)
            level = []  # Reset level after appending to result
            if queue:
                queue.append(None)  # Add a marker for the next level
    
    return result

if __name__ == "__main__":
    root = TreeNode(3)
    root.left = TreeNode(9)
    root.right = TreeNode(20)
    root.right.left = TreeNode(15)
    root.right.right = TreeNode(7)

    print(levelOrderTraversal(root))  # Output: [[3], [9, 20], [15, 7]]
