# Multi-Threaded Programming: Pthread

In a Unix/Linux operating system, the C/C++ languages provide the POSIX thread(pthread) standard API(Application program Interface) for all thread related functions. It allows us to create multiple threads for concurrent process flow. It is most effective on multiprocessor or multi-core systems where threads can be implemented on a kernel level for achieving the speed of execution. Gains can also be found in uni-processor systems by exploiting the latency in IO or other system functions that may halt a process.

This project has two other branches that implement a parallel book recommender in two modes, using one file and using multi-file as input. 
