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
    
    
    if(M == 16){ //16x16 matrix
        
    }
    else if(M == 32){ //32x32 matrix
        for(int i = 0; i < M; i += 8) {
            for(int j = 0; j < N; j += 4) {
                for(int m = 0; m < i + 8; m ++) {
                    for(int n = 0; n < j + 4; n ++) {
                        B[n][m] = A[m][n];
                    }
                }
            }
        }
    }
    
}




