class Heap:
    """ This class implements the min Heap data structure """

    def __init__(self):
        self._container = []

    def push(self, e):
        """ Push element e on the heap """

        # Add the element to the end of the list and sift up to maintain the
        # heap invariant.
        self._container.append(e)
        self._sift_up(self.size()-1)

    def pop(self):
        """ Remove the smallest element from the heap """

        assert(self.size() > 0)

        # The first element in the list is the smallest element. We store its
        # value in a variable. We move the rightmost element to the first
        # position and sift down to maintain the heap invariant.
        retval = self._container[0]
        self._container[0] = self._container[self.size()-1]
        self._container.pop()
        self._sift_down(0)

        return retval

    def heapify(self, x):
        """ Convert the list into a heap in place in linear time """

        self._container = x
        i = self.size() // 2

        while i >= 0:
            self._sift_down(i)
            i = i - 1

    def nlargest(self):
        pass

    def nsmallest(self, n):
        """ Return the n smallest elements from the list """

        assert(n >= 0 and n <= self.size())
        return [self.pop() for i in range(n)]

    def size(self):
        """ Number of elements in the heap """

        return len(self._container)

    def _parent(self, i):
        """ Parent of node i in the complete binary tree """

        assert(i >= 0 and i < self.size())
        index = (i - 1) // 2
        assert(index >= 0 and index < self.size())

        return index

    def _left_child(self, i):
        """ Left child of node i in the complete binary tree """

        assert(i >= 0 and i < self.size())
        return 2*i + 1

    def _right_child(self, i):
        """ Right child of node i in the complete binary tree """

        assert(i >= 0 and i < self.size())
        return 2*i + 2

    def _sift_up(self, i):
        """ Bubble up the element to the right position in the heap """

        assert(i >= 0 and i < self.size())

        while i > 0:
            parent = self._parent(i)
            assert(parent >= 0 and parent < self.size())
            if self._container[i] < self._container[parent]:
                self._swap(i, parent)
            i = parent

    def _sift_down(self, i):
        """ Push down the element to the right place in the heap """

        if self.size() == 0:
            return

        assert(i >= 0 and i < self.size())

        while self._left_child(i) < self.size():
            mc = self._min_child(i)
            assert(mc >= 0 and mc < self.size())
            if self._container[i] > self._container[mc]:
                self._swap(i, mc)
            i = mc

    def _swap(self, i, j):
        """ Swap the elements i, j in the list """

        assert(i >= 0 and i < self.size())
        assert(j >= 0 and j < self.size())

        self._container[i], self._container[j] = self._container[j], self._container[i]

    def _min_child(self, i):
        """ Find the child of i with the minimum value """

        assert(i >= 0 and i < self.size())

        lc = self._left_child(i)
        rc = self._right_child(i)

        if rc >= self.size():
            return lc

        assert(lc >= 0 and lc < self.size())
        assert(rc >= 0 and rc < self.size())

        # Find the child with the min value
        minc = lc if self._container[lc] < self._container[rc] else rc

        return minc
