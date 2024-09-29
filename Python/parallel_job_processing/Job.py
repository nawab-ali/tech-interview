import Thread

class Job:
    """ This class models jobs that will be processed in parallel """

    def __init__(self, process_time):
        self.thread = Thread.Thread()
        self.start_time = 0L
        self.finish_time = 0L
        self.process_time = process_time

    def get_finish_time(self):
        self.finish_time = self.start_time + self.process_time
        return self.finish_time

    def info(self):
        return [self.start_time, self.finish_time, self.process_time]
