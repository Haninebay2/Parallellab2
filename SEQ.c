#include <stdio.h>
#include <sys/time.h>

#define M 1000
#define N 1000
#define K 1000

double A[M][K], B[K][N], C[M][N];

int main()
{
    int i, j, k;
    struct timeval start_time, end_time;

    // Initialize matrices
    for (i = 0; i < M; i++) {
        for (j = 0; j < K; j++) {
            A[i][j] = i + j;
        }
    }
    for (i = 0; i < K; i++) {
        for (j = 0; j < N; j++) {
            B[i][j] = i + j;
        }
    }

    // Multiply matrices sequentially
    gettimeofday(&start_time, NULL);
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    gettimeofday(&end_time, NULL);

    // Calculate execution time
    double execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1e6;

    // Print result and execution time
    printf("Matrix multiplication completed in %f seconds\n", execution_time);

    return 0;
}