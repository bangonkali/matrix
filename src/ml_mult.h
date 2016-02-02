//
// Created by gilmichael on 1/29/2016.
//

#ifndef MATRIXOPERATIONS_ML_MULT_H
#define MATRIXOPERATIONS_ML_MULT_H

#include <time.h>
#include "ml_mat.h"
#include "ml_display.h"

/** Multiply Matrices using Strassen Method (Currently unoptimized)
 * A recursive multiplication using the Strassen Algorithm. At this moment it is poorly optimized.
 *  Partition A and B into quarter matrices as described above.
 *  2. Compute the intermediate matrices:
 *        1. If the sizes of the matrices are greater than a threshold value, multiply them recursively using Strassen's algorithm.
 *        2. Else use the traditional matrix multiplication algorithm.
 *  3. Construct C using the intermediate matrices.
 *
 * @param A a pointer to the first matrix.
 * @param B a pointer to the second matrix.
 * @param C a *pointer to the product matrix.
 * @param size an optimization variable that passes the size of the output. Only consider the width since width = n and matrix is nxn.
 * @param offset a debugging variable that monitors the level of depth in the recursion.
 * @param request a debugging variable that monitors the name of the operation. The is currently assigned as a number.
 * @return void
 */
void mlMultiplyStrassen(const mlMat *A, const mlMat *B, mlMat **C, int size, int offset, int request);

/** Add Matrices
 * A conventional matrix add operation
 * @param m1 a pointer to the first matrix.
 * @param m2 a pointer to the second matrix.
 * @param m3 a *pointer to the sum matrix. The return value.
 * @param size the size of the return value matrix. Only consider the width since width = n and matrix is nxn.
 */
void mlAddMat(const mlMat *, const mlMat *, mlMat **, int);

/** Subtract Matrices
 * A conventional matrix add operation
 * @param m1 a pointer to the first matrix.
 * @param m2 a pointer to the second matrix.
 * @param m3 a *pointer to the difference matrix. The return value.
 * @param size the size of the return value matrix. Only consider the width since width = n and matrix is nxn.
 */
void mlSubtractMat(const mlMat *m1, const mlMat *m2, mlMat **m3, int size);

/** Multiply Matrices using Sequential Method
 * A conventional matrix multiplication operation
 * @param m1 a pointer to the first matrix.
 * @param m2 a pointer to the second matrix.
 * @param m3 a *pointer to the product matrix. The return value.
 * @param size the size of the return value matrix. Only consider the width since width = n and matrix is nxn.
 */
void mlMultiplySequential(const element *A, const element *B, element *C, int size);

#endif //MATRIXOPERATIONS_ML_MULT_H
