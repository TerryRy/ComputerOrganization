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
    
    // int i, j, t;
    // int v1, v2, v3, v4, v5, v6, v7, v8;
    // int x1, x2, x3, x4, x5, x6, x7, x8;
    // int i, j, x, y;
	// 	for (i = 0; i < N; i += 8)
	// 		for (j = 0; j < M; j += 8)
	// 		{
	// 			for (x = i; x < i + 4; ++x)
	// 			{
	// 				x1 = A[x][j]; 
    //                 x2 = A[x][j+1]; 
    //                 x3 = A[x][j+2]; 
    //                 x4 = A[x][j+3];
	// 				x5 = A[x][j+4]; 
    //                 x6 = A[x][j+5]; 
    //                 x7 = A[x][j+6]; 
    //                 x8 = A[x][j+7];
					
	// 				B[j][x] = x1; 
    //                 B[j+1][x] = x2; 
    //                 B[j+2][x] = x3; 
    //                 B[j+3][x] = x4;
	// 				B[j][x+4] = x5; 
    //                 B[j+1][x+4] = x6; 
    //                 B[j+2][x+4] = x7; 
    //                 B[j+3][x+4] = x8;
	// 			}
	// 			for (y = j; y < j + 4; ++y)
	// 			{
	// 				x1 = A[i+4][y]; 
    //                 x2 = A[i+5][y]; 
    //                 x3 = A[i+6][y]; 
    //                 x4 = A[i+7][y];
	// 				x5 = B[y][i+4]; 
    //                 x6 = B[y][i+5]; 
    //                 x7 = B[y][i+6]; 
    //                 x8 = B[y][i+7];
					
	// 				B[y][i+4] = x1; 
    //                 B[y][i+5] = x2; 
    //                 B[y][i+6] = x3; 
    //                 B[y][i+7] = x4;
	// 				B[y+4][i] = x5;
    //                 B[y+4][i+1] = x6; 
    //                 B[y+4][i+2] = x7; 
    //                 B[y+4][i+3] = x8;
	// 			}
	// 			for (x = i + 4; x < i + 8; ++x)
	// 			{
	// 				x1 = A[x][j+4]; x2 = A[x][j+5]; x3 = A[x][j+6]; x4 = A[x][j+7];
	// 				B[j+4][x] = x1; B[j+5][x] = x2; B[j+6][x] = x3; B[j+7][x] = x4;
	// 			}
	// 		}

    for(int i=0;i<N;i+=8){
            for(int j=0;j<M;j+=8){
                for(int k=i;k<i+4;k++){
                    int t1=A[k][j];
                    int t2=A[k][j+1];
                    int t3=A[k][j+2];
                    int t4=A[k][j+3];
                    int t5=A[k][j+4];
                    int t6=A[k][j+5];
                    int t7=A[k][j+6];
                    int t8=A[k][j+7];

                    B[j][k]=t1;
                    B[j+1][k]=t2;
                    B[j+2][k]=t3;
                    B[j+3][k]=t4;

                    B[j][k+4]=t5;
                    B[j+1][k+4]=t6;
                    B[j+2][k+4]=t7;
                    B[j+3][k+4]=t8;

                }
                for(int k=j;k<j+4;k++){
                    int t1=A[i+4][k];
                    int t2=A[i+5][k];
                    int t3=A[i+6][k];
                    int t4=A[i+7][k];

                    int t5=B[k][i+4];
                    int t6=B[k][i+5];
                    int t7=B[k][i+6];
                    int t8=B[k][i+7];

                    B[k][i+4]=t1;
                    B[k][i+5]=t2;
                    B[k][i+6]=t3;
                    B[k][i+7]=t4;


                    B[k+4][i]=t5;
                    B[k+4][i+1]=t6;
                    B[k+4][i+2]=t7;
                    B[k+4][i+3]=t8;

                }

                for(int k=i;k<i+4;k++){
                    int t1=A[k+4][j+4];
                    int t2=A[k+4][j+5];
                    int t3=A[k+4][j+6];
                    int t4=A[k+4][j+7];

                    B[j+4][k+4]=t1;
                    B[j+5][k+4]=t2;
                    B[j+6][k+4]=t3;
                    B[j+7][k+4]=t4;
                }
            }
        }
}




