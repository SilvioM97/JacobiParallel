# JacobiParallel
A sequential and parallel (standard threads and FastFlow) implementation of the Jacobi method.  
The Jacobi method is an iterative algorithm for determining the solution of a square and strictly diagonally dominant system of linear equations).

## How to compile
`g++ -std=c++20 -O3 -pthread jacobi_main.cpp -o jacobi_main`

## How to run the code
No initial input needed, everything will be asked after the execution command: `./jacobi_main`

## What the code does
It will ask to you to insert the dimension of the space, the desired number of threads and the number of iterations of the Jacobi method.  
Taken these inputs, it generates a (strictly diagonally dominant) matrix and a vector (known term vector) and it solves the system in the following ways:  
- Sequential  
- Parallel version 1 (standard threads)  
- Parallel version 1 with 1 thread (in order to compute the scalability)  
- Parallel version 2 (FastFlow)  
- Parallel version 2 with 1 thread (in order to compute the scalability)  

## The output
The code will print the service time of each execution (in microseconds) and three measures for each of the two parallel versions:  
- Speedup  
- Efficiency  
- Scalability  
