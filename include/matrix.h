#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct Matrix {
    int rows, cols;
    char *name;
    double **elems;
} Matrix;


Matrix* readMatrix();
int isNameValid(char *name);
int isMatInList(MatrixList *list, char *matName);
void clearInput();
void clearConsole();
void printMatrixList(MatrixList *list);
void printMatrix(MatrixList *list, char *matName);
void freeMatrix(void *matrix);
Matrix *multiplication(Matrix *mat1, Matrix *mat2);
#endif