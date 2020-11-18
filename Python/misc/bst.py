# Binary Search Tree

class Node(object):
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


class BinarySearchTree(object):
    def __init__(self, root=None):
        self.root = root

    def insert(self, data):
        self.root = self._insert_util(self.root, data)

    def search(self, data):
        return self._search_util(self.root, data)

    def inorder_traversal(self, nodes):
        self._inorder_traversal_util(self.root, nodes)

    def _insert_util(self, node, data):
        if node is None:
            return Node(data)
        else:
            if data < node.data:
                node.left = self._insert_util(node.left, data)
            elif data > node.data:
                node.right = self._insert_util(node.right, data)
            return node

    def _search_util(self, node, data):
        if node is None or data is None:
            return False

        if data == node.data:
            return True
        elif data < node.data:
            return self._search_util(node.left, data)
        else:
            return self._search_util(node.right, data)

    def _inorder_traversal_util(self, node, nodes):
        if node is None:
            return
        else:
            self._inorder_traversal_util(node.left, nodes)
            nodes.append(node.data)
            self._inorder_traversal_util(node.right, nodes)


def main():
    nodes = []
    numbers = [5, 2, 1, 13, 13, 8, 4, 14, 37, 89, 89, 244, 5677]
    bst = BinarySearchTree()

    for n in numbers:
        bst.insert(n)

    bst.inorder_traversal(nodes)

    print(numbers)
    print(nodes)

    assert (bst.search(5) is True)
    assert (bst.search(2) is True)
    assert (bst.search(1) is True)
    assert (bst.search(13) is True)
    assert (bst.search(17) is False)


if __name__ == '__main__':
    main()