#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include "timer.h"  

#define N 6400000  // Fixed number of intervals

sem_t sem; // Semaphore declaration (Global)
double sum = 0.0; // Global sum to accumulate results from all threads
int thread_count; 
double low = 0.0;
double high = 1.0;

// Function to compute part of pi using Simpson's method in a thread
void* compute_pi(void* rank) {
    long thread_id = (long) rank; // Get the thread ID
    double dx = (high - low) / N; 
    double local_N = N / thread_count; 
    double local_low = low + (local_N * thread_id * dx); 
    double local_high = local_low + (local_N * dx); 

    double local_sum = 0.0; 

    // Loop through each subinterval
    for (int i = 0; i <= local_N; i++) {
        double x = local_low + i * dx;
        double fx = 4.0 / (1.0 + x * x);  // f(x) = 4 / (1 + x^2)

        // Simpson's rule coefficients
        if (i == 0 || i == local_N) {  
            local_sum = local_sum + fx; 
        }
        else if (i % 2 == 0) { // Even index multiplied by 2
            local_sum = local_sum + 2 * fx; 
        }
        else { // Odd index multiplied by 4
            local_sum = local_sum + 4 * fx;
        }
    }

    // Protect the critical section with semaphore
    sem_wait(&sem);
    sum += local_sum; 
    sem_post(&sem);

    return NULL;
}

int main(int argc, char *argv[]) {

    double start, finish, elapsed; // Variables for time measurement

    // Ensure the program is called with the correct number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_threads>\n", argv[0]);
        return 1;
    }

    // Get the number of threads from the command-line argument
    thread_count = strtol(argv[1], NULL, 10); 
    if (thread_count <= 0) {
        fprintf(stderr, "Error: number_of_threads must be a positive integer.\n");
        return 1;
    }

    // Allocate memory for thread handles
    pthread_t* thread_handles = malloc(thread_count * sizeof(pthread_t)); 
    sem_init(&sem, 0, 1); // Initialize the semaphore

    GET_TIME(start);  // Start the timer

    // Reset the global sum before starting computation
    sum = 0.0;

    // Create threads
    for (long thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, compute_pi, (void*)thread);
    }

    // Join threads
    for (int thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    GET_TIME(finish);  // Stop the timer

    sum = sum * (1.0 / 3.0) * (high - low) / N; // Final calculation for Simpson's rule

    elapsed = finish - start; // Calculate elapsed time
    double exact_pi = M_PI; 
    double compError = fabs(exact_pi - sum); // Calculate computation error

    // Print the results
    printf("Results with %d threads:\n", thread_count);
    printf("Computation error: %.16f\n", compError);
    printf("Elapsed time: %.6f seconds\n", elapsed);

    // Clean up
    sem_destroy(&sem); // Destroy the semaphore
    free(thread_handles); // Free allocated memory

    return 0;
}
