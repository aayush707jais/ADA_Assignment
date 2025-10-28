#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void multiply_matrices(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int sizes[] = {100, 200, 300, 400, 500, 600 , 700 };  // Matrix sizes to test
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time( NULL));

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        printf("\nMatrix size: %d x %d\n", n, n);

        int (*A)[n] = malloc(sizeof(int[n][n]));
        int (*B)[n] = malloc(sizeof(int[n][n]));
        
      int (*C)[n] = malloc(sizeof(int[n][n]));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }

        clock_t start = clock();
        multiply_matrices(n, A, B, C);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Execution time: %.6f seconds\n", time_taken);

        // Free memory
        free(A);
        free(B);
        
free(C);
   
 }
   
 return 0;

}