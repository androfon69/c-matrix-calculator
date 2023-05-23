#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/matrix.h"
#include "../include/list.h"

int isNameValid(char *name) {
    char validChars[] = "abcdefghijklmnopqrstuvwxyz"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "0123456789-_";

    for (u_int i = 0; i < strlen(name); ++i) {
        if (!strchr(validChars, name[i])) {
            printf("Name can contain only letters and numbers!\n");
            return 0;
        }
    }

    return 1;
}

Matrix* readMatrix() {
    Matrix *newMatrix = malloc(sizeof(Matrix));
    char tempBuff[256];

    do {
        printf("Enter a name for your matrix: ");
        scanf("%s", tempBuff);
    } while (isNameValid(tempBuff) == 0);

    newMatrix->name = malloc((strlen(tempBuff) + 1) * sizeof(char));
    strcpy(newMatrix->name, tempBuff);

    printf("Enter the dimensions of the matrix you want to read:\n");
    printf("Rows: ");
    scanf("%d", &newMatrix->rows);
    printf("Cols: ");
    scanf("%d", &newMatrix->cols);

    newMatrix->elems = malloc(newMatrix->rows * sizeof(double*));
    newMatrix->elems[0] = malloc(newMatrix->rows * newMatrix->cols * sizeof(double));
    for (int i = 1; i < newMatrix->rows; ++i) {
        newMatrix->elems[i] = newMatrix->elems[0] + i * newMatrix->cols;
    }

    printf("Enter the elements of your matrix");

    for (int i = 0; i < newMatrix->rows; ++i) {
        for (int j = 0; j < newMatrix->cols; ++j) {
            scanf("%lf", &newMatrix->elems[i][j]);
        }
    }

    return newMatrix;
}

int main() {
    MatrixList *list = initMatList();
    Matrix *mat = readMatrix();
    insertMatrix(list, mat);

    for (int i = 0; i < mat->rows; ++i) {
        for (int j = 0; j < mat->cols; ++j) {
            printf("%lf ", mat->elems[i][j]);
        }
        printf("\n");
    }

    freeMatList(list);

	return 0;
}
