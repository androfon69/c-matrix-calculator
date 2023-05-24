#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include "../include/matrix.h"

int main() {
    MatrixList *list = initMatList();

    Matrix *mat = readMatrix(list);

    Matrix *mat2 = readMatrix(list);

    for (int i = 0; i < mat->rows; ++i) {
        for (int j = 0; j < mat->cols; ++j) {
            printf("%lf ", mat->elems[i][j]);
        }
        printf("\n");
    }

    if (isMatInList(list, "Bala")) {
        printf("da\n");
    }

    mat = isMatInList(list, "Baba");

    deleteMatrix(list, mat, freeMatrix);

    printMatrixList(list);

    freeMatList(list, freeMatrix);

    return 0;
}
