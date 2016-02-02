//
// Created by Bangonkali on 1/23/2016.
//

#ifndef MATRIXOPERATIONS_MATRIX_H
#define MATRIXOPERATIONS_MATRIX_H

#include <stdlib.h>
#include <stdio.h>

/** Matrix Elements
 * This is done this way so that it will be easy to change the type of the elements.
 */
typedef double element;

/** Matrix Structure
 * Stores the region of interest and the size of the matrix. Also includes the pointer to the Matrix Data.
 */
typedef struct _Matrix {
    int rs; /*!< Region of Interest row start.  */
    int re; /*!< Region of Interest rew end.  */
    int cs; /*!< Region of Interest columns start.  */
    int ce; /*!< Region of Interest columns end.  */
    int size; /*!< Size of Matrix (currently not utilized. To be used for optimized array creation.  */
    element *Mat; /*!< Matrix data.  */
} mlMat;

mlMat * mlNewMat(int size);
mlMat * mlCopyToNewMat(const mlMat *src, int size);
void mlCopyToExistingMat(const mlMat *src, mlMat **dest, int size);
int mlIsArrEquals(const element *arr1, const element *arr2, const int size);
void mlDisposeMat(mlMat **mat);

#endif //MATRIXOPERATIONS_MATRIX_H
