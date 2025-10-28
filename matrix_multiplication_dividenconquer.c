#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Add and subtract helper functions
void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiplyDC(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) { C[0][0] = A[0][0] * B[0][0]; return; }

    int mid = n/2;
    int A11[mid][mid], A12[mid][mid], A21[mid][mid], A22[mid][mid];
    int B11[mid][mid], B12[mid][mid], B21[mid][mid], B22[mid][mid];
    int C11[mid][mid], C12[mid][mid], C21[mid][mid], C22[mid][mid];
    int temp1[mid][mid], temp2[mid][mid];

    for(int i=0;i<mid;i++)
        for(int j=0;j<mid;j++){
            A11[i][j]=A[i][j]; A12[i][j]=A[i][j+mid];
            A21[i][j]=A[i+mid][j]; A22[i][j]=A[i+mid][j+mid];
            B11[i][j]=B[i][j]; B12[i][j]=B[i][j+mid];
            B21[i][j]=B[i+mid][j]; B22[i][j]=B[i+mid][j+mid];
        }

    multiplyDC(mid,A11,B11,temp1); multiplyDC(mid,A12,B21,temp2); add(mid,temp1,temp2,C11);
    multiplyDC(mid,A11,B12,temp1); multiplyDC(mid,A12,B22,temp2); add(mid,temp1,temp2,C12);
    multiplyDC(mid,A21,B11,temp1); multiplyDC(mid,A22,B21,temp2); add(mid,temp1,temp2,C21);
    multiplyDC(mid,A21,B12,temp1); multiplyDC(mid,A22,B22,temp2); add(mid,temp1,temp2,C22);

    for(int i=0;i<mid;i++)
        for(int j=0;j<mid;j++){
            C[i][j]=C11[i][j]; C[i][j+mid]=C12[i][j];
            C[i+mid][j]=C21[i][j]; C[i+mid][j+mid]=C22[i][j];
        }
}

int main() {
    int sizes[] = {16, 32, 64, 128, 256}; // must be powers of 2
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(NULL));

    for(int s=0; s<numSizes; s++){
        int n = sizes[s];

        int (*A)[n] = malloc(sizeof(int[n][n]));
        int (*B)[n] = malloc(sizeof(int[n][n]));
        int (*C)[n] = malloc(sizeof(int[n][n]));

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                A[i][j] = rand()%10;
                B[i][j] = rand()%10;
            }

        clock_t start = clock();
        multiplyDC(n,A,B,C);
        clock_t end = clock();

        printf("Divide & Conquer %d x %d: %.6f seconds\n", n, n, ((double)(end-start))/CLOCKS_PER_SEC);

        free(A); free(B); free(C);
    }

    return 0;
}
