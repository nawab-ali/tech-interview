import Job
import Thread
import ThreadPool

def read_input(filename):
    """ Read the thread and jobs information from file """

    line_num = 0
    num_jobs = 0L
    num_threads = 0L
    process_times = []

    with open(filename, 'r') as file:
        for line in file:
            if line_num == 0:
                num_threads, num_jobs = (int(i) for i in line.split())
            elif line_num == 1:
                process_times = [int(i) for i in line.split()]
            line_num += 1

    assert(line_num == 2)
    assert(len(process_times) == num_jobs)
    return num_threads, num_jobs, process_times

def process_jobs(num_threads, job_queue):
    """ Process the jobs in parallel """

    # Create the thread pool
    tp = ThreadPool.ThreadPool(num_threads)

    # Process the jobs
    job_queue = tp.process_jobs(job_queue)

    for i in range(len(job_queue)):
        job = job_queue[i]
        print(job.thread.thread_id, job.start_time)

def main():
    job_queue = []

    # Read the threads and jobs information from file
    num_threads, num_jobs, process_times = read_input('testcases.txt')

    # Create jobs from process times
    for i in range(num_jobs):
        job = Job.Job(process_times[i])
        job_queue.append(job)

    # Process the jobs in parallel
    process_jobs(num_threads, job_queue)

if (__name__ == '__main__'):
    main()
