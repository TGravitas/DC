#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MATRIX_SIZE 3

// Function to initialize matrices A and B with fixed values
void initialize_matrices(int A[MATRIX_SIZE][MATRIX_SIZE], int B[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j;

    int values_A[MATRIX_SIZE][MATRIX_SIZE] = {
        {0, 7, 2},
        {1, 9, 3},
        {2, 8, 4}
    };

    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            A[i][j] = values_A[i][j];
        }
    }

    int values_B[MATRIX_SIZE][MATRIX_SIZE] = {
        {1, 2, 3},
        {2, 1, 3},
        {5, 0, 1}
    };

    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            B[i][j] = values_B[i][j];
        }
    }
}

void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int rank, size, i, j, k;
    int A[MATRIX_SIZE][MATRIX_SIZE], B[MATRIX_SIZE][MATRIX_SIZE], C[MATRIX_SIZE][MATRIX_SIZE];
    int row_A[MATRIX_SIZE], row_C[MATRIX_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Master process initializes matrices A and B
    if (rank == 0) {
        initialize_matrices(A, B);
        printf("Matrix A:\n");
        print_matrix(A);
        printf("\nMatrix B:\n");
        print_matrix(B);
    }

    // Broadcast matrix B to all processes
    if (rank == 0) {
        for (i = 1; i < size; i++) {
            MPI_Send(B, MATRIX_SIZE * MATRIX_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(B, MATRIX_SIZE * MATRIX_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Scatter rows of matrix A to all processes
    MPI_Scatter(A, MATRIX_SIZE * MATRIX_SIZE / size, MPI_INT, row_A, MATRIX_SIZE * MATRIX_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform local multiplication
    for (i = 0; i < MATRIX_SIZE; i++) {
        row_C[i] = 0;
        for (j = 0; j < MATRIX_SIZE; j++) {
            row_C[i] += row_A[j] * B[j][i];
        }
    }

    // Collect all rows of C in the master process
    if (rank == 0) {
    	for(int i=0;i<MATRIX_SIZE;i++)
    		C[0][i]=row_C[i];
    		
        for (i = 1; i < size; i++) {
            MPI_Recv(C[i], MATRIX_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    } else {
        MPI_Send(row_C, MATRIX_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Master process prints the result
    if (rank == 0) {
        printf("\nMatrix C (Result):\n");
        print_matrix(C);
    }

    MPI_Finalize();
    return 0;
}
