#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocate memory for a square matrix
int **createMatrix(int size) {
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }
    return matrix;
}

// Free memory of a matrix
void destroyMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Fill a matrix with random values (0–9)
void fillMatrix(int **matrix, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            matrix[row][col] = rand() % 10;
        }
    }
}

// Add two matrices
void addMatrix(int **matA, int **matB, int **result, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            result[row][col] = matA[row][col] + matB[row][col];
        }
    }
}

// Subtract two matrices
void subtractMatrix(int **matA, int **matB, int **result, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            result[row][col] = matA[row][col] - matB[row][col];
        }
    }
}

// Copy a submatrix from a bigger one
void extractSubMatrix(int **source, int **dest, int startRow, int startCol, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            dest[row][col] = source[row + startRow][col + startCol];
        }
    }
}

// Place a submatrix back into the main matrix
void placeSubMatrix(int **source, int **dest, int startRow, int startCol, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            dest[row + startRow][col + startCol] = source[row][col];
        }
    }
}

// Regular matrix multiplication
void multiplyIterative(int **matA, int **matB, int **result, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            result[row][col] = 0;
            for (int k = 0; k < size; k++) {
                result[row][col] += matA[row][k] * matB[k][col];
            }
        }
    }
}

// Recursive multiplication (divide & conquer)
void multiplyRecursive(int **matA, int **matB, int **result, int size) {
    if (size <= 16) {
        multiplyIterative(matA, matB, result, size);
        return;
    }

    int half = size / 2;

    // Allocate submatrices
    int **A11 = createMatrix(half), **A12 = createMatrix(half);
    int **A21 = createMatrix(half), **A22 = createMatrix(half);
    int **B11 = createMatrix(half), **B12 = createMatrix(half);
    int **B21 = createMatrix(half), **B22 = createMatrix(half);
    int **C11 = createMatrix(half), **C12 = createMatrix(half);
    int **C21 = createMatrix(half), **C22 = createMatrix(half);
    int **temp1 = createMatrix(half), **temp2 = createMatrix(half);

    // Split matrices
    extractSubMatrix(matA, A11, 0, 0, half);
    extractSubMatrix(matA, A12, 0, half, half);
    extractSubMatrix(matA, A21, half, 0, half);
    extractSubMatrix(matA, A22, half, half, half);

    extractSubMatrix(matB, B11, 0, 0, half);
    extractSubMatrix(matB, B12, 0, half, half);
    extractSubMatrix(matB, B21, half, 0, half);
    extractSubMatrix(matB, B22, half, half, half);

    // Compute subproducts
    multiplyRecursive(A11, B11, temp1, half);
    multiplyRecursive(A12, B21, temp2, half);
    addMatrix(temp1, temp2, C11, half);

    multiplyRecursive(A11, B12, temp1, half);
    multiplyRecursive(A12, B22, temp2, half);
    addMatrix(temp1, temp2, C12, half);

    multiplyRecursive(A21, B11, temp1, half);
    multiplyRecursive(A22, B21, temp2, half);
    addMatrix(temp1, temp2, C21, half);

    multiplyRecursive(A21, B12, temp1, half);
    multiplyRecursive(A22, B22, temp2, half);
    addMatrix(temp1, temp2, C22, half);

    // Combine into final result
    placeSubMatrix(C11, result, 0, 0, half);
    placeSubMatrix(C12, result, 0, half, half);
    placeSubMatrix(C21, result, half, 0, half);
    placeSubMatrix(C22, result, half, half, half);

    // Free memory
    destroyMatrix(A11, half); destroyMatrix(A12, half);
    destroyMatrix(A21, half); destroyMatrix(A22, half);
    destroyMatrix(B11, half); destroyMatrix(B12, half);
    destroyMatrix(B21, half); destroyMatrix(B22, half);
    destroyMatrix(C11, half); destroyMatrix(C12, half);
    destroyMatrix(C21, half); destroyMatrix(C22, half);
    destroyMatrix(temp1, half); destroyMatrix(temp2, half);
}

// Strassen's Algorithm
void strassenMultiply(int **matA, int **matB, int **result, int size) {
    if (size <= 16) {
        multiplyIterative(matA, matB, result, size);
        return;
    }

    int half = size / 2;

    // Allocate submatrices
    int **A11 = createMatrix(half), **A12 = createMatrix(half);
    int **A21 = createMatrix(half), **A22 = createMatrix(half);
    int **B11 = createMatrix(half), **B12 = createMatrix(half);
    int **B21 = createMatrix(half), **B22 = createMatrix(half);

    extractSubMatrix(matA, A11, 0, 0, half);
    extractSubMatrix(matA, A12, 0, half, half);
    extractSubMatrix(matA, A21, half, 0, half);
    extractSubMatrix(matA, A22, half, half, half);

    extractSubMatrix(matB, B11, 0, 0, half);
    extractSubMatrix(matB, B12, 0, half, half);
    extractSubMatrix(matB, B21, half, 0, half);
    extractSubMatrix(matB, B22, half, half, half);

    int **P1 = createMatrix(half), **P2 = createMatrix(half);
    int **P3 = createMatrix(half), **P4 = createMatrix(half);
    int **P5 = createMatrix(half), **P6 = createMatrix(half);
    int **P7 = createMatrix(half);
    int **tempA = createMatrix(half), **tempB = createMatrix(half);

    // P1 = (A11 + A22)(B11 + B22)
    addMatrix(A11, A22, tempA, half);
    addMatrix(B11, B22, tempB, half);
    strassenMultiply(tempA, tempB, P1, half);

    // P2 = (A21 + A22)B11
    addMatrix(A21, A22, tempA, half);
    strassenMultiply(tempA, B11, P2, half);

    // P3 = A11(B12 - B22)
    subtractMatrix(B12, B22, tempB, half);
    strassenMultiply(A11, tempB, P3, half);

    // P4 = A22(B21 - B11)
    subtractMatrix(B21, B11, tempB, half);
    strassenMultiply(A22, tempB, P4, half);

    // P5 = (A11 + A12)B22
    addMatrix(A11, A12, tempA, half);
    strassenMultiply(tempA, B22, P5, half);

    // P6 = (A21 - A11)(B11 + B12)
    subtractMatrix(A21, A11, tempA, half);
    addMatrix(B11, B12, tempB, half);
    strassenMultiply(tempA, tempB, P6, half);

    // P7 = (A12 - A22)(B21 + B22)
    subtractMatrix(A12, A22, tempA, half);
    addMatrix(B21, B22, tempB, half);
    strassenMultiply(tempA, tempB, P7, half);

    // C11 = P1 + P4 - P5 + P7
    int **C11 = createMatrix(half), **C12 = createMatrix(half);
    int **C21 = createMatrix(half), **C22 = createMatrix(half);

    addMatrix(P1, P4, tempA, half);
    subtractMatrix(tempA, P5, tempB, half);
    addMatrix(tempB, P7, C11, half);

    // C12 = P3 + P5
    addMatrix(P3, P5, C12, half);

    // C21 = P2 + P4
    addMatrix(P2, P4, C21, half);

    // C22 = P1 - P2 + P3 + P6
    subtractMatrix(P1, P2, tempA, half);
    addMatrix(tempA, P3, tempB, half);
    addMatrix(tempB, P6, C22, half);

    // Combine into final result
    placeSubMatrix(C11, result, 0, 0, half);
    placeSubMatrix(C12, result, 0, half, half);
    placeSubMatrix(C21, result, half, 0, half);
    placeSubMatrix(C22, result, half, half, half);

    // Free memory
    destroyMatrix(A11, half); destroyMatrix(A12, half);
    destroyMatrix(A21, half); destroyMatrix(A22, half);
    destroyMatrix(B11, half); destroyMatrix(B12, half);
    destroyMatrix(B21, half); destroyMatrix(B22, half);
    destroyMatrix(C11, half); destroyMatrix(C12, half);
    destroyMatrix(C21, half); destroyMatrix(C22, half);
    destroyMatrix(P1, half); destroyMatrix(P2, half);
    destroyMatrix(P3, half); destroyMatrix(P4, half);
    destroyMatrix(P5, half); destroyMatrix(P6, half);
    destroyMatrix(P7, half);
    destroyMatrix(tempA, half); destroyMatrix(tempB, half);
}

// Main function
int main() {
    srand(time(NULL));

    printf("Iterative Multiplication Timing\n");
    printf("%-10s %-15s\n", "Size", "Time (sec)");
    for (int n = 2; n <= 256; n *= 2) {
        int **A = createMatrix(n);
        int **B = createMatrix(n);
        int **C = createMatrix(n);

        fillMatrix(A, n);
        fillMatrix(B, n);

        clock_t start = clock();
        multiplyIterative(A, B, C, n);
        clock_t end = clock();

        printf("%-10d %-15f\n", n, (double)(end - start) / CLOCKS_PER_SEC);

        destroyMatrix(A, n);
        destroyMatrix(B, n);
        destroyMatrix(C, n);
    }

    printf("\nStrassen Multiplication Timing\n");
    printf("%-10s %-15s\n", "Size", "Time (sec)");
    for (int n = 2; n <= 256; n *= 2) {
        int **A = createMatrix(n);
        int **B = createMatrix(n);
        int **C = createMatrix(n);

        fillMatrix(A, n);
        fillMatrix(B, n);

        clock_t start = clock();
        strassenMultiply(A, B, C, n);
        clock_t end = clock();

        printf("%-10d %-15f\n", n, (double)(end - start) / CLOCKS_PER_SEC);

        destroyMatrix(A, n);
        destroyMatrix(B, n);
        destroyMatrix(C, n);
    }

    printf("\nRecursive Multiplication Timing\n");
    printf("%-10s %-15s\n", "Size", "Time (sec)");
    for (int n = 2; n <= 256; n *= 2) {
        int **A = createMatrix(n);
        int **B = createMatrix(n);
        int **C = createMatrix(n);

        fillMatrix(A, n);
        fillMatrix(B, n);

        clock_t start = clock();
        multiplyRecursive(A, B, C, n);
        clock_t end = clock();

        printf("%-10d %-15f\n", n, (double)(end - start) / CLOCKS_PER_SEC);

        destroyMatrix(A, n);
        destroyMatrix(B, n);
        destroyMatrix(C, n);
    }

    return 0;
}
