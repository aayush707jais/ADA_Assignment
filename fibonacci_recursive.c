#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fibrecursion(int n) {
    if(n<=1)
        return n;
    return fibrecursion(n-1)+fibrecursion(n-2);
}

int main() {
    int terms;
    clock_t start, end;
    double cpu_time_used;
    printf("Enter the number of terms: ");
    scanf("%d", &terms);

    start = clock();

    for (int i = 0; i < terms; i++)
        printf("%d ", fibrecursion(i));

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nTime taken: %f seconds\n", cpu_time_used);
    return 0;
}