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
    int x1, x2, x3, x4, x5, x6, x7, x8;
    int i, j, x, y;
		for (i = 0; i < N; i += 8)
			for (j = 0; j < M; j += 8)
			{
				for (x = i; x < i + 4; ++x)
				{
					x1 = A[x][j]; x2 = A[x][j+1]; x3 = A[x][j+2]; x4 = A[x][j+3];
					x5 = A[x][j+4]; x6 = A[x][j+5]; x7 = A[x][j+6]; x8 = A[x][j+7];
					
					B[j][x] = x1; B[j+1][x] = x2; B[j+2][x] = x3; B[j+3][x] = x4;
					B[j][x+4] = x5; B[j+1][x+4] = x6; B[j+2][x+4] = x7; B[j+3][x+4] = x8;
				}
				for (y = j; y < j + 4; ++y)
				{
					x1 = A[i+4][y]; x2 = A[i+5][y]; x3 = A[i+6][y]; x4 = A[i+7][y];
					x5 = B[y][i+4]; x6 = B[y][i+5]; x7 = B[y][i+6]; x8 = B[y][i+7];
					
					B[y][i+4] = x1; B[y][i+5] = x2; B[y][i+6] = x3; B[y][i+7] = x4;
					B[y+4][i] = x5; B[y+4][i+1] = x6; B[y+4][i+2] = x7; B[y+4][i+3] = x8;
				}
				for (x = i + 4; x < i + 8; ++x)
				{
					x1 = A[x][j+4]; x2 = A[x][j+5]; x3 = A[x][j+6]; x4 = A[x][j+7];
					B[j+4][x] = x1; B[j+5][x] = x2; B[j+6][x] = x3; B[j+7][x] = x4;
				}
			}


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


}




