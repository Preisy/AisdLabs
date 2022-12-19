#include "stdlib.h"

#include "Matrix.h"

void matrixDestructor(Matrix* matrix) {
    for (int i = 0; i < matrix->n; ++i) {
        free(matrix->matrix[i].arr);
    }
    free(matrix->matrix);
    free(matrix);
}