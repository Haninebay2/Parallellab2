#include <stdio.h>
#include <omp.h>

#define M 1000
#define N 1000
#define P 1000
#define NUM_THREADS 1

double A[M][N], B[N][P], C[M][P];

int main() {
    int i, j, k;
    int tid;
    double start_time, end_time;
    omp_set_num_threads(NUM_THREADS);

    // Initialize matrices A and B
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < P; j++) {
            B[i][j] = i + j;
        }
    }

    start_time = omp_get_wtime();

    #pragma omp parallel private(i, j, k, tid)
    {
        tid = omp_get_thread_num();
        int chunk_size = M / NUM_THREADS;
        int start = tid * chunk_size;
        int end = (tid == NUM_THREADS - 1) ? M : start + chunk_size;

        for (i = start; i < end; i++) {
            for (j = 0; j < P; j++) {
                double sum = 0.0;
                for (k = 0; k < N; k++) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
            }
        }
    }

    end_time = omp_get_wtime();
    printf("Matrix multiplication completed in %f seconds\n", end_time - start_time);

    // Print the result (C matrix)

    return 0;
}