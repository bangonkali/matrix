//
// Created by gilmichael on 1/29/2016.
//

#include "ml_mult.h"

void mlMultiplyStrassen(const mlMat *A, const mlMat *B, mlMat **C, int size, int offset, int request) {
//    mlPrintSpaces(offset);
//    printf("offset: %2.2d request: %2.2d\n", offset, request);


    int m1_rows, m1_cols;
    int rows, cols;
    int n = A->re - A->rs;
    int n2 = B->re - B->rs;

    mlMat *A11, *A12, *A21, *A22, *B11, *B12, *B21, *B22;
    mlMat *M1, *M2, *M3, *M4, *M5, *M6, *M7;
    mlMat *C11, *C12, *C21, *C22;

    mlMat *PP1, *PP2, *PP3, *PP4, *PP5, *PP6;
    mlMat *PM1, *PM2, *PM3, *PM4;
    mlMat *Q1P1, *Q1M1, *Q4P1, *Q4M1;

    if (n != n2) {
        printf("Error State.\n");
        exit(EXIT_FAILURE);
    }

    if (n <= 1 || n2 <= 1) {

        if (n != n2) {
            printf("Error State.\n");
            exit(EXIT_FAILURE);
        }

        element a, b, c, d, e, f, g, h;
        mlCopyToExistingMat(A, C, size);

        (*C)->cs = 0;
        (*C)->ce = 1;
        (*C)->rs = 0;
        (*C)->re = 1;

        #pragma omp parallel sections
        {
            #pragma omp section
            { a = A->Mat[(A->rs) * size + (A->cs)]; }

            #pragma omp section
            { c = A->Mat[(A->rs + 1) * size + (A->cs)]; }

            #pragma omp section
            { b = A->Mat[(A->rs) * size + (A->cs + 1)]; }

            #pragma omp section
            { d = A->Mat[(A->rs + 1) * size + (A->cs + 1)]; }

            #pragma omp section
            { e = B->Mat[(B->rs) * size + (B->cs)]; }

            #pragma omp section
            { g = B->Mat[(B->rs + 1) * size + (B->cs)]; }

            #pragma omp section
            { f = B->Mat[(B->rs) * size + (B->cs + 1)]; }

            #pragma omp section
            { h = B->Mat[(B->rs + 1) * size + (B->cs + 1)]; }
        }

        (*C)->Mat[(((*C)->rs) * size) + ((*C)->cs)] = (a * e) + (b * g);
        (*C)->Mat[(((*C)->rs + 1) * size) + ((*C)->cs)] = (c * e) + (d * g);
        (*C)->Mat[(((*C)->rs) * size) + ((*C)->cs + 1)] = (a * f) + (b * h);
        (*C)->Mat[(((*C)->rs + 1) * size) + ((*C)->cs + 1)] = (c * f) + (d * h);

        return;
    }

    if (A->cs < 0 || A->ce < 1 || B->cs < 0 || B->ce < 1 || A->rs < 0 || A->re < 1 || B->rs < 0 || B->re < 1) {
        printf("Error State.\n");
        exit(EXIT_FAILURE);
    }

    mlCopyToExistingMat(A, C, size);

    A11 = mlCopyToNewMat(A, size);
    A12 = mlCopyToNewMat(A, size);
    A21 = mlCopyToNewMat(A, size);
    A22 = mlCopyToNewMat(A, size);

    B11 = mlCopyToNewMat(B, size);
    B12 = mlCopyToNewMat(B, size);
    B21 = mlCopyToNewMat(B, size);
    B22 = mlCopyToNewMat(B, size);

    C11 = mlNewMat(size);
    C12 = mlNewMat(size);
    C21 = mlNewMat(size);
    C22 = mlNewMat(size);

    M1 = mlNewMat(size);
    M2 = mlNewMat(size);
    M3 = mlNewMat(size);
    M4 = mlNewMat(size);
    M5 = mlNewMat(size);
    M6 = mlNewMat(size);
    M7 = mlNewMat(size);

    PP1 = mlNewMat(size);
    PP2 = mlNewMat(size);
    PP3 = mlNewMat(size);
    PP4 = mlNewMat(size);
    PP5 = mlNewMat(size);
    PP6 = mlNewMat(size);

    PM1 = mlNewMat(size);
    PM2 = mlNewMat(size);
    PM3 = mlNewMat(size);
    PM4 = mlNewMat(size);

    Q1P1 = mlNewMat(size);
    Q4P1 = mlNewMat(size);
    Q1M1 = mlNewMat(size);
    Q4M1 = mlNewMat(size);

    A11->rs = A->rs; // Fixed;
    A11->re = (((A->re - A->rs + 1) / 2) + A->rs) - 1; // Fixed
    A11->cs = A->cs; // Fixed
    A11->ce = (((A->ce - A->cs + 1) / 2) + A->cs) - 1; // Fixed

    A12->rs = A->cs; // Fixed
    A12->re = (((A->re - A->rs + 1) / 2) + A->rs) - 1; // Fixed
    A12->cs = ((A->ce - A->cs + 1) / 2) + A->cs; // Fixed
    A12->ce = A->ce; // Fixed

    A21->rs = ((A->re - A->rs + 1) / 2) + A->rs; // Fixed
    A21->re = A->re; // Fixed
    A21->cs = A->cs; // Fixed
    A21->ce = (((A->ce - A->cs + 1) / 2) + A->cs) - 1; // Fixed

    A22->rs = ((A->re - A->rs + 1) / 2) + A->rs; // Fixed
    A22->re = A->re; //
    A22->cs = ((A->ce - A->cs + 1) / 2) + A->cs; // Fixed
    A22->ce = A->ce;

    B11->rs = B->rs; // Fixed;
    B11->re = (((B->re - B->rs + 1) / 2) + B->rs) - 1; // Fixed
    B11->cs = B->cs; // Fixed
    B11->ce = (((B->ce - B->cs + 1) / 2) + B->cs) - 1; // Fixed

    B12->rs = B->cs; // Fixed
    B12->re = (((B->re - B->rs + 1) / 2) + B->rs) - 1; // Fixed
    B12->cs = ((B->ce - B->cs + 1) / 2) + B->cs; // Fixed
    B12->ce = B->ce; // Fixed

    B21->rs = ((B->re - B->rs + 1) / 2) + B->rs; // Fixed
    B21->re = B->re; // Fixed
    B21->cs = B->cs; // Fixed
    B21->ce = (((B->ce - B->cs + 1) / 2) + B->cs) - 1; // Fixed

    B22->rs = ((B->re - B->rs + 1) / 2) + B->rs; // Fixed
    B22->re = B->re; //
    B22->cs = ((B->ce - B->cs + 1) / 2) + B->cs; // Fixed
    B22->ce = B->ce;


    // M1 = (A11 + A22) (B11 + B22)
    #pragma omp task
    mlAddMat(A11, A22, &PP1, size);
    #pragma omp task
    mlAddMat(B11, B22, &PP2, size);
    // M2 = (A21 + A22) B11
    #pragma omp task
    mlAddMat(A21, A22, &PP3, size);
    // M5 = (A11 + A12) B22
    #pragma omp task
    mlAddMat(A11, A12, &PP4, size);
    // M6 = (A21 – A11) (B11 + B12)
    #pragma omp task
    mlAddMat(B11, B12, &PP5, size);
    // M7 = (A12 – A22) (B21 + B22)
    #pragma omp task
    mlAddMat(B21, B22, &PP6, size);
    #pragma omp taskwait

    // M3 = A11 (B12 – B22)
    #pragma omp task
    mlSubtractMat(B12, B22, &PM1, size);
    // M4 = A22 (B21 – B11)
    #pragma omp task
    mlSubtractMat(B21, B11, &PM2, size);
    // M6 = (A21 – A11) (B11 + B12)
    #pragma omp task
    mlSubtractMat(A21, A11, &PM3, size);
    // M7 = (A12 – A22) (B21 + B22)
    #pragma omp task
    mlSubtractMat(A12, A22, &PM4, size);
    #pragma omp taskwait

    #pragma omp task
    mlMultiplyStrassen(PP1, PP2, &M1, size, offset + 1, 1);
    #pragma omp task
    mlMultiplyStrassen(PP3, B11, &M2, size, offset + 1, 2);
    #pragma omp task
    mlMultiplyStrassen(A11, PM1, &M3, size, offset + 1, 3);
    #pragma omp task
    mlMultiplyStrassen(A22, PM2, &M4, size, offset + 1, 4);
    #pragma omp task
    mlMultiplyStrassen(PP4, B22, &M5, size, offset + 1, 5);
    #pragma omp task
    mlMultiplyStrassen(PM3, PP5, &M6, size, offset + 1, 6);
    #pragma omp task
    mlMultiplyStrassen(PM4, PP6, &M7, size, offset + 1, 7);
    #pragma omp taskwait

    mlDisposeMat(&PP1);
    mlDisposeMat(&PP2);
    mlDisposeMat(&PP3);
    mlDisposeMat(&PP4);
    mlDisposeMat(&PP5);
    mlDisposeMat(&PP6);

    mlDisposeMat(&A11);
    mlDisposeMat(&A12);
    mlDisposeMat(&A21);
    mlDisposeMat(&A22);
    mlDisposeMat(&B11);
    mlDisposeMat(&B12);
    mlDisposeMat(&B21);
    mlDisposeMat(&B22);

    mlDisposeMat(&PM1);
    mlDisposeMat(&PM2);
    mlDisposeMat(&PM3);
    mlDisposeMat(&PM4);

//    if (M1->re - M1->rs == 3) {
//        printf("Debug M1 Size: %d\n", M1->re - M1->rs);
//        mlPrintMat(M1);
//        printf("Debug M2 Size: %d\n", M2->re - M2->rs);
//        mlPrintMat(M2);
//        printf("Debug M3 Size: %d\n", M3->re - M3->rs);
//        mlPrintMat(M3);
//        printf("Debug M4 Size: %d\n", M4->re - M4->rs);
//        mlPrintMat(M4);
//        printf("Debug M5 Size: %d\n", M5->re - M5->rs);
//        mlPrintMat(M5);
//        printf("Debug M6 Size: %d\n", M6->re - M6->rs);
//        mlPrintMat(M6);
//        printf("Debug M7 Size: %d\n", M7->re - M7->rs);
//        mlPrintMat(M7);
//
//        printf("\n");
//    }

    mlAddMat(M1, M4, &Q1P1, size);
    mlSubtractMat(Q1P1, M5, &Q1M1, size);
    mlAddMat(Q1M1, M7, &C11, size);

    mlAddMat(M3, M5, &C12, size);

    mlAddMat(M2, M4, &C21, size);

    mlAddMat(M1, M3, &Q4P1, size);
    mlSubtractMat(Q4P1, M2, &Q4M1, size);
    mlAddMat(Q4M1, M6, &C22, size);

    mlDisposeMat(&Q1P1);
    mlDisposeMat(&Q4P1);
    mlDisposeMat(&Q1M1);
    mlDisposeMat(&Q4M1);

    mlDisposeMat(&M1);
    mlDisposeMat(&M2);
    mlDisposeMat(&M3);
    mlDisposeMat(&M4);
    mlDisposeMat(&M5);
    mlDisposeMat(&M6);
    mlDisposeMat(&M7);


    for (m1_cols = C11->rs, cols = 0; m1_cols <= C11->re; m1_cols++, cols++)
        for (m1_rows = C11->cs, rows = 0; m1_rows <= C11->ce; m1_rows++, rows++)
            (*C)->Mat[(cols * size) + rows] = C11->Mat[(m1_cols * size) + m1_rows];

    for (m1_cols = C21->rs, cols = ((n + 1) / 2); m1_cols <= C21->re; m1_cols++, cols++)
        for (m1_rows = C21->cs, rows = 0; m1_rows <= C21->ce; m1_rows++, rows++)
            (*C)->Mat[(cols * size) + rows] = C21->Mat[(m1_cols * size) + m1_rows];

    for (m1_cols = C12->rs, cols = 0; m1_cols <= C12->re; m1_cols++, cols++)
        for (m1_rows = C12->cs, rows = ((n + 1) / 2); m1_rows <= C12->ce; m1_rows++, rows++)
            (*C)->Mat[(cols * size) + rows] = C12->Mat[(m1_cols * size) + m1_rows];

    for (m1_cols = C22->rs, cols = ((n + 1) / 2); m1_cols <= C22->re; m1_cols++, cols++)
        for (m1_rows = C22->cs, rows = ((n + 1) / 2); m1_rows <= C22->ce; m1_rows++, rows++)
            (*C)->Mat[(cols * size) + rows] = C22->Mat[(m1_cols * size) + m1_rows];

    (*C)->rs=0;
    (*C)->cs=0;
    (*C)->re=n;
    (*C)->ce=n;

    mlDisposeMat(&C11);
    mlDisposeMat(&C12);
    mlDisposeMat(&C21);
    mlDisposeMat(&C22);

    return;
}

void mlAddMat(const mlMat *m1, const mlMat *m2, mlMat **m3, int size) {
    int m1_rows, m1_cols;
    int m2_rows, m2_cols;
    int rows, cols;
    int n = m1->re - m1->rs;

    (*m3)->rs = (*m3)->cs = 0;
    (*m3)->re = (*m3)->ce = n;
    (*m3)->size = m1->size;

    for (m1_rows = m1->rs, m2_rows = m2->rs, rows = 0; m1_rows <= m1->re; m1_rows++, m2_rows++, rows++) {
        for (m1_cols = m1->cs, m2_cols = m2->cs, cols = 0; m1_cols <= m1->ce; m1_cols++, m2_cols++, cols++) {
            (*m3)->Mat[rows * size + cols] = m1->Mat[m1_rows * size + m1_cols] + m2->Mat[m2_rows * size + m2_cols];
            /*(*m3)->Mat[cols * size + rows] = m1->Mat[m1_cols * size + m1_rows] + m2->Mat[m2_cols * size + m2_rows];*/
        }
    }
}

void mlSubtractMat(const mlMat *m1, const mlMat *m2, mlMat **m3, int size) {
    int m1_rows, m1_cols;
    int m2_rows, m2_cols;
    int rows, cols;
    int n = m1->re - m1->rs;

    (*m3)->rs = (*m3)->cs = 0;
    (*m3)->re = (*m3)->ce = n;
    (*m3)->size = m1->size;

    for (m1_rows = m1->rs, m2_rows = m2->rs, rows = 0; m1_rows <= m1->re; m1_rows++, m2_rows++, rows++) {
        for (m1_cols = m1->cs, m2_cols = m2->cs, cols = 0; m1_cols <= m1->ce; m1_cols++, m2_cols++, cols++) {
            (*m3)->Mat[rows * size + cols] = m1->Mat[m1_rows * size + m1_cols] - m2->Mat[m2_rows * size + m2_cols];
            /*(*m3)->Mat[cols * size + rows] = m1->Mat[m1_cols * size + m1_rows] - m2->Mat[m2_cols * size + m2_rows];*/
        }
    }
}

void mlMultiplySequential(const element *A, const element *B, element *C, int size) {
    for (int rows = 0; rows < size; rows++) {
        for (int cols = 0; cols < size; cols++) {
            C[rows * size + cols] = 0.0;
            for (int k = 0; k < size; k++) {
                C[rows * size + cols] += A[rows * size + k] * B[k * size + cols];
            }
        }
    }
}