#include <stdio.h>
#include <omp.h>

int ackermannFunction(int, int);

int main() {
    int m, n;

    printf("Ackermann Function\n");

    printf("\nEnter m and n: ");
    scanf("%d%d", &m, &n);

    #pragma omp parallel 
    {
        #pragma omp single
        printf("A(%d, %d) = %d\n", m, n, ackermannFunction(m, n));
    }

    return 0;
}

int ackermannFunction(int m, int n) {
    int ans;

    if (m == 0) {
        ans = n + 1;
    } else if (m > 0 && n == 0) {
        #pragma omp task
        ans = ackermannFunction(m - 1, 1);
    } else if (m > 0 && n > 0) {
        int shared;
        #pragma omp task shared(shared)
        shared = ackermannFunction(m, n - 1);

        #pragma omp task
        ans = ackermannFunction(m - 1, shared);
    }

    #pragma omp taskwait
    return ans;
}
