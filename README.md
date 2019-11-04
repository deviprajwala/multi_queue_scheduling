# multi_queue_scheduling

The main objective of the program is to schedule the process in an effecient way.Here we are considering two factors in scheduling process that 
is priority and execution time.

In this program we maintain 3 queues for the execution of the processes,each with different quantum.In this program the first queue is of 8 
quantum,second one is of 16 quantum and third one is of more than 16 quantum.

We calculate a 'value' which is the average of time and priority for each of the process.At the time of execution of the processes in the 
queue ,we sort the 'value' of each process in ascending order and execute the processes in the queue.This procedure is repeated for each of the queue.
