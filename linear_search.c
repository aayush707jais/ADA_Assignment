#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
        return i;
    }
    return -1;
}

int main() {
    int sizes[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int runs = 5000; // repeat to average
    srand(time(NULL));
    printf("n,LinearSearchTime\n");
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed for n = %d\n", n);
            continue;
        }
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
        // Worst-case: last element
        int key = arr[n - 1];
        int result;
        clock_t start, end;
        double total_time = 0;
        for (int r = 0; r < runs; r++) {
            start = clock();
            result = linearSearch(arr, n, key);
            end = clock();
            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        double avg_time = total_time / runs;
        printf("Number of elements:%d\n,Time taken %f\n", n, avg_time);
        free(arr);
    }
    return 0;
}
