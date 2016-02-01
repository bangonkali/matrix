#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "ml_mat.h"

void mlPrintMatArray(element *array, int size);
void mlPrintMat(mlMat *mat);
void mlPrintCompare(const element *arr1, const element *arr2, const int size);
void mlPrintSpaces(int n);

#endif