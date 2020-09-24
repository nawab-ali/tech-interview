import heapq
import Thread

class ThreadPool:
    """ This class models a thread pool to manage all the parallel threads """

    def __init__(self, num_threads):
        assert(num_threads > 0)
        self.thread_pool = []
        self.num_threads = num_threads

        # Create threads and add to the thread pool
        for i in range(num_threads):
            thread = Thread.Thread(i)
            self.add_thread(thread)

    def add_thread(self, thread):
        heapq.heappush(self.thread_pool, thread)

    def remove_thread(self):
        return heapq.heappop(self.thread_pool)

    def process_jobs(self, job_queue):
        for i in range(len(job_queue)):
            job = job_queue[i]
            thread = self.remove_thread()
            job.start_time = thread.next_free_time
            thread.next_free_time = job.get_finish_time()
            job.thread = thread
            self.add_thread(thread)

        return job_queue

    def info(self):
        return self.thread_pool
