#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main() {
    int min, max, arr[N];
    double start, end; 
    srand(time(0));

    printf("20BCE2955 Arjun Sivaraman\n");
    
    for (int i = 0; i < N; i++) {
        arr[i] = rand() + 1;
    }

    // Min element
    start = omp_get_wtime();
    min = arr[0];
    #pragma omp parallel for reduction(min\
    :min)
    for (int i = 1; i < N; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    end = omp_get_wtime();

    printf("\nMinimum element: %d", min);
    printf("\nTime taken: %f\n", end - start);

    // Max element
    start = omp_get_wtime();
    max = arr[0];
    #pragma omp parallel for reduction(max \
                                   : max)
    for (int i = 1; i < N; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    end = omp_get_wtime();
    
    printf("\nMaximum element: %d", max);
    printf("\nTime taken: %f\n", end - start);

    return 0;
}
