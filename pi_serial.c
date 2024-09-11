#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double calcSimp(int n) {
    double a = 0.0; // lower limit 
    double b = 1.0; // Upper limit 
    double y = (b -a) / n;  // Width of interval 
    double total = 0.0; 

    // Loop through each subinterval 
    for (int i = 0; i <= n; i++ ) {
        double x = i * y;  
        double fx = 4.0 / (1.0 + x * x);  // f(x) = 4/(1+x^2)

        // Is current index at endpoint?
        if (i == 0 || i == n) {  
            total = total + fx; 
        }
        else if (i % 2 == 0) { // Even index multiplied by 2
            total = total + (2 * fx); 
        }
        else { // Odd index multiplied by 4
            total = total + (4 * fx); 
        }
    }
    return total * y / 3.0;  // Estimation of integral 
}


int main(int argc, char *argv[]) {

    // Error: Incorrect arugment 
    if (argc != 2) {  
        fprintf(stderr, "Incorrect Usage. Run as ./pi_serial <number>\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]); // atoi will return 0 if n isn't a number

    // Error: Not a valid number 
    if (n == 0) {
        fprintf(stderr, "The entered argument is not a valid number.\n");
        exit(EXIT_FAILURE);
    }

    // Error: Entered arguement is not within 1-10 
    if (n <= 0 || n > 10) {
        fprintf(stderr, "The entered argument is not valid, please enter a number 1-10.\n");
        exit(EXIT_FAILURE);
    }

    // Loop to determine the number of intervals 
    int N = 1;
    for (int i = 0; i < n; i++) {
        N = N * 10;  
    }

    double estimatePi = calcSimp(N);  
    double exactPi = M_PI;  
    double compError = fabs(exactPi - estimatePi);  // Find computation error

    // Print results
    printf("Number of intervals: 10^%d = %d\n", n, N);
    printf("Computation Error: %.16f\n", compError);
    return 0;
}

