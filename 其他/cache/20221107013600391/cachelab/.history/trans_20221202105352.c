/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Your transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * The transpose function is evaluated by counting the number of misses
 * on a 512B direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */

void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    /*
     * Please define your local variables here. 
     * You are allowed to define at most 12 local variables.
    */
    
    int i, j, k;
    int v1, v2, v3, v4, v5, v6, v7, v8;
    if(M == 16){ //16x16 matrix
        for(i = 0; i < M; i += 8) {
            for(j = 0; j < N; j += 8) {
                for(k = i; k < i + 8; k ++) {
                    v1 = A[k][j];
                    v2 = A[k][j + 1];
                    v3 = A[k][j + 2];
                    v4 = A[k][j + 3];
                    v5 = A[k][j + 4];
                    v6 = A[k][j + 5];
                    v7 = A[k][j + 6];
                    v8 = A[k][j + 7];
                    B[j][k] = v1;
                    B[j + 1][k] = v2;
                    B[j + 2][k] = v3;
                    B[j + 3][k] = v4;
                    B[j + 4][k] = v5;
                    B[j + 5][k] = v6;
                    B[j + 6][k] = v7;
                    B[j + 7][k] = v8;
                }
            }
        }
    }
    else if(M == 32){ //32x32 matrix

        for(i = 0; i < M; i += 8) {
            for(j = 0; j < N; j += 8) {
                for(k = i; k < i + 8; k +=2) {
                    v1 = A[k][j];
                    v2 = A[k][j + 1];
                    v3 = A[k][j + 2];
                    v4 = A[k][j + 3];
                    v5 = A[k + 1][j];
                    v6 = A[k + 1][j + 1];
                    v7 = A[k + 1][j + 2];
                    v8 = A[k + 1][j + 3];
                    B[j][k] = v1;
                    B[j + 1][k] = v2;
                    B[j + 2][k] = v3;
                    B[j + 3][k] = v4;
                    B[j][k + 1] = v5;
                    B[j + 1][k + 1] = v6;
                    B[j + 2][k + 1] = v7;
                    B[j + 3][k + 1] = v8;
                }
            }
        }
    }
    
}




