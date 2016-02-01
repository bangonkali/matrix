#include "ml_display.h"

void mlPrintMat(mlMat *mat) {
    printf("Matrix: rs: %d re:%d cs:%d ce:%d sz:%d\n",
           mat->rs,
           mat->re,
           mat->cs,
           mat->ce,
           mat->size
    );
    mlPrintMatArray(mat->Mat, mat->size);
}

void mlPrintMatArray(element *array, int size) {
    int i, j, l = size * size;

//    for (int k = 0; k < l; ++k) {
//        if (l-1 == k)
//            printf("%g\n", array[k]);
//        else
//            printf("%g, ", array[k]);
//    }


    printf("{\n");
    for (i=0 ; i<size ; i++) {

        printf("{ ");

        for (j=0 ; j<size ; j++){

            if (j != size -1)
                printf("%5d, ", array[i * size + j]);
            else
                printf("%5d ", array[i * size + j]);
        }

        if (i != size - 1)
            printf("},\n");
        else
            printf("}");
    }

    printf("\n}\n\n");

    return;
}

void mlPrintCompare(const element *arr1, const element *arr2, const int size){
    for (int i=0 ; i < size ; i++) {
        for (int j=0 ; j<size ; j++){

            if (arr1[i * size + j] == arr2[i * size + j])
                printf("O");
            else
                printf("X");

        }

        printf("\n");
    }
}

void mlPrintSpaces(int n){
    for (int i=0; i<n; i++){
        printf("  ");
    }
}