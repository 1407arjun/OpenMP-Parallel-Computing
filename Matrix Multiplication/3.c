#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 100

int main() {
    double start, end;
    double a[N][N], b[N][N], c[N][N];

    printf("20BCE2955 Arjun Sivaraman\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
            c[i][j] = 0;
        }
    }

    // In serial
    start = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    end = omp_get_wtime();

    printf("\nTime taken in serial: %f\n", end - start);

    // In parallel
    start = omp_get_wtime();
    #pragma omp parallel for collapse(3)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    end = omp_get_wtime();

    printf("\nTime taken in parallel: %f\n", end - start);

    return 0;
}
