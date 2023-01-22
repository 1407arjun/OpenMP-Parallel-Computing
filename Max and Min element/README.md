# Max and Min element

### Question

Develop an OpenMP program to find the occurrence of minimum and maximum element in the randomly generated list. These operations have to be performed in different sections and print the time taken by both the sections. [Solution File](./solution.c)

### Solution (C)

```C
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main() {
    int min, max, arr[N];
    double start, end;
    srand(time(0));

    printf("Max and Min element\n");

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
```
