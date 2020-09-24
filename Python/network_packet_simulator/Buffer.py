import Packet

class Buffer:
    """ This class models the network buffer. """

    def __init__(self, size):
        self.size = size
        self.queue = []

    def is_full(self):
        return len(self.queue) == self.size

    def is_empty(self):
        return len(self.queue) == 0

    def append(self, packet):
        if not self.is_full():
            self.queue.append(packet)
            return True
        else:
            return False

    def pop(self):
        if not self.is_empty():
            return self.queue.pop(0)
        else:
            return None

    def num_elements(self):
        return len(self.queue)

    def get_packet(self, i):
        assert(i >= 0 and i < self.num_elements())
        return self.queue[i]
