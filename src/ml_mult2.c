//
// Created by Bangonkali on 1/31/2016.
//


#include "ml_mult2.h"

void strassen(const element *a, const element *b, element *c, int size) {
    int num = 0;
    int half_size = size / 2;
    int arr_size = half_size * half_size;

    element *p1 = NULL;
    element *p2 = NULL;
    element *p3 = NULL;
    element *p4 = NULL;
    element *p5 = NULL;
    element *p6 = NULL;
    element *p7 = NULL;
    element *temp1 = NULL;
    element *temp2 = NULL;

    if (half_size > 0){
        p1 = (element*) calloc ((size_t) (arr_size), sizeof(element));
        p2 = (element*) calloc ((size_t) (arr_size), sizeof(element));
        p3 = (element*) calloc ((size_t) (arr_size), sizeof(element));
        p4 = (element*) calloc ((size_t) (arr_size), sizeof(element));
        p5 = (element*) calloc ((size_t) (arr_size), sizeof(element));
        p6 = (element*) calloc ((size_t) (arr_size), sizeof(element));
        p7 = (element*) calloc ((size_t) (arr_size), sizeof(element));

        temp1 = (element*) calloc ((size_t) (arr_size), sizeof(element));
        temp2 = (element*) calloc ((size_t) (arr_size), sizeof(element));
    }
    
    int row, col;
    
    if (size >= 2) {    //give recursive calls
        //p1
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp1[row* half_size +col] = a[row* half_size +col] + a[(row + half_size)* half_size +(col + half_size)];
            }
        }
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp2[row* half_size +col] = b[row* half_size +col] + b[(row + half_size)* half_size +(col + half_size)];
            }
        }
        num = half_size;
        strassen(temp1, temp2, p1, half_size);

        // p2
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp1[row* half_size +col] = a[(row + half_size)* half_size +col] + a[(row + half_size)* half_size +(col + half_size)];
            }
        }
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp2[row* half_size +col] = b[row* half_size +col];
            }
        }
        num = half_size;
        strassen(temp1, temp2, p2, half_size);

        //p3
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp1[row* half_size +col] = a[row* half_size +col];
            }
        }
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp2[row* half_size +col] = b[row* half_size +(col + half_size)] - b[(row + half_size)* half_size +(col + half_size)];
            }
        }
        num = half_size;
        strassen(temp1, temp2, p3, half_size);

        //p4
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp1[row* half_size +col] = a[(row + half_size)* half_size +(col + half_size)];
            }
        }
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp2[row* half_size +col] = b[(row + half_size)* half_size +col] - b[row* half_size +col];
            }
        }
        num = half_size;
        strassen(temp1, temp2, p4, half_size);

        //p5
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp1[row* half_size +col] = a[row* half_size +col] + a[row* half_size +(col + half_size)];
            }
        }
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp2[row* half_size +col] = b[(row + half_size)* half_size +(col + half_size)];
            }
        }
        num = half_size;
        strassen(temp1, temp2, p5, half_size);

        //p6
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp1[row* half_size +col] = a[(row + half_size)* half_size +col] - a[row* half_size +col];
            }
        }
        num = half_size;
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp2[row* half_size +col] = b[row* half_size +col] + b[row* half_size +(col + half_size)];
            }
        }
        num = half_size;
        strassen(temp1, temp2, p6, half_size);

        //p7
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp1[row* half_size +col] = a[row* half_size +(col + half_size)] - a[(row + half_size)* half_size +(col + half_size)];
            }
        }
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                temp2[row* half_size +col] = b[(row + half_size)* half_size +col] + b[(row + half_size)* half_size +(col + half_size)];
            }
        }
        num = half_size;
        strassen(temp1, temp2, p7, half_size);

        //c11
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                c[row* half_size +col] = p1[row* half_size +col] + p4[row* half_size +col] - p5[row* half_size +col] + p7[row* half_size +col];
            }
        }

        //c12
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                c[row* half_size +(col + half_size)] = p3[row* half_size +col] + p5[row* half_size +col];
            }
        }

        //c21
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                c[(row + half_size)* half_size +col] = p2[row* half_size +col] + p4[row* half_size +col];
            }
        }

        //c22
        for (row = 0; row < half_size; row++) {
            for (col = 0; col < half_size; col++) {
                c[(row + half_size)* half_size +(col + half_size)] = p1[row* half_size +col] + p3[row* half_size +col] - p2[row* half_size +col] + p6[row* half_size +col];
            }
        }
    }
    else if (size == 1) {
        c[0] = a[0] * b[0];
    }

    if (p1!=NULL) free(p1);
    if (p2!=NULL) free(p2);
    if (p3!=NULL) free(p3);
    if (p4!=NULL) free(p4);
    if (p5!=NULL) free(p5);
    if (p6!=NULL) free(p6);
    if (p7!=NULL) free(p7);
    if (temp1!=NULL) free(temp1);
    if (temp2!=NULL) free(temp2);
}
