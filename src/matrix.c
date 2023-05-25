#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"
#include "../include/matrix.h"

Matrix* allocMatrix(int rows, int cols, char *name) {
    Matrix *newMatrix = malloc(sizeof(Matrix));
    newMatrix->name = malloc((strlen(name) + 1) * sizeof(char));
    newMatrix->rows = rows;
    newMatrix->cols = cols;
    strcpy(newMatrix->name, name);

    newMatrix->elems = malloc(newMatrix->rows * sizeof(double*));
    newMatrix->elems[0] = malloc(newMatrix->rows * newMatrix->cols * sizeof(double));
    for (int i = 1; i < newMatrix->rows; ++i) {
        newMatrix->elems[i] = newMatrix->elems[0] + i * newMatrix->cols;
    }

    return newMatrix;
}

Matrix* isMatInList(MatrixList *list, char *matName) {
    ListNode *temp = list->head;

    while (temp != NULL) {
        Matrix *mat = (Matrix*)temp->mat;
        if (!strcmp(mat->name, matName)) {
            return mat;
        }

        temp = temp->next;
    }

    return NULL;
}

int isNameValid(MatrixList *list, char *name) {
    char validChars[] = "abcdefghijklmnopqrstuvwxyz"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "0123456789-_";

    Matrix *mat = isMatInList(list, name);

    if (mat != NULL) {
        printf("Matrix already exists!\n");
        printf("Do you want to replace it?\n");
        printf("Yes(y) No(n)\n");

        char c = getchar();

        while (c != 'y' && c != 'n') {
            c = getchar();
        }

        if (c == 'y') {
            deleteMatrix(list, mat, freeMatrix);
            return 1;
        }
        else {
            return 0;
        }
    }

    for (u_int i = 0; i < strlen(name); ++i) {
        if (!strchr(validChars, name[i])) {
            printf("Name can contain only letters, numbers, \"-\" and \"_\" !\n");
            return 0;
        }
    }

    return 1;
}

void clearInput() {
    while (getchar() != '\n');
}

void clearConsole() {
    system("clear");
}

Matrix* readMatrix(MatrixList *list) {
    char tempBuff[256];
    int rows, cols;

    do {
        printf("Enter a name for your matrix:\n");
        scanf("%s", tempBuff);
        clearInput();
    } while (isNameValid(list, tempBuff) == 0);

    printf("Enter the dimensions of the matrix you want to read:\n");

    while (1) {
        printf("Rows: ");
        int retValue = scanf("%d", &rows);
        clearInput();

        if (retValue != 1 || rows < 1) {
            printf("Invalid size! Please enter an integer\n");
        }
        else {
            break;
        }
    }

    while (1) {
        printf("Cols: ");
        int retValue = scanf("%d", &cols);
        clearInput();

        if (retValue != 1 || cols < 1) {
            printf("Invalid size! Please enter an integer\n");
        }
        else {
            break;
        }
    }

    Matrix *newMatrix = allocMatrix(rows, cols, tempBuff);

    printf("Enter the elements of your matrix\n");

    for (int i = 0; i < newMatrix->rows; ++i) {
        for (int j = 0; j < newMatrix->cols; ++j) {
            scanf("%lf", &newMatrix->elems[i][j]);
        }
    }

    clearInput();

    insertMatrix(list, newMatrix);

    return newMatrix;
}

void printMatrixList(MatrixList *list) {
    ListNode *node = list->head;

    if (node == NULL) {
        printf("You haven't read any matrices!\n");
        return;
    }

    while (node != NULL) {
        Matrix *mat = (Matrix*)node->mat;
        printf("%s of size (%d, %d)\n", mat->name, mat->rows, mat->cols);

        node = node->next;
    }
}

void printMatrix(MatrixList *list, char *matName) {
    ListNode *temp = list->head;

    if (temp == NULL) {
        printf("You haven't read any matrices!\n");
        return;
    }

    while (temp != NULL) {
        Matrix *mat = (Matrix*)temp->mat;
        if (!strcmp(mat->name, matName)) {

            printf("Matrix %s contains:\n", mat->name);

            for (int i = 0; i < mat->rows; ++i) {
                for (int j = 0; j < mat->cols; ++j) {
                    printf("%lf ", mat->elems[i][j]);
                }
                printf("\n");
            }
            return;
        }

        temp = temp->next;
    }

    printf("Matrix doesn't exist!\n");
}

void freeMatrix(void *matrix) {
    Matrix *mat = (Matrix*)matrix;
    if (mat != NULL) {
        free(mat->name);
        free(mat->elems[0]);
        free(mat->elems);
        free(mat);
    }
}
