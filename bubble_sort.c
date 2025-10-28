#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n) {
   for (int i = 0; i < n-1; i++) {
       for (int j = 0; j < n-i-1; j++) {
           if (arr[j] > arr[j+1]) {
               // swap
               int temp = arr[j];
               arr[j] = arr[j+1];
               arr[j+1] = temp;
           }
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
 
     for (i = 0; i < n; i++) {
         arr[i] = rand() % 10000;
     }
     start = clock();
     bubbleSort(arr, n);
     end = clock();
     cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC*1000;
     printf("Time taken for %d elements: %f ms\n", n, cpu_time_used);
     free(arr);
 }
 return 0;
}