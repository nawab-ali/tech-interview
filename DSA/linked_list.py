# Linked list

class Node(object):
    def __init__(self, data) -> None:
        self.data = data
        self.next = None

class LinkedList(object):
    def __init__(self) -> None:
        self.head = None
        self.size = 0

    def print_list(self) -> None:
        node = self.head
        while node:
            print(node.data, end=' ')
            node = node.next
        print()

    def insert(self, data, pos=0) -> None:
        if pos < 0 or pos > self.size:
            raise ValueError('Error: invalid position specified')
        
        current = self.head
        node = Node(data)
        
        if pos == 0:
            self.head = node
            node.next = current
        else:
            for _ in range(pos - 1):
                current = current.next
            node.next = current.next
            current.next = node
            
        self.size += 1

    def delete(self, pos=0) -> None:
        if pos < 0 or pos >= self.size:
            raise ValueError('Error: invalid position specified')

        prev = current = self.head
        
        if pos == 0:
            self.head = current.next
        else:
            for _ in range(pos):
                prev = current
                current = current.next
            prev.next = current.next
        
        del(current)
        self.size -= 1

    def reverse(self) -> None:
        prev = None
        current = self.head
        
        while current:
            next = current.next
            current.next = prev
            prev = current
            current = next
        self.head = prev
        
def main():
    ll = LinkedList()
    numbers = [5, 2, 1, 13, 13, 8, 4, 14, 37, 89, 89, 244, 5677]

    for n in numbers:
        try:
            ll.insert(n, ll.size)
        except ValueError as e:
            print(e)
    
    ll.print_list()
    
    for data, pos in [[35, 2], [37, 7], [6, 0]]:
        try:
            ll.insert(data, pos)
            ll.print_list()
        except ValueError as e:
            print(e)
            
    for n in [0, 1, 2, ll.size - 1]:
        try:
            ll.delete(n)
            ll.print_list()
        except ValueError as e:
            print(e)
    
    ll.reverse()
    ll.print_list()

if __name__ == "__main__":
    main()
