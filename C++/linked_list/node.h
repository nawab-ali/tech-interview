// This class defines a node of the singly linked list.

#ifndef NODE_H
#define NODE_H

template <class T> class Node {
  private:
    T data;
    Node<T> *next;

  public:
    Node(const T &data) : data(data), next(nullptr) {}
    T get_data(void) const;
    Node<T> *get_next(void) const;
    void set_data(const T &data);
    void set_next(Node<T> *const next);
};

template <class T> T Node<T>::get_data(void) const { return (data); }

template <class T> Node<T> *Node<T>::get_next(void) const { return (next); }

template <class T> void Node<T>::set_data(const T &data) { this->data = data; }

template <class T> void Node<T>::set_next(Node<T> *const next) {
    this->next = next;
}

#endif // NODE_H
