#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"
#include "../include/matrix.h"

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

void clearInput() {
    while (getchar() != '\n');
}

void clearConsole() {
    system("clear");
}

Matrix* readMatrix() {
    Matrix *newMatrix = malloc(sizeof(Matrix));
    char tempBuff[256];

    do {
        printf("Enter a name for your matrix:\n");
        scanf("%s", tempBuff);
        clearInput();
    } while (isNameValid(tempBuff) == 0);

    newMatrix->name = malloc((strlen(tempBuff) + 1) * sizeof(char));
    strcpy(newMatrix->name, tempBuff);

    printf("Enter the dimensions of the matrix you want to read:\n");

    while (1) {
        printf("Rows: ");
        int retValue = scanf("%d", &newMatrix->rows);
        clearInput();

        if (retValue != 1) {
            printf("Invalid size! Please enter an integer\n");
        }
        else {
            break;
        }
    }

    while (1) {
        printf("Cols: ");
        int retValue = scanf("%d", &newMatrix->cols);
        clearInput();

        if (retValue != 1) {
            printf("Invalid size! Please enter an integer\n");
        }
        else {
            break;
        }
    }

    newMatrix->elems = malloc(newMatrix->rows * sizeof(double*));
    newMatrix->elems[0] = malloc(newMatrix->rows * newMatrix->cols * sizeof(double));
    for (int i = 1; i < newMatrix->rows; ++i) {
        newMatrix->elems[i] = newMatrix->elems[0] + i * newMatrix->cols;
    }

    printf("Enter the elements of your matrix\n");

    for (int i = 0; i < newMatrix->rows; ++i) {
        for (int j = 0; j < newMatrix->cols; ++j) {
            scanf("%lf", &newMatrix->elems[i][j]);
        }
    }

    clearInput();

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

            printf("Elementele matricei %s sunt:\n", mat->name);

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

    printf("Matricea %s nu a fost declarata.\n", matName);
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
