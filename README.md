# JacobiParallel
A sequential and parallel (standard threads and FastFlow) implementation of the Jacobi method.  
The Jacobi method is an iterative algorithm for determining the solution of a square and strictly diagonally dominant system of linear equations.

## Table of contents[![](./docs/img/pin.svg)](#table-of-contents)
1. [How to compile](#compiling)
2. [How to run the code](#execution)
3. [What the code does](#functioning)
4. [The output](#output)
5. [The code](#code)

## Compiling
`g++ -std=c++20 -O3 -pthread jacobi_main.cpp -o jacobi_main`

## Execution
No initial input needed, everything will be prompted after the run command: `./jacobi_main`

## Functioning
The program will ask you to insert the dimension of the space, the desired number of threads and the number of iterations of the Jacobi method.  
Taken these inputs, it generates a (strictly diagonally dominant) matrix and a vector (known term vector) and it solves the system in the following ways:  
- Sequential  
- Parallel version 1 (standard threads)  
- Parallel version 1 with 1 thread (in order to compute the scalability)  
- Parallel version 2 (FastFlow)  
- Parallel version 2 with 1 thread (in order to compute the scalability)  

## Output
The code will print the service time of each execution (in microseconds) and three measures for each of the two parallel versions:  
- Speedup  
- Efficiency  
- Scalability  

## Code
The code is divided into 5 files:  
- `jacobi_main.cpp`: the main
- `jacobi.h`: the file which contains the three Jacobi method algorithms (sequential, standard threads, FastFlow)
- `libr.h`: useful functions
- `measures.h`: functions which compute the measures (speedup, efficiency, scalability)
- `utimer.cpp`: definition of the timer class provided by Professor Danelutto
