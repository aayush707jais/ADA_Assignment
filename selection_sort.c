#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n) {
   int i, j, minIndex, temp;
   for (i = 0; i < n-1; i++) {
       minIndex = i;
     for (j = i+1; j < n; j++) {
           if (arr[j] < arr[minIndex]) {
               minIndex = j;
           }
       }
       // Swap if needed
       if (minIndex != i) {
           temp = arr[i];
           arr[i] = arr[minIndex];
           arr[minIndex] = temp;
       }
   }
}

int main() {
   int sizes[] = {500, 1000, 1500, 2000,2500,3000,3500};
   int numTests = 7;
   int n, i;
   clock_t start, end;
   double cpu_time_used;
   srand(time(0));
   for (int t = 0; t < numTests; t++) {
       n = sizes[t];
       int *arr = (int*)malloc(n * sizeof(int));
       // Generate random array
       for (i = 0; i < n; i++) {
           arr[i] = rand() % 10000;
       }

       // Measure sorting time
       start = clock();
       selectionSort(arr, n);
       end = clock();
       cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC*1000;
       printf("Time taken for %d elements: %f ms\n", n, cpu_time_used);
       free(arr);
   }
   return 0;
}
