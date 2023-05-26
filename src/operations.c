#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "../include/list.h"
#include "../include/matrix.h"
#include "../include/operations.h"

Matrix *multiplication(MatrixList *list, char *matName1, char *matName2) {
    Matrix *mat1 = isMatInList(list, matName1);

    if (mat1 == NULL) {
        printf("Matrix %s doesn't exist!\n", matName1);
        return NULL;
    }

    Matrix *mat2 = isMatInList(list, matName2);

    if (mat2 == NULL) {
        printf("Matrix %s doesn't exist!\n", matName2);
        return NULL;
    }

    if (mat1->cols != mat2->rows) {
        printf("Matrix size mismatch!\n");
        printf("Attempted to multiply matrices of sizes (%d, %d) and (%d, %d)\n",
               mat1->rows, mat1->cols, mat2->rows, mat2->cols);
        
        return NULL;
    }

    char nameBuff[256];
    int retResult;

    do {
        printf("Enter a name for the result matrix:\n");
        scanf("%s", nameBuff);
        clearInput();

        if (!strcmp(nameBuff, matName1) || !strcmp(nameBuff, matName2)) {
            printf("Matrix name can't be the same as input matrices!\n");
            retResult = 0;
        }
        else {
            retResult = isNameValid(list, nameBuff);
        }
    } while (retResult == 0);

    Matrix *newMatrix = allocMatrix(mat1->rows, mat2->cols, nameBuff);
    for (int i = 0; i < newMatrix->rows; ++i) {
        for (int j = 0; j < newMatrix->cols; ++j) {
            newMatrix->elems[i][j] = 0;

            for (int k = 0; k < mat1->cols; ++k) {
                newMatrix->elems[i][j] += mat1->elems[i][k] * mat2->elems[k][j];
            }
        }
    }

    insertMatrix(list, newMatrix);

    return newMatrix;
}

Matrix *addition(MatrixList *list, char *matName1, char *matName2) {
    Matrix *mat1 = isMatInList(list, matName1);

    if (mat1 == NULL) {
        printf("Matrix %s doesn't exist!\n", matName1);
        return NULL;
    }

    Matrix *mat2 = isMatInList(list, matName2);

    if (mat2 == NULL) {
        printf("Matrix %s doesn't exist!\n", matName2);
        return NULL;
    }

    if (mat1->cols != mat2->cols || mat1->rows != mat2->rows) {
        printf("Matrix size mismatch!\n");
        printf("Attempted to add matrices of sizes (%d, %d) and (%d, %d)\n",
               mat1->rows, mat1->cols, mat2->rows, mat2->cols);

        return NULL;
    }

    char nameBuff[256];
    int retResult;

    do {
        printf("Enter a name for the result matrix:\n");
        scanf("%s", nameBuff);
        clearInput();

        if (!strcmp(nameBuff, matName1) || !strcmp(nameBuff, matName2)) {
            printf("Matrix name can't be the same as input matrices!\n");
            retResult = 0;
        }
        else {
            retResult = isNameValid(list, nameBuff);
        }
    } while (retResult == 0);

    Matrix *newMatrix = allocMatrix(mat1->rows, mat1->cols, nameBuff);

    for (int i = 0; i < mat1->rows; ++i) {
        for (int j = 0; j < mat1->cols; ++j) {
            newMatrix->elems[i][j] = mat1->elems[i][j] + mat2->elems[i][j];
        }
    }

    insertMatrix(list, newMatrix);

    return newMatrix;
}

Matrix *transpose(MatrixList *list, char *matName) {
    Matrix *mat = isMatInList(list, matName);

    if (mat == NULL) {
        printf("Matrix doesn't exist!\n");
        return NULL;
    }

    double **transp = malloc(mat->cols * sizeof(double*));
    transp[0] = malloc(mat->cols * mat->rows * sizeof(double));
    for (int i = 1; i < mat->cols; ++i) {
        transp[i] = transp[0] + i * mat->rows;
    }

    for (int i = 0; i < mat->cols; ++i) {
        for (int j = 0; j < mat->rows; ++j) {
            transp[i][j] = mat->elems[j][i];
        }
    }

    int aux = mat->rows;
    mat->rows = mat->cols;
    mat->cols =aux;

    free(mat->elems[0]);
    free(mat->elems);

    mat->elems = transp;

    return mat;
}

double det(MatrixList *list, char *matName, int *matExists) {
    Matrix *mat = isMatInList(list, matName);

    if (mat == NULL) {
        printf("Matrix doesn't exist!\n");
        *matExists = 0;
        return 0;
    }

    if (mat->rows != mat->cols) {
        printf("Can't calculate determinant of non-square matrix\n");
        *matExists = 0;
        return 0;
    }

    *matExists = 1;
    int size = mat->rows;
    double det = 1;

    double **detMat = malloc(size * sizeof(double*));
    for (int i = 0; i < size; ++i) {
        detMat[i] = malloc(size * sizeof(double));
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            detMat[i][j] = mat->elems[i][j];
        }
    }

    /* Gaussian elimination with the partial pivoting method */
    /* At each step, the pivot with the largest absolute value is chosen */

    for (int i = 0; i < size; ++i) {
        double pivot = detMat[i][i];
        int pivotRow = i;

        for (int j = i + 1; j < size; ++j) {
            if (fabs(detMat[j][i]) > fabs(pivot)) {
                pivot = detMat[j][i];
                pivotRow = j;
            }
        }

        if (pivot == 0.0) {
            return 0;
        }

        if (pivotRow != i) {
            double *tempRow = detMat[i];
            detMat[i] =detMat[pivotRow];
            detMat[pivotRow] = tempRow;
            det *= -1;
        }
        det *= pivot;

        for (int j = i + 1; j < size; ++j) {
            for (int k = i + 1; k < size; ++k) {
                detMat[j][k] -= detMat[j][i] * detMat[i][k] / pivot;
            }
        }

    }

    for (int i = 0; i < size; ++i) {
        free(detMat[i]);
    }
    free(detMat);

    return det;
}

double norm(MatrixList *list, char *matName, int *matExists) {
    Matrix *mat = isMatInList(list, matName);

    if (mat == NULL) {
        printf("Matrix doesn't exist!\n");
        *matExists = 0;
        return 0;
    }

    *matExists = 1;
    double result = 0;

    for (int i = 0; i < mat->rows; ++i) {
        for (int j = 0; j < mat->cols; ++j) {
            result += mat->elems[i][j] * mat->elems[i][j];
        }
    }

    result = sqrt(result);

    return result;
}

double trace(MatrixList *list, char *matName, int *matExists) {
    Matrix *mat = isMatInList(list, matName);

    if (mat == NULL) {
        printf("Matrix doesn't exist!\n");
        *matExists = 0;
        return 0;
    }

    if (mat->rows != mat->cols) {
        printf("Can't calculate trace of non-square matrix\n");
        *matExists = 0;
        return 0;
    }

    *matExists = 1;
    double result = 0;

    for (int i = 0; i < mat->rows; ++i) {
        result += mat->elems[i][i];
    }

    return result;
}

int gaussElimination(double **mat, int size) {
    double factor;

    for (int i = 0; i < size; ++i) {
        if (mat[i][i] == 0.0) {
            return 0;
        }

        for (int j = 0; j < size; ++j) {
            if (j != i) {
                factor = mat[j][i] / mat[i][i];

                for (int k = 0; k < size * 2; ++k) {
                    mat[j][k] -= factor * mat[i][k];
                }
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        factor = mat[i][i];

        for (int j = 0; j < size * 2; ++j) {
            mat[i][j] /= factor;
        }
    }

    return 1;
}

Matrix *inverse(MatrixList *list, char *matName) {
    Matrix *mat = isMatInList(list, matName);

    if (mat == NULL) {
        printf("Matrix %s doesn't exist!\n", matName);
        return NULL;
    }

    if (mat->rows != mat->cols) {
        printf("Can't find the inverse of non-square matrix\n");
        return NULL;
    }

    char nameBuff[256];
    int retResult;

    do {
        printf("Enter a name for the inverse matrix:\n");
        scanf("%s", nameBuff);
        clearInput();

        if (!strcmp(nameBuff, matName)) {
            printf("Matrix name can't be the same as input matrices!\n");
            retResult = 0;
        }
        else {
            retResult = isNameValid(list, nameBuff);
        }
    } while (retResult == 0);

    int size = mat->rows;

    double **augmentedMatrix = malloc(size * sizeof(double*));
    for (int i = 0; i < size; ++i) {
        augmentedMatrix[i] = malloc((size * 2) * sizeof(double));
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size * 2; ++j) {
            if (j < size) {
                augmentedMatrix[i][j] = mat->elems[i][j];
            }
            else {
                if (i == j - size) {
                    augmentedMatrix[i][j] = 1.0;
                }
                else {
                    augmentedMatrix[i][j] = 0.0;
                }
            }
        }
    }

    if (gaussElimination(augmentedMatrix, size) == 0) {
        printf("Matrix is singular, can't calculate inverse\n");

        for (int i = 0; i < size; ++i) {
            free(augmentedMatrix[i]);
        }
        free(augmentedMatrix);

        return NULL;
    }

    Matrix *inverse = allocMatrix(mat->rows, mat->cols, nameBuff);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            inverse->elems[i][j] = augmentedMatrix[i][j + size];
        }
    }

    for (int i = 0; i < size; ++i) {
        free(augmentedMatrix[i]);
    }
    free(augmentedMatrix);

    insertMatrix(list, inverse);
    return inverse;
}