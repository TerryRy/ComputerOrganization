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
    // int x1, x2, x3, x4, x5, x6, x7, x8;
    // for (i = 0; /i < N; i += 8) // 2243
	// 		for (j = 0; j < M; j += 8)
	// 		{
	// 			for (k = i; k < i + 4; ++k)
	// 			{
	// 				v1 = A[k][j];
    //                 v2 = A[k][j+1];
    //                 v3 = A[k][j+2];
    //                 v4 = A[k][j+3];
	// 				v5 = A[k][j+4];
    //                 v6 = A[k][j+5];
    //                 v7 = A[k][j+6];
    //                 v8 = A[k][j+7];
					
	// 				B[j][k] = v1;
    //                 B[j+1][k] = v2;
    //                 B[j+2][k] = v3;
    //                 B[j+3][k] = v4;
	// 				B[j][k+4] = v5;
    //                 B[j+1][k+4] = v6;
    //                 B[j+2][k+4] = v7;
    //                 B[j+3][k+4] = v8;
	// 			}
	// 			for (k = j; k < j + 4; ++k)
	// 			{
	// 				v1 = A[i+4][k];
    //                 v2 = A[i+5][k];
    //                 v3 = A[i+6][k];
    //                 v4 = A[i+7][k];
	// 				v5 = B[k][i+4];
    //                 v6 = B[k][i+5];
    //                 v7 = B[k][i+6];
    //                 v8 = B[k][i+7];
					
	// 				B[k][i+4] = v1;
    //                 B[k][i+5] = v2;
    //                 B[k][i+6] = v3;
    //                 B[k][i+7] = v4;
	// 				B[k+4][i] = v5;
    //                 B[k+4][i+1] = v6;
    //                 B[k+4][i+2] = v7;
    //                 B[k+4][i+3] = v8;
	// 			}
	// 			for (k = i + 4; k < i + 8; ++k)
	// 			{
	// 				v1 = A[k][j+4];
    //                 v2 = A[k][j+5];
    //                 v3 = A[k][j+6];
    //                 v4 = A[k][j+7];

	// 				B[j+4][k] = v1;
    //                 B[j+5][k] = v2;
    //                 B[j+6][k] = v3;
    //                 B[j+7][k] = v4;
	// 			}
	// 		}

    // for (i = 0; i < N; i += 8)
	// 	for (j = 0; j < N; j += 8)
	// 	{
	// 		if (i == j)
	// 		{
	// 			x=i;
	// 			x1=A[x][j];x2=A[x][j+1];x3=A[x][j+2];x4=A[x][j+3];
	// 			x5=A[x][j+4];x6=A[x][j+5];x7=A[x][j+6];x8=A[x][j+7];
 
	// 			B[x][j]=x1;B[x][j+1]=x2;B[x][j+2]=x3;B[x][j+3]=x4;
	// 			B[x][j+4]=x5;B[x][j+5]=x6;B[x][j+6]=x7;B[x][j+7]=x8;
 
	// 			x1=A[x+1][j];x2=A[x+1][j+1];x3=A[x+1][j+2];x4=A[x+1][j+3];
	// 			x5=A[x+1][j+4];x6=A[x+1][j+5];x7=A[x+1][j+6];x8=A[x+1][j+7];
 
	// 			B[x+1][j]=B[x][j+1];B[x][j+1]=x1;
 
	// 			B[x+1][j+1]=x2;B[x+1][j+2]=x3;B[x+1][j+3]=x4;
	// 			B[x+1][j+4]=x5;B[x+1][j+5]=x6;B[x+1][j+6]=x7;B[x+1][j+7]=x8;
 
	// 			x1=A[x+2][j];x2=A[x+2][j+1];x3=A[x+2][j+2];x4=A[x+2][j+3];
	// 			x5=A[x+2][j+4];x6=A[x+2][j+5];x7=A[x+2][j+6];x8=A[x+2][j+7];
 
	// 			B[x+2][j]=B[x][j+2];B[x+2][j+1]=B[x+1][j+2];
	// 			B[x][j+2]=x1;B[x+1][j+2]=x2;B[x+2][j+2]=x3;
	// 			B[x+2][j+3]=x4;B[x+2][j+4]=x5;B[x+2][j+5]=x6;B[x+2][j+6]=x7;B[x+2][j+7]=x8;
 
	// 			x1=A[x+3][j];x2=A[x+3][j+1];x3=A[x+3][j+2];x4=A[x+3][j+3];
	// 			x5=A[x+3][j+4];x6=A[x+3][j+5];x7=A[x+3][j+6];x8=A[x+3][j+7];
 
	// 			B[x+3][j]=B[x][j+3];B[x+3][j+1]=B[x+1][j+3];B[x+3][j+2]=B[x+2][j+3];
	// 			B[x][j+3]=x1;B[x+1][j+3]=x2;B[x+2][j+3]=x3;B[x+3][j+3]=x4;
	// 			B[x+3][j+4]=x5;B[x+3][j+5]=x6;B[x+3][j+6]=x7;B[x+3][j+7]=x8;
 
	// 			x1=A[x+4][j];x2=A[x+4][j+1];x3=A[x+4][j+2];x4=A[x+4][j+3];
	// 			x5=A[x+4][j+4];x6=A[x+4][j+5];x7=A[x+4][j+6];x8=A[x+4][j+7];
 
	// 			B[x+4][j]=B[x][j+4];B[x+4][j+1]=B[x+1][j+4];B[x+4][j+2]=B[x+2][j+4];B[x+4][j+3]=B[x+3][j+4];
	// 			B[x][j+4]=x1;B[x+1][j+4]=x2;B[x+2][j+4]=x3;B[x+3][j+4]=x4;B[x+4][j+4]=x5;
	// 			B[x+4][j+5]=x6;B[x+4][j+6]=x7;B[x+4][j+7]=x8;
 
	// 			x1=A[x+5][j];x2=A[x+5][j+1];x3=A[x+5][j+2];x4=A[x+5][j+3];
	// 			x5=A[x+5][j+4];x6=A[x+5][j+5];x7=A[x+5][j+6];x8=A[x+5][j+7];
 
	// 			B[x+5][j]=B[x][j+5];B[x+5][j+1]=B[x+1][j+5];B[x+5][j+2]=B[x+2][j+5];B[x+5][j+3]=B[x+3][j+5];B[x+5][j+4]=B[x+4][j+5];
	// 			B[x][j+5]=x1;B[x+1][j+5]=x2;B[x+2][j+5]=x3;B[x+3][j+5]=x4;B[x+4][j+5]=x5;B[x+5][j+5]=x6;
	// 			B[x+5][j+6]=x7;B[x+5][j+7]=x8;
 
	// 			x1=A[x+6][j];x2=A[x+6][j+1];x3=A[x+6][j+2];x4=A[x+6][j+3];
	// 			x5=A[x+6][j+4];x6=A[x+6][j+5];x7=A[x+6][j+6];x8=A[x+6][j+7];
 
	// 			B[x+6][j]=B[x][j+6];B[x+6][j+1]=B[x+1][j+6];B[x+6][j+2]=B[x+2][j+6];B[x+6][j+3]=B[x+3][j+6];
	// 			B[x+6][j+4]=B[x+4][j+6];B[x+6][j+5]=B[x+5][j+6];
	// 			B[x][j+6]=x1;B[x+1][j+6]=x2;B[x+2][j+6]=x3;B[x+3][j+6]=x4;B[x+4][j+6]=x5;B[x+5][j+6]=x6;
	// 			B[x+6][j+6]=x7;B[x+6][j+7]=x8;
 
	// 			x1=A[x+7][j];x2=A[x+7][j+1];x3=A[x+7][j+2];x4=A[x+7][j+3];
	// 			x5=A[x+7][j+4];x6=A[x+7][j+5];x7=A[x+7][j+6];x8=A[x+7][j+7];
 
	// 			B[x+7][j]=B[x][j+7];B[x+7][j+1]=B[x+1][j+7];B[x+7][j+2]=B[x+2][j+7];B[x+7][j+3]=B[x+3][j+7];
	// 			B[x+7][j+4]=B[x+4][j+7];B[x+7][j+5]=B[x+5][j+7];B[x+7][j+6]=B[x+6][j+7];
	// 			B[x][j+7]=x1;B[x+1][j+7]=x2;B[x+2][j+7]=x3;B[x+3][j+7]=x4;B[x+4][j+7]=x5;B[x+5][j+7]=x6;B[x+6][j+7]=x7;
	// 			B[x+7][j+7]=x8;
	// 		}
				
	// 		else
	// 		{
	// 			for(x = i; x < (i + 8); ++x)
	// 				for(y = j; y < (j + 8); ++y)
	// 					B[y][x] = A[x][y];
	// 		}
	// 	}


    // for (i = 0; i < N; i += 16) // 
	// 		for (j = 0; j < M; j += 16)
	// 		{
	// 			for (k = i; k < i + 8; ++k)
	// 			{
	// 				v1 = A[k][j];
    //                 v2 = A[k][j+1];
    //                 v3 = A[k][j+2];
    //                 v4 = A[k][j+3];
	// 				v5 = A[k][j+4];
    //                 v6 = A[k][j+5];
    //                 v7 = A[k][j+6];
    //                 v8 = A[k][j+7];
					
	// 				B[j][k] = v1;
    //                 B[j+1][k] = v2;
    //                 B[j+2][k] = v3;
    //                 B[j+3][k] = v4;
    //                 B[j+4][k] = v5;
    //                 B[j+5][k] = v6;
    //                 B[j+6][k] = v7;
    //                 B[j+7][k] = v8;

    //                 v1 = A[k][j+8];
    //                 v2 = A[k][j+9];
    //                 v3 = A[k][j+10];
    //                 v4 = A[k][j+11];
	// 				v5 = A[k][j+12];
    //                 v6 = A[k][j+13];
    //                 v7 = A[k][j+14];
    //                 v8 = A[k][j+15];

	// 				B[j][k + 8] = v1;
    //                 B[j+1][k+8] = v2;
    //                 B[j+2][k+8] = v3;
    //                 B[j+3][k+8] = v4;
    //                 B[j+4][k+8] = v5;
    //                 B[j+5][k+8] = v6;
    //                 B[j+6][k+8] = v7;
    //                 B[j+7][k+8] = v8;
	// 			}
	// 			for (k = j; k < j + 8; ++k)
	// 			{
	// 				v1 = A[i+8][k];
    //                 v2 = A[i+9][k];
    //                 v3 = A[i+10][k];
    //                 v4 = A[i+11][k];
	// 				v5 = B[k][i+8];
    //                 v6 = B[k][i+9];
    //                 v7 = B[k][i+10];
    //                 v8 = B[k][i+11];
					
	// 				B[k][i+8] = v1;
    //                 B[k][i+9] = v2;
    //                 B[k][i+10] = v3;
    //                 B[k][i+11] = v4;
	// 				B[k+8][i] = v5;
    //                 B[k+9][i+1] = v6;
    //                 B[k+10][i+2] = v7;
    //                 B[k+11][i+3] = v8;
    //                 B[k+12][i+4] = B[k][i+12];
    //                 B[k+13][i+5] = B[k][i+13];
    //                 B[k+14][i+6] = B[k][i+14];
    //                 B[k+15][i+7] = B[k][i+15]; 
    //                 B[k][i+12] = A[i+12][k];
    //                 B[k][i+13] = A[i+13][k];
    //                 B[k][i+14] = A[i+14][k];
    //                 B[k][i+15] = A[i+15][k];
	// 			}
	// 			for (k = i + 8; k < i + 16; ++k)
	// 			{
	// 				v1 = A[k][j+8];
    //                 v2 = A[k][j+9];
    //                 v3 = A[k][j+10];
    //                 v4 = A[k][j+11];
    //                 v5 = A[k][j+12];
    //                 v6 = A[k][j+13];
    //                 v7 = A[k][j+14];
    //                 v8 = A[k][j+15];

	// 				B[j+8][k] = v1;
    //                 B[j+9][k] = v2;
    //                 B[j+10][k] = v3;
    //                 B[j+11][k] = v4;
    //                 B[j+12][k] = v5;
    //                 B[j+13][k] = v6;
    //                 B[j+14][k] = v7;
    //                 B[j+15][k] = v8;
	// 			}
	// 		}
}




