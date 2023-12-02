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
    
    int _0, _1, _2, _3, _4, _5, _6, _7;
    int m, n, i, j;
    for (int m = 0; m < 64; m += 8)
{
    for (int n = m; n < 64; n += 8)
    {
        if (m != n)
        {
            for (int i = n; i < n + 4; ++i)
            {
                // 这里，把 M 和 N 都搭上，
                // 用来存储 i、j 的偏移量，
                // 是十分不提倡的做法……
                // 不过想到代码本就可怜的可读性，
                // 这边实在不忍心把 M 和 N 代入表达式。

                N = i - n;

                _0 = A[i][m];
                _1 = A[i][m + 1];
                _2 = A[i][m + 2];
                _3 = A[i][m + 3];

                _4 = A[i][m + 4];
                _5 = A[i][m + 5];
                _6 = A[i][m + 6];
                _7 = A[i][m + 7];

                B[m + 4][n + N] = _4;
                B[m + 5][n + N] = _5;
                B[m + 6][n + N] = _6;
                B[m + 7][n + N] = _7;

                B[m + 4][n + 4 + N] = _0;
                B[m + 5][n + 4 + N] = _1;
                B[m + 6][n + 4 + N] = _2;
                B[m + 7][n + 4 + N] = _3;
            }

            for (int i = m + 4; i < m + 8; ++i)
            {
                N = i - (m + 4);

                _0 = A[n + 4][m + 4 + N];
                _1 = A[n + 5][m + 4 + N];
                _2 = A[n + 6][m + 4 + N];
                _3 = A[n + 7][m + 4 + N];

                _4 = B[m + 4 + N][n + 4];
                _5 = B[m + 4 + N][n + 5];
                _6 = B[m + 4 + N][n + 6];
                _7 = B[m + 4 + N][n + 7];

                B[m + 4 + N][n + 4] = _0;
                B[m + 4 + N][n + 5] = _1;
                B[m + 4 + N][n + 6] = _2;
                B[m + 4 + N][n + 7] = _3;

                B[m + N][n] = _4;
                B[m + N][n + 1] = _5;
                B[m + N][n + 2] = _6;
                B[m + N][n + 3] = _7;
            }

            for (int i = m; i < m + 4; ++i)
            {
                _0 = A[n + 4][i];
                _1 = A[n + 5][i];
                _2 = A[n + 6][i];
                _3 = A[n + 7][i];

                B[i][n + 4] = _0;
                B[i][n + 5] = _1;
                B[i][n + 6] = _2;
                B[i][n + 7] = _3;
            }
/*********** 把代码反过来，处理对称位置的矩阵块 ***********/
            for (int i = m + 4; i < m + 8; ++i)
            {
                M = i - (m + 4);

                _0 = A[i][n];
                _1 = A[i][n + 1];
                _2 = A[i][n + 2];
                _3 = A[i][n + 3];

                _4 = A[i][n + 4];
                _5 = A[i][n + 5];
                _6 = A[i][n + 6];
                _7 = A[i][n + 7];

                B[n][m + M] = _4;
                B[n + 1][m + M] = _5;
                B[n + 2][m + M] = _6;
                B[n + 3][m + M] = _7;

                B[n][m + 4 + M] = _0;
                B[n + 1][m + 4 + M] = _1;
                B[n + 2][m + 4 + M] = _2;
                B[n + 3][m + 4 + M] = _3;
            }

            for (int i = n; i < n + 4; ++i)
            {
                _0 = A[m][i];
                _1 = A[m + 1][i];
                _2 = A[m + 2][i];
                _3 = A[m + 3][i];

                _4 = B[i][m];
                _5 = B[i][m + 1];
                _6 = B[i][m + 2];
                _7 = B[i][m + 3];

                B[i][m] = _0;
                B[i][m + 1] = _1;
                B[i][m + 2] = _2;
                B[i][m + 3] = _3;

                B[i + 4][m + 4] = _4;
                B[i + 4][m + 5] = _5;
                B[i + 4][m + 6] = _6;
                B[i + 4][m + 7] = _7;
            }

            for (int i = m; i < m + 4; ++i)
            {
                M = i - m;

                _0 = A[i][n + 4];
                _1 = A[i][n + 5];
                _2 = A[i][n + 6];
                _3 = A[i][n + 7];

                B[n + 4][m + M] = _0;
                B[n + 5][m + M] = _1;
                B[n + 6][m + M] = _2;
                B[n + 7][m + M] = _3;
            }                
/*******************************************************/
        }
        else{
                    // 处理对角线上的矩阵块……
                if (m != 56 && n != 56)
                {
            for (int i = m; i < m + 4; ++i)
            {
                // 这里，把 M 和 N 都搭上，
                // 用来存储 i、j 的偏移量，
                // 是十分不提倡的做法……
                // 不过想到代码本就可怜的可读性，
                // 这边实在不忍心把 M 和 N 代入表达式。
                M = i - m;

                _0 = A[i][n];
                _1 = A[i][n + 1];
                _2 = A[i][n + 2];
                _3 = A[i][n + 3];

                _4 = A[i][n + 4];
                _5 = A[i][n + 5];
                _6 = A[i][n + 6];
                _7 = A[i][n + 7];

                B[m + 4][n + 8 + M] = _0;
                B[m + 5][n + 8 + M] = _1;
                B[m + 6][n + 8 + M] = _2;
                B[m + 7][n + 8 + M] = _3;

                B[m + 4][n + 12 + M] = _4;
                B[m + 5][n + 12 + M] = _5;
                B[m + 6][n + 12 + M] = _6;
                B[m + 7][n + 12 + M] = _7;
            }

            // -----------------------------------------------------------------------
            for (int i = m + 4; i < m + 8; ++i)
            {
                _0 = A[i][n];
                _1 = A[i][n + 1];
                _2 = A[i][n + 2];
                _3 = A[i][n + 3];
                _4 = A[i][n + 4];
                _5 = A[i][n + 5];
                _6 = A[i][n + 6];
                _7 = A[i][n + 7];

                B[i][n] = _0;
                B[i][n + 1] = _1;
                B[i][n + 2] = _2;
                B[i][n + 3] = _3;
                B[i][n + 4] = _4;
                B[i][n + 5] = _5;
                B[i][n + 6] = _6;
                B[i][n + 7] = _7;
            }

            for (int i = m + 4; i < m + 8; ++i)
            {
                M = i - (m + 4);
                for (int j = n + M; j < n + 4; ++j)
                {
                    N = j - n;

                    _0 = B[i][j];
                    B[i][j] = B[m + 4 + N][n + M];
                    B[m + 4 + N][n + M] = _0;
                }
            }

            for (int i = m + 4; i < m + 8; ++i)
            {
                M = i - (m + 4);
                for (int j = n + 4 + M; j < n + 8; ++j)
                {
                        N = j - (n + 4);
                                    
                        _0 = B[i][j];
                        B[i][j] = B[m + 4 + N][n + 4 + M];
                        B[m + 4 + N][n + 4 + M] = _0;
                }
            }
            // -------------------------------------------------------------------------------
            
            for (int i = m + 4; i < m + 8; ++i)
            {
                _0 = B[i][n];
                _1 = B[i][n + 1];
                _2 = B[i][n + 2];
                _3 = B[i][n + 3];

                _4 = B[i][n + 12];
                _5 = B[i][n + 13];
                _6 = B[i][n + 14];
                _7 = B[i][n + 15];

                B[i][n] = _4;
                B[i][n + 1] = _5;
                B[i][n + 2] = _6;
                B[i][n + 3] = _7;

                B[i][n + 12] = _0;
                B[i][n + 13] = _1;
                B[i][n + 14] = _2;
                B[i][n + 15] = _3;
            }

            for (int i = m; i < m + 4; ++i)
                for (int j = n; j < n + 8; ++j)
                    B[i][j] = B[i + 4][j + 8];
        }
        else
        {
            for (int i = m; i < m + 4; ++i)
            {
                _0 = A[i][n];
                _1 = A[i][n + 1];
                _2 = A[i][n + 2];
                _3 = A[i][n + 3];
                _4 = A[i][n + 4];
                _5 = A[i][n + 5];
                _6 = A[i][n + 6];
                _7 = A[i][n + 7];

                B[i][n] = _0;
                B[i][n + 1] = _1;
                B[i][n + 2] = _2;
                B[i][n + 3] = _3;
                B[i][n + 4] = _4;
                B[i][n + 5] = _5;
                B[i][n + 6] = _6;
                B[i][n + 7] = _7;
            }

            for (int i = m; i < m + 4; ++i)
            {
                for (int j = n + (i - m); j < n + 4; ++j)
                {
                    if (i != j)
                    {
                        _0 = B[i][j];
                        B[i][j] = B[j][i];
                        B[j][i] = _0;
                    }
                }
            }

            for (int i = m; i < m + 4; ++i)
            {
                M = i - m;
                for (int j = n + 4 + M; j < n + 8; ++j)
                {
                    N = j - (n + 4);

                    _0 = B[i][j];
                    B[i][j] = B[m + N][n + 4 + M];
                    B[m + N][n + 4 + M] = _0;
                }
            }

            for (int i = m + 4; i < m + 8; ++i)
            {
                _0 = A[i][n];
                _1 = A[i][n + 1];
                _2 = A[i][n + 2];
                _3 = A[i][n + 3];
                _4 = A[i][n + 4];
                _5 = A[i][n + 5];
                _6 = A[i][n + 6];
                _7 = A[i][n + 7];

                B[i][n] = _0;
                B[i][n + 1] = _1;
                B[i][n + 2] = _2;
                B[i][n + 3] = _3;
                B[i][n + 4] = _4;
                B[i][n + 5] = _5;
                B[i][n + 6] = _6;
                B[i][n + 7] = _7;
            }

            for (int i = m + 4; i < m + 8; ++i)
            {
                for (int j = n + 4 + i - (m + 4); j < n + 8; ++j)
                {
                    if (i != j)
                    {
                        _0 = B[i][j];
                        B[i][j] = B[j][i];
                        B[j][i] = _0;
                    }
                }
            }

            for (int i = m + 4; i < m + 8; ++i)
            {
                M = i - (m + 4);
                for (int j = n + M; j < n + 4; ++j)
                {
                    N = j - n;

                    _0 = B[i][j];
                    B[i][j] = B[m + 4 + N][n + M];
                    B[m + 4 + N][n + M] = _0;
                }
            }

            for (int i = m + 4; i < m + 8; ++i)
            {
                _0 = B[i][n];
                _1 = B[i][n + 1];
                _2 = B[i][n + 2];
                _3 = B[i][n + 3];

                _4 = B[i - 4][n + 4];
                _5 = B[i - 4][n + 5];
                _6 = B[i - 4][n + 6];
                _7 = B[i - 4][n + 7];

                B[i - 4][n + 4] = _0;
                B[i - 4][n + 5] = _1;
                B[i - 4][n + 6] = _2;
                B[i - 4][n + 7] = _3;

                B[i][n] = _4;
                B[i][n + 1] = _5;
                B[i][n + 2] = _6;
                B[i][n + 3] = _7;
            }
        }
            }
        }
    }
}




