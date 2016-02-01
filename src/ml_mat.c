//
// Created by Bangonkali on 1/23/2016.
//

#include "ml_mat.h"

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

int mlIsArrEquals(const element *arr1, const element *arr2, const int size) {
    for (int i = 0; i < size * size; i++) {
        if (arr1[i] != arr2[i]) return 0;
    }

    return 1;
}

void mlInitZeroes(element *array, int size) {
    for (int i = 0; i < size * size; i++) {
        array[i] = 0;
    }
}

void mlInitMat(element **array, int size) {
    *array = NULL;
    *array = (element*) calloc ((size_t) (size * size), sizeof(element));
    if (*array == NULL) {
        printf("Error allocating memory!\n"); //print an error message
        exit(EXIT_FAILURE);
    }
}

void mlDisposeMatArray(element **array) {
    free(*array);
    *array = NULL;
}

void mlDisposeMat(mlMat **mat){
    (*mat)->cs = 0;
    (*mat)->ce = 0;
    (*mat)->rs = 0;
    (*mat)->re = 0;
    (*mat)->size = 0;
    free((*mat)->Mat);
    free(*mat);
}