# Implementation of minimum heap data structure.

from typing import List, Optional

class MinHeap(object):
    def __init__(self):
        self._container = []

    def push(self, key) -> None:
        # Push the element to the end of the heap and sift up to maintain the heap invariant
        self._container.append(key)
        self._sift_up(self._size() - 1)

    def pop(self) -> Optional[int]:
        if self._size() == 0:
            return None
        
        # Return the first element of the container which is the smallest element
        val = self._container[0]
        self._container[0] = self._container[self._size() - 1]
        self._container.pop()
        if self._size() > 0:
            self._sift_down(0)
        
        return val

    def heapify(self, l: List) -> None:
        # Convert list into a heap in place in linear time
        self._container = l
        i = self._size() // 2 - 1
        
        while i >= 0:
            self._sift_down(i)
            i -= 1

    def _size(self) -> int:
        return len(self._container)

    def _parent(self, i: int) -> int:
        # Return parent of node i in the complete binary tree
        assert(i >= 0 and i < self._size())
        return (i - 1) // 2
        
    def _left_child(self, i: int) -> int:
        # Return left child of node i in the complete binary tree
        assert(i >= 0 and i < self._size())
        return 2*i + 1

    def _right_child(self, i: int) -> int:
        # Return right child of node i in the complete binary tree
        assert(i >= 0 and i < self._size())
        return 2*i + 2

    def _sift_up(self, i: int) -> None:
        # Bubble up the element to the right position in the heap
        assert(i >= 0 and i < self._size())
        
        while i > 0:
            p = self._parent(i)
            if self._container[i] < self._container[p]:
                self._container[i], self._container[p] = self._container[p], self._container[i]
                i = p
            else:
                break
    
    def _sift_down(self, i: int) -> None:
        # Push down the element to the right position in the heap
        assert(i >= 0 and i < self._size())

        while self._left_child(i) < self._size():
            lc = self._left_child(i)
            rc = self._right_child(i)
            mc = lc
            
            if rc < self._size() and self._container[rc] < self._container[mc]:
                mc = rc
            if self._container[i] <= self._container[mc]:
                break
            
            self._container[i], self._container[mc] = self._container[mc], self._container[i]
            i = mc

def main():
    heap = MinHeap()
    numbers = [3, 1, 6, 5, 2, 4]
    l = [9, 5, 6, 2, 3]
    
    for n in numbers:
        heap.push(n)
    
    print('Heap after insertions: ', heap._container)
    print('Pop: ', heap.pop())
    print('Heap after pop: ', heap._container)
    
    heap.heapify(l)
    print('Heap after heapify: ', heap._container)

if __name__ == "__main__":
    main()
