#include "stdio.h"

#include "Matrix.h"

void printMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->n; ++i) {
        for (int j = 0; j < matrix->matrix[i].m; ++j) {
            printf("%d ", matrix->matrix[i].arr[j]);
        }
        printf("\n");
    }
}

//345 6543 3245 563433
//3543 	 3465	 343456
//132454 	 	 	 67545  5643 76 5 	 	 5643546 54