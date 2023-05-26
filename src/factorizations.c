#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
        else if (!strcmp(nameBuff, L->name)) {
            printf("Matrix name can't be the same as Lower matrix!\n");
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

void qr(MatrixList *list, char *matName) {
    register int  i, j, k;

    Matrix *mat = isMatInList(list, matName);

    if (mat == NULL) {
        printf("Matrix %s doesn't exist!\n", matName);
        return;
    }

    /* Agorithm only works for square matrices */
    if(mat->rows != mat->cols) {
        printf("Matrix %s is not square!\n", mat->name);
        return;
    }

    char nameBuff[256];
    int retResult;

    do {
        printf("Enter a name for the Q matrix:\n");
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

    /* Allocating Q matrix */
    Matrix *Q = allocMatrix(mat->rows, mat->cols, nameBuff);

    do {
        printf("Enter a name for the R matrix:\n");
        scanf("%s", nameBuff);
        clearInput();

        if (!strcmp(nameBuff, matName)) {
            printf("Matrix name can't be the same as input matrix!\n");
            retResult = 0;
        }
        else if (!strcmp(nameBuff, Q->name)){
            printf("Matrix name can't be the same as Q!\n");
        }
        else {
            retResult = isNameValid(list, nameBuff);
        }
    } while (retResult == 0);

    /* Allocating R matrix */
    Matrix *R = allocMatrix(mat->rows, mat->cols, nameBuff);

    /* Initializing matrices */
    for(i = 0; i < mat->rows; ++i) {
        for(j = 0; j < mat->rows; ++j) {
            Q->elems[i][j] = 0.0;
            R->elems[j][i] = 0.0;
        }
    }

    /* Copying mat into R */
    for (i = 0; i < mat->rows; ++i) {
        for (j = 0; j < mat->rows; ++j) {
            R->elems[i][j] = mat->elems[i][j];
        }
    }

    /* Iterating over columns of mat */
    for (k = 0; k < mat->rows; ++k) {
        /* Calculating norm of column k in R */
        double norm = 0.0;
        for (i = k; i < mat->rows; ++i) {
            norm += R->elems[i][k] * R->elems[i][k];
        }
        norm = sqrt(norm);

        if (norm == 0.0) {
            printf("QR impossible, det(R) = 0 \n");
            freeMatrix(R);
            freeMatrix(Q);
            return;
        }

        /* Updating diagonal element of R */
        if (R->elems[k][k] < 0.0) {
            norm = -norm;
        }
        R->elems[k][k] += norm;

        /* Getting column k of Q */
        for (i = k; i < mat->rows; ++i) {
            Q->elems[i][k] = R->elems[i][k] / norm;
        }

        /* Updating R */
        for (j = k + 1; j < mat->rows; ++j) {
            double dot_product = 0.0;
            for (i = k; i < mat->rows; ++i) {
                dot_product += Q->elems[i][k] * R->elems[i][j];
            }
            for (i = k; i < mat->rows; ++i) {
                R->elems[i][j] -= 2.0 * Q->elems[i][k] * dot_product;
            }
        }
    }

    insertMatrix(list, Q);
    insertMatrix(list, R);

    printMatrix(list, Q->name);
    printf("\n");
    printMatrix(list, R->name);

}
