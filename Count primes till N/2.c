#include <stdio.h>
#include <omp.h>
#include <time.h>

int isPrime(int);

int main() {
    int n, count = 0;
    double start, end;

    printf("20BCE2955 Arjun Sivaraman\n");

    printf("\nEnter N: ");
    scanf("%d", &n);

    start = omp_get_wtime();
    #pragma omp parallel for reduction(+\
    :count)
    for (int i = 2; i <= n; i++) {
        if (isPrime(i)) {
            count++;
        }
    }
    end = omp_get_wtime();

    printf("\nNo. of primes between 1 and %d: %d\n", n, count);
    printf("\nTime taken: %f\n", end - start);

    return 0;
}

int isPrime(int num) {
    if (num < 2) {
        return 0;
    }

    for (int i = 2; i <= num/2; i++) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}
