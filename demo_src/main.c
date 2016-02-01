#include <stdio.h>
#include <math.h>
#include <time.h>
#include "ml_mult.h"

int main() {
    for (int size = 2; size <= 4096; size*=2){
        int next = (element) pow(2, ceil(log(size) / log(2)));

        mlMat *mD;
        mlMat *mE;
        mlMat *mF;
        mlMat *mG;

        mD = mlNewMat(size);
        mE = mlNewMat(size);
        mF = mlNewMat(size);
        mG = mlNewMat(size);

        for (int i=0; i<size*size; i++){
            mD->Mat[i] = i+1;
            mE->Mat[i] = i+1;
        }

        clock_t start = clock(), diff;
        mlMultiplySequential(mD->Mat, mE->Mat, mG->Mat, size);
        diff = clock() - start;
        long msecSeq = diff * 1000 / CLOCKS_PER_SEC;

        start = clock();
        mlMultiplyStrassen(mD, mE, &mF, size, 0, 0);
        diff = clock() - start;
        long msecStrassen = diff * 1000 / CLOCKS_PER_SEC;

        printf("size: %6d Actual Size: %6d ", next, size);
        printf("Time Conventional : %10ld ms Time Conventional Strassen: %10d ms ", msecSeq, msecStrassen);
        printf("Result: %d\n", mlIsArrEquals(mG->Mat, mF->Mat, size));
        if (!mlIsArrEquals(mG->Mat, mF->Mat, size)){
            mlPrintMatArray(mD->Mat, size);
            mlPrintMatArray(mE->Mat, size);
            mlPrintMatArray(mG->Mat, size);
            mlPrintMatArray(mF->Mat, size);
            mlPrintCompare(mG->Mat, mF->Mat, size);
        }

        mlDisposeMat(&mD);
        mlDisposeMat(&mE);
        mlDisposeMat(&mF);
        mlDisposeMat(&mG);
    }

    return 0;
}
