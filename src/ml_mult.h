//
// Created by gilmichael on 1/29/2016.
//

#ifndef MATRIXOPERATIONS_ML_MULT_H
#define MATRIXOPERATIONS_ML_MULT_H

#include <time.h>
#include "ml_mat.h"
#include "ml_display.h"

void mlMultiplyStrassen(const mlMat *A, const mlMat *B, mlMat **C, int size, int offset, int request);
void mlAddMat(const mlMat *, const mlMat *, mlMat **, int);
void mlSubtractMat(const mlMat *m1, const mlMat *m2, mlMat **m3, int size);
void mlMultiplySequential(const element *A, const element *B, element *C, int size);

#endif //MATRIXOPERATIONS_ML_MULT_H
