# Binary Search Tree

class Node(object):
    def __init__(self, key) -> None:
        self.key = key
        self.left = None
        self.right = None

class BinarySearchTree(object):
    def __init__(self):
        self.root = None

    def insert(self, key) -> None:
        if self.root is None:
            self.root = Node(key)
        else:
            self._insert(self.root, key)
    
    def _insert(self, node, key) -> None:
        if key < node.key:
            if node.left is None:
                node.left = Node(key)
            else:
                self._insert(node.left, key)
        elif key > node.key:
            if node.right is None:
                node.right = Node(key)
            else:
                self._insert(node.right, key)
        else:
            raise ValueError("Duplicate keys are not allowed in a BST")

    # Left -> Root -> Right
    def inorder_traversal(self, node: Node) -> None:
        if node:
            self.inorder_traversal(node.left)
            print(node.key, end=' ')
            self.inorder_traversal(node.right)

    def delete(self, key) -> None:
        self.root = self._delete(self.root, key)
    
    def _delete(self, node: Node, key):
        if node is None:
            return node
        
        if key < node.key:
            node.left = self._delete(node.left, key)
        elif key > node.key:
            node.right = self._delete(node.right, key)
        else:
            # Node with only one child or no child
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            
            # Node with two children. Get the in-order successor (smallest in the right subtree)
            temp = self._min_value_node(node.right)
            node.key = temp.key
            node.right = self._delete(node.right, temp.key)
        
        return node

    def _min_value_node(self, node: Node) -> Node:
        current = node
        while current.left:
            current = current.left
        return current

    def search(self, key) -> bool:
        return self._search(self.root, key)

    def _search(self, node: Node, key) -> bool:
        if node is None:
            return False
        
        if key < node.key:
            return self._search(node.left, key)
        elif key > node.key:
            return self._search(node.right, key)
        else:
            return True

def main():
    bst = BinarySearchTree()
    numbers = [20, 10, 30, 5, 15, 25, 35]
    
    for n in numbers:
        bst.insert(n)
    
    bst.inorder_traversal(bst.root)
    print()
    
    bst.delete(10)
    bst.inorder_traversal(bst.root)
    print()
    
    keys = [15, 35, 100]
    for key in keys:
        print(key, bst.search(key))
    
if __name__ == "__main__":
    main()
