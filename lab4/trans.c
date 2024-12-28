/*
 * CSE 351 Lab 4 (Caches and Cache-Friendly Code)
 * Part 2 - Optimizing Matrix Transpose
 *
 * Name(s):  Zifeng Wang
 * NetID(s): zifenw
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 * and compute B = A^T.
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */

#include <stdio.h>
#include "support/cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);


/*
 * transpose_submit - This is the transpose function that you will be graded
 *     on. Do not change the description string "Transpose submission", as the
 *     driver searches for that string to identify the transpose function to be
 *     graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M]) {
int bj, bi, i, j;
int a, b, c, d, e, f, g, h;  //8 local variables
if (M == 32 && N == 32){
	for (bi = 0; bi < M; bi += 8) {
    		for (bj = 0; bj < N; bj += 8) {
        		for (i = bi; i < bi + 8; i++) {
            a = A[i][0+bj]; b = A[i][1+bj]; c = A[i][2+bj]; d = A[i][3+bj];
            e = A[i][4+bj]; f = A[i][5+bj]; g = A[i][6+bj]; h = A[i][7+bj]; 
            B[0+bj][i] = a; B[1+bj][i] = b; B[2+bj][i] = c; B[3+bj][i] = d;
            B[4+bj][i] = e; B[5+bj][i] = f; B[6+bj][i] = g; B[7+bj][i] = h;
        		}
    		}
	}
}
if(M==64 && N==64){
	
	for (bi = 0; bi < N; bi += 8) {
    		for (bj = 0; bj < M; bj += 8) {
        		for (i = bi; i < bi + 4; i++) {
            a = A[i][0+bj]; b = A[i][1+bj]; c = A[i][2+bj]; d = A[i][3+bj];  //store a a a a
            e = A[i][4+bj]; f = A[i][5+bj]; g = A[i][6+bj]; h = A[i][7+bj];  //store 1 1 1 1

            B[0+bj][i] = a; B[1+bj][i] = b; B[2+bj][i] = c; B[3+bj][i] = d;              //assign a a a a
            B[0+bj][4+i] = e; B[1+bj][4+i] = f; B[2+bj][4+i] = g; B[3+bj][4+i] = h;  //assign 1 1 1 1 
        		}
        		for (j = bj; j < bj + 4; j++) {
            a = A[4+bi][j]; b = A[5+bi][j]; c = A[6+bi][j]; d = A[7+bi][j];   //store e f g h
            e = B[j][4+bi]; f = B[j][5+bi]; g = B[j][6+bi]; h = B[j][7+bi];   //store 1 2 3 4

            B[j][4+bi] = a; B[j][5+bi] = b; B[j][6+bi] = c; B[j][7+bi] = d;          //assign e f g h
            B[4+j][0+bi] = e; B[4+j][1+bi] = f; B[4+j][2+bi] = g; B[4+j][3+bi] = h;  //assign 1 2 3 4
        		}
        		for (i = bi + 4; i < bi + 8; i++) {
            a = A[i][4+bj]; b = A[i][5+bj]; c = A[i][6+bj]; d = A[i][7+bj]; 
            B[4+bj][i] = a; B[5+bj][i] = b; B[6+bj][i] = c; B[7+bj][i] = d; 
        		}
    		}
	}
}
}

// You can define additional transpose functions below. We've defined a simple
// one below to help you get started.

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M]) {
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}


/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}


/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M]) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
