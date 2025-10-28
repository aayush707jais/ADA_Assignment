#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Add/subtract helper
void add(int n,int A[n][n],int B[n][n],int C[n][n]){
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) C[i][j]=A[i][j]+B[i][j];
}
void sub(int n,int A[n][n],int B[n][n],int C[n][n]){
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) C[i][j]=A[i][j]-B[i][j];
}

// Strassen multiplication for power-of-2 matrices
void multiplyStrassen(int n,int A[n][n],int B[n][n],int C[n][n]){
    if(n==1){ C[0][0]=A[0][0]*B[0][0]; return; }

    int mid=n/2;
    int A11[mid][mid],A12[mid][mid],A21[mid][mid],A22[mid][mid];
    int B11[mid][mid],B12[mid][mid],B21[mid][mid],B22[mid][mid];
    int C11[mid][mid],C12[mid][mid],C21[mid][mid],C22[mid][mid];
    int M1[mid][mid],M2[mid][mid],M3[mid][mid],M4[mid][mid],M5[mid][mid],M6[mid][mid],M7[mid][mid];
    int T1[mid][mid],T2[mid][mid];

    for(int i=0;i<mid;i++)
        for(int j=0;j<mid;j++){
            A11[i][j]=A[i][j]; A12[i][j]=A[i][j+mid];
            A21[i][j]=A[i+mid][j]; A22[i][j]=A[i+mid][j+mid];
            B11[i][j]=B[i][j]; B12[i][j]=B[i][j+mid];
            B21[i][j]=B[i+mid][j]; B22[i][j]=B[i+mid][j+mid];
        }

    add(mid,A11,A22,T1); add(mid,B11,B22,T2); multiplyStrassen(mid,T1,T2,M1);
    add(mid,A21,A22,T1); multiplyStrassen(mid,T1,B11,M2);
    sub(mid,B12,B22,T1); multiplyStrassen(mid,A11,T1,M3);
    sub(mid,B21,B11,T1); multiplyStrassen(mid,A22,T1,M4);
    add(mid,A11,A12,T1); multiplyStrassen(mid,T1,B22,M5);
    sub(mid,A21,A11,T1); add(mid,B11,B12,T2); multiplyStrassen(mid,T1,T2,M6);
    sub(mid,A12,A22,T1); add(mid,B21,B22,T2); multiplyStrassen(mid,T1,T2,M7);

    add(mid,M1,M4,T1); sub(mid,T1,M5,T2); add(mid,T2,M7,C11);
    add(mid,M3,M5,C12); add(mid,M2,M4,C21);
    sub(mid,M1,M2,T1); add(mid,T1,M3,T2); add(mid,T2,M6,C22);

    for(int i=0;i<mid;i++)
        for(int j=0;j<mid;j++){
            C[i][j]=C11[i][j]; C[i][j+mid]=C12[i][j];
            C[i+mid][j]=C21[i][j]; C[i+mid][j+mid]=C22[i][j];
        }
}

// Helper to get next power of 2
int nextPowerOf2(int n){
    int power=1;
    while(power<n) power*=2;
    return power;
}

int main(){
    int sizes[] = {16,32,64,128,256};
    int numSizes = sizeof(sizes)/sizeof(sizes[0]);

    srand(time(NULL));

    for(int s=0;s<numSizes;s++){
        int n = sizes[s];
        int N = nextPowerOf2(n); // padded size

        // Allocate padded matrices
        int (*A)[N] = calloc(N*N, sizeof(int));
        int (*B)[N] = calloc(N*N, sizeof(int));
        int (*C)[N] = calloc(N*N, sizeof(int));

        // Initialize random values in the top-left n x n block
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                A[i][j]=rand()%10;
                B[i][j]=rand()%10;
            }

        clock_t start=clock();
        multiplyStrassen(N,A,B,C);
        clock_t end=clock();

        printf("Strassen %d x %d: %.6f seconds\n",n,n,((double)(end-start))/CLOCKS_PER_SEC);

        free(A); free(B); free(C);
    }

    return 0;
}
