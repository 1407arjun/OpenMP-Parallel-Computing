# Ackermann Function

### Question

The Ackermann function is a classic example of a recursive function, as it grows very quickly in value, as does the size of its call tree. Develop an OpenMP program to implement the same using tasks. [Solution File](./solution.c)

### Solution (C)

```C
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
```
