# Singly Linked List

class Node(object):
    def __init__(self, data):
        self.data = data
        self.next = None


class SinglyLinkedList(object):
    def __init__(self):
        self.head = None
        self.size = 0

    def insert(self, data, pos=0):
        assert (0 <= pos <= self.size)

        tmp = self.head
        node = Node(data)

        if pos == 0:
            self.head = node
            node.next = tmp
        else:
            for _ in range(pos - 1):
                tmp = tmp.next
            node.next = tmp.next
            tmp.next = node

        self.size += 1

    def delete(self, pos=0):
        assert (0 <= pos < self.size)

        prev = tmp = self.head

        if pos == 0:
            self.head = tmp.next
        else:
            for _ in range(pos):
                prev = tmp
                tmp = tmp.next
            prev.next = tmp.next

        self.size -= 1

    def print_list(self):
        node = self.head

        for _ in range(self.size):
            print(node.data, end=' ')
            node = node.next
        print()


def main():
    ll = SinglyLinkedList()
    numbers = [5, 2, 1, 13, 13, 8, 4, 14, 37, 89, 89, 244, 5677]

    for n in numbers:
        ll.insert(n, ll.size)

    ll.insert(35, 2)
    ll.insert(37, 7)
    ll.insert(6, 0)

    ll.print_list()

    ll.delete(0)
    ll.print_list()
    ll.delete(1)
    ll.print_list()
    ll.delete(2)
    ll.print_list()
    ll.delete(ll.size - 1)
    ll.print_list()


if __name__ == '__main__':
    main()