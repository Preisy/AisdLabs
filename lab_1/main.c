#include "stdio.h"

#include "Matrix.h"

int main() {
    Matrix* matrix = readMatrix();
    printf("\n------------------------\n");
    printMatrix(matrix);

    printf("------------------------\n");

    Matrix* newMatrix = processMatrix(matrix);
    printMatrix(newMatrix);

    matrixDestructor(matrix);
    matrixDestructor(newMatrix);

    return 0;
}
