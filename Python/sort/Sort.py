import Heap
import random

def heapsort(x):
    """ Sort list x using Heap Sort. x remains unchanged """

    h = Heap.Heap()
    y = x[:]
    h.heapify(y)

    return [h.pop() for i in range(h.size())]
