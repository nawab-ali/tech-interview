class Thread:
    """ This class models the thread that executes the jobs """

    def __init__(self, thread_id = 0L):
        self.thread_id = thread_id
        self.next_free_time = 0L

    def __cmp__(self, thread):
        if self.next_free_time == thread.next_free_time:
            return cmp(self.thread_id, thread.thread_id)
        else:
            return cmp(self.next_free_time, thread.next_free_time)

    def info(self):
        return [self.thread_id, self.next_free_time]
