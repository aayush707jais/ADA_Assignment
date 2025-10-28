#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long fib_array[100]; 

long long fib(int n) {
    if (n <= 1)
        return n;
    if (fib_array[n] != 0)
        return fib_array[n];

    fib_array[n] = fib(n - 1) + fib(n - 2);
    return fib_array[n];
}

int main() {
    int terms;
    clock_t start, end;
    double cpu_time_used;
    for (int i = 0; i < 100; i++) 
        fib_array[i] = 0;

    printf("Enter the number of terms: ");
    scanf("%d", &terms);
    start = clock();

    printf("Fibonacci Series: ");
    for (int i = 0; i < terms; i++)
        printf("%lld ", fib(i));

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", cpu_time_used);
    return 0;
}