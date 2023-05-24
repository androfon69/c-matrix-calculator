#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct Matrix {
    int rows, cols;
    char *name;
    double **elems;
} Matrix;

Matrix* allocMatrix(int rows, int cols, char *name);
Matrix* readMatrix(MatrixList *list);
int isNameValid(MatrixList *list, char *name);
Matrix* isMatInList(MatrixList *list, char *matName);
void clearInput();
void clearConsole();
void printMatrixList(MatrixList *list);
void printMatrix(MatrixList *list, char *matName);
void freeMatrix(void *matrix);

#endif
