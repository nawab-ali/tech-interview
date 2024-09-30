// Binary Search Tree

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

template <class T> struct Node {
    T data;
    Node *left;
    Node *right;
};

template <class T> class BinarySearchTree {
  public:
    BinarySearchTree(Node<T> *root) : root(root) {}
    void inorder_traversal(vector<Node<T> *> &v);
    void insert(const T &data);
    bool search(const T &data);

    friend ostream &operator<<(ostream &out, BinarySearchTree<T> &bst) {
        vector<Node<T> *> nodes;
        bst.inorder_traversal(nodes);

        for (const auto &node : nodes) {
            cout << node->data << " ";
        }

        return (out);
    }

    ~BinarySearchTree();

  private:
    Node<T> *root;
    void insert_util(Node<T> *root, const T &data);
    bool search_util(Node<T> *root, const T &data);
    void inorder_traversal_util(Node<T> *root, vector<Node<T> *> &v);
};

template <class T>
void BinarySearchTree<T>::inorder_traversal(vector<Node<T> *> &v) {
    inorder_traversal_util(root, v);
}

template <class T>
void BinarySearchTree<T>::inorder_traversal_util(Node<T> *root,
                                                 vector<Node<T> *> &v) {
    if (root) {
        inorder_traversal_util(root->left, v);
        v.push_back(root);
        inorder_traversal_util(root->right, v);
    }
}

template <class T> void BinarySearchTree<T>::insert(const T &data) {
    try {
        insert_util(root, data);
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}

template <class T>
void BinarySearchTree<T>::insert_util(Node<T> *root, const T &data) {
    if (root) {
        Node<int> *node = new Node<int>;

        node->data = data;
        node->left = nullptr;
        node->right = nullptr;

        if (data < root->data) {
            if (root->left) {
                insert_util(root->left, data);
            } else {
                root->left = node;
            }
        } else if (data > root->data) {
            if (root->right) {
                insert_util(root->right, data);
            } else {
                root->right = node;
            }
        } else {
            throw runtime_error("Duplicate data not allowed in BST");
        }
    }
}

template <class T> bool BinarySearchTree<T>::search(const T &data) {
    return (search_util(root, data));
}

template <class T>
bool BinarySearchTree<T>::search_util(Node<T> *root, const T &data) {
    if (root) {
        if (data == root->data) {
            return (true);
        } else if (data < root->data) {
            return (search_util(root->left, data));
        } else {
            return (search_util(root->right, data));
        }
    } else {
        return (false);
    }
}

template <class T> BinarySearchTree<T>::~BinarySearchTree(void) {
    vector<Node<T> *> nodes;

    inorder_traversal(nodes);

    for (const auto &node : nodes) {
        delete node;
    }
}

int main(int argc, char **argv) {
    vector<Node<int> *> nodes;
    Node<int> *root = new Node<int>;
    vector<int> v = {17, 34, 8, 3567, 8, 425, 5, 3, 100, 45, 34, 23, 67};

    root->data = 10;
    root->left = nullptr;
    root->right = nullptr;

    BinarySearchTree<int> bst = BinarySearchTree<int>(root);

    for (const auto &i : v) {
        bst.insert(i);
    }

    bst.inorder_traversal(nodes);

    for (const auto &node : nodes) {
        cout << node->data << " ";
    }
    cout << endl;

    cout << bst << endl;

    assert(bst.search(425));
    assert(!bst.search(1425));

    return 0;
}
