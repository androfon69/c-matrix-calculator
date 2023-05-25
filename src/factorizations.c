#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"
#include "../include/matrix.h"
#include "../include/factorizations.h"

void crout(MatrixList *list, char *matName) {
    Matrix *mat = isMatInList(list, matName);

    if (mat == NULL) {
        printf("Matrix %s doesn't exist!\n", matName);
        return;
    }

    if(mat->rows != mat->cols) {
        printf("Can't perform LU decomposition on non-square matrix\n");
        return;
    }

    char nameBuff[256];
    int retResult;

    do {
        printf("Enter a name for the Lower matrix:\n");
        scanf("%s", nameBuff);
        clearInput();

        if (!strcmp(nameBuff, matName)) {
            printf("Matrix name can't be the same as input matrix!\n");
            retResult = 0;
        }
        else {
            retResult = isNameValid(list, nameBuff);
        }
    } while (retResult == 0);

    Matrix *L = allocMatrix(mat->rows, mat->cols, nameBuff);

    do {
        printf("Enter a name for the Upper matrix:\n");
        scanf("%s", nameBuff);
        clearInput();

        if (!strcmp(nameBuff, matName)) {
            printf("Matrix name can't be the same as input matrix!\n");
            retResult = 0;
        }
        else {
            retResult = isNameValid(list, nameBuff);
        }
    } while (retResult == 0);

    Matrix *U = allocMatrix(mat->rows, mat->cols, nameBuff);

    int i, j, p, k;
    int size = mat->rows;

    /* Initializing L and U matrices with 0 */
    for(i = 0; i < size; ++i) {
        for(j = 0; j < size; ++j) {
            L->elems[i][j] = 0;
            U->elems[j][i] = 0;
        }
    }

    /* Initializing U's diagonal with 1 */
    for(i = 0; i < size; i++) {
        U->elems[i][i] = 1;
    }

    /* Factorization algorithm */
    for(p = 0; p < size; p++) {
        for(i = p; i < size; i++) {
            int sum = 0;

            for(k = 0; k < p; k++) {
                sum += L->elems[i][k] * U->elems[k][p];
            }

            L->elems[i][p] = mat->elems[i][p] - sum;
        }

        for(j = p; j < size; j++) {
            int sum = 0;

            for(k = 0; k < p; k++) {
                sum = sum + L->elems[p][k] * U->elems[k][j];
            }

            U->elems[p][j] = (mat->elems[p][j] - sum) / L->elems[p][p];
        }
    }

    insertMatrix(list, L);
    insertMatrix(list, U);

    printMatrix(list, L->name);
    printf("\n");
    printMatrix(list, U->name);
}
