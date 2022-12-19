#include "stdlib.h"

#include "Matrix.h"

int checkOrder(int n);
//#ifndef MATRIX_PUSH_BACK
//#define MATRIX_PUSH_BACK
void pushBack(int **arr, int el, int *len, int *bufLen) {
    if (*len >= *bufLen) {
        *bufLen *= 2;
        *arr = (int *) realloc(*arr, sizeof(int) * *bufLen);
    }
    (*arr)[*len] = el;
    ++(*len);
}
//#endif

Matrix* processMatrix(Matrix* matrix) {
    Matrix* newMatrix = (Matrix*) malloc(sizeof (Matrix));
    newMatrix->matrix = (MatrixLine*) malloc(sizeof (MatrixLine) * matrix->n);
    newMatrix->n = matrix->n;
    for (int i = 0; i < matrix->n; ++i) {
        int mIBufLen = 10, mILen = 0;
        int* bufArr = (int *) malloc(sizeof(int) * mIBufLen);
        for (int j = 0; j < matrix->matrix[i].m; ++j) {
            if (checkOrder(matrix->matrix[i].arr[j]))
                pushBack(&bufArr, matrix->matrix[i].arr[j], &mILen, &mIBufLen);
        }
        bufArr = (int*) realloc(bufArr, sizeof (int) * mILen);
        newMatrix->matrix[i].arr = bufArr;
        newMatrix->matrix[i].m = mILen;
    }

    return newMatrix;
}

int checkOrder(int n) {
    int prev = n % 10;
    if (n < 0) n *= -1;
    while (n > 10) {
        int cur = n % 10;
        if (cur > prev) {
            return 0;
        }
        n = n / 10;
        prev = cur;
    }
    if (n > prev) return 0;
    else return 1;
}


