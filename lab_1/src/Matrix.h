#ifndef AA
#define AA

typedef struct Matrix {
    struct MatrixLine* matrix;
    int n;
} Matrix;

typedef struct MatrixLine {
    int* arr;
    int m;
} MatrixLine;

void matrixDestructor(Matrix* matrix);

void printMatrix(Matrix* matrix);

Matrix* processMatrix(Matrix* matrix);

Matrix* readMatrix();

#endif