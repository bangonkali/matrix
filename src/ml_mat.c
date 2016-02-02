//
// Created by Bangonkali on 1/23/2016.
//

#include "ml_mat.h"

/** Initializes a new Matrix.
 * Initializes the Matrix using malloc and then preparing the array using calloc.
 * @param size Gets the size of the Matrix to Initialize.
 * @return pointer to the initialized Matrix.
 */
mlMat * mlNewMat(int size) {
    mlMat *matrix = malloc (sizeof (struct _Matrix));
    if (matrix == NULL) {
        printf("Error allocating memory!\n"); //print an error message
        exit(EXIT_FAILURE);
    }

    matrix->Mat = (element*) calloc ((size_t) (size * size), sizeof(element));
    if (matrix->Mat == NULL) {
        printf("Error allocating memory!\n"); //print an error message
        exit(EXIT_FAILURE);
    }

    matrix->re = size - 1;
    matrix->ce = size - 1;
    matrix->cs = 0;
    matrix->rs = 0;
    matrix->size = size;

    return matrix;
}

/** Initializes a new Matrix and copies contents from another matrix.
 * Initializes the Matrix using malloc and then preparing the array using calloc. Also copies the source matrix to the new matrix.
 * @param src Gets the source matrix.
 * @param size Gets the size of the Matrix to Initialize.
 * @return pointer to the initialized Matrix.
 */
mlMat * mlCopyToNewMat(const mlMat *src, int size){
    mlMat *matrix = malloc (sizeof (struct _Matrix));
    if (matrix == NULL) {
        printf("Error allocating memory!\n"); //print an error message
        exit(EXIT_FAILURE);
    }

    element *arr = NULL;
    arr = (element*) calloc ((size_t) (size * size), sizeof(element));
    if (arr == NULL) {
        printf("Error allocating memory!\n"); //print an error message
        exit(EXIT_FAILURE);
    }

    matrix->Mat = arr;
    matrix->re = src->re;
    matrix->ce = src->ce;
    matrix->cs = src->cs;
    matrix->rs = src->rs;
    matrix->size = src->size;

    for (int i = 0; i < size * size; i++){
        matrix->Mat[i] = src->Mat[i];
    }

    return matrix;
}

/** Copies content from another matrix and moves them to another existing matrix.
 * Copies content from another matrix and moves them to another existing matrix.
 * @param src Gets the source matrix.
 * @param dest Sets the *pointer to the destination matrix.
 * @param size Gets the size of the Matrix to Initialize.
 * @return void
 */
void mlCopyToExistingMat(const mlMat *src, mlMat **dest, int size){
    (*dest)->re = src->re;
    (*dest)->ce = src->ce;
    (*dest)->cs = src->cs;
    (*dest)->rs = src->rs;
    (*dest)->size = src->size;

    for (int i = 0; i < size * size; i++){
        (*dest)->Mat[i] = src->Mat[i];
    }
}

/** Compares equality of two matrix.
 * Gets two arrays and compares each element with the other.
 * @param arr1 First array
 * @param arr2 Second array
 * @param size Gets the size of the arrays to compare.
 * @return the equality. 0 if unequal and 1 if equal.
 */
int mlIsArrEquals(const element *arr1, const element *arr2, const int size) {
    for (int i = 0; i < size * size; i++) {
        if (arr1[i] != arr2[i]) return 0;
    }

    return 1;
}

/** Disposes a Matrix array
 * Disposes the Matrix object and the array within it.
 * @param mat tha *pointer to the matrix to dispose.
 */
void mlDisposeMat(mlMat **mat){
    (*mat)->cs = 0;
    (*mat)->ce = 0;
    (*mat)->rs = 0;
    (*mat)->re = 0;
    (*mat)->size = 0;
    free((*mat)->Mat);
    free(*mat);
}