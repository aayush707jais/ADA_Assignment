#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to merge two subarrays
void merge(int arr[], int left, int mid, int right) {
   int n1 = mid - left + 1;
   int n2 = right - mid;

   // Temporary arrays
   int L[n1], R[n2];

   // Copy data into temp arrays
   for (int i = 0; i < n1; i++)
       L[i] = arr[left + i];
   for (int j = 0; j < n2; j++)
       R[j] = arr[mid + 1 + j];

   // Merge the temp arrays back into arr[]
   int i = 0, j = 0, k = left;
   while (i < n1 && j < n2) {
       if (L[i] <= R[j]) {
           arr[k] = L[i];
           i++;
       } else {
           arr[k] = R[j];
           j++;
       }
       k++;
   }

   // Copy remaining elements (if any)
   while (i < n1) {
       arr[k] = L[i];
       i++; k++;
   }
   while (j < n2) {
       arr[k] = R[j];
       j++; k++;
   }
}

// Recursive Merge Sort
void mergeSort(int arr[], int left, int right) {
   if (left < right) {
       int mid = left + (right - left) / 2;

       // Sort first and second halves
       mergeSort(arr, left, mid);
       mergeSort(arr, mid + 1, right);

       // Merge the sorted halves
       merge(arr, left, mid, right);
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
     mergeSort(arr,0,n);
     end = clock();
     cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC*1000;
     printf("Time taken for %d elements: %f ms\n", n, cpu_time_used);
     free(arr);
 }
 return 0;
}
