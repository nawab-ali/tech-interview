# Common binary tree algorithms

class Node:
    def __init__(self, value=0, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

# Breadth First Search of a binary tree
# O(n)
def bfs(root: Node) -> list:
    if not root:
        return []
    
    queue = [root]
    result = []

    while queue:
        node = queue.pop(0)
        result.append(node.value)

        if node.left:
            queue.append(node.left)
        if node.right:
            queue.append(node.right)

    return result

# Pre-order DFS: Root -> Left -> Right
def preorder_dfs(root: Node) -> list:
    if not root:
        return []
    return [root.value] + preorder_dfs(root.left) + preorder_dfs(root.right)

# In-order DFS: Left -> Root -> Right
def inorder_dfs(root: Node) -> list:
    if not root:
        return []
    return inorder_dfs(root.left) + [root.value] + inorder_dfs(root.right)

# Post-order DFS: Left -> Right -> Root
def postorder_dfs(root: Node) -> list:
    if not root:
        return []
    return postorder_dfs(root.left) + postorder_dfs(root.right) + [root.value]

def is_bst(root: Node) -> bool:
    # Inorder traversal of a BST sorts the tree in ascending order
    inorder_nodes = inorder_dfs(root)

    for i in range(len(inorder_nodes) - 1):
        if inorder_nodes[i] > inorder_nodes[i + 1]:
            return False
    return True

def height(root: Node) -> int:
    if root is None:
        return 0
    return max(height(root.left), height(root.right)) + 1

def is_balanced(root: Node) -> bool:
    if root is None:
        return True
    return (is_balanced(root.left) and 
            is_balanced(root.right) and 
            (abs(height(root.left) - height(root.right)) <= 1))

def is_balanced_opt(root: Node) -> bool:
    _, balanced = check_height_and_balance(root)
    return balanced

def check_height_and_balance(root: Node) -> tuple[int, bool]:
    if root is None:
        return 0, True
    
    left_height, left_balanced = check_height_and_balance(root.left)
    right_height, right_balanced = check_height_and_balance(root.right)

    height = 1 + max(left_height, right_height)
    current_balanced = abs(left_height - right_height) <= 1

    return height, current_balanced and left_balanced and right_balanced

def are_identical(root1: Node, root2: Node) -> bool:
    if root1 is None and root2 is None:
        return True
    
    if root1 is None or root2 is None:
        return False
    
    return (root1.value == root2.value and 
            are_identical(root1.left, root2.left) and 
            are_identical(root1.right, root2.right))

if __name__ == "__main__":
    root = Node(5)
    root.left = Node(3)
    root.right = Node(8)
    root.left.left = Node(2)
    root.left.right = Node(4)
    root.right.left = Node(6)
    root.right.right = Node(9)

    print("BFS: ", bfs(root))
    print("Preorder DFS: ", preorder_dfs(root))
    print("Inorder DFS: ", inorder_dfs(root))
    print("Postorder DFS: ", postorder_dfs(root))
    print("Is tree a BST: ", is_bst(root))
    print("Height of tree: ", height(root))
    print("Is tree balanced: ", is_balanced(root))
    print("Is tree balanced: ", is_balanced_opt(root))
    print("Are trees identical: ", are_identical(root, root))
    print("Are trees identical: ", are_identical(root, None))
