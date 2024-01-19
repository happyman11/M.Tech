#include <stdio.h>
#include <stdlib.h>

/// Coarse grain Lock on whole data structure no thread are allowed
/// Fine Grain Lock on individual lock on data structures waitint time is more
///  Optimistion search >> validate >> lock 
// Lazy Logical deletion >> physical deletion


// Function to perform matrix multiplication for a given block size
void block_matrix_multiply(int **A, int **B, int **C, int n, int block_size) {
    for (int i = 0; i < n; i += block_size) {
        for (int j = 0; j < n; j += block_size) {
            for (int k = 0; k < n; k += block_size) {
                // Multiply the current block
                for (int ii = i; ii < i + block_size; ii++) {
                    for (int jj = j; jj < j + block_size; jj++) {
                        for (int kk = k; kk < k + block_size; kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n = 512; // Size of the matrices (assuming they are square)
    int **A, **B, **C;

    // Allocate memory for matrices A, B, and C
    A = (int **)malloc(n * sizeof(int *));
    B = (int **)malloc(n * sizeof(int *));
    C = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        B[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(n * sizeof(int));
    }

    // Initialize matrices A and B (you can do this as needed)
    // ...

    // Initialize matrix C to all zeros
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
        }
    }

    int block_sizes[] = {4, 8, 16, 32, 64};
    int num_block_sizes = sizeof(block_sizes) / sizeof(block_sizes[0]);

    // Perform matrix multiplication for each block size
    for (int i = 0; i < num_block_sizes; i++) {
        int block_size = block_sizes[i];
        block_matrix_multiply(A, B, C, n, block_size);

        // Output or use the result C as needed
        // ...

        // Reset matrix C for the next block size
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
            }
        }
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
