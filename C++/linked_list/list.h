// This class defines a singly linked list.

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <cassert>
#include <iostream>
#include <new>
#include <vector>

using namespace std;

template <class T> class LinkedList {
  private:
    int size;
    Node<T> *head;
    Node<T> *tail;

    vector<int> search(const T &data);
    Node<T> *create_node(const T &data);

  public:
    LinkedList() : size(0), head(nullptr), tail(nullptr) {}
    LinkedList(const LinkedList<T> &list);
    LinkedList<T> &operator=(const LinkedList<T> &list);
    T &front(void) const;
    int insert_after(const int pos, const T &data);
    bool erase_after(const int pos);
    void push_front(const T &data);
    bool pop_front(void);
    void remove(const T &data);
    bool empty(void) const;
    void clear(void);

    // Overload the << operator
    friend ostream &operator<<(ostream &out, const LinkedList<T> &list) {
        Node<T> *ptr = list.head;
        while (ptr) {
            out << ptr->get_data() << " ";
            ptr = ptr->get_next();
        }
        return (out);
    }

    // Perform a deep copy of the list l2 into l1
    friend void deep_copy(LinkedList<T> &l1, const LinkedList<T> &l2) {
        int pos = 0;
        Node<T> *ptr = l2.head;
        while (ptr) {
            pos = l1.insert_after(pos, ptr->get_data());
            ptr = ptr->get_next();
        }
    }

    ~LinkedList();
};

// Search for 'data' in the list and return the positions
template <class T> vector<int> LinkedList<T>::search(const T &data) {
    int i = 1;
    vector<int> pos;
    Node<T> *ptr = head;

    while (ptr) {
        if (data == ptr->get_data()) {
            pos.push_back(i);
        }
        i++;
        ptr = ptr->get_next();
    }

    return (pos);
}

// Create a new linked list node
template <class T> Node<T> *LinkedList<T>::create_node(const T &data) {
    Node<T> *node = new Node<T>(data);
    assert(node);
    return (node);
}

// Copy constuctor
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) : LinkedList() {
    deep_copy(*this, list);
}

// Overload the assignment operator
template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list) {
    clear();
    deep_copy(*this, list);
    return (*this);
}

// Return the data from the front of the list
template <class T> T &LinkedList<T>::front(void) const {
    assert(head);
    return (head->get_data());
}

// Insert node after pos nodes
template <class T>
int LinkedList<T>::insert_after(const int pos, const T &data) {
    assert(pos >= 0 && pos <= size);

    if (pos == 0) {
        push_front(data);
    } else if (pos == size) {
        Node<T> *ptr = tail;
        tail = create_node(data);
        ptr->set_next(tail);
        size++;
    } else {
        Node<T> *ptr1 = head;
        Node<T> *ptr2 = nullptr;
        Node<T> *ptr3 = nullptr;

        for (int i = 1; i < pos; i++) {
            ptr1 = ptr1->get_next();
        }

        ptr2 = ptr1->get_next();
        ptr3 = create_node(data);
        ptr1->set_next(ptr3);
        ptr3->set_next(ptr2);

        size++;
    }

    assert((pos + 1) <= size);
    return (pos + 1);
}

// Erase the node after pos
template <class T> bool LinkedList<T>::erase_after(const int pos) {
    assert(pos >= 0 && pos < size);
    assert(head);

    if (pos == 0) {
        assert(pop_front());
    } else if (pos == size - 1) {
        Node<T> *ptr1 = head;
        Node<T> *ptr2 = nullptr;

        for (int i = 1; i < pos; i++) {
            ptr1 = ptr1->get_next();
        }
        ptr2 = ptr1->get_next();
        ptr1->set_next(nullptr);
        tail = ptr1;
        delete ptr2;
        size--;
    } else {
        Node<T> *ptr1 = head;
        Node<T> *ptr2 = nullptr;

        for (int i = 1; i < pos; i++) {
            ptr1 = ptr1->get_next();
        }
        ptr2 = ptr1->get_next();
        ptr1->set_next(ptr2->get_next());
        delete ptr2;
        size--;
    }

    return (true);
}

// Push a node to the front of the list
template <class T> void LinkedList<T>::push_front(const T &data) {
    if (!head) {
        head = tail = create_node(data);
    } else {
        Node<T> *ptr_old_node = head;
        Node<T> *ptr_new_node = create_node(data);
        head = ptr_new_node;
        ptr_new_node->set_next(ptr_old_node);
    }
    size++;
}

// Remove the first node from the list
template <class T> bool LinkedList<T>::pop_front(void) {
    if (!head) {
        return (false);
    } else {
        Node<T> *node = head;
        head = head->get_next();
        delete node;
        size--;
        return (true);
    }
}

// Remove all elements = data
template <class T> void LinkedList<T>::remove(const T &data) {
    vector<int> pos = search(data);
    for (int i = 0; i < pos.size(); i++) {
        erase_after(pos[i] - 1 - i);
    }
}

// Is the list empty?
template <class T> bool LinkedList<T>::empty(void) const {
    assert(size >= 0);
    return (size == 0);
}

// Delete all the nodes in the list
template <class T> void LinkedList<T>::clear(void) {
    while (head) {
        assert(pop_front());
    }
    assert(size == 0);
}

// Destructor
template <class T> LinkedList<T>::~LinkedList() {
    // Delete the nodes in the list
    clear();
}

#endif // LINKEDLIST_H
