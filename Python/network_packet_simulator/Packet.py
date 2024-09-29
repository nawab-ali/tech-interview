class Packet:
    """ This class represents the network packets that will be simulated. """

    def __init__(self, arrival_time, process_time):
        self.arrival_time = arrival_time
        self.process_time = process_time
        self.start_time = 0
        self.finish_time = 0
        self.dropped = False

    def get_finish_time(self):
        self.finish_time = self.start_time + self.process_time
        return self.finish_time

    def drop(self):
        self.dropped = True

    def is_dropped(self):
        return self.dropped

    def print_info(self):
        print(self.arrival_time, self.process_time, self.start_time,
              self.finish_time, self.dropped)
