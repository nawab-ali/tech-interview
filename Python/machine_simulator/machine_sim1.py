# Here’s a sample practice challenge that mimics the Anthropic-style take-home test.
# This simplified version includes a Python-based simulator for a hypothetical parallel
# machine and an example function to optimize.
#
# Overview
# This practice task involves:
# 1. A simplified simulator for a custom machine with parallelism capabilities.
# 2. A sample_function that you need to optimize for performance.
# 3. Opportunities to make optimizations both in “assembly-like” operations and through higher-level
#    transformations.
#
# Instructions
# 1. Setup: Download the code and run it on your computer.
# 2. Goal: Optimize the runtime of sample_function on this simulated machine by making any transformations you
#    find beneficial.
# 3. Debugging: Use the provided trace output to analyze and debug your optimizations.
# 4. Submission: Once optimized, record the runtime and describe your approach and reasoning.

import time
import numpy as np
from multiprocessing import Pool, shared_memory

class MachineSimulator:
    def __init__(self, max_workers=4, memory_size=100000):
        self.max_workers = max_workers
        self.memory_size = memory_size

        # Initialize shared memory for the memory array
        self.shm = shared_memory.SharedMemory(create=True, size=memory_size * np.int32().nbytes)
        self.memory = np.ndarray((memory_size,), dtype=np.int32, buffer=self.shm.buf)
        self.memory[:] = 0
    
    def load_memory(self, data):
        """Load data into the machine's memory."""
        self.memory[:len(data)] = data
    
    def execute(self, instructions):
        """Simulate executing a series of instructions with parallelism."""
        start = time.time()

        # Split the instructions into chunks based on the number of workers
        chunks = [chunk.tolist() for chunk in np.array_split(instructions, self.max_workers)]

        with Pool(self.max_workers) as pool:
            # Pass shared memory name and instruction chunks to child processes
            pool.starmap(self._execute_chunk, [(chunk, self.shm.name, self.memory_size) for chunk in chunks])
        
        end = time.time()
        return end - start
    
    @staticmethod
    def _execute_chunk(chunk, shm_name, memory_size):
        """Process a chunk of instructions using shared memory."""
        existing_shm = shared_memory.SharedMemory(name=shm_name)
        memory = np.ndarray((memory_size,), dtype=np.int32, buffer=existing_shm.buf)

        for instr in chunk:
            # Ensure instr is a tuple and the expected length
            if not isinstance(instr, (tuple, list)) or len(instr) != 3:
                raise ValueError(f"Unexpected instruction format: {instr}")
            
            op, addr, val = instr
            addr = int(addr)  # Ensure addr is explicitly cast to integer
            val = int(val)    # Explicitly cast val to integer to prevent type mismatch

            # Debugging print to track addresses
            print(f"Executing instruction: {op}, Address: {addr}, Value: {val}")

            # Validate address
            if not isinstance(addr, int) or not (0 <= addr < memory_size):
                raise IndexError(f"Invalid memory address: {addr}")
            
            if op == 'add':
                memory[addr] += val
            elif op == 'mul':
                memory[addr] *= val
            elif op == 'div':
                memory[addr] /= (val + 1e-8)
            # Add more operations here as needed for optimization
        
        # Close the shared memory in this process
        existing_shm.close()

    def trace(self):
        """Print a simple trace for debugging."""
        print("Memory:", self.memory[:10])

    def cleanup(self):
        """Clean up shared memory."""
        self.shm.close()
        self.shm.unlink()

if __name__ == "__main__":
    data = np.random.randint(1, 100, 100000)

    simulator = MachineSimulator()
    simulator.load_memory(data)
    
    # Sample sequence of instructions (can be optimized)
    instructions = [('add', i, 5) for i in range(10000)] + \
                   [('mul', i, 2) for i in range(10000, 20000)] + \
                   [('div', i, 3) for i in range(20000, 30000)]
    
    runtime = simulator.execute(instructions)
    print("Initial runtime:", runtime, "seconds")
    simulator.trace()
    simulator.cleanup()
