//
// Created by Bangonkali on 1/23/2016.
//

#ifndef MATRIXOPERATIONS_MATRIX_H
#define MATRIXOPERATIONS_MATRIX_H

#include <stdlib.h>
#include <stdio.h>

typedef double element;

typedef struct _Matrix {
    int rs;
    int re;
    int cs;
    int ce;
    int size;
    element *Mat;
} mlMat;

typedef struct _MatrixHeader {
    int rs;
    int re;
    int cs;
    int ce;
} mlHeader;

mlMat * mlNewMat(int size);
mlMat * mlCopyToNewMat(const mlMat *src, int size);
void mlCopyToExistingMat(const mlMat *src, mlMat **dest, int size);
int mlIsArrEquals(const element *arr1, const element *arr2, const int size);
void mlInitZeroes(element *array, int size);
void mlInitMat(element **array, int size);
void mlDisposeMatArray(element **array);
void mlDisposeMat(mlMat **mat);

#endif //MATRIXOPERATIONS_MATRIX_H
