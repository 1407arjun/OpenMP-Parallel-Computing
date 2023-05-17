# Private Clauses

### Question

Develop an OpenMP code to describe the use of threadprivate directive, lastprivate and firstprivate clauses. [Solution File](./solution.c)

### Solution (C)

```C
#include <stdio.h>
#include <omp.h>

int global = 0;
#pragma omp threadprivate(global)

int main() {
    printf("Private Clauses\n\n");
    int private = 0;
    int first = 0;
    int last = 0;

    #pragma omp parallel num_threads(3)
    {
        #pragma omp for private(private) lastprivate(last) firstprivate(first)
        for (int i = 0; i < omp_get_num_threads(); i++) {
            global += 1;
            private += 1;
            last = global;
            first = global;

            printf("Thread %d\nThreadprivate variable value: %d\nPrivate variable: %d\nFirstprivate variable: %d\nLastprivate variable: %d\n\n",
                omp_get_thread_num(), global, private, first, last);
        }
    }

    printf("After parallel region\nThreadprivate variable value: %d\nPrivate variable: %d\nFirstprivate variable: %d\nLastprivate variable: %d\n\n",
                global, private, first, last);
}
```
