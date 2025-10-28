#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Fib(int n) {
    if (n <= 1) 
        return n;

    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter the value of n: ");
    scanf("%d", &n);
    start = clock();

    printf("Fibonacci Series: ");
    for (int i = 0; i < n; i++)
        printf("%d ", Fib(i));

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", cpu_time_used);
    return 0;
}