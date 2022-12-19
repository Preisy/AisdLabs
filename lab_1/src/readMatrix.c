#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "Matrix.h"


int validate(char c);

int readInt(char *c);

void pushBackInt(int **arr, int el, int *len, int *bufLen);

void pushBackLine(MatrixLine **arr, MatrixLine *el, int *len, int *bufLen);

int findLineBreaker(char *c);

Matrix *readMatrix() {
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix)); // удалить
    char c = (char) getchar();
    int nBufLen = 10, nLen = 0;

    MatrixLine *bufLines = (MatrixLine *) malloc(sizeof(MatrixLine) * nBufLen);
    for (int i = 0;; ++i) {
        int mBufLen = 10, mLen = 0;
        MatrixLine bufLine;
        bufLine.arr = (int *) malloc(sizeof(int) * mBufLen);
        for (int j = 0;; ++j) {
            pushBackInt(&bufLine.arr, readInt(&c), &mLen, &mBufLen);

            int res = findLineBreaker(&c);
            if (res == 1 || res == -1) {
                bufLine.arr = (int *) realloc(bufLine.arr, sizeof(int) * mLen);
                break;
            }
        }
        bufLine.m = mLen;
        pushBackLine(&bufLines, &bufLine, &nLen, &nBufLen);

        int res = findLineBreaker(&c);
        if (res == 1) {
            c = (char) getchar();
            if (findLineBreaker(&c) == -1) {
                bufLines = (MatrixLine *) realloc(bufLines, sizeof(MatrixLine) * nLen);
                break;
            }
        }
        else if (res == -1) {
            bufLines = (MatrixLine *) realloc(bufLines, sizeof(MatrixLine) * nLen);
            break;
        }
    }
    matrix->matrix = bufLines;
    matrix->n = nLen;
    return matrix;
}

int findLineBreaker(char *c) {
    while (*c == ' ' || *c == '\t' || *c == '\n' || *c == EOF) {
        if (*c == EOF)
            return -1;
        if (*c == '\n')
            return 1;
        *c = (char) getchar();
    }
    return 0;
}

void pushBackInt(int **arr, int el, int *len, int *bufLen) {
    if (*len >= *bufLen) {
        *bufLen *= 2;
        *arr = (int *) realloc(*arr, sizeof(int) * *bufLen);
    }
    (*arr)[*len] = el;
    ++(*len);
}

void pushBackLine(MatrixLine **arr, MatrixLine *el, int *len, int *bufLen) {
    if (*len >= *bufLen) {
        *bufLen *= 2;
        *arr = (MatrixLine *) realloc(*arr, sizeof(MatrixLine) * *bufLen);
    }
    memcpy((*arr) + *len, el, sizeof(MatrixLine));
//    (*arr)->matrix[*len] = *el;
    ++(*len);
}

int readInt(char *c) {
    int sign = 1;
    while (*c == ' ' || *c == '\t')
        *c = (char) getchar();
    if (*c == '-') {
        sign = -1;
        *c = (char) getchar();
    }

    int res = 0;
    while (validate(*c)) {
        res = res * 10 + (int) (*c - '0');
        *c = (char) getchar();
    }
    if (res == 0) exit(-1);
    else return sign * res;
}

int validate(char c) {
    if ('0' <= c && c <= '9') return 1;
    else return 0;
}
