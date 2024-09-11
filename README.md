# Pi Calculation Using Simpson's Method 

## Overview
This project calculates the value of Pi using **Simpson's Rule**, a numerical method for approximating integrals. The goal is to compare the performance of serial and parallel implementations of Simpson's Method. The parallel version demonstrates the use of **mutexes** and **semaphores** for thread synchronization, highlighting the advantages of multithreading in improving computation time.

## Project Goals
The objective of this project is to explore numerical integration methods and their performance in a parallel computing environment. By developing both serial and parallel versions of Simpson's Method, the project showcases the impact of thread synchronization on performance. 

## Core Concepts Used
* **Simpson's Rule**: A numerical method that approximates the integral of a function by fitting parabolas to segments of the curve.
* **POSIX Threads**: A standard threading API used for creating and managing threads.
* **Mutexes**: A synchronization mechanism used to prevent race conditions in parallel programming.
* **Semaphores**: Another synchronization mechanism that controls access to shared resources in a concurrent system.
* **Performance Benchmarking**: The project includes a timing utility (`timer.h`) to compare the execution times of the serial and parallel versions.

## Getting Started
To get this project running on your local machine, follow the steps below.

### Installing Dependencies
Before we begin, you will need to have GCC installed on your machine. You can install it using the package manager for your operating system.

#### On Ubuntu:
```
sudo apt update
sudo apt install build-essential
```

This project also requires the POSIX Threads library, which should come pre-installed on most Unix-based systems.

## Downloading the FIles 
You will need to download the following files: 
*pi_serial.c
*pi_mutex.c
*pi_semaphore.c
*timer.h
*makefile

## Final Steps 
Once the files are downloaded, compile the project using the provided makefile. Open a terminal in the project directory and run 
```
make
```
This will compile both the serial and parallel versions of the Pi calculation program. 

## Usage
Once compiled, you can run the programs as follows:

For the serial version:
```
./pi_serial [intervals]
```

For the parallel version using mutexes:
```
./pi_mutex [intervals] [threads]
```

For the parallel version using semaphores:

```
./pi_semaphore [intervals] [threads]
```

Example:
```
./pi_serial 1000000
./pi_mutex 1000000 4
./pi_semaphore 1000000 4
```

Note: Higher values for intervals will result in more precise approximations of Pi, but will also take longer to compute.

## Performance 
You can compare the execution times of the serial and parallel versions using the timing utility provided in timer.h. The parallel versions are designed to improve performance with multithreading, especially when a large number of intervals are used.

## Reference and Sources
Simpson's Method for numerical integration 
POSIX Threads library for parallel programming 

## License 
This project is licensed under the MIT license.


