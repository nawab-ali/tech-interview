# Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all
# the functions of a normal queue (push, peek, pop, and empty).

# Implement the MyQueue class:
# void push(int x) Pushes element x to the back of the queue.
# int pop() Removes the element from the front of the queue and returns it.
# int peek() Returns the element at the front of the queue.
# boolean empty() Returns true if the queue is empty, false otherwise.
#
# Notes:
# You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is
# empty operations are valid. Depending on your language, the stack may not be supported natively. You may simulate
# a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.
#
# Input
# ["MyQueue", "push", "push", "peek", "pop", "empty"]
# [[], [1], [2], [], [], []]
# Output
# [null, null, null, 1, 1, false]
#
# Explanation
# MyQueue myQueue = new MyQueue();
# myQueue.push(1); // queue is: [1]
# myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
# myQueue.peek(); // return 1
# myQueue.pop(); // return 1, queue is [2]
# myQueue.empty(); // return false
#
# Constraints:
# 1 <= x <= 9
# At most 100 calls will be made to push, pop, peek, and empty.
# All the calls to pop and peek are valid.
#
# Follow-up: Can you implement the queue such that each operation is amortized O(1) time complexity? In other words,
# performing n operations will take overall O(n) time even if one of those operations may take longer.

class MyStack:
    def __init__(self):
        self.s = []

    def push(self, x: int) -> None:
        self.s.append(x)

    def peek(self) -> int:
        if self.s:
            return self.s[-1]

    def pop(self) -> int:
        if self.s:
            return self.s.pop()

    def empty(self) -> bool:
        return not self.s

    def size(self) -> int:
        return len(self.s)

class MyQueue:
    def __init__(self):
        self.s1 = MyStack()
        self.s2 = MyStack()

    def push(self, x: int) -> None:
        self.s1.push(x)

    def _transfer(self) -> None:
        while not self.s1.empty():
            self.s2.push(self.s1.pop())

    def peek(self) -> int:
        if self.s2.empty():
            self._transfer()
        if not self.s2.empty():
            return self.s2.peek()

    def pop(self) -> int:
        if self.s2.empty():
            self._transfer()
        if not self.s2.empty():
            return self.s2.pop()
        
    def empty(self) -> bool:
        return self.s1.empty() and self.s2.empty()

if __name__ == "__main__":
    queue = MyQueue()

    queue.push(1)
    queue.push(2)

    print(queue.peek())  # Output: 1
    print(queue.pop())   # Output: 1
    print(queue.empty()) # Output: False

    queue.push(3)
    print(queue.peek())  # Output: 2
    print(queue.pop())   # Output: 2
    print(queue.pop())   # Output: 3
    print(queue.empty()) # Output: True
